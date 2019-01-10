 /* Stopwatch.c
  Version: 1.0
  Author: Sophie O. Ketiku
  Date: 29/3/17
  Description: Implementation of the stopwatch exercise from Lab 6
  */
  #include <xc.h>
  #include "LCDdrive.h"

 // Function prototypes
 void setup(void);
 void tmr1_delay(unsigned char);
 void update_display(void);

  // File scope (global) variable definitions
  unsigned int elapsed_time = 0; // Variable to store time elapsed in seconds
  
  void stopwatch(void)
  {
  setup();
  while(1)
  {
  tmr1_delay(1); // Wait for one second
  elapsed_time++; // increase elapsed time
  update_display(); // Update display with current time
  }
  }

  /* Contains configuration and initialisation routines */
  void setup(void)
  {
  LCD_initialise(); // Initialise LCD display
  TRISB = 0x00; // Set all ports outputs except RD0 & RD1
  TRISD = 0x03;
  PORTB = 0x00; // Initialise all ports
  PORTD = 0x00;
  OPTION_REG = 0x07; // Set Timer 0 in timer mode, prescaler=256
  INTCON = 0x20; // Setup TMR0 interrupt ONLY
  INTCONbits.GIE = 1; // Enable interrupts
  }

  /* Generic delay function using Timer 1 */
  void tmr1_delay (unsigned char delay)
  {
  unsigned int x; // Define variable for loop index
  T1CON = 0x30; // Set prescaler to 1:8
  for (x=0; x < 2*delay; x++) // Setup delay loop
  {
  PIR1bits.TMR1IF = 0; // Clear interrupt flag

  T1CONbits.TMR1ON = 0;
  TMR1H = 0x38; // Load High byte
  TMR1L = 0x00; // Load low byte
  T1CONbits.TMR1ON = 1;
  while(!PIR1bits.TMR1IF); // Wait for overflow (500 ms)

  }
  }

  /* Function updates the display with minutes:seconds */
  void update_display(void)
  {
  // Local variables for displaying digits
  unsigned char hours, minutes, seconds;

  // Calculate minutes and second from elapsed time
  hours = (elapsed_time / 3600) % 24;
  minutes = (elapsed_time / 60) % 60; //Calculate total minutes elapsed
  seconds = elapsed_time % 60; //Calculate total second remaining

  // Display routine
  LCD_cursor(0,0);
  if(hours<10) LCD_putch('0'); // Add leading zero for single digit values
  LCD_display_value(hours);
  LCD_putch(':');
  if(minutes<10) LCD_putch('0'); // Add leading zero for single digit values
  LCD_display_value(minutes);
  LCD_putch(':');
  if(seconds<10) LCD_putch('0'); // Add leading zero for single digit values
  LCD_display_value(seconds);
  }

  /* Interrupt service routine - services TMR0 overflow ONLY
 89 RD0 and RD1 are polled every 80 ms and the mode variable is updated
 90 if the button has been pressed. */

 void interrupt myISR(void)
 {
  if(TMR0IF) // Check whether TMR0 interrupt occurred
  {
   INTCONbits.T0IF = 0; // Reset TMR0 interrupt flag
  }
 }
