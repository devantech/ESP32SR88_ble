
#ifndef RELAYS_H
#define RELAYS_H



#define RELAY_1                   13
#define RELAY_2                   12
#define RELAY_3                   4
#define RELAY_4                   27
#define RELAY_5                   26
#define RELAY_6                   25
#define RELAY_7                   33
#define RELAY_8                   32

#define NUMBER_OF_RELAYS          8


/**
 * Init the relay pins and set them to the default LOW values.
 */
void init_relays();

/**
 * Reads the current relay states and places them in the passed 
 * char array.
 * 
 * Onus is on the user to make sure that the char array is big enough
 * for the relay data to fit in it.
 */
void get_relay_states( char * states );

/**
 * Sets the relay states to the values in the passed char array.
 * 
 * Onus is on the user to make sure that the char array contains
 * enough data for the relays to be set.
 */
void set_relay_states( const char *st );



#endif
