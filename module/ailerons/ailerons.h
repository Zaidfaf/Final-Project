//=====[#include guards - begin]===============================================

#ifndef _AILERONS_H_
#define _AILERONS_H_

//=====[Declaration of public defines]=========================================

// Define the time increment in milliseconds for ailerons update
#define TIME_INCREMENT_MS   10

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

// Function to initialize aileron control
void aileronsInit();

// Function to update aileron control based on ignition status
void aileronsUpdate();

// Function to calculate and return the aileron angle in degrees
float aileronsdegrees();

//=====[#include guards - end]=================================================

#endif // _AILERONS_H_
