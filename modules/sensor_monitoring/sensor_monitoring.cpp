//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "sensor_monitoring.h"
#include "airplane_system.h"

//=====[Declaration of private defines]========================================

#define LM35_NUMBER_OF_AVG_SAMPLES    10

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn lm35(A1);
DigitalIn gasDetector(PE_12);
DigitalOut alarmLed(LED3);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

float lm35TemperatureC = 0.0;
float lm35ReadingsArray[LM35_NUMBER_OF_AVG_SAMPLES];

//=====[Declarations (prototypes) of private functions]========================

/**
 * @brief Scales an analog reading using the LM35 formula.
 * @param analogReading The raw analog reading.
 * @return The scaled temperature in Celsius.
 */
static float analogReadingScaledWithTheLM35Formula(float analogReading);

//=====[Implementations of public functions]===================================

/**
 * @brief Initializes the sensor monitoring module.
 */
void sensorMonitoringInit()
{
    gasDetector.mode(PullDown);
    alarmLed = OFF;
    int i;

    for (i = 0; i < LM35_NUMBER_OF_AVG_SAMPLES; i++) {
        lm35ReadingsArray[i] = 0;
    }
}

/**
 * @brief Updates the sensor monitoring module, including LM35 temperature readings.
 */
void sensorMonitoringUpdate()
{
    static int lm35SampleIndex = 0;
    float lm35ReadingsSum = 0.0;
    float lm35ReadingsAverage = 0.0;

    int i = 0;

    lm35ReadingsArray[lm35SampleIndex] = lm35.read();
    lm35SampleIndex++;
    if (lm35SampleIndex >= LM35_NUMBER_OF_AVG_SAMPLES) {
        lm35SampleIndex = 0;
    }

    lm35ReadingsSum = 0.0;
    for (i = 0; i < LM35_NUMBER_OF_AVG_SAMPLES; i++) {
        lm35ReadingsSum = lm35ReadingsSum + lm35ReadingsArray[i];
    }
    lm35ReadingsAverage = lm35ReadingsSum / LM35_NUMBER_OF_AVG_SAMPLES;
    lm35TemperatureC = analogReadingScaledWithTheLM35Formula(lm35ReadingsAverage);
}

/**
 * @brief Reads the current temperature from the LM35 sensor in Celsius.
 * @return The current temperature in Celsius.
 */
float temperatureSensorReadCelsius()
{
    return lm35TemperatureC;
}

//=====[Implementations of private functions]==================================

/**
 * @brief Scales an analog reading using the LM35 formula.
 * @param analogReading The raw analog reading.
 * @return The scaled temperature in Celsius.
 */
static float analogReadingScaledWithTheLM35Formula(float analogReading)
{
    return (analogReading * 3.3 / 0.01);
}

/**
 * @brief Checks for gas detection using the gas detector sensor.
 * @return True if gas is detected, false otherwise.
 */
bool gasDetection()
{
    if (gasDetector) {
        alarmLed = ON;
        return true;
    } else {
        alarmLed = OFF;
        return false;
    }
}
