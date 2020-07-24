/*
 LK9analog is a simple library, intended for getting readings from one or several analog sensors by internal timer.
 See using instructions in the example program.
 
 created Jun 2020
 by Vladimir Gorshunin aka Jim (http://jimblog.me)
 */

#ifndef LK9analog_h
	#define LK9analog_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	
	// Default values:
	#define LK9ANLG_INTERVAL 3000		// Time interval between data collecting (millis; 3000 = 3 sec.)
	#define LK9ANLG_LIMIT_MIN 0		// Minimum limit value (0)
	#define LK9ANLG_LIMIT_MAX 1023		// Maximum limit value (1023)

	class LK9analog  {
		public:
			LK9analog(uint8_t pin);							// Class declaration (control pin number)
			void set(uint32_t interval);						// Set time interval only
			void set(uint16_t limitMIN, uint16_t limitMAX);				// Set constrains only
			void set(uint32_t interval, uint16_t limitMIN, uint16_t limitMAX);	// Set time interval and constrains
		
			bool update(bool force = false);					// Update sensor readings (true = override timer)
			uint8_t get();								// Get adopted reading (0-223)
			uint16_t getRaw();							// Get raw reading (0-1023)
				
		private:
			// Some required working variables:
			uint8_t _pin;
			uint32_t _interval = LK9ANLG_INTERVAL;
			uint16_t _limitMIN = LK9ANLG_LIMIT_MIN;
			uint16_t _limitMAX = LK9ANLG_LIMIT_MAX;
		
			uint8_t _valueAdopted;
			uint16_t _valueRaw;
			uint32_t _now;
			uint32_t _timer;
	};
#endif
