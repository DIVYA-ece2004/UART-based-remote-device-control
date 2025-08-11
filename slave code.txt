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
void lcd_init();
void lcd_command(unsigned char);
void lcd_data(unsigned char);
unsigned char value,rx_rec,a[8]={"TX DATA:"},b[8]={"RX DATA:"},i;
void main()
{
    uart_init();
    lcd_init();
    lcd_command(0x80);  
    for(i=0;i<8;i++)
    {
        lcd_data(a[i]); // DISPLAY ARRAY TO LCD
    }
    lcd_command(0xc0);
    /*for(i=0;i<8;i++)
    {
        lcd_data(b[i]);// DISPLAY ARRAY TO LCD
    }*/
    while(1)
    {
        if(PIR1 & 0x20) //true if data received
        {
            rx_rec=RCREG;
            switch(rx_rec)
            {
                case 'A':
                    TXREG='a';  //Send a to TX pin
                    __delay_ms(100);
                    lcd_command(0x88);  
                    lcd_data(rx_rec);   //DISPLAY A
                    lcd_command(0xc0);
                    lcd_data('P');
                    lcd_data('U');
                    lcd_data('M');
                    lcd_data('P');
                    lcd_data(' ');
                    lcd_data(' ');
                    lcd_data(' ');
                    lcd_data('O');
                    lcd_data('N');
                    
                    
                    break;
                 case 'B':
                    TXREG='b';  //Send b to TX pin
                    __delay_ms(100);
                    lcd_command(0x88);
                    lcd_data(rx_rec);   //DISPLAY B
                    lcd_command(0xc0);
                    lcd_data('P');
                    lcd_data('U');
                    lcd_data('M');
                    lcd_data('P');
                    lcd_data(' ');
                    lcd_data(' ');
                    lcd_data('O');
                    lcd_data('F');
                    lcd_data('F');
                    //lcd_data(rx_rec+32);//DISPLAY b
                    break;
                case 'C':
                    TXREG='c';  //Send c to TX pin
                    __delay_ms(100);
                    lcd_command(0x88);
                    lcd_data(rx_rec);   //DISPLAY C
                    lcd_command(0xC0);
                    lcd_data('L');
                    lcd_data('I');
                    lcd_data('G');
                    lcd_data('H');
                    lcd_data('T');
                    lcd_data(' ');
                    lcd_data(' ');
                    lcd_data('O');
                    lcd_data('N');
                    //lcd_data(rx_rec+32);//DISPLAY c
                    break;
                case 'D':
                    TXREG='d';  //Send d to TX pin
                    __delay_ms(100);
                    lcd_command(0x88);
                    lcd_data(rx_rec);   //DISPLAY D
                    lcd_command(0xC0);
                    lcd_data('L');
                    lcd_data('I');
                    lcd_data('G');
                    lcd_data('H');
                    lcd_data('T');
                    lcd_data(' ');
                    lcd_data('O');
                    lcd_data('F');
                    lcd_data('F');
                    //lcd_data(rx_rec+32);//DISPLAY d
                    break;
            }
        }
    }  
}
void uart_init()
{
    //UART CONFIGURATION
    TRISC=0xC0; //SET RC6 (TX) and RC7 (RX) 1100 0000
    TXSTA=0x20;//transmitter enable bit    0010 0000
    SPBRG=0x09;//set baud rate
    RCSTA=0x90;//set SPEN and CREN bit 1001 0000
}
void lcd_init()
{
    //LCD INITIALIZATION
    TRISB=0x00;  //set all pins as output
    TRISD=0x00;  //set all pins as output
    PORTB=0x00;   // set all pins are low
    PORTD=0x00;  // set all pins are low
    lcd_command(0x30);  
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x30);
    __delay_ms(100);
    lcd_command(0x38);
    __delay_ms(100);
    lcd_command(0x06);  //cursor move from left to right
    __delay_ms(100);
    lcd_command(0x0C);  //display ON cursor OFF
    __delay_ms(100);
    lcd_command(0x01);  //CLEAR display
    __delay_ms(100);
}

void lcd_command(unsigned char i)
{
    PORTB &=~0x08;  //RS=0 for COMMAND
    PORTD=i;
    PORTB|=0x01;    //EN=1 
    PORTB &=~0x01;  //EN=0
    __delay_ms(100);
}
void lcd_data(unsigned char i)
{
    PORTB |=0x08;   //RS=0 for DATA
    PORTD=i;
    PORTB|=0x01;    //EN=1 
    PORTB &=~0x01;  //EN=0
    __delay_ms(100);
}
