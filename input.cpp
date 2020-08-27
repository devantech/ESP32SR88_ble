
#include "input.h"

void setOptoPinModes( int p_mode );

char opto_states[ 8 ];

void init_inputs() {
  
  setOptoPinModes( INPUT );

  pinMode( LED_POWER, OUTPUT );
  digitalWrite( LED_POWER, HIGH );

  do_inputs();
  
}

void get_inputs( char * states ) {
  
  do_inputs();
  
  states[7] = ( opto_states[0] == LOW ) ? '1' : '0';
  states[6] = ( opto_states[1] == LOW ) ? '1' : '0';
  states[5] = ( opto_states[2] == LOW ) ? '1' : '0';
  states[4] = ( opto_states[3] == LOW ) ? '1' : '0';
  states[3] = ( opto_states[4] == LOW ) ? '1' : '0';
  states[2] = ( opto_states[5] == LOW ) ? '1' : '0';
  states[1] = ( opto_states[6] == LOW ) ? '1' : '0';
  states[0] = ( opto_states[7] == LOW ) ? '1' : '0';
  states[8] = '\0';
  
}

void setOptoPinModes( int p_mode ) {
  
  pinMode( OPTO_1, p_mode );
  pinMode( OPTO_2, p_mode );
  pinMode( OPTO_3, p_mode );
  pinMode( OPTO_4, p_mode );
  pinMode( OPTO_5, p_mode );
  pinMode( OPTO_6, p_mode );
  pinMode( OPTO_7, p_mode );
  pinMode( OPTO_8, p_mode );
  
}

void readOptoPins() {
  
  setOptoPinModes( INPUT );                 // Set the opto pins to inputs
  
  delayMicroseconds( 5 );                   // Short delay to allow voltage to settle
  
  opto_states[ 0 ] = digitalRead( OPTO_1 ); // Read the input states.
  opto_states[ 1 ] = digitalRead( OPTO_2 );
  opto_states[ 2 ] = digitalRead( OPTO_3 );
  opto_states[ 3 ] = digitalRead( OPTO_4 );
  opto_states[ 4 ] = digitalRead( OPTO_5 );
  opto_states[ 5 ] = digitalRead( OPTO_6 );
  opto_states[ 6 ] = digitalRead( OPTO_7 );
  opto_states[ 7 ] = digitalRead( OPTO_8 );

}

void driveOptoPins() {

  setOptoPinModes( OUTPUT );                // Set the opto pins to outputs to drive the LEDs.
  
  digitalWrite( OPTO_1, opto_states[ 0 ] ); // Drive the LEDs to show the opto states.
  digitalWrite( OPTO_2, opto_states[ 1 ] );
  digitalWrite( OPTO_3, opto_states[ 2 ] );
  digitalWrite( OPTO_4, opto_states[ 3 ] );
  digitalWrite( OPTO_5, opto_states[ 4 ] );
  digitalWrite( OPTO_6, opto_states[ 5 ] );
  digitalWrite( OPTO_7, opto_states[ 6 ] );
  digitalWrite( OPTO_8, opto_states[ 7 ] );

}

void do_inputs() {

  digitalWrite( LED_POWER, HIGH );  // Turn the opto led power off
  readOptoPins();                   // Read the state of the optos
  driveOptoPins();                  
  digitalWrite( LED_POWER, LOW );   // Turn the opto led power on again

}
