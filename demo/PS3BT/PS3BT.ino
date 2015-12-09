/*
 Example sketch for the PS3 Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <PS3BT.h>
#include <usbhub.h>
#include <TM1638.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#include <SPI.h>
#endif

USB Usb;
USBHub Hub1(&Usb);	// needed for Belkin dongle
BTD Btd(&Usb);
PS3BT PS3(&Btd);

// use these to hard-code controller setup for a particular dongle
// PS3BT PS3(&Btd, 0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x12);		// Rocketek
// PS3BT PS3(&Btd, 0x00, 0x19, 0x0E, 0x06, 0xA9, 0x38);		// Belkin (w/internal hub)
// PS3BT PS3(&Btd, 0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x0C);		// UDOO

RumbleEnum rumble = RumbleOff;
bool printAngle = false;

TM1638 led_key(5, 6, 7);
byte buttons = 0;
word leds = 0;
char display[9] = "        ";
word dots = 0; // decimal points

#define	BUTTON_THROTTLE		0x01
#define	BUTTON_LEFTSTICK	0x02
#define	BUTTON_RIGHTSTICK	0x04
#define	BUTTON_PITCHROLL	0x08

#define	LED_UP			0x01
#define	LED_RIGHT		0x02
#define	LED_DOWN		0x04
#define	LED_LEFT		0x08
#define LED_TRIANGLE		0x10
#define	LED_CIRCLE		0x20
#define	LED_CROSS		0x40
#define	LED_SQUARE		0x80

void ntoa( char *out, int n)
{
    if (n < 0) {
	out[0] = '-';
	n = -n;
    } else {
	out[0] = ' ';
    }
    uint8_t i = 3;
    while (i > 0) {
	out[i] = '0' + (n % 10);
	n /= 10;
	--i;
	if (n == 0) break;
    }
    while (i > 0) {
	out[i] = ' ';
	--i;
    }
}

void setup()
{
  USB_HOST_SERIAL.begin(115200);

#if !defined(__MIPSEL__)
  while (!USB_HOST_SERIAL); // Wait for serial port to connect
#endif

  if (Usb.Init() == -1) {
    USB_HOST_SERIAL.println(F("OSC did not start"));
    while (1); //halt
  }

  USB_HOST_SERIAL.println(F("\r\n\r\nPS3 Bluetooth Library Started"));
}

void loop()
{
  Usb.Task();

  leds = 0;
  {
    byte b = led_key.getButtons();
    if (b) buttons = b;
  }
  strcpy(display, "        ");
  dots = 0;

  if (PS3.getButtonClick(PS)) {
    USB_HOST_SERIAL.println(F("PS"));
    PS3.setAllOff();
    PS3.disconnect();
  }

  if (PS3.PS3Connected) {
    if (PS3.getButtonClick(TRIANGLE)) {
      USB_HOST_SERIAL.println(F("Triangle"));
      leds |= LED_TRIANGLE;
    }
    if (PS3.getButtonClick(CIRCLE)) {
      USB_HOST_SERIAL.println(F("Circle"));
      leds |= LED_CIRCLE;
    }
    if (PS3.getButtonClick(CROSS)) {
      USB_HOST_SERIAL.println(F("Cross"));
      leds |= LED_CROSS;
    }
    if (PS3.getButtonClick(SQUARE)) {
      USB_HOST_SERIAL.println(F("Square"));
      leds |= LED_SQUARE;
    }
    if (PS3.getButtonClick(UP)) {
      USB_HOST_SERIAL.println(F("Up"));
      leds |= LED_UP;
      PS3.setLedOff();
      PS3.setLedOn(LED4);
    }
    if (PS3.getButtonClick(RIGHT)) {
      USB_HOST_SERIAL.println(F("Right"));
      leds |= LED_RIGHT;
      PS3.setLedOff();
      PS3.setLedOn(LED1);
    }
    if (PS3.getButtonClick(DOWN)) {
      USB_HOST_SERIAL.println(F("Down"));
      leds |= LED_DOWN;
      PS3.setLedOff();
      PS3.setLedOn(LED2);
    }
    if (PS3.getButtonClick(LEFT)) {
      USB_HOST_SERIAL.print(F("Left"));
      leds |= LED_LEFT;
      PS3.setLedOff();
      PS3.setLedOn(LED3);
    }
    if (PS3.getButtonClick(L1)) {
      USB_HOST_SERIAL.println(F("L1"));
      if (rumble == RumbleLeft) {
	rumble = RumbleOff;
      } else {
	rumble = RumbleLeft;
      }
      PS3.setRumbleOn(rumble);
    }
    if (PS3.getButtonClick(R1)) {
      USB_HOST_SERIAL.println(F("R1"));
      if (rumble == RumbleRight) {
	rumble = RumbleOff;
      } else {
	rumble = RumbleRight;
      }
      PS3.setRumbleOn(rumble);
    }
    if (PS3.getButtonClick(L3)) {
      USB_HOST_SERIAL.println(F("L3"));
      buttons = BUTTON_LEFTSTICK;
      dots |= 0xF0;
    }
    if (PS3.getButtonClick(R3)) {
      USB_HOST_SERIAL.println(F("R3"));
      buttons = BUTTON_RIGHTSTICK;
      dots |= 0x0F;
    }
    if (PS3.getButtonClick(SELECT)) {
      USB_HOST_SERIAL.print(F("Select - "));
      PS3.printStatusString();
      USB_HOST_SERIAL.println();
    }
    if (PS3.getButtonClick(START)) {
      USB_HOST_SERIAL.println(F("Start"));
      printAngle = !printAngle;
    }

    if (buttons) {
      if (buttons == BUTTON_THROTTLE) {
	ntoa(display, (int) PS3.getAnalogButton(L2));
	ntoa(display+4, (int) PS3.getAnalogButton(R2));
      } else if (buttons == BUTTON_LEFTSTICK) {
	ntoa(display, (int) PS3.getAnalogStick(LeftStickX) - 127);
	ntoa(display+4, (int) PS3.getAnalogStick(LeftStickY) - 127);
      } else if (buttons == BUTTON_RIGHTSTICK) {
	ntoa(display, (int) PS3.getAnalogStick(RightStickX) - 127);
	ntoa(display+4, (int) PS3.getAnalogStick(RightStickY) - 127);
      } else if (buttons == BUTTON_PITCHROLL) {
	ntoa(display, (int) PS3.getAngle(Pitch) - 181);  // my controller centers at (+181,+181)
	ntoa(display+4, (int) PS3.getAngle(Roll) - 181);
      }
    }
      
    if (printAngle) {
      {
	USB_HOST_SERIAL.print(F("LeftStickX: "));
	USB_HOST_SERIAL.print(PS3.getAnalogStick(LeftStickX));
	USB_HOST_SERIAL.print(F("\tLeftStickY: "));
	USB_HOST_SERIAL.print(PS3.getAnalogStick(LeftStickY));
	if (PS3.PS3Connected) { // The Navigation controller only have one joystick
	  USB_HOST_SERIAL.print(F("\tRightStickX: "));
	  USB_HOST_SERIAL.print(PS3.getAnalogStick(RightStickX));
	  USB_HOST_SERIAL.print(F("\tRightStickY: "));
	  USB_HOST_SERIAL.print(PS3.getAnalogStick(RightStickY));
	}
	USB_HOST_SERIAL.println();
      }

      // Analog button values can be read from almost all buttons
      {
	USB_HOST_SERIAL.print(F("L2: "));
	USB_HOST_SERIAL.print(PS3.getAnalogButton(L2));
	if (PS3.PS3Connected) {
	  USB_HOST_SERIAL.print(F("\tR2: "));
	  USB_HOST_SERIAL.print(PS3.getAnalogButton(R2));
	}
	USB_HOST_SERIAL.println();
      }

      {
	USB_HOST_SERIAL.print(F("Pitch: "));
	USB_HOST_SERIAL.print(PS3.getAngle(Pitch));
	USB_HOST_SERIAL.print(F("\tRoll: "));
	USB_HOST_SERIAL.print(PS3.getAngle(Roll));
	USB_HOST_SERIAL.println();
      }
    } // if (printAngle)

  } // if (PS3.PS3Connected)

  led_key.setLEDs(leds);
  led_key.setDisplayToString(display, dots);
}
