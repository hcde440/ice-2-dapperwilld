
/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.

//Arduino IO Dashboard URL: https://io.adafruit.com/wdodson/dashboards/hcde-440-ice-number-2
#include "config.h"0

/************************ Example Starts Here *******************************/

// digital pin 
#define BUTTON_PIN 2

// button1 state
bool current = false;
bool last = false;
// button 2 state
bool othercurrent = false;
bool otherlast = false;

// set up the 'digital' feed
AdafruitIO_Feed *digital = io.feed("button");

void setup() {

  // set button pins as an input
  pinMode(BUTTON_PIN, INPUT);
  pinMode(5, INPUT);

  // start the serial connection
  Serial.begin(115200);
  // prints out the file name and compile date to the Serial Monitor
  Serial.print("This board is running: ");
  Serial.println(F(__FILE__));
  Serial.print("Compiled: ");
  Serial.println(F(__DATE__ " " __TIME__));
   
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();// establishes connection to Adafruit IO da

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());// prints status of connection

}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // grab the current state of the button.
  // we have to flip the logic because we are
  // using a pullup resistor.
  if(digitalRead(BUTTON_PIN) == LOW)
    current = true;
  else
    current = false;

  // return if the value hasn't changed
  if(current == last)
    return;
  // makes the same check for the second button.
  if(digitalRead(5) == LOW)
    othercurrent = 0;
  else
    othercurrent = 5;//Assigns other button value to 5 to delineate it from button which is either 0/1

  // return if the value hasn't changed
  if(othercurrent == otherlast)
    return;

  // save the current state to the 'button' feed on adafruit io
  Serial.print("sending button -> ");//prints message to Serial Monitor
  Serial.println(current);
  digital->save(current);//Saves the last button value 
  Serial.print("sending other button -> ");//prints othermessage to Serial Monitor
  Serial.println(othercurrent);
  digital->save(othercurrent);//Saves the last otherbutton value

  // store last button states
  last = current;
  otherlast = othercurrent;

}
