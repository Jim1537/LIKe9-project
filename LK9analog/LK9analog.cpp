#if (ARDUINO >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "LK9analog.h"

LK9analog::LK9analog(uint8_t pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

bool LK9analog::update(bool force) {
	_now = millis();
	if (_now - _timer >= _interval || force) {
		do {
			_timer += _interval;
			if (_timer < _interval) break;
		} while (_timer < _now - _interval);
		
		_valueRaw = analogRead(_pin);
		_valueAdopted = map(constrain(_valueRaw, _limitMIN, _limitMAX), _limitMIN, _limitMAX, 0, 254);
		_timer = _now;
		return true;
	}
	return false;
}

void LK9analog::set(uint32_t interval) {
	_interval = interval;
}
void LK9analog::set(uint16_t limitMIN, uint16_t limitMAX) {
	_limitMIN = limitMIN;
	_limitMAX = limitMAX;
}
void LK9analog::set(uint32_t interval, uint16_t limitMIN, uint16_t limitMAX) {
	_interval = interval;
	_limitMIN = limitMIN;
	_limitMAX = limitMAX;
}

uint8_t LK9analog::get() {
	return _valueAdopted;
}
uint16_t LK9analog::getRaw() {
	return _valueRaw;
}