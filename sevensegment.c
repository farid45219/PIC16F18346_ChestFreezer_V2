
#include<xc.h>
#include<stdint.h>
#define _XTAL_FREQ                    32000000     /*Configure according to system clock*/
//#define SEVENSEGMENT_USING_TIMER0
//#define SEVENSEGMENT_USING_TIMER1
#define SEVENSEGMENT_USING_TIMER6

//#define SEVENSEGMENT_DYNAMIC_BRIGHTNESS
#define SEVENSEGMENT_FIXED_BRIGHTNESS

//#define SEVENSEGMENT_DEFAULT_SETTING
#define SEVENSEGMENT_TEST_SETTING

#ifdef SEVENSEGMENT_USING_TIMER0
#define SEVENSEGMENT_PERIOD_REG       TMR0H
#define SEVENSEGMENT_TxCON_REG        T0CON0
#define SEVENSEGMENT_ON_BIT_POS       0x07
#define SEVENSEGMENT_TxCON1_REG       T0CON1
#define SEVENSEGMENT_PRESCALE_POS     0x00
#define SEVENSEGMENT_PRESCALE_1       0x00
#define SEVENSEGMENT_PRESCALE_2       0x01
#define SEVENSEGMENT_PRESCALE_4       0x02
#define SEVENSEGMENT_PRESCALE_8       0x03
#define SEVENSEGMENT_PRESCALE_16      0x04
#define SEVENSEGMENT_PRESCALE_32      0x05
#define SEVENSEGMENT_PRESCALE_64      0x06
#define SEVENSEGMENT_PRESCALE_128     0x07
#define SEVENSEGMENT_PRESCALE_256     0x08
#define SEVENSEGMENT_PRESCALE_512     0x09
#define SEVENSEGMENT_PRESCALE_1024    0x0A
#define SEVENSEGMENT_PRESCALE_2048    0x0B
#define SEVENSEGMENT_PRESCALE_4096    0x0C
#define SEVENSEGMENT_PRESCALE_8192    0x0D
#define SEVENSEGMENT_PRESCALE_16384   0x0E
#define SEVENSEGMENT_PRESCALE_32768   0x0F

#define SEVENSEGMENT_POSTSCALER_POS   0x00
#define SEVENSEGMENT_POSTSCALER       15    
#define SEVENSEGMENT_INT_FLAG_REG     PIR0
#define SEVENSEGMENT_INT_FLAG_BIT_POS 5
#define SEVENSEGMENT_INT_REG          PIE0
#define SEVENSEGMENT_INT_BIT_POS      5
#define SEVENSEGMENT_INTCON_REG       INTCON
#define SEVENSEGMENT_PEIE_BIT_POS     6
#define SEVENSEGMENT_GIE_BIT_POS      7


void SevenSegment_Timer_Init(void){     
    SEVENSEGMENT_TxCON_REG =0x00;
    SEVENSEGMENT_TxCON1_REG =(SEVENSEGMENT_PRESCALE_4096<<SEVENSEGMENT_PRESCALE_POS);
    SEVENSEGMENT_TxCON1_REG|=(0x02<<5);
    SEVENSEGMENT_PERIOD_REG=1;
    SEVENSEGMENT_TxCON_REG =(1<<SEVENSEGMENT_ON_BIT_POS);
    
    SEVENSEGMENT_INT_REG  |=(1<<SEVENSEGMENT_INT_BIT_POS);
    if(!(SEVENSEGMENT_INTCON_REG & (1<<SEVENSEGMENT_PEIE_BIT_POS))){
        SEVENSEGMENT_INTCON_REG|=(1<<SEVENSEGMENT_PEIE_BIT_POS);
    }
    if(!(SEVENSEGMENT_INTCON_REG & (1<<SEVENSEGMENT_GIE_BIT_POS))){
        SEVENSEGMENT_INTCON_REG|=(1<<SEVENSEGMENT_GIE_BIT_POS);
    }
    if(!(SEVENSEGMENT_INT_FLAG_REG & (1<<SEVENSEGMENT_INT_FLAG_BIT_POS))){
        SEVENSEGMENT_INT_FLAG_REG&=~(1<<SEVENSEGMENT_INT_FLAG_BIT_POS);
    }
}

