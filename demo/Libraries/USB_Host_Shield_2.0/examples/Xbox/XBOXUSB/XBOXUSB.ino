/*
 Example sketch for the Xbox 360 USB library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <XBOXUSB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
XBOXUSB Xbox(&Usb);

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
}
void loop() {
  Usb.Task();
  if (Xbox.Xbox360Connected) {
    if (Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2)) {
      Serial.print("L2: ");
      Serial.print(Xbox.getButtonPress(L2));
      Serial.print("\tR2: ");
      Serial.println(Xbox.getButtonPress(R2));
      Xbox.setRumbleOn(Xbox.getButtonPress(L2), Xbox.getButtonPress(R2));
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

    if (Xbox.getButtonClick(UP)) {
      Xbox.setLedOn(LED1);
      Serial.println(F("Up"));
    }
    if (Xbox.getButtonClick(DOWN)) {
      Xbox.setLedOn(LED4);
      Serial.println(F("Down"));
    }
    if (Xbox.getButtonClick(LEFT)) {
      Xbox.setLedOn(LED3);
      Serial.println(F("Left"));
    }
    if (Xbox.getButtonClick(RIGHT)) {
      Xbox.setLedOn(LED2);
      Serial.println(F("Right"));
    }

    if (Xbox.getButtonClick(START)) {
      Xbox.setLedMode(ALTERNATING);
      Serial.println(F("Start"));
    }
    if (Xbox.getButtonClick(BACK)) {
      Xbox.setLedBlink(ALL);
      Serial.println(F("Back"));
    }
    if (Xbox.getButtonClick(L3))
      Serial.println(F("L3"));
    if (Xbox.getButtonClick(R3))
      Serial.println(F("R3"));

    if (Xbox.getButtonClick(L1))
      Serial.println(F("L1"));
    if (Xbox.getButtonClick(R1))
      Serial.println(F("R1"));
    if (Xbox.getButtonClick(XBOX)) {
      Xbox.setLedMode(ROTATING);
      Serial.println(F("Xbox"));
    }

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
