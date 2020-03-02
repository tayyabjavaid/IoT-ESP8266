
// Author: TAYYAB JAVAID   Date: 9th December 2019, Lahore

#ifndef _USART_DRIVER_H_
#define _USART_DRIVER_H_

#include "stdint.h"
#include "stm32f407xx.h"


typedef enum
{
    USART_DISABLED,
    USART_TX_ENABLED,
    USART_RX_ENABLED,
    USART_TXRX_ENABLED
}usartMode;

typedef enum
{
    USART_PARITY_NONE,
    USART_PARITY_EVEN,
    USART_PARITY_ODD
}usartParity;

typedef enum
{
    USART_WORDLEN_8_BIT,
    USART_WORDLEN_9_BIT
}usartWordLength;

typedef enum
{
    USART_HFC_OFF,
    USART_HFC_CTS,
    USART_HFC_RTS,
    USART_HFC_CTS_RTS
}usartHardwareFlowControl;

typedef enum
{
    USART_BR_2400,
    USART_BR_9600,
    USART_BR_74880,
    USART_BR_115200
}usartBaudRate;

typedef enum
{
    USART_SB_0_5,
    USART_SB_1,
    USART_SB_1_5,
    USART_SB_2
}usartStopBits;


/**
    * @brief User configurations for USART Peripheral
    */
typedef struct
{
    usartMode                             mode;                    /*!< Selected USART mode                                */
    usartBaudRate                         baudrate;                 /*!< select Baudrate for the communication             */
    uint32_t                             *dataBuf;                 /*!< Pointer to the memory containing TX/RX data        */
    uint32_t                             dataLen;                  /*!< Length of data to TX/RX                            */
    usartHardwareFlowControl             flowControlConfig;        /*!< Configurations for Hardware Flow Control           */
    usartWordLength                      dataWordLen;              /*!< Word length to use                                 */
    usartParity                          parityConfig;             /*!< Parity Configuration                               */
    usartStopBits                        stopBitConfig;            /*!< Number of stop bits to be used                     */
    
    
}usartConfigs;
    
/**
    * @brief Handle to the USART peripheral
    */
typedef struct
{
    usartConfigs configs;    /*!< Configurations from the user                     */
    USART_TypeDef *dev;      /*!< pointer to the selected USART peripheral         */
}usartHandle;


/*******************  Function Declarations  ********************/

void USART_Init(usartHandle *handle);
void USART_deInit(usartHandle *handle);
void USART_Config(usartHandle *handle);
void USART_Send_Data(usartHandle *handle);
void USART_Receive_Data(usartHandle *handle);






#endif /* _USART_DRIVER_H_ */