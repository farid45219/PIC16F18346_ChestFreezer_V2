/* 
 * File:   buzzer.h
 * Author: MD. Faridul Islam
 * PIC16F18346 Passive Buzzer Library
 * Created on March 13, 2023, 12:16 PM
 */


void Buzzer_Struct_Init(void);
void Buzzer_GPIO_Disable(void);
void Buzzer_PWM_Register_Config(void);
void Buzzer_GPIO_Enable(void);
void Buzzer_Config_PPS(void);
void Buzzer_PWM_Enable(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_PWM_Init(void);

