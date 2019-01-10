// Filename: Alarm Mode.c
// Version: 1.0
// Date:    <30th June>
// Author: <Sophie O. Ketiku>
//
// Description: A simple program to produce a repeating sequence on PORTB on a
// PIC16F877A
#define _XTAL_FREQ 3276800	// This tells the compiler that the 16F877A
                                // is clocked at 3.2768 MHz. Required by the
                                // __delay_ms macro.
#include <xc.h>                 // Required for all MPLAB XC8 source files
#include "LCDdrive.h"



void alarmmode(void)
{
	unsigned int i;
	TRISB=0x00; // Make PORTB output
	TRISD=0x10; // Make PORTD output

	PORTD=0x00; // Clear all leds on PORTD
	PORTB=0x00; // Clear all leds on PORTB

	INTCONbits.GIE = 0; // Disable interrupts
	PIE1bits.TMR1IE = 1; // Setup Timer1 interrupt
	PIR1bits.TMR1IF = 0; // Clear Timer1 interrupt flag
	INTCON = 0xC0; // Set GIE & PEIE

    
    
      
   
        //for (i=1; i < 20; i++)
       // {

          if (RD4==1)
          {
          TRISB=0x00;
 	  PORTB=0x00;
          __delay_ms(5000);
          }
          else 
            PORTB=0x80;            // Turn msb on i.e RD7 LED
           // __delay_ms(250);       // Wait 250 msecs
            //PORTB=0x00;            // Turn all bits off
            //__delay_ms(500);       // Wait 500 msecs
        }

    
    

