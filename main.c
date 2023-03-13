/*
 * File:   main.c
 * Author: MD. Faridul Islam
 * PIC16F18346 Frost Controller V2
 * Created on March 13, 2023, 12:16 PM
 */

#define _XTAL_FREQ   32000000
#include <xc.h>
#include "configbits.h"
//#include "sevensegment.h"
#include "timebase.h"
#include "captouch.h"
//#include "cooling.h"
//#include "buzzer.h"
#include "uart.h"

void main(void) {
    Timebase_Init();
    CapTouch_Init();
    UART_Init(9600);
    UART_Transmit_Text("\r\nDebug Started\r\n");
    //SevenSegment_Init();
    //SevenSegment_Set_Brightness_Max();
    //SevenSegment_Set_Dimming_And_Sleeping_Delay(10000, 30000);
    //Cooling_Init();
    //Buzzer_PWM_Init();
    
    
    uint8_t mode;
    
    int max=-5000;
    int min=5000;
    int cnt=0;
    
    while(1){
          //Timebase_Wait_Unit_Time();
          //while(SevenSegment_No_Operation_Ongoing()==0);
          CapTouch_Scan_Sensors(Timebase_Get_SubSeconds_Value());
          
          /*if(  CapTouch_Short_Pressed(1)  ){
              SevenSegment_Wakeup_From_Sleep_Mode();
              SevenSegment_Set_Brightness_Max();
              SevenSegment_Set_Dimming_And_Sleeping_Delay(10000, 30000);
          }else if(CapTouch_Long_Pressed(1)){
              SevenSegment_Set_Dimming_And_Sleeping_Delay(10000, 30000);
              Indicator_LED_UNLOCK_Toggle();
          }
          
          else if(CapTouch_Short_Pressed(0)){
              if(!Check_Indicator_LED_Status(Indicator_LED_UNLOCK())){
                  Cooling_Change_Mode();
                  Cooling_Set_Mode(Cooling_Check_Mode());
              }
              SevenSegment_Wakeup_From_Sleep_Mode();
              SevenSegment_Set_Brightness_Max();
              SevenSegment_Set_Dimming_And_Sleeping_Delay(10000, 30000);
          }*/
          
          
          //UART_Transmit_Number(CapTouch_Get_Calibration_Value(0));
          //UART_Transmit_Text(",");
          //UART_Transmit_Number(CapTouch_Get_RawDifferentialADC(0));
          //UART_Transmit_Text(",");
          
          //int calib=CapTouch_Get_Calibration_Value(0);
          //int diffadc=CapTouch_Get_RawDifferentialADC(0);
          //int calib=CapTouch_Get_RawADC1(0);
          //int diffadc=CapTouch_Get_RawADC2(0);
          //if(diffadc>max){max=diffadc;}
          //if(diffadc<min){min=diffadc;}
          
          UART_Transmit_Number(CapTouch_Get_Calibration_Value(0));
          UART_Transmit_Text(",");
          UART_Transmit_Number(CapTouch_Get_RawDifferentialADC(0));
          UART_Transmit_Text(",");
          UART_Transmit_Number(CapTouch_Get_Calibration_Value(1));
          UART_Transmit_Text(",");
          UART_Transmit_Number(CapTouch_Get_RawDifferentialADC(1));
          //UART_Transmit_Text(",");
          //UART_Transmit_Number(CapTouch_IIR_Butterworth(0,CapTouch_Get_RawDifferentialADC(0)));
          UART_Transmit_Text("\r\n");
          __delay_ms(10);
    }
}

void interrupt ISRs(void){
    //SevenSegment_Interrupt_Service_Routine();
    Timebase_Interrupt_Service_Routine();
}