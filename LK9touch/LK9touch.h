/*
LK9touch is a simple library, intended for getting readings from one or several capacitive toch sensors.
Has internal counter of touches with reset timer.
See using instructions in the example program.
 
created Jul 2020
 by Vladimir Gorshunin aka Jim (http://jimblog.me)
 */

#ifndef LK9touch_h
	#define LK9touch_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	
	// Default values:
	#define JTCH_MODE LOW				// Sensor signal mode (LOW is "normal off"; HIGH is "normal on";)
	#define JTCH_INTERVAL 50			// Interval between touches (millis)
	#define JTCH_COUNTER_RESET 1500			// Number of sequential touches counter reset time (millis)


	class LK9touch  {
		public:
			LK9touch(uint8_t pin);							// Class declaration (control pin number)
		
			void setMode(uint8_t mode);						// Set signal mode (true - HIGH state is untouched; false - LOW state is untouched)
			void setInterval(uint32_t interval);					// Time between touches (millis)
			void setReset(uint32_t reset);						// Number of sequential touches counter reset time (millis)
		
			bool update();								// Update PIN (true = do it NOW)
	
			uint8_t getState();							// Get current state (true = touched; false = untouched)
			uint8_t getCounts();							// Get sequential touches counts (0 - 254)
			uint8_t resetCounts();							// Reset sequential touches counter
		private:
			// Some required working variables:
			uint8_t _pin;
			uint8_t _mode = JTCH_MODE;
			uint32_t _interval = JTCH_INTERVAL;
			uint32_t _reset = JTCH_COUNTER_RESET;
		
			uint32_t _now = millis();
			uint32_t _last = _now;
			uint8_t _state;
			uint8_t _lstate;
			uint8_t _nstate;
		
			uint8_t _counts;
	};
#endif
