//=====[#include guards - begin]===============================================

#ifndef _PROPELLER_H_
#define _PROPELLER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

/**
 * @brief Enumeration representing motor directions.
 */
typedef enum {
    DIRECTION_1, /**< Motor direction 1. */
    DIRECTION_2, /**< Motor direction 2. */
    STOPPED      /**< Motor stopped. */
} motorDirection_t;

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes the propeller control module.
 */
void propellerControlInit();

/**
 * @brief Writes the desired direction for the propeller.
 * @param direction The desired direction to set for the propeller.
 */
void propellerDirectionWrite(motorDirection_t direction);

/**
 * @brief Reads the current direction of the propeller.
 * @return The current direction of the propeller.
 */
motorDirection_t propellerDirectionRead();

/**
 * @brief Updates the propeller control module, adjusting the motor state and direction.
 */
void propellerControlUpdate();

/**
 * @brief Calculates the speed based on the analog input value.
 * @return The calculated speed value.
 */
float speedtest();

//=====[#include guards - end]=================================================

#endif // _PROPELLER_H_
