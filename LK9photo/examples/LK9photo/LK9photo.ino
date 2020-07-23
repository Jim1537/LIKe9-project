/*
    LK9photo is a simple library, intended for getting readings from one or several photoresistors by internal timer.
    This example shows how to use the LK9photo functions.

    created Jul 2020
    by Vladimir Gorshunin aka Jim (http://jimblog.me)
    ====================================================
*/

// Include LK9photo lib:
#include "LK9photo.h"

/* Define some constants...

    Note:
    You do not need to define some or all of constants below if you are going to use their default values.
*/
#define PHR_INTERVAL 3000   // Time interval between data collecting (millis; default is 3000 = 3 sec.)
#define PHR_PIN A1          // Photoresistor control pin set as A1 (Any available analog pin can be used)
#define PHR_LIMIT_MIN 0     // Minimum value to constrain readings (default is 0).
#define PHR_LIMIT_MAX 1023  // Maximum value to constrain readings (default is 1023).

// Declare your photoresistor as 'dev1' object:
LK9photo dev1(PHR_PIN);
/*
  You can add as many photoresistors as you need (as long as you have enough analog signal pins on the board).
  Each photoresistor will have its own timer and other settings.
  
      LK9photo dev2(PHR_PIN2);
      LK9photo dev3(PHR_PIN3);
      LK9photo dev4(PHR_PIN4);
      etc...
*/

void setup() {
  Serial.begin(115200);

  /*
    Actually, you can DO NOTHING here!
    In this case, the time interval and other parameters will be taken by their default values (see the description of the constants above).

    But if you want to set your own specific time interval, you can do it (for each photoresistor declared above):
  */
  dev1.set(PHR_INTERVAL);

  /*
    By default, all the readings are constrained by full range of signal between 0 and 1023.
    But in real life this range more narrow. To increase the resolution of results you are able to set
    the actual range of reading.

        dev1.set(PHR_LIMIT_MIN, PHR_LIMIT_MAX);

    In this case you will get a sample of values ​​from a smaller range, which will increase
    the resolution of final readings.
  */

  /*
    Also, you can set all the parameters by one call (time interval and constraints):

        dev1.set(PHR_INTERVAL, PHR_LIMIT_MIN, PHR_LIMIT_MAX);
  */

}

void loop() {
  /* Call update() function to update readings with the time interval you set.
    Function returns boolean 'true' when the data will be collected.

    It doesn't matter how often you will call the update() function. Just be sure to call update() BEFORE read values.

    It is possible to override internal timer sending boolean 'true' as the parameter to the function.
    In this case, internal timer will be bypassed and all the data will be collected immediately. Timer will be reseted to the time of last function call:

        dev1.update(true);

        Function returns the boolean 'true' when timer will be ready and data has been collected.
  */

  // Update the timer and check if it is ready = data has been collected...
  if (dev1.update()) {
    /*
      If so, then you can get the values ​​by accessing the functions:

          dev1.get();

      Function returns the value between 0 (low light level) and 255 (high light level).
    */
    Serial.print("Light level:\t");
    Serial.println(dev1.get());
  }
}
