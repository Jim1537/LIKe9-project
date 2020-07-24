/*
    LK9analog is a simple library, intended for getting readings from one or several analog sensors by internal timer.
    This example shows how to use the LK9analog functions.

    It can be any device providing some data over analogue input on arduino board.
    Let's say... I don't know... Let it be PHOTORESISTOR.

    created Jul 2020
    by Vladimir Gorshunin aka Jim (http://jimblog.me)
    ====================================================
*/

// Include LK9analog lib:
#include "LK9analog.h"

/* Define some constants...

    Note:
    You do not need to define some or all of constants below if you are going to use their default values.
*/
#define PHR_INTERVAL 3000   // Time interval between data collecting (millis; default is 3000 = 3 sec.)
#define PHR_PIN A0          // Photoresistor control pin set as A0 (Any available analog pin can be used)
#define PHR_LIMIT_MIN 0     // Minimum value to constrain readings (default is 0).
#define PHR_LIMIT_MAX 1023  // Maximum value to constrain readings (default is 1023).

// Declare your photoresistor as 'dev1' object:
LK9analog dev1(PHR_PIN);
/*
  You can add as many devices as you need (as long as you have enough analog signal pins on the board).
  Each device will have its own timer and other settings.

      LK9analog dev2(PHR_PIN2);
      LK9analog dev3(PHR_PIN3);
      LK9analog dev4(PHR_PIN4);
      etc...
*/

void setup() {
  Serial.begin(9600);

  /*
    Actually, you can DO NOTHING here!
    In this case, the time interval and other parameters will be taken by their default values (see the description of the constants above).

    But if you want to set your own specific time interval, you can do it (for each photoresistor declared above):
  */
  dev1.set(PHR_INTERVAL);

  /*
    By default, all the readings are constrained by full range of signal between 0 and 1023.
    But in the real life this range is more narrow. To increase the resolution of the results, you are able to set
    the actual range of reading.

        dev1.set(PHR_LIMIT_MIN, PHR_LIMIT_MAX);

    In this case you will get a sample of values ​​from a smaller range, which will increase
    the resolution of final readings.
  */
  dev1.set(PHR_LIMIT_MIN, PHR_LIMIT_MAX);

  /*
    Also, you can set all the parameters by one call (time interval and constraints):

        dev1.set(PHR_INTERVAL, PHR_LIMIT_MIN, PHR_LIMIT_MAX);
  */

}

void loop() {
  /* Call update() function to update readings.
    It doesn't matter how often you will call the update() function, data will be collected with the interval you set above.
    Just be sure to call update() BEFORE read values.
    
    Function returns boolean 'true' when the internal timer is ready and data is collected.

    It is possible to override internal timer sending boolean 'true' as the parameter to the function.
    In this case, internal timer will be bypassed and all the data will be collected immediately. Timer will be reseted to the time of last function call:

        dev1.update(true);

  */

  // Update the timer and check if it is ready and data is collected...
  if (dev1.update()) {
    /*
      If so, then you can get the values ​​by accessing the functions get():

        dev1.get();

      Function returns the value between 0 and 255.

      To get the raw value as is, use getRaw() function:

        dev1.getRaw();
    */
    Serial.print("Light level:\t");
    Serial.println(dev1.get());
  }
}
