


#include<xc.h>
#include<stdint.h>

#define PWM_TRIS  TRISA
#define PWM_LAT   LATA
#define PWM_ANSEL ANSELA
#define PWM_PIN   1

typedef struct pwm_t{
    uint16_t  Freq;
    uint16_t  Duty;
    uint8_t   Status;
}pwm_t;

pwm_t Buzzer;

void Buzzer_Struct_Init(void){
    Buzzer.Duty=0;
    Buzzer.Freq=0;
    Buzzer.Status=0;
}

void Buzzer_GPIO_Disable(void){
    PWM_TRIS |=(1<<PWM_PIN);
    PWM_ANSEL|=(1<<PWM_PIN);
}

void Buzzer_PWM_Register_Config(void){
    PWM5CON=0x00;
    PWM5CON&=~(1<<4);
    PR2=100;
    PWM5DCL=0x00;
    PWM5DCH=0x00;
    if(PIR1 & (1<<1)){
        PIR1&=~(1<<1);
    }
    PWMTMRS|=(1<<0);
    T2CON=(3<<0);
    T2CON|=(1<<2);
    while(!(PIR1 & (1<<1)));
}

void Buzzer_GPIO_Enable(void){
    PWM_TRIS &=~(1<<PWM_PIN);
    PWM_ANSEL&=~(1<<PWM_PIN);
}

void Buzzer_Config_PPS(void){
    RA1PPS=0x02;
}

void Buzzer_PWM_Enable(void){
    PWM5CON|=(1<<7);
}

void Buzzer_On(void){
    PWM5DCH=50;
}

void Buzzer_Off(void){
    PWM5DCH=0;
}

void Buzzer_PWM_Init(void){
    Buzzer_Struct_Init();
    Buzzer_GPIO_Disable();
    Buzzer_PWM_Register_Config();
    Buzzer_GPIO_Enable();
    Buzzer_Config_PPS();
    Buzzer_PWM_Enable();
    Buzzer_Off();
}