#endif

#ifdef  SEVENSEGMENT_USING_TIMER1
//#define SEVENSEGMENT_PERIOD_REG       TMR0H
#define SEVENSEGMENT_TxCON_REG        T1CON
#define SEVENSEGMENT_TxCON_ON_bp      0x00
#define SEVENSEGMENT_TxCON_TxSYNC_bp  0x02
#define SEVENSEGMENT_TxCON_TxSOSC_bp  0x03
#define SEVENSEGMENT_TxCON_TxCKPS_gp  0x04
#define SEVENSEGMENT_TxCON_TMRxCS_gp  0x02
#define SEVENSEGMENT_TxCON_ON_bm      (1<<SEVENSEGMENT_TxCON_ON_bp)
#define SEVENSEGMENT_TxCON_TxSYNC_bm  (1<<SEVENSEGMENT_TxCON_TxSYNC_bp)
#define SEVENSEGMENT_TxCON_TxSOSC_bm  (1<<SEVENSEGMENT_TxCON_TxSOSC_bp)
#define SEVENSEGMENT_TxCON_TxCKPS_bm  (1<<SEVENSEGMENT_TxCON_TxCKPS_bp)
 
#define SEVENSEGMENT_INT_FLAG_REG     PIR1
#define SEVENSEGMENT_INT_FLAG_BIT_POS 0x00
#define SEVENSEGMENT_INT_REG          PIE1
#define SEVENSEGMENT_INT_BIT_POS      0x00
#define SEVENSEGMENT_INTCON_REG       INTCON
#define SEVENSEGMENT_PEIE_BIT_POS     6
#define SEVENSEGMENT_GIE_BIT_POS      7


void SevenSegment_Timer_Init(void){     
    SEVENSEGMENT_TxCON_REG = (0x03<<SEVENSEGMENT_TxCON_TxCKPS_gp);
    SEVENSEGMENT_TxCON_REG|=SEVENSEGMENT_TxCON_ON_bm;
    
    SEVENSEGMENT_INT_REG  |=(1<<SEVENSEGMENT_INT_BIT_POS);
    if(!(SEVENSEGMENT_INTCON_REG & (1<<SEVENSEGMENT_PEIE_BIT_POS))){
        SEVENSEGMENT_INTCON_REG|=(1<<SEVENSEGMENT_PEIE_BIT_POS);
    }
    if(!(SEVENSEGMENT_INTCON_REG & (1<<SEVENSEGMENT_GIE_BIT_POS))){
        SEVENSEGMENT_INTCON_REG|=(1<<SEVENSEGMENT_GIE_BIT_POS);
    }
    if(!(SEVENSEGMENT_INT_FLAG_REG & (1<<SEVENSEGMENT_INT_FLAG_BIT_POS))){
        SEVENSEGMENT_INT_FLAG_REG&=~(1<<SEVENSEGMENT_INT_FLAG_BIT_POS);
    }
}

#endif

#ifdef  SEVENSEGMENT_USING_TIMER6
#define SEVENSEGMENT_PERIOD_REG       PR6
#define SEVENSEGMENT_TxCON_REG        T6CON
#define SEVENSEGMENT_PRESCALE_POS     0x00
#define SEVENSEGMENT_PRESCALE_1       0x00
#define SEVENSEGMENT_PRESCALE_4       0x01
#define SEVENSEGMENT_PRESCALE_16      0x02
#define SEVENSEGMENT_PRESCALE_64      0x03
#define SEVENSEGMENT_ON_BIT_POS       0x02
#define SEVENSEGMENT_POSTSCALER_POS   0x03
#define SEVENSEGMENT_POSTSCALER       10  
#define SEVENSEGMENT_INT_FLAG_REG     PIR2
#define SEVENSEGMENT_INT_FLAG_BIT_POS 7
#define SEVENSEGMENT_INT_REG          PIE2
#define SEVENSEGMENT_INT_BIT_POS      7
#define SEVENSEGMENT_INTCON_REG       INTCON
#define SEVENSEGMENT_PEIE_BIT_POS     6
#define SEVENSEGMENT_GIE_BIT_POS      7

