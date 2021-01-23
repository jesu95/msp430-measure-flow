#include "flow.h"

void main(void) {

    volatile float flow = 0.0;                 // Very inefficient. These types of variables should be avoided in a real application.
    volatile uint16_t pulses = 0;

    WDT_A_hold(WDT_A_BASE);                     // Disable watchdog
    flow_initPort();
    Init_LCD();
    PMM_unlockLPM5();                           // Disable the GPIO power-on default high-impedance mode
                                                // to activate previously configured port settings
    while(1)
    {
        flow_resetCount();
        delay_ms(MEASURE_INTERVAL);
        pulses = flow_getPulses();
        flow = pulses;
        flow /= (MEASURE_INTERVAL / 1000);
        flow /= K;
        show_flow(flow);
    }
}
