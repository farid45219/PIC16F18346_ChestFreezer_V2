


/* 
 * File:   uart.h
 * Author: MD. Faridul Islam
 * PIC16F18346 UART Library
 * Created on March 13, 2023, 12:16 PM
 */

#include<xc.h>
#define _XTAL_FREQ             32000000    /*Configure according to system clock*/

#define UART_TXSTA_REG         TX1STA
#define UART_TXSTA_TX9D_bp     0U
#define UART_TXSTA_TRMT_bp     1U
#define UART_TXSTA_BRGH_bp     2U
#define UART_TXSTA_SENDB_bp    3U
#define UART_TXSTA_SYNC_bp     4U
#define UART_TXSTA_TXEN_bp     5U
#define UART_TXSTA_TX9_bp      6U
#define UART_TXSTA_CSRC_bp     7U
#define UART_TXSTA_TX9D_bm     (1<<UART_TXSTA_TX9D_bp)
#define UART_TXSTA_TRMT_bm     (1<<UART_TXSTA_TRMT_bp)
#define UART_TXSTA_BRGH_bm     (1<<UART_TXSTA_BRGH_bp)
#define UART_TXSTA_SENDB_bm    (1<<UART_TXSTA_SENDB_bp)
#define UART_TXSTA_SYNC_bm     (1<<UART_TXSTA_SYNC_bp)
#define UART_TXSTA_TXEN_bm     (1<<UART_TXSTA_TXEN_bp)
#define UART_TXSTA_TX9_bm      (1<<UART_TXSTA_TX9_bp)
#define UART_TXSTA_CSRC_bm     (1<<UART_TXSTA_CSRC_bp)

#define UART_RCSTA_REG         RC1STA
#define UART_RCSTA_RX9D_bp     0U
#define UART_RCSTA_OERR_bp     1U
#define UART_RCSTA_FERR_bp     2U
#define UART_RCSTA_ADDEN_bp    3U
#define UART_RCSTA_CREN_bp     4U
#define UART_RCSTA_SREN_bp     5U
#define UART_RCSTA_RX9_bp      6U
#define UART_RCSTA_SPEN_bp     7U
#define UART_RCSTA_RX9D_bm     (1<<UART_RCSTA_RX9D_bp)
#define UART_RCSTA_OERR_bm     (1<<UART_RCSTA_OERR_bp)
#define UART_RCSTA_FERR_bm     (1<<UART_RCSTA_FERR_bp)
#define UART_RCSTA_ADDEN_bm    (1<<UART_RCSTA_ADDEN_bp)
#define UART_RCSTA_CREN_bm     (1<<UART_RCSTA_CREN_bp)
#define UART_RCSTA_SREN_bm     (1<<UART_RCSTA_SREN_bp)
#define UART_RCSTA_RX9_bm      (1<<UART_RCSTA_RX9_bp)
#define UART_RCSTA_SPEN_bm     (1<<UART_RCSTA_SPEN_bp)

#define UART_BAUDCON_REG       BAUD1CON
#define UART_BAUDCON_ABDEN_bp  0U
#define UART_BAUDCON_WUE_bp    1U
#define UART_BAUDCON_BRG16_bp  3U
#define UART_BAUDCON_SCKP_bp   4U
#define UART_BAUDCON_RCIDL_bp  6U
#define UART_BAUDCON_ABDOVF_bp 7U
#define UART_BAUDCON_ABDEN_bm  (1<<UART_BAUDCON_ABDEN_bp)
#define UART_BAUDCON_WUE_bm    (1<<UART_BAUDCON_WUE_bp)
#define UART_BAUDCON_BRG16_bm  (1<<UART_BAUDCON_BRG16_bp)
#define UART_BAUDCON_SCKP_bm   (1<<UART_BAUDCON_SCKP_bp)
#define UART_BAUDCON_RCIDL_bm  (1<<UART_BAUDCON_RCIDL_bp)
#define UART_BAUDCON_ABDOVF_bm (1<<UART_BAUDCON_ABDOVF_bp)

#define UART_RCREG_REG         RC1REG
#define UART_TXREG_REG         TX1REG
#define UART_SPBRG_REG         SP1BRG

#define UART_PIR_REG           PIR1
#define UART_PIR_TXIF_bp       4U
#define UART_PIR_RCIF_bp       5U
#define UART_PIR_TXIF_bm       (1<<UART_PIR_TXIF_bp)
#define UART_PIR_RCIF_bm       (1<<UART_PIR_RCIF_bp)

#define UART_PIE_REG           PIE1
#define UART_PIE_TXIE_bp       4U
#define UART_PIE_RCIE_bp       5U
#define UART_PIE_TXIE_bm       (1<<UART_PIE_TXIE_bp)
#define UART_PIE_RCIE_bm       (1<<UART_PIE_RCIE_bp)