void SevenSegment_Timer_Init(void){
    SEVENSEGMENT_TxCON_REG =0x00;
    
    #ifdef SEVENSEGMENT_DEFAULT_SETTING
    SEVENSEGMENT_PERIOD_REG=200;
    SEVENSEGMENT_TxCON_REG|=(uint8_t)(SEVENSEGMENT_PRESCALE_16<<SEVENSEGMENT_POSTSCALER_POS);
    SEVENSEGMENT_TxCON_REG|=(uint8_t)(SEVENSEGMENT_POSTSCALER<<SEVENSEGMENT_POSTSCALER_POS);
    #endif

    #ifdef SEVENSEGMENT_TEST_SETTING
    SEVENSEGMENT_PERIOD_REG=255;
    SEVENSEGMENT_TxCON_REG|=(uint8_t)(SEVENSEGMENT_PRESCALE_64<<SEVENSEGMENT_POSTSCALER_POS);
    SEVENSEGMENT_TxCON_REG|=(uint8_t)(15<<SEVENSEGMENT_POSTSCALER_POS);
    #endif
    
    SEVENSEGMENT_TxCON_REG|=(1<<SEVENSEGMENT_ON_BIT_POS);
    SEVENSEGMENT_INT_REG  |=(1<<SEVENSEGMENT_INT_BIT_POS);
    if(!(SEVENSEGMENT_INTCON_REG & (1<<SEVENSEGMENT_PEIE_BIT_POS))){
        SEVENSEGMENT_INTCON_REG|=(1<<SEVENSEGMENT_PEIE_BIT_POS);
    }
    if(!(SEVENSEGMENT_INTCON_REG & (1<<SEVENSEGMENT_GIE_BIT_POS))){
        SEVENSEGMENT_INTCON_REG|=(1<<SEVENSEGMENT_GIE_BIT_POS);
    }
    if(!(SEVENSEGMENT_INT_FLAG_REG & (1<<SEVENSEGMENT_INT_FLAG_BIT_POS))){
        SEVENSEGMENT_INT_FLAG_REG&=~(1<<SEVENSEGMENT_INT_FLAG_BIT_POS);
    }
}
#endif





#define SEVENSEGMENT_COMMON_ANODE     1
#define SEVENSEGMENT_TRANSISTOR_DRIVE 1
#define SEVENSEGMENT_SEG_TRIS         TRISC
#define SEVENSEGMENT_SEG_LAT          LATC

#define SEVENSEGMENT_DIG_TRIS         TRISB
#define SEVENSEGMENT_DIG_LAT          LATB
#define SEVENSEGMENT_DIG_START_PIN    4
#define SEVENSEGMENT_TOTAL_DIGITS     2
#define SEVENSEGMENT_TOTAL_INDICATORS 2

#define INDICATOR_LED_E_SAVE          0
#define INDICATOR_LED_STANDARD        1
#define INDICATOR_LED_COMPRESSOR      2
#define INDICATOR_LED_MODE            3
#define INDICATOR_LED_UNLOCK          4
#define INDICATOR_LED_TURBO           5
#define INDICATOR_LED_COLDEST         6
#define INDICATOR_LED_REFRIGERATOR    7
#define INDICATOR_LED_NEG             8
#define INDICATOR_LED_DEG             9

volatile uint8_t Segment_Val[19]={
  0b00111111, //0
  0b00000110, //1
  0b01011011, //2
  0b01001111, //3
  0b01100110, //4
  0b01101101, //5
  0b01111101, //6
  0b00000111, //7
  0b01111111, //8
  0b01101111, //9
  0b00000000, //Null
  0b01000000, //'-'
  0b01110111, //'A'
  0b01111100, //'b'
  0b00111001, //'C'
  0b01011110, //'d'
  0b01111001, //'E'
  0b01110001, //'F'
  0b00000000  //Customized
};

