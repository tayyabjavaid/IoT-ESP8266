
#include<stdint.h>
#include<string.h>

#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "at_layer.h"

extern char rxBuf[20][50];



/*****************************************************
*   Function: flush_rx_buf()
*
*   Empties RX buffer for next response.
******************************************************/
void flush_rx_buf()
{
    uint8_t i;
    for(i=0; i<20; i++)
    {
        memset(rxBuf[i], 0, 50);
    }
}

/*****************************************************
*   Function: serial_buf_copy()
*
*   Copies RX buffer for on to TX buffer.
******************************************************/
void print_on_uart(UART_HandleTypeDef *huart, char buf[20][50], uint8_t lines)
{
    uint8_t i;
    for(i=0; i<lines; i++)
    {
        send_AT_command(huart, buf[i], 1000);
    }

}
/*****************************************************
*   Function: AT_Config_uart()
*
*   Configures UART4 as the AT channel.
******************************************************/
void AT_Config_uart(UART_HandleTypeDef *huart, uint32_t Baud)
{
    GPIO_InitTypeDef pGpiohandle;
    GPIO_TypeDef *pGpio;
    
    
    if(huart->Instance == UART4)
    {
         /* Enable clocks for UART4*/
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_UART4_CLK_ENABLE();
    }
    else
    {
         /* Enable clocks for UART5*/
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        __HAL_RCC_UART5_CLK_ENABLE();
    }
    
    //  GPIO Configs for UART 4 or 5
    {
        pGpiohandle.Mode = GPIO_MODE_AF_PP;
        pGpiohandle.Pull = GPIO_PULLUP;
        pGpiohandle.Speed = GPIO_SPEED_FREQ_HIGH;
        
        if(huart->Instance == UART4)
        {
            /* Configure UART4*/
            pGpio = GPIOC;
            
            pGpiohandle.Alternate = GPIO_AF8_UART4;
            
            pGpiohandle.Pin = GPIO_PIN_10;
            HAL_GPIO_Init(pGpio, &pGpiohandle);
            
            pGpiohandle.Pin = GPIO_PIN_11;
            HAL_GPIO_Init(pGpio, &pGpiohandle);
        }
        else
        {
            /* Configure UART5*/
            pGpio = GPIOC;
            
            pGpiohandle.Alternate = GPIO_AF8_UART5;
            
            pGpiohandle.Pin = GPIO_PIN_12;
            HAL_GPIO_Init(pGpio, &pGpiohandle);
            
            pGpio = GPIOD;
            
            pGpiohandle.Pin = GPIO_PIN_2;
            HAL_GPIO_Init(pGpio, &pGpiohandle);
        }
    }

    huart->Init.BaudRate = Baud;
    huart->Init.Parity = USART_PARITY_NONE;
    huart->Init.StopBits = USART_STOPBITS_1;
    huart->Init.WordLength = USART_WORDLENGTH_8B;
    huart->Init.Mode = USART_MODE_TX_RX;

    HAL_UART_Init(huart);
    
}

/*****************************************************
*   Function: read_AT_serial_rsp()
*
*   Reads the serial AT response and puts it in rxBuf.
******************************************************/
void read_AT_serial_rsp(UART_HandleTypeDef *huart, char *buf, uint16_t buflen, char *sigTerm)
{
    char temp[80], *startBuf;
    uint16_t ind = 0;
    
    memset(buf, 0, 1000);
    
    startBuf = buf;
    
    while(1)
    {
        memset(temp, 0, 80);
        
        HAL_UART_Receive(huart, (uint8_t *)temp, 80, 0x03e8);
        
        ind += strlen(temp);
        
        if(ind >= buflen)
        {
            break;
        }
        
        memcpy(buf, temp, strlen(temp));
        
        buf += strlen(temp);
        
        if(strstr(startBuf, sigTerm) != 0)
        {
            // For debugging, uncomment the following line.
            // HAL_UART_Transmit(&huart, (uint8_t *)rxBuf, ind, 0x01);
            break;
        }
    }
}

/*****************************************************
*   Function: read_AT_serial_rsp()
*
*   Reads the serial AT response and puts it in rxBuf.
******************************************************/
void read_AT_serial_lines(UART_HandleTypeDef *huart, uint16_t timeout)
{
    char temp;
    int ind=0, strnum=0;
    
    while(1)
    {
        temp = 0;
        
        HAL_UART_Receive(huart, (uint8_t *)&temp, 1, (timeout << 2));
        
        
        rxBuf[strnum][ind++] = temp;
        
        if(rxBuf[strnum][ind-1] == 0)
        {
            break;
        }
        
        if((rxBuf[strnum][ind-2] == '\r' && rxBuf[strnum][ind-1] == '\n') || ind == 50)
        {
            strnum++;
            ind = 0;
        }
    }
}
/*****************************************************
*   Function: send_AT_command()
*
*   Sends the AT command over the serial channel.
******************************************************/
void send_AT_command(UART_HandleTypeDef *huart, char *cmd, uint16_t timeout)
{
    HAL_UART_Transmit(huart, (uint8_t *)cmd, strlen(cmd), timeout);
}

void atRspHandler()
{
    return;
}
void atGmrRspHandler()
{
    return;
}
void atCwmodedefRspHandler()
{
    return;
}
void atCwlapRspHandler()
{
    return;
}
void atCwjapdefRspHandler()
{
    return;
}
void atCifsrRspHandler()
{
    return;
}
void atCipmuxRspHandler()
{
    return;
}
void atCipserverRspHandler()
{
    return;
}

atCommandHandlers cmdLookupTable[MAX_NUM_AT_CMDS] = 
{
  {"AT\r\n",                                            "OK\r\n",       atRspHandler,               100},
  {"AT+GMR\r\n",                                        "OK\r\n",       atGmrRspHandler,            100},
  {"AT+CWMODE_DEF=1\r\n",                               "OK\r\n",       atCwmodedefRspHandler,      100},
  {"AT+CWLAP\r\n",                                      "OK\r\n",       atCwlapRspHandler,          1500},
  {"AT+CWJAP_DEF=\"Teejayyy\",\"abcd1w34\"\r\n",        "+CWJAP:",      atCwjapdefRspHandler,       1000},
  {"AT+CIFSR\r\n",                                      "OK\r\n",       atCifsrRspHandler,          100},
  {"AT+CIPMUX=1\r\n",                                   "OK\r\n",       atCipmuxRspHandler,         100},
  {"AT+CIPSERVER=1,80\r\n",                             "OK\r\n",       atCipserverRspHandler,      500}
    
};


