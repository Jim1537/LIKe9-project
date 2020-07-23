/*
    LK9touch is a simple library, intended for getting readings from one or several capacitive toch sensors.
    Has internal counter of touches with reset timer.
    This example shows how to use the LK9touch functions.

    created Jul 2020
    by Vladimir Gorshunin aka Jim (http://jimblog.me)
    ====================================================
*/

// Include LK9touch lib:
#include "LK9touch.h"

/* Define some constants...

    Note:
    You do not need to define some or all of constants below if you are going to use their default values.
*/
#define TCH_PIN 8                                 // Control pin
#define TCH_INTERVAL 200                          // Interval between single touches (millis, default is 50)
#define TCH_COUNTER_RESET 1500                    // Number of sequential touches counter reset time (millis, default is 1500 = 1.5 sec)

// Declare your sensor as 'dev1' object:
LK9touch dev1(TCH_PIN);
/* Note:
  You can add as many photoresistors as you need (as long as you have enough analog signal pins on the board).
  Each photoresistor will have its own timer and other settings.

      LK9photo dev2(TCH_PIN2);
      LK9photo dev3(TCH_PIN3);
      LK9photo dev4(TCH_PIN4);
      etc...
*/

void setup() {
  Serial.begin(115200);

  /*
     Actually, you can DO NOTHING here!
     In this case, all the parameters will be taken by their default values.

     But if you want to set your own specific parameters, you are able to do it.
  */


  /*
    By default the mode of sensor settled as LOW = "normal off".
    This is the same thing as for the common push button. Touch sensor you are using might be "normal on" or "normal off"
    You can change the mode by using setMode() function:

    dev1.setMode(HIGH);
    or
    dev1.setMode(LOW);
  */
  dev1.setMode(LOW);

  /*
    By default the interval betweel touches is setted as 50 millis.
    This is the time must pass between touches to count them as the different events.
    Several touches making with the less interval will be counted as one touch.

    You can change the interval by using setInterval() function:

    dev1.setMode(millis);
  */
  dev1.setInterval(TCH_INTERVAL);

  /*
    By default the internal counter of the sequential touches will be reseted
    in 1500 millis (= 1.5 sec) after the last touch. Next sequence will started from zero.

    You can change this time interval by using setReset() function:

    dev1.setReset(millis);
  */
  dev1.setReset(TCH_COUNTER_RESET);
}

void loop() {
  /*
    Call update() function to update the current sstate of the sensor and counter.
    Function returns boolean 'true' when the data will be collected.

    It doesn't matter how often you will call the update() function. Just be sure to call update() BEFORE read any states.

        dev1.update();
  */

  // Update readings and check if it was touched...
  if (dev1.update()) {
    // If so, then you can just to do something:
    Serial.println("₍^･⚇･₎ Oink!");

    /*
      At any place of the program you can get the current counts of sequential touches using getCounts() function:

        dev1.getCounts();
    */
    Serial.print("Counter: "); Serial.println(dev1.getCounts());


    /*
      The counter of sequential touches will be reset automatically in the time interval you set above.
      But if you need to reset the counter manually for some reason you can use the resetCounts() function at any place
      in the program:

       dev1.resetCounts();

       Counter will be reset immediately as the same as all the timers.
    */
  }
}

// Be in touch! :-)
