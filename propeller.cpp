//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "propeller.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

#define MOTOR_UPDATE_TIME 9

//=====[Declaration of private data types]=====================================

typedef enum {
    DIRECTION_1,
    DIRECTION_2,
    STOPPED
} motorDirection_t;

motorDirection_t motorDirection;
motorDirection_t motorState;

//=====[Declaration and initialization of public global objects]===============

AnalogIn speedControl(A0);
DigitalInOut motorM1Pin(PF_2);
DigitalInOut motorM2Pin(PE_3);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static motorDirection_t propellerDirectionRead();
static void propellerDirectionWrite(motorDirection_t direction);

//=====[Implementations of public functions]===================================

void propellerControlInit()
{
    motorM1Pin.mode(OpenDrain);
    motorM2Pin.mode(OpenDrain);
    
    motorM1Pin.input();
    motorM2Pin.input();

    motorDirection = STOPPED;
    motorState = STOPPED;
}

float speedtest() {
    if (speedControl.read()> 0.5){
        return (speedControl.read() - 0.4)*1000;
    }
    else{
        return 0.0;
    }
}

void propellerControlUpdate()
{   

        if ((speedControl.read() > 0.5)&& isIgnition())  {
            propellerDirectionWrite(STOPPED);
        } else {
            propellerDirectionWrite(DIRECTION_1);
        }
        
        static int motorUpdateCounter = 0;
        motorUpdateCounter++;
        
        if (motorUpdateCounter > MOTOR_UPDATE_TIME) {
        motorUpdateCounter = 0;
        
        switch (motorState) {
            case DIRECTION_1:
                if (motorDirection != DIRECTION_1) {
                    motorM1Pin.input();
                    motorM2Pin.input();
                    motorState = STOPPED;
                }
                break;
    
            case STOPPED:
            default:
                if (motorDirection == DIRECTION_1) {
                    motorM2Pin.input();
                    motorM1Pin.output();
                    motorM1Pin = LOW;
                    motorState = DIRECTION_1;
                }
                break;
        }
    }        
            
        
}

//=====[Implementations of private functions]==================================

static motorDirection_t propellerDirectionRead()
{
    return motorDirection;
}

static void propellerDirectionWrite(motorDirection_t direction)
{
    motorDirection = direction;
}
