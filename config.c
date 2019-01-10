// Filename: Config
// Version: 1.01
// Date:   <30th June>
// Author: <Sophie O. Ketiku>
//
// Description: Implements a simple multilevel menu system for the user to configure the system. Uses the following
//              controls: RD0 = UP, RD1 = DOWN, RD2 = SELECT

#define _XTAL_FREQ 3276800         // This tells the compiler that the 16F877A  
                                  // __delay_ms macro.
#include <xc.h>                    // Required for all MPLAB XC8 source files
#include "LCDdrive.h"              // Header file needed to access to LCD custom  
                                   // library
#include "set_time.h"
#include "set_alarm.h"


#define MENU1ITEMS 2
#define MENU2ITEMS 2
#define MENU3ITEMS 2
#define MENU4ITEMS 2
#define MENU5ITEMS 2

//########## Function Prototypes ####################################################################################################################//


unsigned char ChkButton(void);
void DoMenu (void);
void DoMenu1 (void);
//void DoMenu2 (void);
//void DoMenu3 (void);
//void DoMenu4 (void);




//######################################### Define strings for menu items (uses const types to store in program memory) ###########################//

const char Menu1Item1[] = "Set Time        ";
const char Menu1Item2[] = "Set Alarm       ";
const char Menu1Item3[] = "Temp Mode       ";

const char Menu2Item1[] = "Set Time        ";
const char Menu2Item2[] = "__:__           ";

const char Menu3Item1[] = "Set Alarm       ";
const char Menu3Item2[] = "__:__           ";

const char Menu4Item1[] = "Centigrade      ";
const char Menu4Item2[] = "Fahrenheit      ";




unsigned char Choice;                                            // Encodes choice as a 2 digit number:
                                                                 // 1st digit = menu no., 2nd digit = item no.
                                                                 // e.g. Menu 3, Item 2 = 32


unsigned char MenuNumber= 1;                                     // Stores current menu
unsigned char MenuItem = 1;                                      // Stores current menu item

void config(void)
{

    DoMenu();

}



//#################################### Function checks RD0, RD1 and RD2. If pressed, updates the menu position ######################################//
//#################################### accordingly and returns a 1, if no button pressed returns 0. ################################################//

unsigned char ChkButton(void)
{
    if (RD0)
    {
        MenuItem--;             // Decrement currently selected menu item (UP)
        return(1);
    }
    if (RD1)
    {
        MenuItem++;               // Increment currently selected menu item (DOWN)
        return(1);
    }
    if (RD2) return(1);

    return(0);
}





//################################# This function carries out the multi-level menu routines. The MenuLevel ##########################################//
//################################# variable controls which menu is being implemented at any time. The while ########################################//
//################################## loops hold the code in a given menu until ######################################################################//


void DoMenu(void)
{
    DoMenu1();
    while(MenuNumber==1)                 // Initialise first menu on LCD
    {
        while(ChkButton()==0);          // Wait for button press
        DoMenu1();                      // Update displayed menu
        __delay_ms(5000);
    }


  /*  DoMenu2();                        // Initialise second menu on LCD
    while(MenuNumber==2)
    {
        while(ChkButton()==0);          // Wait for button press
        DoMenu2();                      // Update displayed menu
        __delay_ms(5000);
    }
    DoMenu3();                          // Initialise third menu on LCD
    while(MenuNumber==3)
    {
        while(ChkButton()==0);          // Wait for button press
        DoMenu3();                      // Update displayed menu
        __delay_ms(5000);
    }
    DoMenu4();                          // Initialise fourth menu on LCD
    while(MenuNumber==4);
    {
        while(ChkButton()==0);          // Wait for button press
        DoMenu4();                      // Update displayed menu
        __delay_ms(5000);
    }*/
}



//################### Code for Executing First Menu ###############################################################################################//
//#################################################################################################################################################//

void DoMenu1(void)
{
    // Bounds Checking
    if (MenuItem==0) MenuItem = 1;
    if (MenuItem > MENU1ITEMS) MenuItem = MENU1ITEMS;

    LCD_clear();

    switch (MenuItem)
    {
        case 1:
          if(RD2)                                                                         //Selection Checking
          {
             //set_time();
              MenuNumber = 2;
              MenuItem = 1;
          }
          LCD_cursor(0,0);
          LCD_putsc("* ");
          LCD_putsc(Menu1Item1);
          LCD_cursor(2,1);
          LCD_putsc(Menu1Item2);
          break;

      case 2:
          if(RD2)                                                                        //Selection Checking
          {
              //set_alarm();
              MenuNumber = 3;
              MenuItem = 1;
           }
          LCD_cursor(2,0);
          LCD_putsc(Menu1Item1);
          LCD_cursor(0,1);
          LCD_putsc("* ");
          LCD_putsc(Menu1Item2);
          break;

       case 3:
          if(RD2)
          {
              MenuNumber = 4;
              MenuItem = 1;
          }
          LCD_cursor(2,0);
          LCD_putsc(Menu1Item2);
          LCD_cursor(0,1);
          LCD_putsc("* ");
          LCD_putsc(Menu1Item3);
          break;

    }
}





