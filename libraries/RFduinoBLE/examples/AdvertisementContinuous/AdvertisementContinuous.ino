/*
The sketch demonstrates how to do continuous Bluetooth Low Energy 4
Advertisement with the RFduino.
*/

#include <RFduinoBLE.h>

// pin 3 on the RGB shield is the green led
int led = 3;

void setup() {
  // led used to indicate that the RFduino is advertising
  pinMode(led, OUTPUT);

  // this is the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "data";
  
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
