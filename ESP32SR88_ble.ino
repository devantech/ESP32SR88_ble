#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include "relays.h"
#include "input.h"

#define SERVICE_MODULE_UUID       "3d666724-e775-11ea-adc1-0242ac120002"  // Service that defines module information
#define CHARACTERISTIC_ID         "af1fdb15-5f75-4559-aa02-f575cf21da39"  // Characteristic that contains the module ID
#define CHARACTERISTIC_VER        "91857612-9071-45c3-88ad-433105d5f8fa"  // Characteristic that defines a modules firmware version

#define SERVICE_RELAY_UUID        "eda0f9e6-e78f-11ea-adc1-0242ac120002"  // Service for relay interaction
#define CHARACTERISTIC_NR         "a96f34fe-19f7-401f-873a-30462c535402"  // Characteristic that tells you how many relays the board has
#define CHARACTERISTIC_RS         "d1482882-1fd0-4f72-96bd-b6c953345653"  // Characteristic for the state of the relays

#define SERVICE_IN_UUID           "b5da2b54-e7a3-11ea-adc1-0242ac120002"  // Service for input reading
#define CHARACTERISTIC_NI         "24ca2348-e112-4f7c-b31a-253a21b5a0c2"  // Characteristic for the number of inputs
#define CHARACTERISTIC_GI         "8ff314b7-36f5-4ccf-a142-0c36a6da78c8"  // Characteristic holding input states

#define MODULE_NAME               "ESP32SR88"
#define MODULE_ID                 "43"
#define MODULE_V                  "1"

#define CONNECT_LED               5

char relay_st[ NUMBER_OF_RELAYS + 1 ];
char input_st[ NUMBER_OF_INPUTS + 1 ];

/**
 * Class that handles callbacks to the relay state 
 * characteristic.
 * 
 * Allows the getting and setting of the relays from
 * reading and writing the characteristic!
 */

class RelayCallbacks: public BLECharacteristicCallbacks {

    void onWrite(BLECharacteristic *pCharacteristic) {
 
      std::string value = pCharacteristic->getValue();

      if ( value.length() >= 8 ) {
        set_relay_states( value.c_str() );
      }
      
    }

    void onRead(BLECharacteristic *pCharacteristic) {
      
      get_relay_states( relay_st );
      pCharacteristic->setValue( relay_st );
      
    }
    
};

/**
 * Class that handles callbacks to the input state 
 * characteristic.
 *
 * Allows the getting of the input states.
 */
class InputCallbacks: public BLECharacteristicCallbacks {

    void onRead(BLECharacteristic *pCharacteristic) {
      
      get_inputs( input_st );
      pCharacteristic->setValue( input_st );
      
    }
    
};

/**
 * Class that handles callbacks for connection and disconnection.
 */
class ConnectionCallbacks: public BLEServerCallbacks {
    void onConnect( BLEServer* pServer ) {
      digitalWrite( CONNECT_LED, LOW );
    };

    void onDisconnect(BLEServer* pServer) {
      digitalWrite( CONNECT_LED, HIGH );
    }
};

void setup() {
  
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  pinMode( CONNECT_LED, OUTPUT );
  digitalWrite( CONNECT_LED, HIGH );

  init_relays();
  init_inputs();
  
  BLEDevice::init( MODULE_NAME );
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks( new ConnectionCallbacks() );
  init_module_service( pServer );
  init_relay_service( pServer );
  init_input_service( pServer );
  
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  
  pAdvertising->addServiceUUID( SERVICE_MODULE_UUID );
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  
  BLEDevice::startAdvertising();
  
  Serial.println("Characteristic defined! Now you can read it in your phone!");
  
}

void loop() {
  
  delay(500);
  do_inputs();
  
}

/**
 * Init the service that provides information about the module.
 * This service provides characteristics for the module ID and the 
 * firmware version.
 * 
 */
void init_module_service( BLEServer * pServer ) {
  
  BLEService *mService = pServer->createService( SERVICE_MODULE_UUID );
  
  BLECharacteristic *idCharacteristic = mService->createCharacteristic(
                                         CHARACTERISTIC_ID,
                                         BLECharacteristic::PROPERTY_READ
                                       );
  
  idCharacteristic->setValue( MODULE_ID );
  
  BLECharacteristic *vCharacteristic = mService->createCharacteristic(
                                         CHARACTERISTIC_VER,
                                         BLECharacteristic::PROPERTY_READ
                                       );
  
  vCharacteristic->setValue( MODULE_V );
  
  mService->start();
  
}

/**
 * Init the service that provides the interface fot the relays on the module.
 */
void init_relay_service( BLEServer * pServer ) {

  BLEService *mService = pServer->createService( SERVICE_RELAY_UUID );
  
  BLECharacteristic *idCharacteristic = mService->createCharacteristic(
                                         CHARACTERISTIC_NR,
                                         BLECharacteristic::PROPERTY_READ
                                       );

  idCharacteristic->setValue( String( NUMBER_OF_RELAYS ).c_str() );
  
  BLECharacteristic *vCharacteristic = mService->createCharacteristic(
                                         CHARACTERISTIC_RS,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  
  vCharacteristic->setCallbacks( new RelayCallbacks() );
  
  mService->start();

}

/**
 * Init the service provides information about the inputs on the module.
 */
void init_input_service( BLEServer * pServer ) {

  BLEService *mService = pServer->createService( SERVICE_IN_UUID );
  
  BLECharacteristic *idCharacteristic = mService->createCharacteristic(
                                         CHARACTERISTIC_NI,
                                         BLECharacteristic::PROPERTY_READ
                                       );

  idCharacteristic->setValue( String( NUMBER_OF_INPUTS ).c_str() );
  
  BLECharacteristic *vCharacteristic = mService->createCharacteristic(
                                         CHARACTERISTIC_GI,
                                         BLECharacteristic::PROPERTY_READ
                                       );
  
  vCharacteristic->setCallbacks( new InputCallbacks() );
  
  mService->start();

}
