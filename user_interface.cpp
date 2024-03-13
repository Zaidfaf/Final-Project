//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "user_interface.h"
#include "display.h"
#include "sensor_monitoring.h"
#include "ignition.h"
#include "propeller.h"
#include "ailerons.h"


//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 1000
#define TIME_INCREMENT_INTERFACE_MS 10

//=====[Declarations (prototypes) of private functions]========================

// Enum to represent the different screens on the user interface
typedef enum {
    screen1,
    screen2,
} screenNumber;

float aileronDeg = 0;
static screenNumber ScreenType = screen1;

/**
 * @brief Changes the current screen number based on the state of the displayChange button.
 */
static void getScreenNumber();

/**
 * @brief Initializes the LCD display for the user interface.
 */
static void userInterfaceDisplayInit();

/**
 * @brief Updates the LCD display for the user interface based on the current screen.
 */
static void userInterfaceDisplayUpdate();

//=====[Implementations of public functions]===================================

void userInterfaceInit()
{
    userInterfaceDisplayInit();
}

void userInterfaceUpdate()
{
    userInterfaceDisplayUpdate();
}

//=====[Implementations of private functions]===================================

static void getScreenNumber()
{
    if (displayChange && (ScreenType == screen1)) {
        ScreenType = screen2;
    } else if (displayChange && (ScreenType == screen2)) {
        ScreenType = screen1;
    }
}

static void userInterfaceDisplayInit()
{
    displayInit();
    displayChange.mode(PullDown);
    sensorMonitoringInit();
}

static void userInterfaceDisplayUpdate()
{
    static int accumulatedDisplayTime = 0;
    char temperatureString[3] = "";
    char speedString[4] = "";
    char angleString[3] = "";
    getScreenNumber();
    sensorMonitoringUpdate();

    if (accumulatedDisplayTime >= DISPLAY_REFRESH_TIME_MS) {
        accumulatedDisplayTime = 0;
        if (isIgnition()) {
            switch (ScreenType) {
                case screen1:
                    if (gasDetection()) {
                        displayCharPositionWrite(0, 0);
                        displayStringWrite("     URGENT     ");
                        displayCharPositionWrite(0, 1);
                        displayStringWrite("  GAS DETECTED  ");
                    } else {
                        sprintf(temperatureString, "%.0f", temperatureSensorReadCelsius());
                        displayCharPositionWrite(0, 0);
                        displayStringWrite("Tmp:   ");
                        displayCharPositionWrite(4, 0);
                        displayStringWrite(temperatureString);
                        displayCharPositionWrite(6, 0);
                        displayStringWrite("\xDF");
                        displayCharPositionWrite(7, 0);
                        displayStringWrite("C ");
                        displayCharPositionWrite(9, 0);
                        displayStringWrite("Gas:ND ");
                        displayCharPositionWrite(0, 1);
                        displayStringWrite("Engine Status:ON");
                    }
                    break;
                case screen2:
                    if (gasDetection()) {
                        displayCharPositionWrite(0, 0);
                        displayStringWrite("     URGENT     ");
                        displayCharPositionWrite(0, 1);
                        displayStringWrite("  GAS DETECTED  ");
                    } else {
                        sprintf(speedString, "%.2f", speedtest());
                        displayCharPositionWrite(0, 0);
                        displayStringWrite("Speed:");
                        displayCharPositionWrite(6, 0);
                        displayStringWrite(speedString);
                        displayCharPositionWrite(9, 0);
                        displayStringWrite(" mph  ");

                        if (aileronsdegrees() < 0) {
                            aileronDeg = -aileronsdegrees();
                            displayCharPositionWrite(15, 1);
                            displayStringWrite("E");
                        } else {
                            aileronDeg = aileronsdegrees();
                            displayCharPositionWrite(15, 1);
                            displayStringWrite("W");
                        }
                        sprintf(angleString, "%.1f", aileronDeg);
                        displayCharPositionWrite(0, 1);
                        displayStringWrite("Alr angle:");
                        displayCharPositionWrite(10, 1);
                        displayStringWrite(angleString);
                        displayCharPositionWrite(14, 1);
                        displayStringWrite("\xDF");
                    }
                    break;
            }
        } else {
            displayCharPositionWrite(0, 0);
            displayStringWrite("   Welcome to   ");

            displayCharPositionWrite(0, 1);
            displayStringWrite("  the airplane  ");
        }
    } else {
        accumulatedDisplayTime = accumulatedDisplayTime + TIME_INCREMENT_INTERFACE_MS;
    }
}