typedef struct sevensegment_t{
    volatile uint8_t  LoopCounter;
    volatile uint8_t  CurrentlyActiveDigit;
    volatile uint8_t  Brightness;
    volatile uint8_t  DigitValues[SEVENSEGMENT_TOTAL_DIGITS+SEVENSEGMENT_TOTAL_INDICATORS];
    volatile uint8_t  DigitCommonPinsOffState;
    volatile uint8_t  CommonPinPositions[SEVENSEGMENT_TOTAL_DIGITS+SEVENSEGMENT_TOTAL_INDICATORS];
    volatile uint8_t  CommonPinInvertedDrive;
    volatile uint8_t  CommonPinDriveMethod;
    volatile uint8_t  Sleep;
    volatile uint8_t  TotalDigits;
    uint32_t          TempTime;
    uint8_t           SleepCounterStarted;
    volatile uint32_t SleepCounter;
    volatile uint32_t DeemingValue;
    volatile uint32_t SleepingValue;
    volatile uint8_t  FreeFlag;
}sevensegment_t;

sevensegment_t    SevenSegment;

uint8_t SevenSegment_Byte_Invert(uint8_t val){
    for(uint8_t i=0;i<8;i++){
        if(val & (1<<i)){
            val&=(uint8_t)(~(1<<i));
        }else{
            val|=(uint8_t)(1<<i);
        }
    }
    return val;
}

void SevenSegment_Struct_Init(void){
    SevenSegment.LoopCounter=0;
    SevenSegment.CurrentlyActiveDigit=0;
    SevenSegment.Brightness=10;
    SevenSegment.DigitCommonPinsOffState=0x00;
    SevenSegment.CommonPinInvertedDrive=0;
    SevenSegment.Sleep=0;
    SevenSegment.TotalDigits=SEVENSEGMENT_TOTAL_DIGITS+SEVENSEGMENT_TOTAL_INDICATORS;
    for(uint8_t i=SEVENSEGMENT_DIG_START_PIN;i<(SEVENSEGMENT_DIG_START_PIN+SevenSegment.TotalDigits);i++){
        SevenSegment.DigitCommonPinsOffState|=(uint8_t)(1<<i);
        SevenSegment.CommonPinPositions[i-SEVENSEGMENT_DIG_START_PIN]=(uint8_t)(1<<i);
        if((i-SEVENSEGMENT_DIG_START_PIN)<SEVENSEGMENT_TOTAL_DIGITS){
            SevenSegment.DigitValues[i-SEVENSEGMENT_DIG_START_PIN]=10;
        }else{
            SevenSegment.DigitValues[i-SEVENSEGMENT_DIG_START_PIN]=18;
        }
    }
    SevenSegment.CommonPinDriveMethod=(SEVENSEGMENT_TRANSISTOR_DRIVE<<1)|(SEVENSEGMENT_COMMON_ANODE<<0);
    SevenSegment.TempTime=0;
    SevenSegment.SleepCounterStarted=0;
    SevenSegment.SleepCounter=0;
    SevenSegment.DeemingValue=0xFFFFFFFF;
    SevenSegment.SleepingValue=0xFFFFFFFF;
    SevenSegment.FreeFlag=0;
}

void SevenSegment_Config_Variables(void){
    if(SevenSegment.CommonPinDriveMethod & 0x01){
        for(uint8_t i=0;i<19;i++){
            Segment_Val[i]= SevenSegment_Byte_Invert(Segment_Val[i]);
        }
    }
    if((SevenSegment.CommonPinDriveMethod==0x00) || (SevenSegment.CommonPinDriveMethod==0x03)){
        SevenSegment.CommonPinInvertedDrive=1;
    }else if((SevenSegment.CommonPinDriveMethod==0x01) || (SevenSegment.CommonPinDriveMethod==0x02)){
        SevenSegment.CommonPinInvertedDrive=0;
    }
}

void SevenSegment_SEG_And_Digit_Pins_Output(void){
    SEVENSEGMENT_SEG_TRIS&=(uint8_t)(~0xFF);
    SEVENSEGMENT_DIG_TRIS&=(uint8_t)(~SevenSegment.DigitCommonPinsOffState);
//    SEVENSEGMENT_IND_TRIS&=(uint8_t)(~(1<<SEVENSEGMENT_IND_PIN));
//    SEVENSEGMENT_IND_ANSEL&=(uint8_t)(~(1<<SEVENSEGMENT_IND_PIN));
}

