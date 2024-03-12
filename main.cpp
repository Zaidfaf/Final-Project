//=====[Libraries]=============================================================

#include "airplane_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    airplaneSystemInit();
    while (true) {
        airplaneSystemUpdate();
    }
}
