#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>

#define OPTO_1                    14
#define OPTO_2                    16
#define OPTO_3                    17
#define OPTO_4                    18
#define OPTO_5                    19
#define OPTO_6                    21
#define OPTO_7                    22
#define OPTO_8                    23

#define LED_POWER                 15  // The pin that is used to control the power for the input LEDs

#define NUMBER_OF_INPUTS          8
 
/**
 * Set the opto pins into the correct mode.
 */
void init_inputs();

/**
 * Checks the opto states and sets the input LEDs accordingly.
 * 
 * Call this regularly or the input LEDs will not light up to
 * show the input states!
 */
void do_inputs();

/**
 * Read the input states and place them in the passed buffer.
 * 
 * Onus is on the user to make sure that the buffer is big enough to 
 * store all of the data.
 */
void get_inputs( char * states );

#endif
