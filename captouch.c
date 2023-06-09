


/* 
 * File:   captouch.h
 * Author: MD. Faridul Islam
 * PIC16F18346 CapTouch Library
 * Created on March 13, 2023, 12:16 PM
 */

#include<xc.h>
#include "uart.h"
#define    _XTAL_FREQ                     32000000UL

#define    CAPTOUCH_ADC_TRIS              TRISA
#define    CAPTOUCH_ADC_LAT               LATA
#define    CAPTOUCH_ADC_ANSEL             ANSELA
#define    CAPTOUCH_ADC_CHANNEL_POS       0x02
#define    CAPTOUCH_PORT_WISE_OFFSET      0x00
#define    CAPTOUCH_INT_VREF_ADC_CHANNEL  0x3F
#define    CAPTOUCH_INT_GND_ADC_CHANNEL   0x3C
#define    CAPTOUCH_THRESHOLD             20
#define    CAPTOUCH_SHORT_PRESS_TIME_MIN  1   
#define    CAPTOUCH_SHORT_PRESS_TIME_MAX  20   
#define    CAPTOUCH_LONG_PRESS_TIME       40
#define    CAPTOUCH_IIR_ALPHA             70

#define    CAPTOUCH_CALIBRATION_SAMPLES   240
#define    CAPTOUCH_TOTAL_TOUCH_KEY       2
#define    CAPTOUCH_TOUCH_KEY_1           4
#define    CAPTOUCH_TOUCH_KEY_2           5
uint8_t    CapTouch_Pins[CAPTOUCH_TOTAL_TOUCH_KEY]={CAPTOUCH_TOUCH_KEY_1,CAPTOUCH_TOUCH_KEY_2};

