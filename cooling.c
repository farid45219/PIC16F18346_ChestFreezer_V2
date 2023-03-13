
#include <xc.h>
#include "sevensegment.h"

typedef struct compressor_t{
    uint8_t  Status;
    uint32_t OnTime;
    uint32_t OffTime;
}compressor_t;

typedef struct temperature_t{
    int      Sensor;
    int      Set;
    int      CutIn;
    int      CutOff;
}temperature_t;

typedef struct cooling_t{
    compressor_t  Compressor;
    uint8_t       Mode;
    temperature_t Temperature;
}cooling_t;

cooling_t Cooling_Type;
cooling_t *Cooling;

int set_temp[5]={-2, -22, -27, -15, -18};
int cut_in[5]  ={-13, -24, -27, -17, -21};
int cut_off[5] ={-17, -28, -28, -21, -25};

void Cooling_Stuct_Init(void){
    Cooling=&Cooling_Type;
    Cooling->Compressor.Status=0;
    Cooling->Compressor.OnTime=0;
    Cooling->Compressor.OffTime=0;
    Cooling->Mode=0;
    Cooling->Temperature.Sensor=0;
    Cooling->Temperature.Set=0;
    Cooling->Temperature.CutIn;
    Cooling->Temperature.CutOff=0;
}

void Cooling_Select_Mode(uint8_t mode){
    if(mode==0){
        Indicator_LED_All_Off();
        Indicator_LED(Indicator_LED_REFRIGERATOR(), 1);
    }else if(mode==1){
        Indicator_LED_All_Off();
        Indicator_LED(Indicator_LED_COLDEST(), 1);
    }else if(mode==2){
        Indicator_LED_All_Off();
        Indicator_LED(Indicator_LED_TURBO(), 1);
    }else if(mode==3){
        Indicator_LED_All_Off();
        Indicator_LED(Indicator_LED_E_SAVE(), 1);
    }else if(mode==4){
        Indicator_LED_All_Off();
        Indicator_LED(Indicator_LED_STANDARD(), 1);
    }
}

uint8_t Cooling_Check_Mode(void){
    return Cooling->Mode;
}

void Cooling_Change_Mode(void){
    Cooling->Mode++;
    if(Cooling->Mode>4){
        Cooling->Mode=0;
    }
}

void Cooling_Set_Mode(uint8_t mode){
    Cooling->Mode=mode;
    Cooling_Select_Mode(Cooling->Mode);
    Cooling->Temperature.Set=set_temp[Cooling->Mode];
    Cooling->Temperature.CutIn=cut_in[Cooling->Mode];
    Cooling->Temperature.CutOff=cut_off[Cooling->Mode];
    SevenSegment_Print(set_temp[Cooling->Mode]);
}

void Cooling_Init(void){
    Cooling_Stuct_Init();
    Cooling_Set_Mode(0);
}