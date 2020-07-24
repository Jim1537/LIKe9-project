/*
    LK9toggle is a simple library, intended for driving of single digital pin (on/off/periodical).
    This example shows how to use the LK9toggle functions.

    created Jul 2020
    by Vladimir Gorshunin aka Jim (http://jimblog.me)
    ====================================================
*/

// Include jPRes lib:
#include "LK9toggle.h"

/* For example let it be some LED on some digital pin
    But, of course, it can be something else drivable by signal on this pin: fan, relay, logical switch, etc.
*/

#define DEV_PIN 8           // LED control pin set as D8 (Any available digital pin can be used)

// Declare your LED as 'led1' object:
LK9toggle led1(DEV_PIN);
/* Note:
    You can add as many LEDs or other devices as you need (as long as you have enough digital signal pins on the board).
    LK9toggle dev(DEV2_PIN);
    LK9toggle fan1(FAN1_PIN);
    LK9toggle switch(SWITCH_PIN4);
    etc...
*/
void setup() {
  Serial.begin(115200);
  /* You can drive LED at any place in the code.
      There are several commands available:
      on()            - turn LED on
      off()           - turn LED off
      timer(interval) - set LED blink with the interval (millis: 1000 = 1 sec.)

      If you send boolean parameter 'true' to the on() or off() functions, LED will be updated instantly.
      Otherwise, the state of LED will be changed during the update() cycle (see below).
  */

  led1.on(true);
  Serial.println("LED is ON now");
  delay(2000);

  led1.off(true);
  Serial.println("LED is OFF now");
  delay(2000);

  led1.timer(2000);
  Serial.println("LED set to blink with the period of 2 sec...");
}

void loop() {
  /* Call update() function to drive LED.
      It's recommended to call update as frequently as it possible. It need to be called al least one time per blinking period you set.
      Function returns boolean 'true' if state of LED has been changed during current update.

    Note:
      You do not need to call update() function to set LED by on(true) or off(true). It happens automatically.
  */
  if (led1.update()) Serial.println("₍^･⚇･₎ Oink!");

  /* At any place in the code you can get the current state of LED using:
    isOn()        - returns boolean 'true' (LED is on) or boolean 'false' (LED is off)
    isTimer()     - returns boolean 'true' (LED is blinking = timer is ON) or boolean 'false' (LED is not blinking = timer is OFF)

    if (led1.update()) {
      if (led1.isOn())
        Serial.println("LED is ON");
      else
        Serial.println("LED is OFF");

      if (led1.isTimer())
        Serial.println("LED is blinking");
      else
        Serial.println("LED is NOT blinking");
    }
  */
}
