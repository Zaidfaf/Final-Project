//=====[#include guards - begin]===============================================

#ifndef _SENSOR_MONITORING_H_
#define _SENSOR_MONITORING_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void sensorMonitoringInit();
void sensorMonitoringUpdate();
float temperatureSensorReadCelsius();
bool gasDetection();
//=====[#include guards - end]=================================================

#endif // _SENSOR_MONITORING_H_