void SevenSegment_SEG_Pins_High(void){
    SEVENSEGMENT_SEG_LAT=0xFF;
}

void SevenSegment_SEG_Pins_Low(void){
    SEVENSEGMENT_SEG_LAT=0x00;
}

void SevenSegment_SEG_Pins_Enable(void){
    if(SevenSegment.CurrentlyActiveDigit<2){
        SEVENSEGMENT_SEG_LAT=Segment_Val[SevenSegment.DigitValues[SevenSegment.CurrentlyActiveDigit]];
    }else if (SevenSegment.CurrentlyActiveDigit==2){
        SEVENSEGMENT_SEG_LAT=Segment_Val[18];
    }

}

void SevenSegment_SEG_Pins_Disable(void){
    if(SevenSegment.CommonPinDriveMethod & 0x01){
        SevenSegment_SEG_Pins_High();
    }else{
        SevenSegment_SEG_Pins_Low();
    }
}

void SevenSegment_Digit_Pins_High(void){
    SEVENSEGMENT_DIG_LAT|=(uint8_t)SevenSegment.DigitCommonPinsOffState;
    //SEVENSEGMENT_IND_LAT|=(uint8_t)(1<<SEVENSEGMENT_IND_PIN);
}

void SevenSegment_Digit_Pins_Low(void){
    SEVENSEGMENT_DIG_LAT&=(uint8_t)(~SevenSegment.DigitCommonPinsOffState);
    //SEVENSEGMENT_IND_LAT&=(uint8_t)(~(1<<SEVENSEGMENT_IND_PIN));
}

void SevenSegment_Digit_Pin_Enable(void){
    if(SevenSegment.CommonPinInvertedDrive){
        if(SevenSegment.CurrentlyActiveDigit<2){
            SEVENSEGMENT_DIG_LAT&=(uint8_t)(~SevenSegment.CommonPinPositions[SevenSegment.CurrentlyActiveDigit]);
        }else if(SevenSegment.CurrentlyActiveDigit==2){
            //SEVENSEGMENT_IND_LAT&=(uint8_t)(~(1<<SEVENSEGMENT_IND_PIN));
        }
        
    }else{
        if(SevenSegment.CurrentlyActiveDigit<2){
            SEVENSEGMENT_DIG_LAT|=(uint8_t)(SevenSegment.CommonPinPositions[SevenSegment.CurrentlyActiveDigit]);
        }else if(SevenSegment.CurrentlyActiveDigit==2){
            //SEVENSEGMENT_IND_LAT|=(uint8_t)(1<<SEVENSEGMENT_IND_PIN);
        }
    }
}

void SevenSegment_Digit_Pins_Disable(void){
    if(SevenSegment.CommonPinInvertedDrive){
        SevenSegment_Digit_Pins_High();
    }else{
        SevenSegment_Digit_Pins_Low();
    }
}

void SevenSegment_GPIO_Init(void){
    SevenSegment_SEG_And_Digit_Pins_Output();
    SevenSegment_SEG_Pins_Disable();
    SevenSegment_Digit_Pins_Disable();
}

void SevenSegment_Init(void){
    SevenSegment_Struct_Init();
    SevenSegment_Config_Variables();
    SevenSegment_GPIO_Init();
    SevenSegment_Timer_Init();
}

void SevenSegment_Print_Number_In_xDigit(uint8_t digit, uint8_t val){
    if(digit<2){
        SevenSegment.DigitValues[digit]=val;
    }
}

uint8_t Indicator_LED_E_SAVE(void){
    return (uint8_t) INDICATOR_LED_E_SAVE;
}

uint8_t Indicator_LED_STANDARD(void){
    return (uint8_t) INDICATOR_LED_STANDARD;
}

uint8_t Indicator_LED_COMPRESSOR(void){
    return (uint8_t) INDICATOR_LED_COMPRESSOR;
}