//#####################################################################################################################################################//
//################### Code for Executing Second Menu ##################################################################################################//


/*void DoMenu2(void)
{
    // Bounds Checking
    if (MenuItem==0) MenuItem = 1;
    if (MenuItem > MENU2ITEMS) MenuItem = MENU2ITEMS;

    LCD_clear();

    switch (MenuItem)
    {
        case 1:
          if (RD2)
          {
              Choice = 22;
              MenuNumber = 0;
          }
          LCD_cursor(0,0);
          LCD_putsc(Menu2Item1);
          LCD_cursor(2,1);
          LCD_putsc(Menu2Item2);

          break;

    }
}





//################### Code for Executing Third Menu ####################################################################################################//
//######################################################################################################################################################//


 void DoMenu3(void)
 {
 // Bounds Checking
 if (MenuItem==0) MenuItem = 1;
 if (MenuItem>MENU3ITEMS) MenuItem = MENU3ITEMS;

 LCD_clear();

 switch (MenuItem)
 {
 case 1:
 if(RD2)
 {
 Choice = 31;
 MenuNumber = 0;
 }
 LCD_cursor(0,0);
 LCD_putsc(Menu3Item1);
 LCD_cursor(2,1);
 LCD_putsc(Menu3Item2);
 break;
 case 2:
 if(RD2)
 {
 Choice = 32;
 MenuNumber = 0;
 }

 LCD_cursor(2,0);
 LCD_putsc(Menu3Item1);
 LCD_cursor(0,1);
 LCD_putsc("* ");
 LCD_putsc(Menu3Item2);

 break;

 }
 }


//################### Code for Executing Fourth Menu ####################################################################################################//
//######################################################################################################################################################//


 void DoMenu4(void)
 {
 // Bounds Checking
 if (MenuItem==0) MenuItem = 1;
 if (MenuItem>MENU4ITEMS) MenuItem = MENU4ITEMS;

 LCD_clear();

 switch (MenuItem)
 {
 case 1:
 if(RD2)
 {
 Choice = 41;
 MenuNumber = 0;
 }
 LCD_cursor(0,0);
 LCD_putsc("* ");
 LCD_putsc(Menu4Item1);
 LCD_cursor(4,1);
 LCD_putsc(Menu4Item2);
 break;
 case 2:
 if(RD2)
 {
 Choice = 42;
 MenuNumber = 0;
 }

 LCD_cursor(2,0);
 LCD_putsc(Menu4Item1);
 LCD_cursor(0,1);
 LCD_putsc("* ");
 LCD_putsc(Menu4Item2);

 break;

 }
 }

*/






//############################################### Function to display final choice. Decodes the selected item by ####################################//
//############################################### the method described in the Choice variable definition at top of file #############################//


/*void DisplayChoice(unsigned char MyChoice)
 {
if Choice = 21;
  DisplayChoice1();
  DisplayChoice2();

 }



//############################################################ Function to display final choice. #######################################################//

void DisplayChoice1(unsigned char MyChoice)
{
 LCD_clear();
 LCD_putsc("Set Time     ");
 LCD_cursor(0,1);

 switch(MyChoice)
 {
 case 21:
 LCD_putsc(Menu2Item1);
 __delay_ms(5000);
                /*if(RD2)
                 {
                   set_time();
                 } */
 //break;
// }
//}

/*void DisplayChoice2(unsigned char MyChoice)
{
 LCD_clear();
 LCD_putsc("Set Alarm    ");
 LCD_cursor(0,1);

 switch(MyChoice)
 {
 case 21:
 LCD_putsc(Menu2Item1);
 __delay_ms(5000);
                /*if(RD2)
                 {
                   set_alarm();
                 } */
/* break;
 }
}
*
/*void DisplayChoice3(unsigned char MyChoice)
{
 LCD_clear();
 LCD_putsc("Set Time     ");
 LCD_cursor(0,1);

 switch(MyChoice)
 {
 case 21:
 LCD_putsc(Menu2Item1);
 __delay_ms(5000);
                /*if(RD2)
                 {
                   set_alarm();
                 } */
// break;
// }