#define UART_INTCON_REG        INTCON
#define UART_INTCON_PEIE_bp    6U
#define UART_INTCON_GIE_bp     7U
#define UART_INTCON_PEIE_bm    (1<<UART_INTCON_PEIE_bp)
#define UART_INTCON_GIE_bm     (1<<UART_INTCON_GIE_bp)


//#define  UART_TX_PIN_RBM
//#define  UART_TX_PIN_MHF
#define  UART_TX_PIN_MHF_V2

#ifdef  UART_TX_PIN_RBM
#define UART_TX_TRIS           TRISA
#define UART_TX_LAT            LATA
#define UART_TX_ANSEL          ANSELA
#define UART_TX_bp             5U
#define UART_TX_bm             (1<<UART_TX_bp)
#define UART_TX_PPS_REG        RA5PPS
#define UART_TX_PPS_OFFSET     0b00010100
#endif

#ifdef  UART_TX_PIN_MHF
#define UART_TX_TRIS           TRISA
#define UART_TX_LAT            LATA
#define UART_TX_ANSEL          ANSELA
#define UART_TX_bp             4U
#define UART_TX_bm             (1<<UART_TX_bp)
#define UART_TX_PPS_REG        RA4PPS
#define UART_TX_PPS_OFFSET     0b00010100
#endif

#ifdef  UART_TX_PIN_MHF_V2
#define UART_TX_TRIS           TRISA
#define UART_TX_LAT            LATA
#define UART_TX_ANSEL          ANSELA
#define UART_TX_bp             1U
#define UART_TX_bm             (1<<UART_TX_bp)
#define UART_TX_PPS_REG        RA1PPS
#define UART_TX_PPS_OFFSET     0b00010100
#endif

#define UART_RX_TRIS           TRISA
#define UART_RX_LAT            LATA
#define UART_RX_ANSEL          ANSELA
#define UART_RX_bp             0U
#define UART_RX_bm             (1<<UART_RX_bp)
#define UART_RX_PPS_REG        RXPPS
#define UART_RX_PPS_OFFSET     0b00000000


#define UART_TX_EN             1
//#define UART_RX_EN             1
//#define UART_RX_INT_EN         1
#define UART_BUF_SIZE          200

/*Don't change anything below this line*/
typedef struct uart_t{
    volatile uint8_t  Error;
    volatile uint8_t  Buffer[UART_BUF_SIZE];
    volatile uint8_t  BufferIndex;
    volatile uint8_t  AvailableBytes;
    volatile uint8_t  ReadIndex;
    volatile uint32_t LastRecivedTimeStamp;
}uart_t;

uart_t UART;

void UART_Struct_Init(void){
    UART.Error=0x00;
    UART.AvailableBytes=0x00;
    UART.ReadIndex=0x00;
    for(uint8_t i=0;i<UART_BUF_SIZE;i++){
        UART.Buffer[i]=0;
    }
    UART.BufferIndex=0;
    UART.LastRecivedTimeStamp=0;
}

void UART_Config_Transmitter(void){
    UART_TX_TRIS |=(uint8_t) UART_TX_bm;
    UART_TX_ANSEL&=(uint8_t)(~UART_TX_bm);
    UART_TX_PPS_REG=UART_TX_PPS_OFFSET;
    UART_TXSTA_REG  |= UART_TXSTA_TXEN_bm;
    UART_RCSTA_REG  |= UART_RCSTA_SPEN_bm;
}

void UART_Config_Receiver(void){
    UART_RX_TRIS |=(uint8_t) UART_RX_bm;
    UART_RX_ANSEL&=(uint8_t)(~UART_RX_bm);
    UART_RX_PPS_REG=UART_RX_PPS_OFFSET;
    UART_RCSTA_REG  |= UART_RCSTA_CREN_bm;
    UART_RCSTA_REG  |= UART_RCSTA_SPEN_bm;
}

void UART_Config_Receiver_Interrupt(void){
    UART_PIE_REG   |=UART_PIE_RCIE_bm;
    if(!(UART_INTCON_REG & UART_INTCON_PEIE_bm)){
        UART_INTCON_REG|=UART_INTCON_PEIE_bm;
    }
    if(!(UART_INTCON_REG & UART_INTCON_GIE_bm)){
        UART_INTCON_REG|=UART_INTCON_GIE_bm; 
    }
}

