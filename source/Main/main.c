#include "../Main/main.h"
#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"
#include "stdio.h"

///Oscilloscope should monitor C6 and C7 channels
#define START_TARGET_ANGLE                      90
#define MOTOR_PIN                               6
int main(void)
{
    /* Initialization */
   
   printf("Vacuum Cleaner is starting ...\n");

    SW_Init();
    DISP_Init();
    VC_Init();
    Motor_Init(START_TARGET_ANGLE, MOTOR_PIN);

    //Initialize the timer and start it
    TMR_Init();
    TMR_Start();
		
		TMR2_Init();
		// TMR2_SetCounter(90);
		// TMR2_Start();
	
		TMR5_Init();
		
    while (1)
    {
      // Sleep
      __WFI();
    }

    return 0;
}

