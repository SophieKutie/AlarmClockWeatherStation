
// Filename: Set Alarm
// Version: 1.0
// Date:   <30th June>
// Author: <Sophie O. Ketiku>
//
// Description: Simple demonstration of the LCD custom library functions

#define _XTAL_FREQ 3276800         // This tells the compiler that the 16F877A
                                   // __delay_ms macro.
#include <xc.h>                    // Required for all MPLAB XC8 source files
#include "LCDdrive.h"              // Header file needed to access to LCD custom
                                   // library
#include "config.h"


// Function prototypes
void setup(void);
void menu2ItemI(void);
void menu2ItemII(void);
void menu2ItemIII(void);
void menu2ItemIV(void);

unsigned int i = 0;

void set_alarm(void)
{
  //setup();
 
      menu2ItemI();                        //set first digit of time to be set//}
      if (RD2)
        {
           // LCD_clear();
            menu2ItemII();
        }
      if (RD2==1)
        {

            menu2ItemIII();
        }
      if (RD2==1)
        {

            menu2ItemIV();
        }
  
 }

  /* Contains configuration and initialisation routines 
  void setup(void)
  {
    TRISB = 0x00;                             // Set all PORTB as output (for LCD)
    TRISD = 0x07;                             // Set RD0:2 as input for menu control
    PORTD = 0x00;
    PORTB = 0x00;
    LCD_initialise();
 }
*/


void menu2ItemI(void)
  {
      if (RD3==1)
      {
          main();
      }
      LCD_cursor(0,0);
      LCD_puts("Set Alarm:      ");
      LCD_cursor(0,1);
      LCD_puts("0_:__           ");

      if (RD0==1)                             //increment digit to 2
        {
           LCD_cursor(0,1);
           LCD_puts("2_:__           ");      //should never go beyond 2. i.e. 24hr clock
           __delay_ms(9500);
        }
      else if (RD1==1)                        //decrease digit to 1
        {
           LCD_cursor(0,1);
           LCD_puts("1_:__           ");      //should never go beyond 2. i.e. 24hr clock
           __delay_ms(9500);
        }

}


void menu2ItemII(void)
  {
    //int i = 0;
      if (RD3==1)
      {
          main();
      }

      LCD_cursor(0,0);
      LCD_puts("Set Alarm:      ");
      for(int i=0; i<9; i++)
      {
         if (RD0==1)
         {
           LCD_cursor(1,1);
           LCD_display_value(i);
         }
      }
      for(int i=0; i<9; i--);
      {
         if (RD1==1)
         {
           LCD_cursor(1,1);
           LCD_display_value(i);
         }
      }
 }

void menu2ItemIII(void)
  {
      if (RD3==1)
      {
          main();
      }
      LCD_cursor(0,0);
      LCD_puts("Set Alarm:      ");
      LCD_cursor(0,1);
      LCD_puts("08:__           ");
      for(int i=0; i<9; i++)
      {
         if (RD0)
         {
           LCD_cursor(3,1);
           LCD_display_value(i);
         }
      }
      for(int i=0; i<9; i--)
      {
         if (RD1)
         {
           LCD_cursor(3,1);
           LCD_display_value(i);
         }
      }
 }

 void menu2ItemIV(void)
  {
      if (RD3==1)
      {
          main();
      }
      LCD_cursor(0,0);
      LCD_puts("Set Alarm:      ");
      LCD_cursor(0,1);
      LCD_puts("08:3_           ");

      for(int i=0; i<9; i++)
      {
         if (RD0)
         {
           LCD_cursor(4,1);
           LCD_display_value(i);
         }
      }
      for(int i=0; i<9; i--)
      {
         if (RD1)
         {
           LCD_cursor(4,1);
           LCD_display_value(i);
         }
      }
 }