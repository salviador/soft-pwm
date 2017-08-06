
// PIC16F819 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTRC oscillator; port I/O function on both RA6/OSC2/CLKO pin and RA7/OSC1/CLKI pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable bit (RB3/PGM pin has PGM function, Low-Voltage Programming enabled)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off)
#pragma config CCPMX = RB2      // CCP1 Pin Selection bit (CCP1 function on RB2)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>

void PWM (void);





// Global variables
unsigned char uchDuty[8];
unsigned char uchStartPWM;


void interrupt isr(void)
{

// Timer 0 overflow
	if (TMR0IF) // Interrupt each 255us
	{
		PWM();		 // Call PWM() function
		TMR0IF = 0;  // Clear TMR0 interrupt bit
	}
}




void main(void) {    
	// Oscillator setup
	OSCCON = 0x70;          //8Mhz
	//while(IOFS == 0);

	// PORTA configuration

	// Disable comparators
	ADCON1 = 0x06;

	// PORTA configured as input
	TRISA = 0xFF;

	// PORTB configured as output
	TRISB = 0x00;

	PORTB = 0x00;

	// TMR0 setup
	OPTION_REG = 0x80;

	// TMR2 setup
	T2CON = 0x07;           2000000/16 = 125000
	TMR2ON = 1;

	// TMR0 and General interrupt enable
	TMR0IE = 1;
	PEIE = 1;
	GIE = 1;

	uchStartPWM = 0;
	uchDuty[0] = 0;
	uchDuty[1] = 0;
	uchDuty[2] = 0;
	uchDuty[3] = 0;
	uchDuty[4] = 0;
	uchDuty[5] = 0;
	uchDuty[6] = 0;
	uchDuty[7] = 0;


    uchStartPWM = 0xFF;

	uchDuty[0] = 25;  // approx. 10%
	uchDuty[1] = 50;  // approx. 20%
	uchDuty[2] = 75;  // approx. 30%
	uchDuty[3] = 100; // approx. 40%
	uchDuty[4] = 125; // approx. 50%
	uchDuty[5] = 150; // approx. 60%
	uchDuty[6] = 175; // approx. 70%
	uchDuty[7] = 200; // approx. 80%
        
    while(1){
    
    
    
    
    
    
    }
}



// Software PWM made with the comparison between a duty value and Timer2 value

void PWM (void)
{
	if (uchStartPWM & 1 == 1)
	{
		if (uchDuty[0] >= TMR2)
		{
			RB0 = 1;
		} else {
			RB0 = 0;
		}
	}

	if (uchStartPWM & 2 == 0x02)
	{
		if (uchDuty[1] >= TMR2)
		{
			RB1 = 1;
		} else {
			RB1 = 0;
		}
	}

	if (uchStartPWM & 4 == 0x04)
	{
		if (uchDuty[2] >= TMR2)
		{
			RB2 = 1;
		} else {
			RB2 = 0;
		}
	}

	if (uchStartPWM & 0x08 == 8)
	{
		if (uchDuty[3] >= TMR2)
		{
			RB3 = 1;
		} else {
			RB3 = 0;
		}
	}

	if (uchStartPWM & 0x10== 0x10)
	{
		if (uchDuty[4] >= TMR2)
		{
			RB4 = 1;
		} else {
			RB4 = 0;
		}
	}

	if (uchStartPWM & 0x20 == 0x20)
	{
		if (uchDuty[5] >= TMR2)
		{
			RB5 = 1;
		} else {
			RB5 = 0;
		}
	}

	if (uchStartPWM & 0x40 == 0x40)
	{
		if (uchDuty[6] >= TMR2)
		{
			RB6 = 1;
		} else {
			RB6 = 0;
		}
	}

	if (uchStartPWM & 0x80 == 0x80)
	{
		if (uchDuty[7] >= TMR2)
		{
			RB7 = 1;
		} else {
			RB7 = 0;
		}
	}

}

