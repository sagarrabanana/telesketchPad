/* Encoder Library - TwoKnobs Example
   http://www.pjrc.com/teensy/td_libs_Encoder.html

   This example code is in the public domain.
*/

#include <Encoder.h>
#include <Mouse.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(5, 6);
Encoder knobRight(7, 8);
//   avoid using pins with LEDs attached

int range = 50;              // output range of X or Y movement; affects movement speed
int responseDelay = 5;     // response delay of the mouse, in ms

int interruptor = 9;

void setup() {
  Mouse.begin();
  Serial.begin(9600);
  //Serial.println("TwoKnobs Encoder Test:");
  pinMode(interruptor, INPUT);
}

long positionLeft  = 0;
long positionRight = 0;

void loop() {
  if (digitalRead(interruptor) == HIGH and Mouse.isPressed(MOUSE_LEFT) != true)
  {
    Mouse.press(MOUSE_LEFT);
  }
  else if (digitalRead(interruptor) == LOW and Mouse.isPressed(MOUSE_LEFT) == true)
  {

    Mouse.release(MOUSE_LEFT);
  }
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    //Mouse.move(newLeft / 4, newRight / 4, 0);
    Mouse.move((positionLeft - newLeft), (-positionRight + newRight), 0);
    //Mouse.move((-positionLeft + newLeft), (-positionRight + newRight), 0);
    positionLeft = newLeft;
    positionRight = newRight;

  }
}
