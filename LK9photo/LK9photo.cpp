#if (ARDUINO >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "LK9photo.h"

LK9photo::LK9photo(uint8_t pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

bool LK9photo::update(bool force) {
	_now = millis();
	if (_now - _timer >= _interval || force) {
		do {
			_timer += _interval;
			if (_timer < _interval) break;
		} while (_timer < _now - _interval);
		
		uint16_t _readings = constrain(analogRead(_pin), _limitMIN, _limitMAX);
		_light = map(_readings, _limitMIN, _limitMAX, 0, 255);
		_timer = _now;
		return true;
	}
	return false;
}

void LK9photo::set(uint32_t interval) {
	_interval = interval;
}
void LK9photo::set(uint16_t limitMIN, uint16_t limitMAX) {
	_limitMIN = limitMIN;
	_limitMAX = limitMAX;
}
void LK9photo::set(uint32_t interval, uint16_t limitMIN, uint16_t limitMAX) {
	_interval = interval;
	_limitMIN = limitMIN;
	_limitMAX = limitMAX;
}

uint8_t LK9photo::get() {
	return _light;
}