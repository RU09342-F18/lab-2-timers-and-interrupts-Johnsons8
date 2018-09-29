/////////////////////// Holding down button changes speed of blink ////////////////////

#include <msp430.h>
#include <msp430G2553.h>

/*
 * main.c
 */
int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x01;                            // P1.0 output
  P1DIR |= BIT6;
  P1SEL &= ~(BIT3 | BIT6);
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 50000;
  TACTL = TASSEL_2 + MC_1 + ID_3;                  // SMCLK, upmode
  P1OUT |= BIT0;
  P1OUT &= ~BIT6;
  P1IFG &= ~BIT3;
  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)

{
    int value = P1IN & BIT3;
           if( value == 0){
               CCR0 = 50000;
           }else{
               CCR0 = 15000;

           }
  P1OUT ^= 0x01;                            // Toggle P1.0
  P1OUT ^= BIT6;                            // Toggle P1.6
}

////////////////////////////////////Pressing button turns one light off and the other on (toggles between the two)
//#include <msp430.h>
//#include <msp430G2553.h>
//
///*
// * main.c
// */
//int main(void)
//{
//  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
//  P1DIR |= 0x01;                            // P1.0 output Green LED
//  P1DIR |= BIT6;                            // P1.6 output Red LED
//  P1SEL &= ~(BIT3 | BIT6);
//  CCTL0 = CCIE;                             // CCR0 interrupt enabled
//  CCR0 = 50000;
//  TACTL = TASSEL_2 + MC_1 + ID_3;                  // SMCLK, upmode
//  P1OUT |= BIT0;
//  P1OUT &= ~BIT6;
//  //P1IFG &= ~BIT3;
//  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
//}
//
//// Timer A0 interrupt service routine
//
//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void Timer_A (void)
//{
//
//  P1OUT ^= 0x01;                            // Toggle P1.0
//  P1OUT ^= BIT6;                            // Toggle P1.6
//}
