#include "mbed.h"
#include "arm_book_lib.h"
#include "ailerons.h"
#include "ignition.h"

// Define constants for the servo control
#define PERIOD_SEC              0.02
#define DUTY_MID                0.075

// Initialize AnalogIn and PwmOut objects for aileron control
AnalogIn ailerons_control(A2);
PwmOut Servo1(D14);
PwmOut Servo2(D15);

// Private function to read the ailerons potentiometer value
static float aileronsPotentiometerRead();

// Public function to calculate and return aileron angle in degrees
float aileronsdegrees() {
    return ((ailerons_control.read() - 0.5) * 100);
}

// Private function to convert aileron angle to servo duty cycle
static float aileronsPotentiometerRead() {
    float angleTarget = DUTY_MID + (aileronsdegrees() / 1850);
    return angleTarget;
}

// Public function to initialize aileron servo control
void aileronsInit() {
    Servo1.period(PERIOD_SEC);
    Servo1.write(DUTY_MID);
    Servo2.period(PERIOD_SEC);
    Servo2.write(DUTY_MID);
}

// Public function to update aileron servo positions based on ignition status
void aileronsUpdate() {
    // Check if ignition is active
    if (isIgnition()) {
        // Update servo positions based on aileronsPotentiometerRead()
        Servo1.write(aileronsPotentiometerRead());
        Servo2.write(aileronsPotentiometerRead());
    } else {
        // Set servo positions to mid-duty cycle if ignition is not active
        Servo1.write(DUTY_MID);
        Servo2.write(DUTY_MID);
    }
}
