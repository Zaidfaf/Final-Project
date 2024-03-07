/*! @mainpage Example 1.5 Modularized and with doxygen comments
* @date Friday, January 29, 2021
* @authors Pablo Gomez, Ariel Lutenberg and Eric Pernia
* @section genDesc General Description
*
* This is a preliminary implementation of the smart home system, where the
* code has been modularized using functions and documented using Doxygen.
* The entry point to the program documentation can be found at
* this \ref Example_1_5_Modularized_withDoxygenComments.cpp "link"
*
* @section genRem General Remarks
* [Write here relevant information about the program]
*
* @section changelog Changelog
*
* | Date | Description |
* |:----------:|:-----------------------------------------------|
* | 01/14/2024 | First version of program |
*
*
*/

//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ailerons.h"

#define DUTY_OFF 0.075
#define TIME_PERIOD 0.02

//=====[Declaration and initialization of public global objects]===============

AnalogIn ailerons_control(A2);
PwmOut Servo1(PF_7);
PwmOut Servo2(PG_1);


//=====[Declaration and initialization of public global variables]=============

float servo_angle = 0;
float target_angle = 0;


//=====[Declarations (prototypes) of public functions]=========================

//Implementation of global functions

void aileronsInit() 
{
    Servo1.period(TIME_PERIOD);
    Servo1.write(DUTY_OFF);
    Servo2.period(TIME_PERIOD);
    Servo2.write(DUTY_OFF);
}


void aileronsUpdate() 
{
    servo_angle = (ailerons_control.read() - 0.5) * 100;
    target_angle = DUTY_OFF + (servo_angle)/1850;
    Servo1.write(target_angle);
    Servo2.write(target_angle);
}

float servoAngle(){
    return ((ailerons_control.read() - 0.5) * 100);
}