#include "Motor.h"



#define SOFT_SWITCHING_TICK_COUNTER             4
#define HARMONIC_REDUCTION_TICK_COUNTER         2


tMotorAngle Current_Angle = 170;
tMotorAngle Target_Angle = 90;
Motor_State Current_State;

tTickCounter Current_Tick_Counter = 0;


void Motor_init(tMotorSpeed StartSpeed, tByte MotorPin)
{
    Current_Angle = StartSpeed;
    Target_Angle = 90;

}

void Motor_Update()
{ 
    TIM2_Start(Current_Angle);
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
        if (Target_Angle == Current_Angle + 5) //then we have increased the Angle by 5 degrees in previous update 
        {
            Current_Angle = Current_Angle -10; // so we will decrease the angle by 10 degrees to make it below the target angle by 5 degrees
        }
        else if (Target_Angle == Current_Angle) // then it is the first update after the soft switching
        {
            Current_Angle = Current_Angle + 5; // we will start oscilliting around the target angle by increasing it by 5 degrees
        }
        else 
        {
            Current_Angle = Current_Angle +10 ; // then we had decreased the current angle to make it below the target angle by 5 degress
                                                // so we will increase the current angle by 10 to make it above the target angle by 5 degrees
        }
    }

    

}

void Motor_SetSpeed(tMotorAngle Angle)
{
    Target_Angle = Angle;
}