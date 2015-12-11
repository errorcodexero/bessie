#include <Servo.h>
#include <usbhub.h>
#include <PS3BT.h>

struct Robot_inputs {
  
};

struct Robot_outputs {
  Servo vex;
};

USB Usb;
USBHub Hub1(&Usb);
BTD Btd(&Usb);
PS3BT PS3(&Btd);

Robot_inputs robot_inputs;
Robot_outputs robot_outputs;

void setup() {
  USB_HOST_SERIAL.begin(115200);

  #if !defined(__MIPSEL__)
    while (!USB_HOST_SERIAL);
  #endif

  if (Usb.Init() == -1) {
    USB_HOST_SERIAL.println(F("OSC did not start"));
    while(1);
  }

  USB_HOST_SERIAL.println(F("Started"));

  robot_outputs.vex.attach(2);
}

void loop() {
  Usb.Task();
  
  if (PS3.getButtonClick(PS)) {
    PS3.setAllOff();
    PS3.disconnect();
  }

  if (PS3.PS3Connected) {
    int stick_value = PS3.getAnalogStick(RightStickY);
    int motor_micros = map(stick_value, 0, 255, 1000, 2000);
    robot_outputs.vex.writeMicroseconds(motor_micros);
    //USB_HOST_SERIAL.println(PS3.getAnalogStick(RightStickY));
  }
}
