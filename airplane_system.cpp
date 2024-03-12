
#include "arm_book_lib.h"
#include "ignition.h"
#include "user_interface.h"
#include "propeller.h"
#include "sensor_monitoring.h"
#include "ailerons.h"

#define TIME_INCREMENT_MS   10

void airplaneSystemInit()
{
    ignitionInit();
    userInterfaceInit();
    propellerControlInit();
    aileronsInit();
    propellerControlInit();
}

void airplaneSystemUpdate()
{
    ignitionUpdate();
    userInterfaceUpdate();
    aileronsUpdate();
    propellerControlUpdate();
    delay(TIME_INCREMENT_MS);
}