uint8_t Indicator_LED_MODE(void){
    return (uint8_t) INDICATOR_LED_MODE;
}

uint8_t Indicator_LED_UNLOCK(void){
    return (uint8_t) INDICATOR_LED_UNLOCK;
}

uint8_t Indicator_LED_TURBO(void){
    return (uint8_t) INDICATOR_LED_TURBO;
}

uint8_t Indicator_LED_COLDEST(void){
    return (uint8_t) INDICATOR_LED_COLDEST;
}

uint8_t Indicator_LED_REFRIGERATOR(void){
    return (uint8_t) INDICATOR_LED_REFRIGERATOR;
}

uint8_t Indicator_LED_NEG(void){
    return (uint8_t) INDICATOR_LED_NEG;
}

uint8_t Indicator_LED_DEG(void){
    return (uint8_t) INDICATOR_LED_DEG;
}

void Indicator_LED(uint8_t led_bit_pos, uint8_t state){
    if((state==1) && (led_bit_pos<8)){
        Segment_Val[18]&=(uint8_t)(~(1<<led_bit_pos));
    }else if((state==0) && (led_bit_pos<8)){
        Segment_Val[18]|=(uint8_t)(1<<led_bit_pos);
    }else if(led_bit_pos==8){
        //SevenSegment.LEDNeg=state;
    }else if(led_bit_pos==9){
        //SevenSegment.LEDDeg=state;
    }
}

void Indicator_LED_All_Off(void){
    Segment_Val[18]=0xFF;
}

uint8_t Check_Indicator_LED_Status(uint8_t led_bit_pos){
    uint8_t status=0;
    if(led_bit_pos<8){
        if(Segment_Val[18] & (1<<led_bit_pos)){
            status=0;
        }else{
            status=1;
        }
    }else if(led_bit_pos==8){
        //status=SevenSegment.LEDNeg;
    }
    else if(led_bit_pos==8){
        //status=SevenSegment.LEDDeg;
    }
    return status;
}

void Indicator_LED_UNLOCK_Toggle(void){
    if(Check_Indicator_LED_Status(INDICATOR_LED_UNLOCK)){
        Indicator_LED(INDICATOR_LED_UNLOCK, 0);
    }else{
        Indicator_LED(INDICATOR_LED_UNLOCK, 1);
    }
}

void SevenSegment_Print(int value){
    if(value<0){
        Indicator_LED(INDICATOR_LED_NEG, 1);
        value=-value;
    }else{
        Indicator_LED(INDICATOR_LED_NEG, 0);
    }
    uint8_t d1=(value/10)%10;
    uint8_t d2=(value%10);
    SevenSegment_Print_Number_In_xDigit(0, d1);
    SevenSegment_Print_Number_In_xDigit(1, d2);
}


#ifdef SEVENSEGMENT_DYNAMIC_BRIGHTNESS
void SevenSegment_Set_Brightness(uint8_t brightness){
    if(brightness>10){
        brightness=10;
    }else if(brightness<3){
        brightness=3;
    }
    SevenSegment.SetBrightness=brightness;
}

void SevenSegment_Set_Brightness_Max(void){
    SevenSegment.SetBrightness=10;
}

void SevenSegment_Set_Brightness_Min(void){
    SevenSegment.SetBrightness=3;
}
#endif


#ifdef SEVENSEGMENT_FIXED_BRIGHTNESS
void SevenSegment_Set_Brightness(uint8_t brightness){
    if(brightness>2){
        brightness=2;
    }else if(brightness<1){
        brightness=1;
    }
}

void SevenSegment_Set_Brightness_Max(void){ 
//    SevenSegment.SetBrightness=2;
//    SevenSegment.BrightnessControl=2;
}

void SevenSegment_Set_Brightness_Min(void){ 
//    SevenSegment.SetBrightness=1;
//    SevenSegment.BrightnessControl=1;
}
#endif

void SevenSegment_Enter_Sleep_Mode(void){
    SevenSegment.Sleep=1;
}

void SevenSegment_Wakeup_From_Sleep_Mode(void){
    SevenSegment.Sleep=0;
}

