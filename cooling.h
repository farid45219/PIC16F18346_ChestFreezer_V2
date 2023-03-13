/* 
 * File:   cooling.h
 * Author: MD. Faridul Islam
 * PIC16F18346 Frost Controller cooling
 * Created on March 13, 2023, 12:16 PM
 */

void    Cooling_Stuct_Init(void);
void    Cooling_Select_Mode(uint8_t mode);
uint8_t Cooling_Check_Mode(void);
void    Cooling_Change_Mode(void);
void    Cooling_Set_Mode(uint8_t mode);
void    Cooling_Init(void);

