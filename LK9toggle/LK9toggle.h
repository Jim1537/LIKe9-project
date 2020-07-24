/*
 LK9toggle is a simple library, intended for driving of single digital pin (on/off/periodical).
 See using instructions in the example program.
 
 created Jul 2020
 by Vladimir Gorshunin aka Jim (http://jimblog.me)
 */

#ifndef LK9toggle_h
	#define LK9toggle_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif

	class LK9toggle  {
		public:
			LK9toggle(uint8_t pin);							// Class declaration (control pin number)
		
			void on(bool upd = false);						// Set PIN on (true = do it NOW)
			void off(bool upd = false);						// Set PIN off (true = do it NOW)
			void timer(uint32_t interval);						// Set PIN auto on/off with time interval
		
			bool update(bool upd = false);						// Update PIN (true = do it NOW)
		
			bool isOn();								// Get On/Off status
			bool isTimer();								// Get timer status
		
		private:
			// Some required working variables:
			uint8_t _pin;
		
			bool _state = false;
			bool _lstate = false;
			uint32_t _interval = 0;
			uint32_t _now;
			uint32_t _timer;
	};
#endif
