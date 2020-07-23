/*
 LK9thermo is a simple library, intended for getting readings from one or several thermistors by internal timer.
 See using instructions in the example program.
 
 created Jun 2020
 by Vladimir Gorshunin aka Jim (http://jimblog.me)
 */

#ifndef LK9thermo_h
	#define LK9thermo_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	
	// Default values:
	#define JTRES_INTERVAL 3000								// Time interval between data collecting (millis; 3000 = 3 sec.)
	#define JTRES_VCC 3.3									// Thermistor control voltage (3.3V)
	#define JTRES_R 10000									// Pull-down resistor (Ω; 10000 = 10KΩ)
	#define JTRES_RT0  10000								// Resistance from thermistor parameters (Ω; 10000 = 10KΩ)
	#define JTRES_BC 3977									// Beta coefficient from thermistor parameters (3977)
	#define JTRES_T0 298.15									// 'T0' from thermistor parameters, converted to Kelvin (25 + 273.15)	

	class LK9thermo  {
		public:
			LK9thermo(uint8_t pin);							// Class declaration (control pin number)
		
			void set(uint32_t interval);						// Set time interval only
			void set(uint32_t interval, float VCC);					// Set time interval and operating voltage
			void set(uint32_t interval, float VCC, uint16_t R);			// Set time interval, operating voltage and Pull-down resistor value
			void set(uint32_t interval, float VCC, uint16_t R, uint16_t RT0, uint16_t BC, float T0); // Set time interval, operating voltage, Pull-down resistor value and RT0/K/T0 from thermistor datasheet
		
			bool update(bool force = false);					// Update sensor readings (true = override timer)
		
			float getK();								// Get reading, converted to Kelvin
			float getC();								// Get reading, converted to Celsius
			float getF();								// Get reading, converted to Fahrenheit
		
		private:
			// Some required working variables:
			uint8_t _pin;
			uint32_t _interval  = JTRES_INTERVAL;
			float _VCC = JTRES_VCC;
			uint16_t _R = JTRES_R;
			uint16_t _RT0 = JTRES_RT0;
			uint16_t _BC = JTRES_BC;
			float _T0 = JTRES_T0;
		
			float _tprK;
			uint32_t _now;
			uint32_t _timer;
	};
#endif
