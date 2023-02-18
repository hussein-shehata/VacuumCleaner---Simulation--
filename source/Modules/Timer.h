#ifndef __TIMER_H__
#define __TIMER_H__

#include "../Main/main.h"
#include "stm32f4xx_ll_tim.h"

#define TMR_TICK_MS				(20)   // HCF(P1, P2, ..., PN)
typedef unsigned char tTickCounter;

void TMR_Init(void);
void TMR_Start(void);
void TMR_Stop(void);
void TMR2_Init(void);
void TMR2_Start(void);
void TMR2_SetCounter(uint8_t angle);
void TMR2_Stop(void);
void SysTick_Handler(void);
void TIM2_IRQHandler(void);

void TMR5_Init(void);
void TMR5_Start(void);
void TMR5_SetCounter(uint8_t wcet);
void TMR5_Stop(void);
void TIM5_IRQHandler(void);
#endif // __TIMER_H__
