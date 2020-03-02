

#ifndef __AT_LAYER_H__
#define __AT_LAYER_H__


#include "stm32f407xx.h"

#define MAX_NUM_AT_CMDS 8

typedef enum
{
    UART_4,
    UART_5
}
uartConfig;

typedef struct
{
    char *atCmd;
    char *sigterm;
    void *cbRspHandler;
    uint16_t timeout;
}atCommandHandlers;

void flush_rx_buf(void);
void print_on_uart(UART_HandleTypeDef *huart, char buf[20][50], uint8_t lines);
void AT_Config_uart(UART_HandleTypeDef *huart, uint32_t Baud);
void read_AT_serial_rsp(UART_HandleTypeDef *huart, char *buf, uint16_t buflen, char *sigTerm);
void read_AT_serial_lines(UART_HandleTypeDef *huart, uint16_t timeout);
void send_AT_command(UART_HandleTypeDef *huart, char *cmd, uint16_t timeout);










#endif /*__AT_LAYER_H__*/
