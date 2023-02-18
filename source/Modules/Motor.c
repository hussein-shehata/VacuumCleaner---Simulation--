#include "Motor.h"
#include "Timer.h"


#define SOFT_SWITCHING_TICK_COUNTER             4
#define HARMONIC_REDUCTION_TICK_COUNTER         2
#define START_TARGET_ANGLE                      90


tMotorAngle Current_Angle = 170;
tMotorAngle Target_Angle = 90;
Motor_State Current_State;
Harmonic_Reduction_State Previous_Harmonic_State;

extern tTickCounter Current_Tick_Counter;


void Motor_Init(tMotorAngle StartAngle, tByte MotorPin)
{
    Current_Angle = StartAngle;
    Target_Angle = START_TARGET_ANGLE;

}

void Motor_Update()
{ 
	  
	  TMR5_SetCounter(10);
	  TMR5_Start();
    //TIM2_Start(Current_Angle);
    TMR2_SetCounter(Current_Angle);
    /*Writing the algorithm to determine if we are going to Soft switching state of harmonic reduction state */
    if (Current_Angle != Target_Angle)
    {
        Current_State = Soft_Switching;
    }
    else
    {
        Current_State = Harmonic_Reduction;
    }

    if ((Current_State == Soft_Switching) && (Current_Tick_Counter == SOFT_SWITCHING_TICK_COUNTER))
    {
        Previous_Harmonic_State = Constant;

        if (Target_Angle > Current_Angle)
        {
            Current_Angle = Current_Angle + 1;
        }
        else
        {
            Current_Angle = Current_Angle - 1;
        }
    }


    else if ((Current_State == Harmonic_Reduction) && (Current_Tick_Counter == HARMONIC_REDUCTION_TICK_COUNTER))
    {
        if (Previous_Harmonic_State == Constant) // then it is the first update after the soft switching
        {
            Current_Angle = Current_Angle + 5; // we will start oscilliting around the target angle by increasing it by 5 degrees
            Previous_Harmonic_State = Added_5Degrees;
            Target_Angle = Current_Angle;     // So we can enter the harmonic_Reduction state again
        }
        else if (Previous_Harmonic_State == Added_5Degrees)  // then we had increased the current angle to make it above the target angle by 5 degress
        {
            Current_Angle = Current_Angle - 10;  // so we will decrease the angle by 10 degrees to make it below the target angle by 5 degrees
            Previous_Harmonic_State = Subtracted_5Degrees;
            Target_Angle = Current_Angle;     // So we can enter the harmonic_Reduction state again
        }
        else if(Previous_Harmonic_State == Subtracted_5Degrees)// then we had decreased the current angle to make it below the target angle by 5 degress
        {
            Current_Angle = Current_Angle +10 ; // so we will increase the current angle by 10 to make it above the target angle by 5 degrees
            Previous_Harmonic_State = Added_5Degrees;     
            Target_Angle = Current_Angle;     // So we can enter the harmonic_Reduction state again                      
        }

        else
        {
            // do nothing
        }
    }
			  while(!(TIM5->SR&(1<<0))>>0);
        TIM5->SR &= ~(1<<0);
		    TMR5_Stop();
    

}

void Motor_SetAngle(tMotorAngle Angle)
{
    Target_Angle = Angle;
}