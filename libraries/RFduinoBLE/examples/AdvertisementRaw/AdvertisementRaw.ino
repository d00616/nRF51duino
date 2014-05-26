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
  0x05,  // length
  0x09,  // complete local name type
  0x41,  // 'A'
  0x42,  // 'B'
  0x43,  // 'C'
  0x44,  // 'D'
  
  0x02,  // length
  0x01,  // flags type
  0x06,  // le general discovery mode | br edr not supported

  0x02,  // length
  0x0A,  // tx power level
  0x04,  // +4dBm

  // if this variable block is not included, the RFduino iPhone apps won't see the device
  0x03,  // length
  0x03,  // 16 bit service uuid (complete)
  0x20,  // uuid low
  0x22,  // uuid hi
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
