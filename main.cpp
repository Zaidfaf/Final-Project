//=====[Libraries]=============================================================

#include "airplane_system.h"

//=====[Main function, the program entry point after power on or reset]========

/**
 * @brief The main function, the program entry point after power on or reset.
 * @return The exit status of the program.
 */
int main()
{
    // Initialize the airplane system components
    airplaneSystemInit();

    // Main program loop to continuously update the airplane system
    while (true) {
        airplaneSystemUpdate();
    }

}
