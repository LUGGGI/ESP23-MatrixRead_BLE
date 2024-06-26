#include "Ble.h"
#include <NimBLEDevice.h>

#define SIZE(n) sizeof(n) / sizeof(n[0]) // get length of array

BLEServer* pServer = NULL;
BLECharacteristic* pVal = NULL;
BLECharacteristic* pTime = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


void Ble::setup(String name){
  // Create the BLE Device
  BLEDevice::init(name.c_str());

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pVal = pService->createCharacteristic(
    VAL_UUID,
    NIMBLE_PROPERTY::READ|
    NIMBLE_PROPERTY::NOTIFY
  );
  pTime = pService->createCharacteristic(
    TIME_UUID,
    NIMBLE_PROPERTY::READ|
    NIMBLE_PROPERTY::NOTIFY
  );

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}


void Ble::sent_data(String data){
  if (deviceConnected) {      
    pVal->setValue(data.c_str());
    pVal->notify();
  }
  else connection_event();
}


void Ble::sent_data_raw(uint16_t* arr){
  if (deviceConnected) {  
    uint8_t temp[SIZE(arr)*2];
    for (int i=0; i<SIZE(arr); ++i){
      temp[i*2] = arr[i] >> 8;
      temp[i*2+1] = arr[i]; 
    }
       
    pVal->setValue((uint8_t *) temp, 12);
    pVal->notify();
  }
  else connection_event();
}


void Ble::sent_time(uint32_t data){
  if (deviceConnected) {      
    pTime->setValue(data);
    pTime->notify();
  }
  else connection_event();
}



void Ble::connection_event(void){
  // disconnecting
  if (!deviceConnected && oldDeviceConnected) {
      delay(500); // give the bluetooth stack the chance to get things ready
      pServer->startAdvertising(); // restart advertising
      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
  }
  // connecting
  if (deviceConnected && !oldDeviceConnected) {
      // do stuff here on connecting
      oldDeviceConnected = deviceConnected;
  }
}
