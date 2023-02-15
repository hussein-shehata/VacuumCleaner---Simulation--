#include "../Main/main.h"
#include "../Modules/SW.h"
#include "../Modules/Timer.h"
#include "../Modules/Display.h"
#include "../Modules/Led.h"
#include "../Modules/VC.h"
#include "../Modules/Motor.h"
#include "stdio.h"

///Oscilloscope should monitor C6 and C7 channels

int main(void)
{
    /* Initialization */
   
   printf("Vacuum Cleaner is starting ...\n");
   
    SW_Init();
    DISP_Init();
    VC_Init();
    Motor_Init();

    //Initialize the timer and start it
    TMR_Init();
    TMR_Start();

    while (1)
    {
      // Sleep
      __WFI();
    }

    return 0;
}