void SevenSegment_Set_Dimming_And_Sleeping_Delay(uint32_t dim, uint32_t sleep){
    SevenSegment.SleepCounter=0;
    SevenSegment.DeemingValue=dim;
    SevenSegment.SleepingValue=sleep;
}

void SevenSegment_Reset_Dimming_And_Sleeping_Delay(void){
    SevenSegment.SleepCounter=0;
}

uint8_t SevenSegment_No_Operation_Ongoing(void){
    return SevenSegment.FreeFlag;
}

#ifdef SEVENSEGMENT_DYNAMIC_BRIGHTNESS
void SevenSegment_ISR_Executables(void){
    if((SevenSegment.LoopCounter==0)&& (!SevenSegment.Sleep)){
        SevenSegment_SEG_Pins_Enable();
        SevenSegment_Digit_Pin_Enable();
        SevenSegment.BrightnessControl=SevenSegment.BrightnessUpdate;
    }else if(SevenSegment.LoopCounter==SevenSegment.BrightnessControl){
        SevenSegment_SEG_Pins_Disable();
        SevenSegment_Digit_Pins_Disable();
        SevenSegment.CurrentlyActiveDigit++;
        if(SevenSegment.CurrentlyActiveDigit>SevenSegment.TotalDigits){
            SevenSegment.CurrentlyActiveDigit=0;
        }
    }
    SevenSegment.BrightnessUpdateCounter++;
    if(SevenSegment.BrightnessUpdateCounter>400){
        SevenSegment.BrightnessUpdateCounter=0;
        if(SevenSegment.BrightnessUpdate>SevenSegment.SetBrightness){
            SevenSegment.BrightnessUpdate--;
        }
        else if(SevenSegment.BrightnessUpdate<SevenSegment.SetBrightness){
            SevenSegment.BrightnessUpdate++;
        }
    }
    SevenSegment.LoopCounter++;
    if(SevenSegment.LoopCounter>10){
        SevenSegment.LoopCounter=0;
    }
    SevenSegment.SleepCounter++;
    if(SevenSegment.SleepCounter>SevenSegment.SleepingValue){
        SevenSegment_Enter_Sleep_Mode();
    }else if(SevenSegment.SleepCounter>SevenSegment.DeemingValue){
        SevenSegment_Set_Brightness_Min();
    }
}
#endif


#ifdef SEVENSEGMENT_FIXED_BRIGHTNESS
void SevenSegment_ISR_Executables(void){
    if((SevenSegment.LoopCounter==0) && (!SevenSegment.Sleep)){
        SevenSegment_SEG_Pins_Enable();
        SevenSegment_Digit_Pin_Enable();
    }else if(SevenSegment.LoopCounter==0 ){
        SevenSegment_SEG_Pins_Disable();
        SevenSegment_Digit_Pins_Disable();
        SevenSegment.CurrentlyActiveDigit++;
        if(SevenSegment.CurrentlyActiveDigit==3){
            SevenSegment.FreeFlag=1;
        }
        if(SevenSegment.CurrentlyActiveDigit>SevenSegment.TotalDigits){
            SevenSegment.CurrentlyActiveDigit=0;
            SevenSegment.FreeFlag=0;
        }
    }
    SevenSegment.LoopCounter++;
    if(SevenSegment.LoopCounter>3){
        SevenSegment.LoopCounter=0;
    }
    SevenSegment.SleepCounter++;
    if(SevenSegment.SleepCounter>SevenSegment.SleepingValue){
        SevenSegment_Enter_Sleep_Mode();
    }else if(SevenSegment.SleepCounter>SevenSegment.DeemingValue){
        SevenSegment_Set_Brightness_Min();
    }
}
#endif


void SevenSegment_Interrupt_Service_Routine(void){
    if(SEVENSEGMENT_INT_FLAG_REG & (1<<SEVENSEGMENT_INT_FLAG_BIT_POS)){
        SevenSegment_ISR_Executables();
        SEVENSEGMENT_INT_FLAG_REG&=~(1<<SEVENSEGMENT_INT_FLAG_BIT_POS);
    }
}
