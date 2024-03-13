//=====[#include guards - begin]===============================================

#ifndef _PROPELLER_H_
#define _PROPELLER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
    DIRECTION_1,
    DIRECTION_2,
    STOPPED
} motorDirection_t;

//=====[Declarations (prototypes) of public functions]=========================

void propellerControlInit();
void propellerControlUpdate();
float speedtest();

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_
