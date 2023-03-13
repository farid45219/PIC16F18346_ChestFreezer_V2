/* 
 * File:   sevensegment.h
 * Author: MD. Faridul Islam
 * PIC16F18346 SevenSegment Library
 * Created on March 13, 2023, 12:16 PM
 */

uint8_t SevenSegment_Byte_Invert(uint8_t val);
void    SevenSegment_Struct_Init(void);
void    SevenSegment_Config_Variables(void);
void    SevenSegment_SEG_And_Digit_Pins_Output(void);
void    SevenSegment_SEG_Pins_High(void);
void    SevenSegment_SEG_Pins_Low(void);
void    SevenSegment_SEG_Pins_Enable(void);
void    SevenSegment_SEG_Pins_Disable(void);
void    SevenSegment_Digit_Pins_High(void);
void    SevenSegment_Digit_Pins_Low(void);
void    SevenSegment_Digit_Pin_Enable(void);
void    SevenSegment_Digit_Pins_Disable(void);
void    SevenSegment_GPIO_Init(void);
void    SevenSegment_Timer_Init(void);
void    SevenSegment_Init(void);
void    SevenSegment_Print_Number_In_xDigit(uint8_t digit, uint8_t val);
uint8_t Indicator_LED_E_SAVE(void);
uint8_t Indicator_LED_STANDARD(void);
uint8_t Indicator_LED_COMPRESSOR(void);
uint8_t Indicator_LED_MODE(void);
uint8_t Indicator_LED_UNLOCK(void);
uint8_t Indicator_LED_TURBO(void);
uint8_t Indicator_LED_COLDEST(void);
uint8_t Indicator_LED_REFRIGERATOR(void);
uint8_t Indicator_LED_NEG(void);
uint8_t Indicator_LED_DEG(void);
void    Indicator_LED(uint8_t led_bit_pos, uint8_t state);
void    Indicator_LED_All_Off(void);
uint8_t Check_Indicator_LED_Status(uint8_t led_bit_pos);
void    Indicator_LED_UNLOCK_Toggle(void);
void    SevenSegment_Print(int value);
void    SevenSegment_Set_Brightness(uint8_t brightness);
void    SevenSegment_Set_Brightness_Max(void);
void    SevenSegment_Set_Brightness_Min(void);
void    SevenSegment_Enter_Sleep_Mode(void);
void    SevenSegment_Wakeup_From_Sleep_Mode(void);
void    SevenSegment_Set_Dimming_And_Sleeping_Delay(uint32_t dim, uint32_t sleep);
void    SevenSegment_Reset_Dimming_And_Sleeping_Delay(void);
uint8_t SevenSegment_No_Operation_Ongoing(void);
void    SevenSegment_ISR_Executables(void);
void    SevenSegment_Interrupt_Service_Routine(void);
