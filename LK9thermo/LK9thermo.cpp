#if (ARDUINO >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "LK9thermo.h"

LK9thermo::LK9thermo(uint8_t pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

void LK9thermo::set(uint32_t interval) {
	_interval = interval;
}
void LK9thermo::set(uint32_t interval, float VCC) {
	_interval = interval;
	_VCC = VCC;
}
void LK9thermo::set(uint32_t interval, float VCC, uint16_t R) {
	_interval = interval;
	_VCC = VCC;
	_R = R;
}
void LK9thermo::set(uint32_t interval, float VCC, uint16_t R, uint16_t RT0, uint16_t BC, float T0) {
	_interval = interval;
	_VCC = VCC;
	_R = R;
	_RT0 = RT0;
	_BC = BC;
	_T0 = T0 + 273.15;
}

bool LK9thermo::update(bool force) {
	_now = millis();
	if (_now - _timer >= _interval || force) {
		do {
			_timer += _interval;
			if (_timer < _interval) break;
		} while (_timer < _now - _interval);
		
		float VRT = (_VCC / 1023.00) * analogRead(_pin);
		_tprK = (1 / ((log((VRT / ((_VCC - VRT) / _R)) / _RT0) / _BC) + (1 / _T0)));
		_timer = _now;
		return true;
	}
	return false;
}


float LK9thermo::getK() {
	return _tprK*100;
}
float LK9thermo::getC() {
	return _tprK - 273.15;
}
float LK9thermo::getF() {
	return (_tprK - 273.15) * 1.8 + 32;
}