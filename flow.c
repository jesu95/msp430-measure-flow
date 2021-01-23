/*
 * yfs201.c
 *
 *  Created on: 16 jul. 2020
 *      Author: Jesús
 */
#include "flow.h"

//********************************************************************************************************************************************************************
// Init the pins and configure the Timer1 as a counter.
void flow_initPort(void)
{
    FLOW_PORT_SEL |= FLOW_PIN_TA1CLK;               // TA1CLK second function module
    TA1CTL |= TACLR;
    TA1CTL |= TASSEL_0 | ID_0 | MC_2 | TAIE;        // TA1CLK to count, continuous mode
}

//********************************************************************************************************************************************************************
// Return the pulses counted by the Timer1.
uint16_t flow_getPulses(void)
{
    return(TA1R);
}

//********************************************************************************************************************************************************************
// Reset the Timer1.
void flow_resetCount(void)
{
    TA1CTL |= TACLR;
}

//********************************************************************************************************************************************************************
void delay_ms(uint16_t ms)
{
    TA0CTL = TACLR;
    TA0CCR0 = ms;
    TA0CCTL0 |= CCIE;
    TA0EX0 = TAIDEX_3;
    TA0CTL = TASSEL_1 + ID_3 + MC_1;
    __bis_SR_register(LPM3_bits + GIE);
}

//**********************************************************************************************************************************************************
void show_flow(float flow)
{
    uint16_t aux;

    aux = flow/10;
    showChar(aux+48,pos1);
    aux=(int16_t)flow % 10;
    showChar(aux+48,pos2);
    LCDMEM[pos2+1] |= 0x01;

    volatile float mantisa = flow - (int16_t)flow;
    volatile uint16_t dosDecimales = mantisa * 100;
    aux=((int)dosDecimales)/10;
    showChar(aux+48,pos3);
    aux=((int)dosDecimales)%10;
    showChar(aux+48,pos4);
}

//********************************************************************************************************************************************************************
// Timer A0 interrupt service routine --> Timer0_A3 CC0
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
    TA0CTL = 0;
    TA0CCTL0 = 0;
    TA0CCR0 = 0;
    TA0EX0 = TAIDEX_0;
    __bic_SR_register_on_exit(LPM3_bits + GIE);
}
