
#include <msp430.h>
#include <msp430g2553.h>
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set pin 1.0 to output (Green LED)
  P1DIR |= BIT6;                            // Set pin 1.6 to output (Red LED)
  P1IE |=  BIT3;                            // Enable interupt on pin 1.3
  P1IES |= BIT3;                            // Detect falling edge on button press
  P1IFG &= ~BIT3;                           // Clear Flag
  P1OUT |= BIT0;                            // Initialize Green LED as on
  P1OUT &= ~BIT6;                           // Initialize Red LED as off

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

#pragma vector=PORT1_VECTOR                 //Interrupt when flag is triggered aka if button is pressed
__interrupt void Port_1(void)
{
  P1OUT ^= BIT6;                            // Toggle Red LED
  P1OUT ^= BIT0;                            // Toggle Green LED
  P1IFG &= ~BIT3;                           // Clear flag
}
