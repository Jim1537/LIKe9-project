#if (ARDUINO >=100)
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "LK9mic.h"

LK9mic::LK9mic(uint8_t pin) {
  pinMode(pin, INPUT);
  _pin = pin;
}

void LK9mic::set(uint32_t interval) {
	_interval = interval;
}
void LK9mic::set(uint32_t interval, float fltr_measure, float fltr_q) {
	_interval = interval;
	_fltr_measure = _fltr_estimate = fltr_measure;
	_fltr_q = fltr_q;
}
void LK9mic::set(uint32_t interval, float fltr_measure, float fltr_estimate, float fltr_q) {
	_interval = interval;
	_fltr_measure = fltr_measure;
	_fltr_estimate = fltr_estimate;
	_fltr_q = fltr_q;
}
		
bool LK9mic::update(bool force) {
	_now = millis();
	if (_now - _timer >= _interval || force) {
		do {
			_timer += _interval;
			if (_timer < _interval) break;
		} while (_timer < _now - _interval);
		_sndReadings = analogRead(_pin);
		if (++_sndData_Counter > LK9MIC_SND_SAMPLES - 1) _sndData_Counter = 0;
		_sndData[_sndData_Counter] = _sndReadings;

		for (uint16_t i = 0; i < LK9MIC_SND_SAMPLES - 1; i++)
			for (uint16_t j = 0; j < LK9MIC_SND_SAMPLES - i - 1; j++)
				if (_sndData[j] > _sndData[j + 1])
					swap(&_sndData[j], &_sndData[j + 1]);
		_sndLimit_Min = _sndData[0];
		_sndLimit_Max = _sndData[LK9MIC_SND_SAMPLES - 1];
		_sndLimit_Mid = (_sndLimit_Min + _sndLimit_Max) / 2;
		if (_sndReadings < _sndLimit_Mid)
			_sndAdopted = _sndLimit_Mid + (_sndLimit_Mid - _sndReadings);
		else
			_sndAdopted = _sndReadings;
		_sndCurrent = filter(map(_sndAdopted - _sndLimit_Mid, 0, 1023 - _sndLimit_Mid, 0, 255));
		return true;
	}
	return false;
}
		
uint8_t LK9mic::get() {
	return _sndCurrent;
}
uint16_t LK9mic::getRaw() {
	return _sndReadings;
}
uint16_t LK9mic::getRawAdopted() {
	return _sndAdopted - _sndLimit_Mid;
}

void LK9mic::swap (uint16_t *xp, uint16_t *yp) {
  uint16_t temp = *xp;
  *xp = *yp;
  *yp = temp;
}

float LK9mic::filter(float value) {
  _fltr_kalman_gain = _fltr_estimate / (_fltr_estimate + _fltr_measure);
  _fltr_current_estimate = _fltr_last_estimate + _fltr_kalman_gain * (value - _fltr_last_estimate);
  _fltr_estimate =  (1.0 - _fltr_kalman_gain) * _fltr_estimate + fabs(_fltr_last_estimate - _fltr_current_estimate) * _fltr_q;
  _fltr_last_estimate = _fltr_current_estimate;

  return _fltr_current_estimate;
}