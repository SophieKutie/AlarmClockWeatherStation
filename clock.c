/*Filename: clock.c
Version: 1.0
Author: Sophie O. Ketiku
Date: 29/3/17
Description: Implementation of an alarm clock to display current time,  relative humidity and temperature . */
#define _XTAL_FREQ 3276800         // This tells the compiler that the 16F877A  
                                   // __delay_ms macro.
#include <xc.h>                    // Required for all MPLAB XC8 source files
#include "LCDdrive.h"              // Header file needed to access to LCD custom  
                                   // library
#include "ADClib.h"
#include "stopwatch.h"
#include "config.h"
#include "set_time.h"
#include "set_alarm.h"
#include "alarmmode.h"

// Function prototypes
 void setup(void);
 void running_mode(void);
 void RH_display(void);
 void temp_display(void);
 void update_display(void);

// File scope (global) variable definitions
unsigned int
elapsed_time = 0,  // Variable to store time elapsed in seconds
counter = 0;

//To store constant strings of Alarm, Relative Humidity and Temperature //
const char Alarm[] = "Alarm: 08:00    ";
const char RH[] = "RH:             ";
const char Temp[] = "Temp:           ";


void main(void)
{
    setup();
    while(1)
    {
        running_mode();
     
    }
  
}


/* Contains configuration and initialisation routines */
 void setup(void)
 {
    INTCONbits.GIE = 0;
    LCD_initialise();                  // Initialise LCD display
    TRISB = 0x00;                      // Set all ports outputs
    TRISD = 0x9F;                      // Set all ports inputs except RD5 and RD6
    PORTB = 0x00;                      // Initialise all ports
    PORTD = 0x00;
    PIE1 = 0x3;                        // Set TMR1IE and TMR2IE bits
    PIR1bits.TMR1IF = 0;               // Clear Timer1 interrupt flag
    //PIR1bits.TMR2IF = 0;
    OPTION_REG = 0x07;                 // Set Timer 0 in timer mode, prescaler=256
    INTCONbits.GIE = 0;                // Clear Interrupt
    INTCONbits.TMR0IE = 1;             // Enable interrupts
    INTCONbits.TMR0IF = 0;
    INTCON = 0xA0;
    TMR0 = 0x38;
        T1CONbits.TMR1ON = 0;        // Turn Timer 1 OFF
        TMR1H = 0xB0;                // Load high byte
        TMR1L = 0x00;                // Load low byte
        T1CONbits.TMR1ON = 1;        // Turn Timer 1 ON
        counter++;


        INTCONbits.RBIE = 1;
}

 void running_mode(void){
        LCD_initialise();             // Initialise LCD
        update_display();             // update clock display to show Time throughout first line of screen
        LCD_cursor(0,1);              // cursor position for item below
        LCD_putsc(Alarm);             // display Alarm time
        stopwatch();                  // run stopwatch for 5 seconds before screen changes
        LCD_cursor(0,1);              // cursor position for second line of screen to display bottom item
        LCD_putsc(RH);                // change current display to show RH
        RH_display();                 // display the value of RH at the right position
        stopwatch();                  // keep running stopwatch for 5s before screen changes
        LCD_cursor(0,1);              // cursor position for second line of screen to display bottom item
        LCD_putsc(Temp); // change current display to show Temperature
        temp_display();               // display the value of temperature next to Temp
        stopwatch();

 }

/* To display Relative Humidity */
void RH_display(void)
{
    LCD_cursor(4, 1); //To place the display of this function at the second line of the LCD
    ADC_channel_select(0);  //To use the LDR as the input for simulating relative humidity
    LCD_display_float(((ADC_read()*0.078) + 10), 1); //To display the output values as decimals which are correct to one decimal place.
    LCD_putch('%');             //Unit for relative humidity
    LCD_putsc("       ");
}

/* To display Temperature */
void temp_display(void)
{
    LCD_cursor(5, 1);      //To place the display of this function at the second line of the LCD
    ADC_channel_select(1); //To use the POT as the input for simulating temperature
    LCD_display_float(((ADC_read()*0.088) - 40), 1); //To display the output values as decimals which are correct to one decimal place.
    LCD_putsc("deg C");             //Unit for temperature
    LCD_putch(' ');
}

//Interrupt to control overflow
void interrupt myISR(void)
{
    if (INTCONbits.TMR0IF)
    {
        if (RD2)
        {
            config();
            
        }
        if (RD3)
          {
            running_mode();
            
          }
        if (RD7)
        {
            alarmmode();
        }
    }
    INTCONbits.TMR0IF = 0; 
	
}
