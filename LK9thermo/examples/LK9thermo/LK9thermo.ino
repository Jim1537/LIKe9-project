/*
    LK9thermo is a simple library, intended for getting readings from one or several thermistors by internal timer.
    This example shows how to use the LK9thermo functions.

    created Jun 2020
    by Vladimir Gorshunin aka Jim (http://jimblog.me)
    ====================================================
*/

/* thermistor parameters from datasheet (example):
  RT0:  10000Ω
        Thermistor base resistance.

  B:    3977K (±0.75%)
        'Beta coefficient' (B).
        The B value is a material constant which is determined by the ceramicmaterial from which it is made.
        It describes the gradient of the resistive (R/T) curve over a particular temperature range between two temperature points.

  T0:   25C (±5%)
        As the resistance varies with temperature, it is necessary to state the temperature at which the component has the required resistance.
        Normally a temperature of 25°C is used and this may be stated as the value.
*/


// Include LK9thermo lib:
#include "LK9thermo.h"

//  Now, define some constants:
#define THR_PIN A1          // Thermistor control pin set as A1 (Any available analog pin can be used)
/* Note:
	You do not need to define some or all of constants below if you are going to use their default values.
*/
#define THR_INTERVAL 3000   // Time interval between data collecting (millis; default is 3000 = 3 sec.)
#define THR_VCC 3.3         // Thermistor Control Voltage set as (VCC; default is 3.3)
#define THR_R 10000         // Pull-down resistor value (Ω; default is 10000 = 10KΩ)
#define THR_RT0 10000       // Resistance from the thermistor parameters above (Ω; default is 10000 = 10KΩ)
#define THR_B 3977          // Temperature range (Kelvins) from the thermistor parameters above (default is 3977)
#define THR_T0 25           // T0 from the thermistor parameters above (!!!IMPORTANT: Celsius!!! default is 25)

// Declare your thermistor as 'dev1' object:
LK9thermo dev1(THR_PIN);
/* Note:
  You can add as many thermistors as you need (as long as you have enough analog signal pins on the board).
  Each thermistor may have its own parameters, including different time intervals between readings
    LK9thermo dev2(THR_PIN2);
    LK9thermo dev3(THR_PIN3);
    LK9thermo dev4(THR_PIN4);
    etc...
*/

void setup() {
  Serial.begin(115200);

  /*
    You can DO NOTHING here!
    In this case, ALL the parameters will be taken by its default values (see the description of the constants above).

    If you need to use your own specific parameters, you can do this for some or all of them (for each photoresistor declared above):

        set(THR_INTERVAL);
    Set Time Interval only. The rest of the parameters will be taken by defaults.

        set(THR_INTERVAL, SNS_THR_VCC);
    Set Time Interval and Control Voltage value. The rest of the parameters will be taken by defaults.

        set(THR_INTERVAL, SNS_THR_VCC, SNS_THR_R);
    Set Time Interval, Voltage and Pull-down resistor values. The rest of the parameters will be taken by defaults.

    Set ALL the parametrs manualy:
  */
  dev1.set(THR_INTERVAL, THR_VCC, THR_R, THR_RT0, THR_B, THR_T0);
}

void loop() {
  /*
    Call dev1.update() function to update readings with the time interval you set. It doesent matter how often you will call the update function. Just be sure to call update() BEFORE read values.

    Function returns boolean 'true' when the data will be collected.

    It is possible to override internal timer sending boolean 'true' as the parameter to the function.
    In this case, internal timer will be bypassed and all the data will be collected immediately. Timer will be reseted to the time of last function call:

        dev1.update(true);

    Function returns the boolean 'true' when timer will be ready and data has been collected.
  */

  // Update the timer and check if it is ready = data has been collected...
  if (dev1.update()) {
    /* If so, then you can get the values ​​by accessing the functions:

        dev1.getK()
        dev1.getC()
        dev1.getF()
        (Kelvin, Celsius or Fahrenheit, respectively)

    */
    Serial.print("Temperature:\t");
    Serial.print(dev1.getK()); Serial.print("°K; \t");
    Serial.print(dev1.getC()); Serial.print("°C; \t");
    Serial.print(dev1.getF()); Serial.print("°F;");
    Serial.print("\n");
  }
}
