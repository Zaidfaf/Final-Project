//=====[#include guards - begin]===============================================

#ifndef _AIRPLANE_SYSTEM_H_
#define _AIRPLANE_SYSTEM_H_

//=====[Declaration of public defines]=========================================

// Define the time increment in milliseconds for the system update
#define TIME_INCREMENT_MS   10

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

// Function to initialize the airplane system components
void airplaneSystemInit();

// Function to update the airplane system components periodically
void airplaneSystemUpdate();

//=====[#include guards - end]=================================================

#endif // _AIRPLANE_SYSTEM_H_
