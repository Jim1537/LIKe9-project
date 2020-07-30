/*
	LK9thermo
		Jun 2020
		by Vladimir Gorshunin aka Jim (http://jimblog.me)
		для проекта LIKe9 (http://like9.jimblog.me)

Простая библиотека чтения простого терморезистора
 
 Особенности:
	- Чтение значений с заданным интервалом (таймер сохраняет интервал даже при переполнении millis())
	- Настройка под любой терморезистор
 
	- Получение значений в Кельвинах, Цельсиях, Фаренгейтах
 */

#ifndef LK9thermo_h
	#define LK9thermo_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	
	// Умолчания:
	#define JTRES_INTERVAL 3000		// Интервал чтения значений (millis 3000 = 3 sec.)
	#define JTRES_VCC 3.3			// Вольтаж сигнала (3.3V)
	#define JTRES_R 10000			// Сопротивление понижающего резистора (Ω; 10000 = 10KΩ)
	#define JTRES_RT0  10000		// Сопротивление терморезистора (Ω; 10000 = 10KΩ)
	#define JTRES_BC 3977			// Beta-коэффициент терморезистора (3977)
	#define JTRES_T0 298.15			// 'T0' терморезистора в Кельвинах (25 + 273.15)	

	class LK9thermo  {
		public:
			LK9thermo(uint8_t pin);					// Объявление класса (номер входа на плате)
		
			void set(uint32_t interval);				// Настройка интервала чтения (millis)
			void set(uint32_t interval, float VCC);			// Настройка интервала чтения и вольтажа сигнала
			void set(uint32_t interval, float VCC, uint16_t R);	// Настройка интервала чтения, вольтажа сигнала и сопротивления понижающего резистора
			void set(uint32_t interval, float VCC, uint16_t R, uint16_t RT0, uint16_t BC, float T0);
										// Настройка ВСЕХ параметров: интервал, вольтаж, сопротивление понижающего резистора, сопротивление терморезистора, beta, T0
		
			bool update(bool force = false);			// Вызов обновления чтений (true - для форсирования встроенного таймера)
		
			float getK();						// Получить температуру в Кельвинах
			float getC();						// Получить температуру в Цельсиях
			float getF();						// Получить температуру в Фаренгейтах
		
		private:
			// Немного локальных переменных:
			uint8_t _pin;
			uint32_t _interval  = JTRES_INTERVAL;
			float _VCC = JTRES_VCC;
			uint16_t _R = JTRES_R;
			uint16_t _RT0 = JTRES_RT0;
			uint16_t _BC = JTRES_BC;
			float _T0 = JTRES_T0;
		
			float _tprK;
			uint32_t _now;
			uint32_t _timer;
	};
#endif
