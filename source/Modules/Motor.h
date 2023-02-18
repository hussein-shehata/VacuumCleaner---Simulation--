typedef unsigned char tMotorSpeed;
typedef unsigned char tMotorAngle;


/* Standard data types */
typedef unsigned char tByte;
typedef unsigned int tWord;
typedef unsigned long int tDWORD;

typedef enum 
{
    Soft_Switching,
    Harmonic_Reduction
}Motor_State;

typedef enum
{
    Added_5Degrees,
    Subtracted_5Degrees,
    Constant
}Harmonic_Reduction_State;


void Motor_Init(tMotorSpeed StartSpeed, tByte MotorPin);
void Motor_Update();
void Motor_SetAngle(tMotorAngle Angle);

