
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000
void uart_init();
unsigned char value,rx_rec;
void main()
{
    uart_init();
    while(1)
    {
        value=PORTB;
        switch(value)
        {
            case 0XE0:      //RB4 ON
                TXREG='A';  //Send A to TX pin
                __delay_ms(100);
                 break;
             case 0XD0:     //RB5 ON
                TXREG='B';  //Send B to TX pin
                __delay_ms(100);
                 break;
             case 0XB0:     //RB6 ON
                TXREG='C';  //Send C to TX pin
                __delay_ms(100);
                 break;
             case 0X70:     //RB7 ON
                TXREG='D';  //Send D to TX pin
                __delay_ms(100);
                break;
        }
        if(PIR1 & 0x20) //true if data received
        {
            rx_rec=RCREG;
            switch(rx_rec)
            {
                case 'a':
                    PORTD=0x40;     //PUMB ON
                    break;
                 case 'b':
                    PORTD=0x00;     //RD6 OFF and RD1 ON
                    break;
                case 'c':
                    PORTD=0x02;     //RD6 OFF and RD1 OFF
                    break;
                case 'd':
                    PORTD=0x00;     //RD6 ON and RD1 ON
                    break;
            }
        }
    }
}
void uart_init()
{
    TRISD=0X00;     // SET ALL PIN AS OUTPUT
    PORTD=0X00;     //INTIALIZE AT LOW
    TRISB=0xF0;     //SET RB4 to RB7 as input pin
    PORTB=0x00;      //INTIALIZE AT LOW
    OPTION_REG=0x7F;//ENABLE INBUILD PULLUP resistor
    
    //UART CONFIGURATION
    
    TRISC=0xC0;     //SET RC6 (TX) and RC7 (RX) 1100 0000
    TXSTA=0x20;     //transmitter enable bit    0010 0000
    SPBRG=0x09;     //set baud rate
    RCSTA=0x90;     //set SPEN and CREN bit 1001 0000
}
