/*
 LK9photo is a simple library, intended for getting readings from one or several thermistors by internal timer.
 See using instructions in the example program.
 
 created Jun 2020
 by Vladimir Gorshunin aka Jim (http://jimblog.me)
 */

#ifndef LK9photo_h
	#define LK9photo_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	
	// Default values:
	#define JPRES_INTERVAL 3000		// Time interval between data collecting (millis; 3000 = 3 sec.)
	#define JPRES_LIMIT_MIN 0		// Minimum limit value (0)
	#define JPRES_LIMIT_MAX 1023		// Maximum limit value (1023)

	class LK9photo  {
		public:
			LK9photo(uint8_t pin);							// Class declaration (control pin number)
			void set(uint32_t interval);						// Set time interval only
			void set(uint16_t limitMIN, uint16_t limitMAX);				// Set constrains only
			void set(uint32_t interval, uint16_t limitMIN, uint16_t limitMAX);	// Set time interval and constrains
		
			bool update(bool force = false);					// Update sensor readings (true = override timer)
			uint8_t get();								// Get reading
				
		private:
			// Some required working variables:
			uint8_t _pin;
			uint32_t _interval = JPRES_INTERVAL;
			uint16_t _limitMIN = JPRES_LIMIT_MIN;
			uint16_t _limitMAX = JPRES_LIMIT_MAX;
		
			uint8_t _light;
			uint32_t _now;
			uint32_t _timer;
	};
#endif
