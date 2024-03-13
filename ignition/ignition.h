//=====[#include guards - begin]===============================================

#ifndef _IGNITION_H_
#define _IGNITION_H_

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes the ignition module.
 */
void ignitionInit();

/**
 * @brief Updates the ignition module.
 */
void ignitionUpdate();

/**
 * @brief Checks if the ignition is currently ON.
 * @return true if ignition is ON, false otherwise.
 */
bool isIgnition();

//=====[#include guards - end]=================================================

#endif // _IGNITION_H_