void UART_Init(uint32_t BAUD){
    uint32_t BRG_VAL=_XTAL_FREQ;
    BRG_VAL=((BRG_VAL/4)/BAUD)-1;
    UART_SPBRG_REG=(uint16_t)BRG_VAL;
    UART_BAUDCON_REG |=UART_BAUDCON_BRG16_bm;;
    UART_TXSTA_REG   |= UART_TXSTA_BRGH_bm;
    UART_Struct_Init();
    #ifdef UART_TX_EN
        UART_Config_Transmitter();
    #endif
    #ifdef UART_RX_EN
        UART_Config_Receiver();
    #endif
    #ifdef UART_RX_INT_EN
        UART_Config_Receiver_Interrupt();
    #endif
}

void UART_Transmit_Byte(uint8_t val){
    UART_TXREG_REG=val;
    while((UART_TXSTA_REG & UART_TXSTA_TRMT_bm)==0);
}

void UART_Transmit_Byte_Hex(uint8_t val){
    uint8_t hex_digits[2];
    hex_digits[0]=(uint8_t)(val>>4);
    hex_digits[1]=(uint8_t)(val & 0x0F);
    if(hex_digits[0]>9){hex_digits[0]+=55;}
    else {hex_digits[0]+=48;}
    if(hex_digits[1]>9){hex_digits[1]+=55;}
    else {hex_digits[1]+=48;}
    UART_Transmit_Byte('0');
    UART_Transmit_Byte('x');
    UART_Transmit_Byte(hex_digits[0]);
    UART_Transmit_Byte(hex_digits[1]);
}

void UART_Transmit_Byte_Bin(uint8_t val){
    uint8_t bin_digits[8];
    for(uint8_t i=0;i<8;i++){
        bin_digits[i]= (uint8_t)((val & 0x01)+48);
        val>>=1;
    }
    UART_Transmit_Byte('0');
    UART_Transmit_Byte('b');
    for(uint8_t i=8;i>0;i--){
        uint8_t index=(uint8_t)(i-1);
        UART_Transmit_Byte(bin_digits[index]);
    }
}

void UART_Transmit_Text(char *str){
    uint8_t i=0;
    while(str[i]!='\0'){
        UART_Transmit_Byte(str[i]);
        i++;
    }
}

void UART_Transmit_Unsigned_Number(uint32_t num){
    uint8_t digits=0;
    uint8_t buf[8];
    if(num==0){UART_Transmit_Byte('0');}
    else{
        while(num!=0){
            buf[digits]=num%10;
            num/=10;
            digits++;
        }
        for(uint8_t i=digits; i>0; i--){
            uint8_t temp=i;
            temp-=1;
            temp=buf[temp];
            temp+=48;
            UART_Transmit_Byte(temp);
        }
    }
}

void UART_Transmit_Number(int32_t num){
    if(num<0){UART_Transmit_Byte('-');num=-num;}
    UART_Transmit_Unsigned_Number((uint32_t)num);
}

void UART_Print_Debug_Data(int *data_in){
  for(int i=1;i<=data_in[0];i++){
    UART_Transmit_Number(data_in[i]);
    UART_Transmit_Text("  ");
  }
}

uint8_t UART_Receive_Byte(void){
    uint8_t val=0;
    if(UART_RCSTA_REG & UART_RCSTA_FERR_bm){
        val=UART_RCSTA_REG;
        val=UART_RCREG_REG;
        UART.Error=0x01;
    }
    else if(UART_RCSTA_REG & UART_RCSTA_OERR_bm){
        UART_RCSTA_REG&=~UART_RCSTA_CREN_bm;
        UART_RCSTA_REG|=UART_RCSTA_CREN_bm;
        UART.Error=0x02;
    }
    else{
        val=UART_RCREG_REG;
        UART.Error=0x00;
    }
    return val;
}

void UART_Flush_Buffer(void){
    UART.Error=0x00;
    for(uint8_t i=0;i<UART_BUF_SIZE;i++){
        UART.Buffer[i]=0x00;
    }
    UART.BufferIndex=0x00;
    UART.AvailableBytes=0x00;
}


uint8_t UART_Read_From_Buffer(uint8_t index){
    return UART.Buffer[index];
}

uint8_t UART_Buffer_Index(void){
    return UART.BufferIndex;
}

//Need to improve and implement Circular buffer clear
uint8_t UART_Bytes_Available_To_Read(void){
    return UART.AvailableBytes;
}

uint32_t UART_Last_Byte_Recevied_Time_Stamp(void){
    return UART.LastRecivedTimeStamp;
}

void UART_Interrupt_Service_Routine(void){
    if(UART_PIR_REG & UART_PIR_RCIF_bm){
        volatile uint8_t received_byte=UART_Receive_Byte();
        if(UART.Error==0){
            UART.Buffer[UART.BufferIndex]=received_byte;
            UART.BufferIndex++;
            UART.AvailableBytes++;
            if(UART.BufferIndex>=UART_BUF_SIZE){UART.BufferIndex=0;}
        }
        UART_PIR_REG &=~ UART_PIR_RCIF_bm;
    }
}
