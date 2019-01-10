#define _XTAL_FREQ 3276800         // This tells the compiler that the 16F877A  
// __delay_ms macro.
#include <xc.h>                    // Required for all MPLAB XC8 source files
#include "LCDdrive.h"              // Header file needed to access to LCD custom  
                                   // library


// Function prototypes
//void setup(void);
void menu2Item1I(void);
void menu2Item1II(void);
void menu2Item1III(void);
void menu2Item1IV(void);

unsigned int i = 0;

void set_time(void)
{
  //setup();
  while(1)
   {
      menu2Item1I();    //select first digit of time//}
      if (RD2)
        {
           // LCD_clear();
            menu2Item1II();
        }
      if (RD2==1)
        {

            menu2Item1III();
        }
      if (RD2==1)
        {

            menu2Item1IV();
        }
   }
 }

  /* Contains configuration and initialisation routines 
  void setup(void)
  {
    TRISB = 0x00;
    TRISD = 0x07;
    PORTD = 0x00;
    PORTB = 0x00;
    LCD_initialise();
 }*/

void menu2Item1I(void)
  {

      LCD_cursor(0,0);
      LCD_puts("Set Time:       ");
      LCD_cursor(0,1);
      LCD_puts("1_:__           ");

      if (RD0==1)                                  // increment digit to 2
        {
           LCD_cursor(0,1);
           LCD_puts("2_:__           ");        //should never go beyond 2. i.e. 24hr clock
           __delay_ms(9500);
        }
      else if (RD1==1)                                // decrease digit to 1
        {
           LCD_cursor(0,1);
           LCD_puts("1_:__           ");      //should never go beyond 2. i.e. 24hr clock
           __delay_ms(9500);
        }

}


void menu2Item1II(void)
  {
    //int i = 0;

      LCD_cursor(0,0);
      LCD_puts("Set Time:       ");
      for(int i=0; i<9; i++)
      {
         if (RD0==1)
         {
           LCD_cursor(1,1);
           LCD_display_value(i);
         }
      }
      for(int i=0; i<9; i--)
      {
         if (RD1==1)
         {
           LCD_cursor(1,1);
           LCD_display_value(i);
         }
      }



 }

void menu2Item1III(void)
  {

      LCD_cursor(0,0);
      LCD_puts("Set Time:       ");
      LCD_cursor(0,1);
      LCD_puts("13:__        ");
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

 void menu2Item1IV(void)
  {

      LCD_cursor(0,0);
      LCD_puts("Set Time:       ");
      LCD_cursor(0,1);
      LCD_puts("13:4_        ");

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



