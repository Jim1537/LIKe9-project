#if (ARDUINO >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "LK9touch.h"

LK9touch::LK9touch(uint8_t pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

void LK9touch::setMode(uint8_t mode) {
	_mode = mode;
}
void LK9touch::setInterval(uint32_t interval) {
	_interval = interval;
}
void LK9touch::setReset(uint32_t reset) {
	_reset = reset;
}


bool LK9touch::update() {
	_state = digitalRead(_pin);
	if (_state != _lstate) {
		_lstate = _state;
		_now = millis();
		
		if (_state != _mode && _now - _last >= _interval) {
			do {
				_last += _interval;
				if (_last < _interval) break;
			} while (_last < _now - _interval);
			
			if (_now - _last >= _reset) _counts = 0;
			_counts++;
			_last = _now;
			_nstate = true;
			return _nstate;
		}
	}
	_nstate = false;
	return _nstate;
}

uint8_t LK9touch::getState() {
	return _nstate;
}
uint8_t LK9touch::getCounts() {
	return _counts;
}
uint8_t LK9touch::resetCounts() {
	_counts = 0;
}