typedef struct captouch_t{
  uint8_t  Channel;
  uint8_t  Result[CAPTOUCH_TOTAL_TOUCH_KEY];
  int      CalibrationValue[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint16_t RawADC1[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint16_t RawADC2[CAPTOUCH_TOTAL_TOUCH_KEY];
  int      RawDiffADC[CAPTOUCH_TOTAL_TOUCH_KEY];
  int      DiffThreshold[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint8_t  TriggerMethod[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint8_t  LastTouchState[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint32_t TouchDuration[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint32_t TouchDurationTemp[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint8_t  LongTouchFlag[CAPTOUCH_TOTAL_TOUCH_KEY];
  uint8_t  UsingReferenceTimer;
  uint8_t  ErrorCode[CAPTOUCH_TOTAL_TOUCH_KEY];
}captouch_t;

typedef struct iir_t{
  uint8_t   Alpha[CAPTOUCH_TOTAL_TOUCH_KEY];
  int32_t   Input[CAPTOUCH_TOTAL_TOUCH_KEY];
  int32_t   Output[CAPTOUCH_TOTAL_TOUCH_KEY];
}iir_t;

captouch_t CapTouch;
iir_t      IIR;
  
  
void CapTouch_Struct_Init(void){
  CapTouch.Channel=0;
  for(uint8_t i=0;i<CAPTOUCH_TOTAL_TOUCH_KEY;i++){
  CapTouch.Result[i]=0;
  CapTouch.CalibrationValue[i]=0;
  CapTouch.RawADC1[i]=0;
  CapTouch.RawADC2[i]=0;
  CapTouch.RawDiffADC[i]=0;
  CapTouch.DiffThreshold[i]=CAPTOUCH_THRESHOLD;
  CapTouch.TriggerMethod[i]=0;
  CapTouch.LastTouchState[i]=0;
  CapTouch.TouchDuration[i]=0;
  CapTouch.TouchDurationTemp[i]=0;
  CapTouch.LongTouchFlag[i]=0;
  CapTouch.UsingReferenceTimer=0;
  CapTouch.ErrorCode[i]=0;
  }
}

void CapTouch_IIR_Butterworth_Struct_Init(void){
  for(uint8_t i=0;i<CAPTOUCH_TOTAL_TOUCH_KEY;i++){
    #ifdef CAPTOUCH_IIR_ALPHA
    IIR.Alpha[i]=CAPTOUCH_IIR_ALPHA;
    #else
    IIR.Alpha[i]=0;
    #endif
    IIR.Input[i]=0;
    IIR.Output[i]=0;
  }
}

int32_t CapTouch_IIR_Butterworth(uint8_t channel, int32_t input){
  IIR.Input[channel]=input;
  IIR.Output[channel] =(IIR.Input[channel]*IIR.Alpha[channel])+((100-IIR.Alpha[channel])*IIR.Output[channel]);
  IIR.Output[channel]/= 100;
  return IIR.Output[channel];
}

void CapTouch_Set_Key_Pin_Input(uint8_t current_channel){
  CAPTOUCH_ADC_ANSEL&=~(1<<current_channel);
  CAPTOUCH_ADC_TRIS |= (1<<current_channel);
}

void CapTouch_Set_Key_Pin_Analog(uint8_t current_channel){
  CAPTOUCH_ADC_TRIS |= (1<<current_channel);
  CAPTOUCH_ADC_ANSEL|= (1<<current_channel);
}

void CapTouch_Set_Key_Pin_Output(uint8_t current_channel){
  CAPTOUCH_ADC_ANSEL&=~(1<<current_channel);
  CAPTOUCH_ADC_TRIS &=~(1<<current_channel);
}

void CapTouch_Set_Key_Pin_Output_Low(uint8_t current_channel){
  CAPTOUCH_ADC_LAT  &=~(1<<current_channel);
}

void CapTouch_Set_Key_Pin_Output_High(uint8_t current_channel){
  CAPTOUCH_ADC_LAT  |= (1<<current_channel);
}

void CapTouch_ADC_Register_Config(void){
  FVRCON=(1<<0)|(1<<1);
  FVRCON|=(1<<7);
  while(!(FVRCON & (1<<6)));
  ADCON0=0x00;
  ADCON1=0x00;
  ADCON1|=(1<<7)|(1<<5);
  ADACT=0x00;
  ADCON0|=(1<<0);
}

void CapTouch_ADC_Wakeup(void){
  ADCON0|=(1<<0);
}

void CapTouch_ADC_Sleep(void){
  ADCON0&=~(1<<0);
}

uint16_t CapTouch_ADC_Sample(uint8_t channel){
  ADCON0=(channel<<CAPTOUCH_ADC_CHANNEL_POS)|(1<<0);
  ADCON0|=(1<<1);
  while(ADCON0 & (1<<1));
  uint16_t res=ADRES;
  PIR1&=~(1<<6);
  return res;
}

void CapTouch_Precharge_SH_Cap(uint8_t current_channel){
  CapTouch_Set_Key_Pin_Output(CapTouch_Pins[current_channel]);
  CapTouch_Set_Key_Pin_Output_Low(CapTouch_Pins[current_channel]);
  CapTouch_ADC_Sample(CAPTOUCH_INT_VREF_ADC_CHANNEL);
  CapTouch_ADC_Sample(CAPTOUCH_INT_VREF_ADC_CHANNEL);
}

void CapTouch_ADC_Sample1(uint8_t current_channel){
  CapTouch_Set_Key_Pin_Analog(CapTouch_Pins[current_channel]);
  CapTouch.RawADC1[current_channel]=CapTouch_ADC_Sample(CapTouch_Pins[current_channel]+CAPTOUCH_PORT_WISE_OFFSET);
}

void CapTouch_Precharge_Button(uint8_t current_channel){
  CapTouch_Set_Key_Pin_Output(CapTouch_Pins[current_channel]);
  CapTouch_Set_Key_Pin_Output_High(CapTouch_Pins[current_channel]);
  CapTouch_ADC_Sample(CAPTOUCH_INT_GND_ADC_CHANNEL);
}

void CapTouch_ADC_Sample2(uint8_t current_channel){
  CapTouch_Set_Key_Pin_Analog(CapTouch_Pins[current_channel]);
  CapTouch.RawADC2[current_channel]=CapTouch_ADC_Sample(CapTouch_Pins[current_channel]+CAPTOUCH_PORT_WISE_OFFSET);
}

void CapTouch_Read_Delta(uint8_t current_channel){
  INTCON&=~(1<<7);
  CapTouch_ADC_Wakeup();
  CapTouch_Precharge_SH_Cap(current_channel);
  CapTouch_ADC_Sample1(current_channel);
  uint32_t temp=0;
  CapTouch_Precharge_Button(current_channel);
  CapTouch_ADC_Sample2(current_channel);
  temp+=CapTouch.RawADC2[current_channel];
  CapTouch_Precharge_Button(current_channel);
  CapTouch_ADC_Sample2(current_channel);
  temp+=CapTouch.RawADC2[current_channel];
  CapTouch_Precharge_Button(current_channel);
  CapTouch_ADC_Sample2(current_channel);
  temp+=CapTouch.RawADC2[current_channel];
  CapTouch.RawADC2[current_channel]=temp;
  CapTouch_ADC_Sleep();
  INTCON|=(1<<7);
  int delta=CapTouch.RawADC1[current_channel];
  delta-=CapTouch.RawADC2[current_channel];
  #ifdef CAPTOUCH_IIR_ALPHA
  CapTouch.RawDiffADC[current_channel]=CapTouch_IIR_Butterworth(current_channel,delta);
  #else
  CapTouch.RawDiffADC[current_channel]=delta;
  #endif
}


void CapTouch_Calibration(void){
  int32_t sum[CAPTOUCH_TOTAL_TOUCH_KEY];
  for(uint8_t key=0;key<CAPTOUCH_TOTAL_TOUCH_KEY;key++){
	sum[key]=0;
  }
  
  for(int i=0;i<CAPTOUCH_CALIBRATION_SAMPLES;i++){
    for(uint8_t key=0;key<CAPTOUCH_TOTAL_TOUCH_KEY;key++){
      CapTouch_Read_Delta(key);
	}
  }

  for(int i=0;i<CAPTOUCH_CALIBRATION_SAMPLES;i++){
    for(uint8_t key=0;key<CAPTOUCH_TOTAL_TOUCH_KEY;key++){
      CapTouch_Read_Delta(key);
      sum[key]+=CapTouch.RawDiffADC[key];
	}
  }
  
  for(uint8_t key=0;key<CAPTOUCH_TOTAL_TOUCH_KEY;key++){
	sum[key]/=CAPTOUCH_CALIBRATION_SAMPLES;
    CapTouch.CalibrationValue[key]=sum[key]-CapTouch.DiffThreshold[key];
  }
}


void CapTouch_Response(uint8_t current_channel){
  CapTouch_Read_Delta(current_channel);
  if(CapTouch.CalibrationValue[current_channel]>CapTouch.RawDiffADC[current_channel]){
    CapTouch.Result[current_channel]=1;
  }else{
    CapTouch.Result[current_channel]=0;
  }
}

void CapTouch_Check_Trigger(uint8_t current_channel){
  uint8_t current_state=0;
  CapTouch_Response(current_channel);
  current_state=CapTouch.Result[current_channel];
    if((CapTouch.LastTouchState[current_channel]==0) && (current_state==1)){
        CapTouch.LongTouchFlag[current_channel]=0;     //Rising Edge
        CapTouch.TriggerMethod[current_channel]=0x01;
    }else if((CapTouch.LastTouchState[current_channel]==1) && (current_state==0)){
        CapTouch.TriggerMethod[current_channel]=0x04;  //Falling Edge
    }else if((CapTouch.LastTouchState[current_channel]==1) && (current_state==1)){
        CapTouch.TriggerMethod[current_channel]=0x02;  //Constant Touched
    }else{
        CapTouch.TriggerMethod[current_channel]=0x00;  //No Touch Event Occured
    }
    CapTouch.LastTouchState[current_channel]=current_state;
}


void CapTouch_Check_Touch_Duration(uint8_t current_channel, uint32_t refernce_time){
  uint32_t duration=0;
  CapTouch_Check_Trigger(current_channel);
  if(CapTouch.TriggerMethod[current_channel]==0x01){
    CapTouch.UsingReferenceTimer|=(1<<current_channel);
    CapTouch.TouchDurationTemp[current_channel]=refernce_time;
  }else if(CapTouch.TriggerMethod[current_channel]==0x04 || CapTouch.TriggerMethod[current_channel]==0x02){
    duration=refernce_time;
    duration-=CapTouch.TouchDurationTemp[current_channel];
    if(duration>0){
      CapTouch.TouchDuration[current_channel]=duration;
    }
    if(CapTouch.TriggerMethod[current_channel]==0x04){
      CapTouch.TouchDurationTemp[current_channel]=refernce_time;
      CapTouch.UsingReferenceTimer&=~(1<<current_channel);
    }
  }
  else{
    CapTouch.TouchDuration[current_channel]=0;
    CapTouch.TouchDurationTemp[current_channel]=0;
  }
}


void CapTouch_Scan_Sensors(uint32_t refernce_time){
  for(uint8_t channel=0;channel<CAPTOUCH_TOTAL_TOUCH_KEY;channel++){
    CapTouch_Check_Touch_Duration(channel, refernce_time);
  }
}

uint8_t CapTouch_Short_Pressed(uint8_t current_channel){
  uint8_t sts=0;
  if(CapTouch.TriggerMethod[current_channel]==0x04){
    if((CapTouch.TouchDuration[current_channel]>CAPTOUCH_SHORT_PRESS_TIME_MIN) && (CapTouch.TouchDuration[current_channel]<CAPTOUCH_SHORT_PRESS_TIME_MAX)){
      sts=1;
    }
  }
  return sts;
}

uint8_t CapTouch_Long_Pressed(uint8_t current_channel){
  uint8_t sts=0;
  if((CapTouch.TouchDuration[current_channel]>CAPTOUCH_LONG_PRESS_TIME) && (CapTouch.LongTouchFlag[current_channel]==0)){
    CapTouch.LongTouchFlag[current_channel]=1;
    sts=1;
  }
  return sts;
}

uint8_t CapTouch_Constant_Pressed(uint8_t current_channel){
  uint8_t sts=0;
  if((CapTouch.TriggerMethod[current_channel]==0x02) && (CapTouch.TouchDuration[current_channel]>CAPTOUCH_SHORT_PRESS_TIME_MIN)){
    sts=1;
  }
  return sts;
}

uint16_t CapTouch_Get_RawADC1(uint8_t current_channel){
  return CapTouch.RawADC1[current_channel];
}

uint16_t CapTouch_Get_RawADC2(uint8_t current_channel){
  return CapTouch.RawADC2[current_channel];
}

int CapTouch_Get_RawDifferentialADC(uint8_t current_channel){
  return CapTouch.RawDiffADC[current_channel];
}

int CapTouch_Get_Calibration_Value(uint8_t current_channel){
  return CapTouch.CalibrationValue[current_channel];
}

uint32_t CapTouch_Get_Touch_Duration(uint8_t current_channel){
  return CapTouch.TouchDuration[current_channel];
}

uint8_t CapTouch_Get_Touch_Response(uint8_t current_channel){
  return CapTouch.Result[current_channel];
}

uint8_t CapTouch_Get_Reference_Timer_Use_Flag(void){
  if(CapTouch.UsingReferenceTimer){
    return 1;
  }else{
    return 0;
  }
}

uint8_t CapTouch_Get_ErrorCode(uint8_t current_channel){
  return CapTouch.ErrorCode[current_channel];
}

void CapTouch_Get_Debug_Data(uint8_t current_channel, int *data_out){
  data_out[0]=8;
  data_out[1]=current_channel;
  data_out[2]=CapTouch_Get_RawADC1(current_channel);
  data_out[3]=CapTouch_Get_RawADC2(current_channel);
  data_out[4]=CapTouch_Get_RawDifferentialADC(current_channel);
  data_out[5]=CapTouch_Get_Calibration_Value(current_channel);
  data_out[6]=CapTouch_Get_Touch_Duration(current_channel);
  data_out[7]=CapTouch_Get_Touch_Response(current_channel);
  data_out[8]=CapTouch_Get_Reference_Timer_Use_Flag();
}

void CapTouch_Init(void){
  CapTouch_Struct_Init();
  CapTouch_IIR_Butterworth_Struct_Init();
  CapTouch_ADC_Register_Config();
  CapTouch_Calibration();
}


