/*
 * yfs201.h
 *
 *  Created on: 16 jul. 2020
 *      Author: Jes�s
 */

#ifndef FLOW_H_
#define FLOW_H_

//********************************************************************************************************************************************************************
#include "driverlib.h"
#include "hal_LCD.h"

//********************************************************************************************************************************************************************
// Defines to configure pins
#define FLOW_PORT_SEL     P8SEL0
#define FLOW_PIN_TA1CLK   BIT2

//********************************************************************************************************************************************************************
// Conversion factor K between frequency (Hz) and flow (L / min)
#define K   7.5         // YF-S201
//#define K   5.5       // FS300A
//#define K   7.5       // FS400A

//********************************************************************************************************************************************************************
// Pulse measurement time interval (ms)
#define MEASURE_INTERVAL    1000

//********************************************************************************************************************************************************************
// Function prototypes
void flow_initPort(void);
uint16_t flow_getPulses(void);
void flow_resetCount(void);
void delay_ms(uint16_t);
void show_flow(float);

#endif /* FLOW_H_ */
