/*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*/

// Need the ESC library.
#include "esc.h"
// Need the Servo library, since the ESC is controlled like a servo.
#include <Servo.h>

// The ESC's we use for the thunderball have a min value of 16 and max of 180
// Tested by trial and error.
#define ESC_MIN_VALUE 16
#define ESC_MAX_VALUE 180

// This is our motor.
Servo myMotor;
ESC esc;

// String to buffer the monitoring commands in.
String incomingString;

void handle_command(String input){
  if(input.equals("arm")){
    esc.arm();
  }
  if(input.equals("disarm")){
    esc.disarm();
  }
  if(input.equals("max")){
    esc.set_speed(1.0);
  }
  if(input.equals("min")){
    esc.set_speed(0.0);
  }
}

// Set everything up
void setup()
{
  // Put the esc to Arduino pin #9
  myMotor.attach(9);
  // Load and ESC and give it it's servo controller, min and max value
  esc = ESC(&myMotor, 5, ESC_MIN_VALUE, ESC_MAX_VALUE);

  // On setup, just to be sure, calibrate the motor, calibrate also arms
  // So once it's calibrated it's also armed.
  esc.calibrate();

  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("Ready for take off..");
}


void loop()
{
  // If there is incoming value
  if(Serial.available() > 0)
  {
    // read the value
    char ch = Serial.read();

    /*
    *  If ch isn't a newline
    *  (linefeed) character,
    *  we will add the character
    *  to the incomingString
    */
    if (ch != 10){
      // Add the character to
      // the incomingString
      incomingString += ch;
    }
    // received a newline (linefeed) character
    // this means we are done making a string
    else // We have receive a command
    {
      // print the incoming command
      Serial.println("Command received: ");
      Serial.println(incomingString);

      // Convert the string to an integer
      int val = incomingString.toInt();

      if(val == 0){
        handle_command(incomingString);
      }else{
        float diff = (float)val / 100.0;
        Serial.print("Setting speed to: ");
        Serial.print(diff);
        esc.set_speed(diff);
      }

      // print the integer

      // Reset the value of the incomingString
      incomingString = "";
    }
  }
}

