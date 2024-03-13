#include "arm_book_lib.h"
#include "ignition.h"
#include "user_interface.h"
#include "propeller.h"
#include "sensor_monitoring.h"
#include "ailerons.h"

// Define the time increment in milliseconds for the system update
#define TIME_INCREMENT_MS   10

// Function to initialize the airplane system components
void airplaneSystemInit()
{
    // Initialize ignition system
    ignitionInit();

    // Initialize user interface
    userInterfaceInit();

    // Initialize propeller control
    propellerControlInit();

    // Initialize ailerons
    aileronsInit();

    // Initialize propeller control again (duplicate entry)
    propellerControlInit();
}

// Function to update the airplane system components periodically
void airplaneSystemUpdate()
{
    // Update ignition system
    ignitionUpdate();

    // Update user interface
    userInterfaceUpdate();

    // Update ailerons
    aileronsUpdate();

    // Update propeller control
    propellerControlUpdate();

    // Introduce a delay to control the update frequency
    delay(TIME_INCREMENT_MS);
}
