#include "../Main/main.h"
#include "../Modules/Timer.h"
#include "../Modules/SW.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "stm32f4xx_ll_tim.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"


LL_TIM_InitTypeDef TIM2_Config = {0, LL_TIM_COUNTERMODE_UP, 0, LL_TIM_CLOCKDIVISION_DIV1, 0};
LL_TIM_InitTypeDef TIM5_Config = {0, LL_TIM_COUNTERMODE_UP, 0, LL_TIM_CLOCKDIVISION_DIV1, 0};

// For debugging only (For logic analyzer)
volatile uint32_t tick = 0;
volatile uint32_t fire = 0;
tTickCounter Current_Tick_Counter = 0;

void TMR_Init(void)
{
   // System clock frequency = 16MHz
   // Tick Period = 1ms
   SysTick_Config(16*TMR_TICK_MS*1000);
   TMR_Stop();
}
void TMR_Start(void)
{
   SysTick->CTRL |= (0x03);
}

void TMR_Stop(void)
{
   SysTick->CTRL &= ~(0x03);
}

void TMR2_Init()
{
		RCC->APB1ENR |= (1<<0);
		NVIC_EnableIRQ(TIM2_IRQn);
	
		LL_TIM_Init(TIM2, &TIM2_Config);
		TIM2->DIER |= (1<<0);
		//TIM2->CR1 |= (1<<7);
		//TIM2->CNT = 1000;	
}

void TMR2_SetCounter(uint8_t angle)
{
	// 180 ---> 0
	// 10  ---> 0
	uint8_t time = angle * ((float)10/180);
	LL_TIM_SetAutoReload(TIM2, time);
	TIM2->CNT = 0;
	
}
void TMR2_Start(void)
{
	// angle logic first
	LL_TIM_EnableCounter(TIM2);
	
}

void TMR2_Stop()
{
	LL_TIM_DisableCounter(TIM2);
	
}
void SysTick_Handler(void)
{
   // For debugging only (For logic analyzer)
   tick ^= 1;
   Current_Tick_Counter++;
   // Do nothing
   // It is made only to wake the cpu up

   //Tasks required 
   	SW_Update();
	/* sandwiching VC_Update*/
	TMR5_SetCounter(2);
    TMR5_Start();
	VC_Update();
	while(!(((TIM5->SR)&(1<<0))>>0));
    TIM5->SR &= ~(1<<0);
    TMR5_Stop();


	/* sandwiching Motor_Update*/
	TMR5_SetCounter(2);
    TMR5_Start();
  	Motor_Update();
	while(!(((TIM5->SR)&(1<<0))>>0));
    TIM5->SR &= ~(1<<0);
    TMR5_Stop();

	TMR5_SetCounter(1);
    TMR5_Start();;
  	DISP_Update();
	while(!(((TIM5->SR)&(1<<0))>>0));
    TIM5->SR &= ~(1<<0);
    TMR5_Stop();

}

void TIM2_IRQHandler(void)
{
	//tick ^= 1;
	fire ^= 1;
	TIM2->SR &= ~(1<<0);
}

void TMR5_Init()
{
		RCC->APB1ENR |= (1<<3);
	  NVIC_EnableIRQ(TIM5_IRQn);
		LL_TIM_Init(TIM5, &TIM5_Config);
	  TIM5->DIER |= (1<<0);
}

void TMR5_SetCounter(uint8_t wcet)
{
	LL_TIM_SetAutoReload(TIM5, wcet);
	TIM5->CNT = 0;
	
}
void TMR5_Start(void)
{
	// angle logic first
	LL_TIM_EnableCounter(TIM5);
	
}

void TMR5_Stop()
{
	LL_TIM_DisableCounter(TIM5);
	
}
