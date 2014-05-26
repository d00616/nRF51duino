/*
Demonstrates advanced raw access to the advertisement and scan response packets.

This example only applies if you have a specific need for raw access to the advertisement
packet.  This is for advanced use only, as the RFduino will not advertise is the packet
is invalid.
*/

#include <RFduinoBLE.h>

// the advertisement packet is composed of a series of variable length blocks, that can appear in any order.
// each block starts with a length byte, followed by a type byte, followed by the data.
// the payload cannot exceed 31 bytes.

uint8_t advdata[] =
{
  0x02,  // length
  0x01,  // flags type
  0x04,  // br edr not supported
  
  0x1A,  // length
  0xFF,  // manufacturer data type
  
  // apple company identifier
  0x4C,
  0x00,

  0x02,  // apple manufacturer data type (0x02 = iBeacon)
  0x15,  // length

  // 128-bit iBeacon uuid (little endian)
  0xE2,
  0xC5,
  0x6D,
  0xB5,
  0xDF,
  0xFB,
  0x48,
  0xD2,
  0xB0,
  0x60,
  0xD0,
  0xF5,
  0xA7,
  0x10,
  0x96,
  0xE0,
  
  0x00,  // iBeacon Major Hi
  0x00,  // iBeacon Major Low
  
  0x00,  // iBeacon Minor Hi
  0x00,  // iBeacon Minor Low
  
  0xC5,  // iBeacon Measured Power
};

// pin 3 on the RGB shield is the green led
int led = 3;

void setup() {
  // led used to indicate that the RFduino is advertising
  pinMode(led, OUTPUT);

  RFduinoBLE_advdata = advdata;
  RFduinoBLE_advdata_len = sizeof(advdata);

  // start the BLE stack
  RFduinoBLE.begin();
}

void loop() {
  // switch to lower power mode
  RFduino_ULPDelay(INFINITE);
}

void RFduinoBLE_onAdvertisement(bool start)
{
  // turn the green led on if we start advertisement, and turn it
  // off if we stop advertisement
  
  if (start)
    digitalWrite(led, HIGH);
  else
    digitalWrite(led, LOW);
}
