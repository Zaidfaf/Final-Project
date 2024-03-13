//=====[#include guards - begin]===============================================

#ifndef _SENSOR_MONITORING_H_
#define _SENSOR_MONITORING_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes the sensor monitoring module.
 */
void sensorMonitoringInit();

/**
 * @brief Updates the sensor monitoring module, including sensor readings.
 */
void sensorMonitoringUpdate();

/**
 * @brief Reads the current temperature from the sensor in Celsius.
 * @return The current temperature in Celsius.
 */
float temperatureSensorReadCelsius();

/**
 * @brief Checks for gas detection using the gas detector sensor.
 * @return True if gas is detected, false otherwise.
 */
bool gasDetection();

//=====[#include guards - end]=================================================

#endif // _SENSOR_MONITORING_H_
