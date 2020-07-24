#if (ARDUINO >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "LK9toggle.h"

LK9toggle::LK9toggle(uint8_t pin) {
  pinMode(pin, OUTPUT);
  _pin = pin;
}

bool LK9toggle::update(bool upd) {
	if (_interval != 0) {
		_now = millis();
		if (_now - _timer >= _interval || upd) {
			do {
				_timer += _interval;
				if (_timer < _interval) break;
			} while (_timer < _now - _interval);
			_state = !_state;
			_timer = _now;
		}
	}
	if (_state != _lstate) {
		digitalWrite(_pin, (_state) ? HIGH : LOW);
		_lstate = _state;
		return true;
	}
	return false;
}

void LK9toggle::on(bool upd) {
	_state = true;
	_interval = 0;
	if (upd) update(true);
}
void LK9toggle::off(bool upd) {
	_state = false;
	_interval = 0;
	if (upd) update(true);
}
void LK9toggle::timer(uint32_t interval) {
	off(true);
	_state = true;
	_timer = millis();
	_interval = interval;
	update(true);
}

bool LK9toggle::isOn() {
	return _state;
}
bool LK9toggle::isTimer() {
	return (_interval != 0) ? true : false;
}