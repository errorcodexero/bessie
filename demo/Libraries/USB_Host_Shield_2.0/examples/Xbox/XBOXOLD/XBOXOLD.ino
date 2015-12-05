/*
 Example sketch for the original Xbox library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <XBOXOLD.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
USBHub  Hub1(&Usb); // The controller has a built in hub, so this instance is needed
XBOXOLD Xbox(&Usb);

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // halt
  }
  Serial.print(F("\r\nXBOX Library Started"));
}
void loop() {
  Usb.Task();
  if (Xbox.XboxConnected) {
    if (Xbox.getButtonPress(BLACK) || Xbox.getButtonPress(WHITE)) {
      Serial.print("BLACK: ");
      Serial.print(Xbox.getButtonPress(BLACK));
      Serial.print("\tWHITE: ");
      Serial.println(Xbox.getButtonPress(WHITE));
      Xbox.setRumbleOn(Xbox.getButtonPress(BLACK), Xbox.getButtonPress(WHITE));
    } else
      Xbox.setRumbleOn(0, 0);

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
    if (Xbox.getButtonClick(L3))
      Serial.println(F("L3"));
    if (Xbox.getButtonClick(R3))
      Serial.println(F("R3"));

    if (Xbox.getButtonPress(A)) {
      Serial.print(F("A: "));
      Serial.println(Xbox.getButtonPress(A));
    }
    if (Xbox.getButtonPress(B)) {
      Serial.print(F("B: "));
      Serial.println(Xbox.getButtonPress(B));
    }
    if (Xbox.getButtonPress(X)) {
      Serial.print(F("X: "));
      Serial.println(Xbox.getButtonPress(X));
    }
    if (Xbox.getButtonPress(Y)) {
      Serial.print(F("Y: "));
      Serial.println(Xbox.getButtonPress(Y));
    }
    if (Xbox.getButtonPress(L1)) {
      Serial.print(F("L1: "));
      Serial.println(Xbox.getButtonPress(L1));
    }
    if (Xbox.getButtonPress(R1)) {
      Serial.print(F("R1: "));
      Serial.println(Xbox.getButtonPress(R1));
    }
  }
  delay(1);
}
