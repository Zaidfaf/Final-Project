//=====[#include guards - begin]===============================================

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

//=====[Declarations (prototypes) of public functions]=========================

/**
 * @brief Initializes the LCD display.
 */
void displayInit( void );

/**
 * @brief Changes the location of the LCD's "cursor" to a given x and y.
 * @param charPositionX The x-coordinate of the character position.
 * @param charPositionY The y-coordinate of the character position.
 */
void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY );

/**
 * @brief Writes a string to the LCD display.
 * @param str The string to be written to the display.
 */
void displayStringWrite( const char * str );

//=====[#include guards - end]=================================================

#endif // _DISPLAY_H_
