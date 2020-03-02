/**************************************************************
*  Author: TAYYAB JAVAID      Date: 26th December, 2019.
*
*
*     Block diagram:
*                                AT over
*               -----------    UART4 SERIAL   -----------
*              |           |       TX       |           |
*              |  CORTEX   |----------------|           |
*              |    M4     |                | ESP 8266  |
*              |   MCU     |       RX       |  (ESP-01) |
*              |           |----------------|           |
*              |           |                |           |
*               -----------                  -----------
*
* Description:
* This is the firmware for STM32F407VG-Discovery board, which 
* has a Cortex-M4 MCU on board. Cortex-M4 is the master device
* that controls slaves, such as ESP8266-WiFi or the home
* appliances.
*   
***************************************************************/

#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "at_layer.h"


/************************  Global Variables  ***********************/
UART_HandleTypeDef huart4;
UART_HandleTypeDef huart5;
char rxBuf[20][50];
char txBuf[20][50];

char rxBuf5[1000];
char txBuf5[1000];
extern atCommandHandlers cmdLookupTable[];

/*********************  Function Declarations  *********************/
//extern void get_IP_addr1( char *str, char *ptr );
extern void get_IP_addr(UART_HandleTypeDef *huart, char *str );


/*********************  Function Definitions  *********************/
void delay(void)
{
	for(uint32_t i = 0 ; i < 50000 ; i++);
}

int main()
{
    uint8_t i, rsp=0;
    char value[25];
    
    HAL_Init();
     
    // Debug UART5 Channel Config
    huart5.Instance = UART5;
    AT_Config_uart(&huart5, 115200);
    
    // AT UART4 Channel Config
    huart4.Instance = UART4;
    AT_Config_uart(&huart4, 115200);
    
    send_AT_command(&huart5, "\r\nSTARTING ...\r\n", 1000);
    
    /* Config ESP8266 module*/
     for (i = 0; i < MAX_NUM_AT_CMDS; i++)
     {
         //send_AT_command(&huart4, "AT+GMR\r\n");
         
         rsp=0;
         
         /*read_AT_serial_rsp(&huart5);*/
         
         
         memset(txBuf5, 0, 1000);
         flush_rx_buf();
         
         send_AT_command(&huart4, cmdLookupTable[i].atCmd, cmdLookupTable[i].timeout);
         
         /****  Data is sent to ESP8266  ****/

         read_AT_serial_lines(&huart4, cmdLookupTable[i].timeout);
         
         //memcpy(txBuf5, rxBuf[0], strlen(rxBuf[0]));
         //send_AT_command(&huart5, txBuf5);
         
         // print the received response data as a trace on UART5
         print_on_uart(&huart5, rxBuf, 20);
         

         if(i == 5)
         {
            get_IP_addr(&huart5, rxBuf[1]);
         }
         
         delay();
    
         
     }
     
     // Below loop is used to receive the URCs resulting from REST API invocation from the internet
     while(1)
     {
         flush_rx_buf();
         read_AT_serial_lines(&huart4, 0x00fa);
         print_on_uart(&huart5, rxBuf, 20);
     }
     
    send_AT_command(&huart5, "\r\nENDING ...\r\n", 1000);
     
	return 0;
}

void SysTick_Handler()
{
    HAL_IncTick();
}


