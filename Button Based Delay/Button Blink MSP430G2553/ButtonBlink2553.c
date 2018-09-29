//#include <msp430.h>
//#include <msp430G2553.h>
//
///*
// * main.c
// */
//
//void main(void)
//{
//    WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
//
//            P1REN |= 0x08;                          //Turn on PullUp on????? How do you turn it off?
//
//            P1DIR &= ~BIT3;                         // Push Port 1 P1.3 (push button) as input
//            P1REN &= ~0x08;                         // Pull down resistor???
//            P1DIR |= BIT0;
//            P1DIR |= BIT6; // Set P1.6 (LED) to output direction
//            P1SEL &= ~(BIT3 | BIT6);                // Select Port 1 P1.3 (push button)
//
//            P1OUT |= BIT0;
//            P1OUT &= ~BIT6;   // Set the LED off
//
//
//            while( 1 ) {
//                int value = P1IN & BIT3;
//                    if( value == 0){         // Push button down when bit 3 == 0
//                            P1OUT |= BIT6;          // Set LED on when button down
//                            P1OUT &= ~BIT0;
//            }else{
//                            P1OUT &= ~BIT6;         // Set LED off when button off
//                            P1OUT |= BIT0;
//            }
//
//
//            }
//} // CCR0_ISR
/**
 * main.c
 */
#include <msp430.h>
#include <msp430g2553.h>
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set pin 1.0 to output
  P1DIR |= BIT6;                            // Set pin 1.6 to output
  P1IE |=  BIT3;                            // Enable interupt on pin 1.3
  P1IES |= BIT3;                            // Detect falling edge on button press
  P1IFG &= ~BIT3;                           // Clear Flag
  P1OUT |= BIT0;                            // Initialize Green LED as on
  P1OUT &= ~BIT6;                           // Initialize Red LED as off

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  P1OUT ^= BIT6;                            // Toggle Red LED
  P1OUT ^= BIT0;                            // Toggle Green LED
  P1IFG &= ~BIT3;                           // Clear flag
}
