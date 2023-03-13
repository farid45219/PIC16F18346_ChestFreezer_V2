/* 
 * File:   uart.h
 * Author: MD. Faridul Islam
 * PIC16F18346 UART Library
 * Created on March 13, 2023, 12:16 PM
 */

void     UART_Struct_Init(void);
void     UART_Config_Transmitter(void);
void     UART_Config_Receiver(void);
void     UART_Config_Receiver_Interrupt(void);
void     UART_Init(uint32_t BAUD);
void     UART_Transmit_Byte(uint8_t val);
void     UART_Transmit_Byte_Hex(uint8_t val);
void     UART_Transmit_Byte_Bin(uint8_t val);
void     UART_Transmit_Text(char *str);
void     UART_Transmit_Unsigned_Number(uint32_t num);
void     UART_Transmit_Number(int32_t num);
void     UART_Print_Debug_Data(int *data_in);
uint8_t  UART_Receive_Byte(void);
void     UART_Flush_Buffer(void);
uint8_t  UART_Read_From_Buffer(uint8_t index);
uint8_t  UART_Buffer_Index(void);
uint8_t  UART_Bytes_Available_To_Read(void);
uint32_t UART_Last_Byte_Recevied_Time_Stamp(void);
void     UART_Interrupt_Service_Routine(void);



