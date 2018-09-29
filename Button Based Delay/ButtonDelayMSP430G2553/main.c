#include <msp430.h> 
#include <msp430g2553.h>
volatile unsigned int TC1 = 0;                  // Timer set initialized to 0
int main(void)
{
WDTCTL = WDTPW | WDTHOLD;                       // Disable the watchdog timer
BCSCTL3 = LFXT1S_2;                             // Enables internal oscillator (This wasn't relavent before but yeah Dr. Google is my boi)
P1DIR |= BIT0;                                  // Set P1.0 to output (green LED)
P1REN |= BIT3;                                  // Enable internal resistor (Still don't really know how this actually works)
P1OUT |= BIT3;                                  // Enable Pull-up Resistor (Don't actually know what this is but its what Dr. Google does)
P1IE |= BIT3;                                   // Set P1.3 (button) as interrupt pin
P1IES |= BIT3;                                  // Set P1.3 to interrupt on falling edge
TACCTL0 = CCIE;                                 // Capture Compare Interrupt Enabled
TACCR0 = 100;                                   // Set Register
TACTL = TASSEL_1 + MC_1 + ID_3;                 // Timer A Control: ACLK, Up Mode, Internal Divider
__enable_interrupt();                           // Enables interrupt algorithm
for(;;){};                                      // Continuous loop (lets program run and only on interrupts will it change anything)
}
#pragma vector=TIMER0_A0_VECTOR                 // This interrupt is based off TIMER A and blinks the light at the given interval
__interrupt void Timer_A(void)
{
P1OUT ^= BIT0;                                  // Toggle P1.0 (Green LED)
}
#pragma vector = PORT1_VECTOR                   // Interrupt for button presses
__interrupt void Port_1(void)
{
if(P1IES & BIT3){                               // Interrupt falling Edge
TACTL = TACLR;                                  // Clear Timer
TACTL = TASSEL_1 + MC_2 + ID_3;                 // Timer A Control: ACLK, Continuous mode, Internal Divider
P1IES &= ~BIT3;                                 // Set Rising Edge interrupt
}
else{
TACCR0 = TA0R;                                  // Sets register
TACTL = TASSEL_1 + MC_1 +ID_3;                  // Timer A Control: ACLK, Up mode, Internal Divider
P1IES |= BIT3;                                  // Set Falling Edge Interrupt
}
P1IFG &= ~BIT3;                                 // Resets interrupt flag for P1.3
}
