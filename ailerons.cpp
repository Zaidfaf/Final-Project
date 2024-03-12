//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ailerons.h"
#include "ignition.h"

//=====[Declaration of private defines]========================================

#define PERIOD_SEC              0.02
#define DUTY_MID                0.075

//=====[Declaration and initialization of public global objects]===============

AnalogIn ailerons_control(A2);
PwmOut Servo1(D14);
PwmOut Servo2(D15);

//=====[Declarations (prototypes) of private functions]========================

static float aileronsPotentiometerRead();

//=====[Implementations of public functions]===================================

float aileronsdegrees(){

    return ((ailerons_control.read()-0.5)*100);
}
static float aileronsPotentiometerRead() {//private function, .cpp file
    float angleTarget = 0.075 + (aileronsdegrees()/1850);
    return angleTarget;
}

void aileronsInit(){//public function, .h file
    Servo1.period(PERIOD_SEC);
    Servo1.write(DUTY_MID);
    Servo2.period(PERIOD_SEC);
    Servo2.write(DUTY_MID);
}

void aileronsUpdate(){//public function, .h file
    if (isIgnition()){
        Servo1.write(aileronsPotentiometerRead());
        Servo2.write(aileronsPotentiometerRead());
    }
    else{
        Servo1.write(DUTY_MID);
        Servo2.write(DUTY_MID);
    }
          
}

