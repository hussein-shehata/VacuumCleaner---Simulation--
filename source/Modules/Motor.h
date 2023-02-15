typedef unsigned char tMotorSpeed;
typedef unsigned char tMotorAngle;
typedef unsigned char tTickCounter;

typedef enum 
{
    Soft_Switching,
    Harmonic_Reduction
}Motor_State;

void Motor_init(tMotorSpeed StartSpeed, tByte MotorPin);
void Motor_Update();
void Motor_SetSpeed(tMotorAngle Angle);

