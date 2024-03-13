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
*/

//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "ignition.h"

#define DEBOUNCE_BUTTON_TIME_MS                 40
#define TIME_INCREMENT_IGNITION_MS              10

//=====[Declaration of private data types]=====================================

typedef enum {
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_FALLING,
    BUTTON_RISING
} buttonState_t;

//=====[Declaration and initialization of private global objects]===============
DigitalIn switch_1(PA_5);
DigitalIn switch_2(D12);
DigitalIn switch_3(D11);
DigitalIn switch_4(D10);
DigitalIn ignitionButton(BUTTON1);

DigitalOut ignitionLed(LED2);
DigitalOut alarmLed1(LED1);
DigitalOut incorrectCodeLed(LED3);

//=====[Declaration and initialization of public global objects]===============



//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]=============

int accumulatedDebounceButtonTime = 0;
buttonState_t ignitionButtonState;

//=====[Declarations (prototypes) of private functions]=========================

void debounceButtonInit();

bool debounceButtonUpdate();


//=====[Implementations of public functions]===================================

/**
 * @brief Initializes the ignition system.
 */
void ignitionInit() 
{
    // Set the pull-down mode for input switches
    switch_1.mode(PullDown);
    switch_2.mode(PullDown);
    switch_3.mode(PullDown);
    switch_4.mode(PullDown);
    ignitionButton.mode(PullDown);
    
    // Initialize the button debounce mechanism
    debounceButtonInit();
}

/**
 * @brief Updates the ignition system state based on button events and switch positions.
 */
void ignitionUpdate() {
    // Check for a released ignition button event with debouncing
    bool enterButtonReleasedEvent = debounceButtonUpdate();

    // Toggle the ignition LED based on button and switch conditions
    if (ignitionLed.read()) {
        if (enterButtonReleasedEvent) {
            ignitionLed = OFF;
        }
    } else {
        if (switch_1 && switch_2 && switch_3 && switch_4 && enterButtonReleasedEvent) {
            ignitionLed = ON;
        }
    }
}

/**
 * @brief Checks if the ignition is currently ON.
 * @return true if ignition is ON, false otherwise.
 */
bool isIgnition()
{
    return ignitionLed.read() == ON;
}

//=====[Implementations of private functions]===================================

/**
 * @brief Initializes the button debounce mechanism.
 */
void debounceButtonInit()
{
    // Determine the initial state of the ignition button
    if( ignitionButton == 1) {
        ignitionButtonState = BUTTON_UP;
    } else {
        ignitionButtonState = BUTTON_DOWN;
    }
}

/**
 * @brief Updates the button debounce mechanism and detects button release events.
 * @return true if an ignition button release event occurred, false otherwise.
 */
bool debounceButtonUpdate()
{
    // Flag for ignition button release event
    bool ignitionButtonReleasedEvent = false;

    // State machine for button debouncing
    switch( ignitionButtonState ) {

    case BUTTON_UP:
        if( ignitionButton == 0 ) {
            ignitionButtonState = BUTTON_FALLING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_FALLING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( ignitionButton == 0 ) {
                ignitionButtonState = BUTTON_DOWN;
            } else {
                ignitionButtonState = BUTTON_UP;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_IGNITION_MS;
        break;

    case BUTTON_DOWN:
        if( ignitionButton == 1 ) {
            ignitionButtonState = BUTTON_RISING;
            accumulatedDebounceButtonTime = 0;
        }
        break;

    case BUTTON_RISING:
        if( accumulatedDebounceButtonTime >= DEBOUNCE_BUTTON_TIME_MS ) {
            if( ignitionButton == 1 ) {
                ignitionButtonState = BUTTON_UP;
                ignitionButtonReleasedEvent = true;
            } else {
                ignitionButtonState = BUTTON_DOWN;
            }
        }
        accumulatedDebounceButtonTime = accumulatedDebounceButtonTime +
                                        TIME_INCREMENT_IGNITION_MS;
        break;

    default:
        // If an unexpected state occurs, reinitialize the button debounce
        debounceButtonInit();
        break;
    }

    return ignitionButtonReleasedEvent;
}
