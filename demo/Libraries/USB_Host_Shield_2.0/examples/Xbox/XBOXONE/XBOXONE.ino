/*
 Example sketch for the Xbox ONE USB library - by guruthree, based on work by
 Kristian Lauszus.
 */

#include <XBOXONE.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXONE Xbox(&Usb);

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
}
void loop() {
  Usb.Task();
  if (Xbox.XboxOneConnected) {
    if (Xbox.getAnalogSwitch(LeftSwitchX) > 7500 || Xbox.getAnalogSwitch(LeftSwitchX) < -7500 || Xbox.getAnalogSwitch(LeftSwitchY) > 7500 || Xbox.getAnalogSwitch(LeftSwitchY) < -7500 || Xbox.getAnalogSwitch(RightSwitchX) > 7500 || Xbox.getAnalogSwitch(RightSwitchX) < -7500 || Xbox.getAnalogSwitch(RightSwitchY) > 7500 || Xbox.getAnalogSwitch(RightSwitchY) < -7500) {
      if (Xbox.getAnalogSwitch(LeftSwitchX) > 7500 || Xbox.getAnalogSwitch(LeftSwitchX) < -7500) {
        Serial.print(F("LeftSwitchX: "));
        Serial.print(Xbox.getAnalogSwitch(LeftSwitchX));
        Serial.print("\t");
      }
      if (Xbox.getAnalogSwitch(LeftSwitchY) > 7500 || Xbox.getAnalogSwitch(LeftSwitchY) < -7500) {
        Serial.print(F("LeftSwitchY: "));
        Serial.print(Xbox.getAnalogSwitch(LeftSwitchY));
        Serial.print("\t");
      }
      if (Xbox.getAnalogSwitch(RightSwitchX) > 7500 || Xbox.getAnalogSwitch(RightSwitchX) < -7500) {
        Serial.print(F("RightSwitchX: "));
        Serial.print(Xbox.getAnalogSwitch(RightSwitchX));
        Serial.print("\t");
      }
      if (Xbox.getAnalogSwitch(RightSwitchY) > 7500 || Xbox.getAnalogSwitch(RightSwitchY) < -7500) {
        Serial.print(F("RightSwitchY: "));
        Serial.print(Xbox.getAnalogSwitch(RightSwitchY));
      }
      Serial.println();
    }

    if (Xbox.getButtonPress(L2) > 0 || Xbox.getButtonPress(R2) > 0) {
      if (Xbox.getButtonPress(L2) > 0) {
        Serial.print(F("L2: "));
        Serial.print(Xbox.getButtonPress(L2));
        Serial.print("\t");
      }
      if (Xbox.getButtonPress(R2) > 0) {
        Serial.print(F("R2: "));
        Serial.print(Xbox.getButtonPress(R2));
        Serial.print("\t");
      }
      Serial.println();
    }

    if (Xbox.getButtonClick(UP))
      Serial.println(F("Up"));
    if (Xbox.getButtonClick(DOWN))
      Serial.println(F("Down"));
    if (Xbox.getButtonClick(LEFT))
      Serial.println(F("Left"));
    if (Xbox.getButtonClick(RIGHT))
      Serial.println(F("Right"));

    if (Xbox.getButtonClick(START))
      Serial.println(F("Start"));
    if (Xbox.getButtonClick(BACK))
      Serial.println(F("Back"));
    if (Xbox.getButtonClick(XBOX))
      Serial.println(F("Xbox"));
    if (Xbox.getButtonClick(SYNC))
      Serial.println(F("Sync"));

    if (Xbox.getButtonClick(L1))
      Serial.println(F("L1"));
    if (Xbox.getButtonClick(R1))
      Serial.println(F("R1"));
    if (Xbox.getButtonClick(L2))
      Serial.println(F("L2"));
    if (Xbox.getButtonClick(R2))
      Serial.println(F("R2"));
    if (Xbox.getButtonClick(L3))
      Serial.println(F("L3"));
    if (Xbox.getButtonClick(R3))
      Serial.println(F("R3"));


    if (Xbox.getButtonClick(A))
      Serial.println(F("A"));
    if (Xbox.getButtonClick(B))
      Serial.println(F("B"));
    if (Xbox.getButtonClick(X))
      Serial.println(F("X"));
    if (Xbox.getButtonClick(Y))
      Serial.println(F("Y"));
  }
  delay(1);
}
