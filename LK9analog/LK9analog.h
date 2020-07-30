/*
	LK9analog
		by Vladimir Gorshunin aka Jim (http://jimblog.me)
		для проекта LIKe9 (http://like9.jimblog.me)

Простая библиотека чтения аналоговых значений с внешних устройств.
 (фоторезисторы, сенсоры серии MQ, простые микрофоны уровня шума и т.п.)
 
 Особенности:
	- Чтение значений с заданным интервалом (таймер сохраняет интервал даже при переполнении millis())
	- Фильтрация значений / устранение шумов (упрощённый Калман для одномерного случая)
	[спасибо, Alex Gyver: https://github.com/AlexGyver/GyverLibs]
 
	- Настройка диапазона чтения
	- Настройка параметров фильтрации
 
	- Получение исходных значений (0-1023)
	- Получение фильтрованных значений с фильтрацией (0-1023)
	- Получение адаптированных фильтрованных значений (0-255)
 */

#ifndef LK9analog_h
	#define LK9analog_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	
	// Умолчания:
	#define LK9ANLG_INTERVAL 3000		// Интервал чтения значений (millis 3000 = 3 sec.)
	
	#define LK9ANLG_LIMIT_MIN 0		// Минимальный порог значений
	#define LK9ANLG_LIMIT_MAX 1023		// Максимальный порог значений
	
	#define LK9ANLG_FILTER_MSR 50.		// Разброс чтений для фильтра
	#define LK9ANLG_FILTER_ERR 50.		// Разброс оценки чтений для фильтра
	#define LK9ANLG_FILTER_GNE 0.5		// Коэффицент скорости изменения значений для фильтра

	class LK9analog  {
		public:
			LK9analog(uint8_t pin);							// Объявление класса (номер входа на плате)
		
			void set(uint32_t interval);						// Настройка интервала чтения (millis)
			void set(uint16_t limitMIN, uint16_t limitMAX);				// Настройка минимального и максимального порогов чтения (0-1023)
			void set(uint32_t interval, uint16_t limitMIN, uint16_t limitMAX);	// Настройка сразу всего (интервал, мин. порог чтения, макс. порог чтения)
			void setFilter(float err_measure, float err_estimate, float q);		// Настройка фильтра (разброс значений, разброс оценки, коэффицент скорости изменения значений)
		
			bool update(bool force = false);					// Вызов обновления чтений (true - для форсирования встроенного таймера)
		
			uint8_t get();								// Получить фильтрованные адаптированне значения (0-255)
			uint16_t getRaw();							// Получение исходные значения (0-1023)
			uint16_t getRawFiltered();						// Получение фильтрованные исходные значения (0-1023) 
				
		private:
			// Немного локальных переменных:
			uint8_t _pin;
			uint32_t _interval = LK9ANLG_INTERVAL;
			uint16_t _limitMIN = LK9ANLG_LIMIT_MIN;
			uint16_t _limitMAX = LK9ANLG_LIMIT_MAX;
		
			uint8_t _valueAdopted = 0;
			uint16_t _valueRaw = 0;
			uint16_t _valueRawFiltered = 0;
			uint32_t _now = 0;
			uint32_t _timer = 0;
		
			float filter(float value);
			float _fltr_measure = LK9ANLG_FILTER_MSR;
			float _fltr_estimate = LK9ANLG_FILTER_ERR;
			float _fltr_q = LK9ANLG_FILTER_GNE;
			float _fltr_current_estimate = 0.0;
			float _fltr_last_estimate = 0.0;
			float _fltr_kalman_gain = 0.0;
	};
#endif
