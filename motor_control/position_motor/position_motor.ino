#include "drv.h"

String inputString = "";
bool stringComplete = false;
float motor_pos = 0;

void serialEvent()
{
  while (Serial.available())
  {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n')
    {
      stringComplete = true;
    }
  }
}

void setup()
{
  // use monitoring with serial
  Serial.begin(115200);
  drv_setup();
}

void loop()
{
  // main FOC algorithm function
  motor_loop();
  serialEvent();
  if (stringComplete)
  {
    if (inputString.substring(0, 1) == "T")
    {
      // take and split the next characters of the string
      motor_pos = inputString.substring(1, 4).toInt();
      update_target(motor_pos);
      Serial.println(motor_pos);
      inputString = "";
      stringComplete = false;
    }
    inputString = "";
    stringComplete = false;
  }
  motor_move();
}