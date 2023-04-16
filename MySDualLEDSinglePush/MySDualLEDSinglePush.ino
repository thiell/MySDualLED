/**
   The MySensors Arduino library handles the wireless radio link and protocol
   between your home built sensors/actuators and HA controller of choice.
   The sensors forms a self healing radio network with optional repeaters. Each
   repeater and gateway builds a routing tables in EEPROM which keeps track of the
   network topology allowing messages to be routed to nodes.

   Copyright (C) 2013-2015 Sensnology AB
   Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   version 2 as published by the Free Software Foundation.

 *******************************
   MySDualLED for board iboat v1.0
   Double Play 2018
*/


#define STOVE_LIGHT                 1

//////////////////////////
//     Configuration    //
//////////////////////////

// This module supports a single press/click button support to control 2 lights

#if STOVE_LIGHT
String Location = "Stove Light";
#define MY_NODE_ID 12
#endif

// Lights with 2 LEDs and a single push switch
#define LED1_CONTROL
#define LED1_DIMMER
#define LED2_CONTROL
#define LED2_DIMMER
#define SW1
#define SW1_CLICK
//#define SW2
//#define SW2_CLICK


// Enable debug prints to serial monitor
//#define MY_DEBUG

// Use custom static node ID
// If disabled node ID will be automatically assigned
//#define MY_NODE_ID 42

// Use custom parent node ID. Use 0 to force direct connection to the gateway.
// If disabled node ID will be automatically assigned
//#define MY_PARENT_NODE_ID 0

// Enable repeater feature for this node
#define MY_REPEATER_FEATURE

// Advanced options
// switch to stand alone mode immediately in case gateway not detected
#define MY_TRANSPORT_WAIT_READY_MS 1
// Use low power transmission for RF24, better signal/noise ratio but shorter range
//#define MY_RF24_PA_LEVEL RF24_PA_LOW
// Enable OTA feature
#define MY_OTA_FIRMWARE_FEATURE         // Require an eeprom on the PCB
// Enable message signing
//#define MY_SIGNING_ATSHA204             // Require an ATSHA205 on the PCB and configured with your system key


//////////////////////////
// End of configuration //
//////////////////////////

// MySensors
#define MY_RADIO_NRF24          // Enable and select radio type attached
#include <SPI.h>
#include <MySensors.h>
#include <Bounce2.h>
#define SN "MySDualLED"         // Name of the sketch
#define SV "2.3.0"              // Version (2.0 : use MySensors 2.0)
boolean metric = true;          // Use SI by default
#define MESSAGEWAIT 500         // Wait a few ms between radio Tx

#if defined LED1_CONTROL
#define MosLED1_PIN 5            // Arduino pin attached to MOSFET Gate pin for LED1
#define CHILD_ID_LED1 0
#define EEPROM_LED1_LEVEL 0
static int16_t currentLED1level = 0;
MyMessage msgStatLED1(CHILD_ID_LED1, V_STATUS);
#if defined LED1_DIMMER
MyMessage msgPercLED1(CHILD_ID_LED1, V_PERCENTAGE);
#endif
#endif

#if defined LED2_CONTROL
#define MosLED2_PIN 6            // Arduino pin attached to MOSFET Gate pin for LED2
#define CHILD_ID_LED2 1
#define EEPROM_LED2_LEVEL 1
static int16_t currentLED2level = 0;
MyMessage msgStatLED2(CHILD_ID_LED2, V_STATUS);
#if defined LED2_DIMMER
MyMessage msgPercLED2(CHILD_ID_LED2, V_PERCENTAGE);
#endif
#endif

#if defined SW1
#define SW1_PIN  4  // Arduino Digital I/O pin for button/reed switch
int oldSW1Val = -1;
#endif

#if defined SW1_CLICK
Bounce debouncerSW1 = Bounce(); 
#endif

#if defined SW2
#define SW2_PIN 7  // Arduino Digital I/O pin for button/reed switch
int oldSW2Val = -1;
#endif

#if defined SW2_CLICK
Bounce debouncerSW2 = Bounce(); 
#endif

// Make sure only to store/fetch values in the range 0-100 from eeprom
int loadLevelState(byte pos) {
  return min(max(loadState(pos), 0), 100);
}
void saveLevelState(byte pos, byte data) {
  saveState(pos, min(max(data, 0), 100));
}
