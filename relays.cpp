
#include "relays.h"


void init_relays() {

  pinMode( RELAY_1, OUTPUT );      
  pinMode( RELAY_2, OUTPUT );
  pinMode( RELAY_3, OUTPUT );
  pinMode( RELAY_4, OUTPUT );
  pinMode( RELAY_5, OUTPUT );
  pinMode( RELAY_6, OUTPUT );
  pinMode( RELAY_7, OUTPUT );
  pinMode( RELAY_8, OUTPUT );

  digitalWrite( RELAY_1, LOW );
  digitalWrite( RELAY_2, LOW );
  digitalWrite( RELAY_3, LOW );
  digitalWrite( RELAY_4, LOW );
  digitalWrite( RELAY_5, LOW );
  digitalWrite( RELAY_6, LOW );
  digitalWrite( RELAY_7, LOW );
  digitalWrite( RELAY_8, LOW );
    
}


void get_relay_states( char * states ) {
    
  states[0] = ( digitalRead(RELAY_8) == LOW ) ? '0' : '1';
  states[1] = ( digitalRead(RELAY_7) == LOW ) ? '0' : '1';
  states[2] = ( digitalRead(RELAY_6) == LOW ) ? '0' : '1';
  states[3] = ( digitalRead(RELAY_5) == LOW ) ? '0' : '1';
  states[4] = ( digitalRead(RELAY_4) == LOW ) ? '0' : '1';
  states[5] = ( digitalRead(RELAY_3) == LOW ) ? '0' : '1';
  states[6] = ( digitalRead(RELAY_2) == LOW ) ? '0' : '1';
  states[7] = ( digitalRead(RELAY_1) == LOW ) ? '0' : '1';
  states[8] = '\0';

}


void set_relay_states( const char *st ) {

  digitalWrite( RELAY_8, ( st[0] == '1' ) ? HIGH : LOW );
  digitalWrite( RELAY_7, ( st[1] == '1' ) ? HIGH : LOW );
  digitalWrite( RELAY_6, ( st[2] == '1' ) ? HIGH : LOW );
  digitalWrite( RELAY_5, ( st[3] == '1' ) ? HIGH : LOW );
  digitalWrite( RELAY_4, ( st[4] == '1' ) ? HIGH : LOW );
  digitalWrite( RELAY_3, ( st[5] == '1' ) ? HIGH : LOW );
  digitalWrite( RELAY_2, ( st[6] == '1' ) ? HIGH : LOW );
  digitalWrite( RELAY_1, ( st[7] == '1' ) ? HIGH : LOW );
  
}
