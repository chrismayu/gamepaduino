// 
// 
// 

#include "SNES_gamepad.h"


void SNES_gamepad::latch() {
  digitalWrite(latch_pin, HIGH);//latch pulse, lock the state of the buttons in the register
  delayMicroseconds(12);
  digitalWrite(latch_pin, LOW);
  delayMicroseconds(6);
}

void SNES_gamepad::read_imp() {
  read_bit(0); //first bit read before clock.

  for (int i = 1; i < 16; i++) {//clock &read
    digitalWrite(clock_pin, HIGH);
    delayMicroseconds(6);
    read_bit(i); //the values are stored for each bit
    digitalWrite(clock_pin, LOW);
    delayMicroseconds(6);
  }

  buttons = ~buttons; //workaround, a button pressed is read as a '0'(pull ups), jus inversing them to my taste.
}

//                                            0    1    2         3        4     5       6       7        8    9   10   11
static const String SNES_gamepad::names[] = {"B", "Y", "select", "start", "up", "down", "left", "right", "A", "X", "L", "R"};
