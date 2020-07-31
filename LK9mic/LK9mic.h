/*
	LK9mic
		by Vladimir Gorshunin aka Jim (http://jimblog.me)
		для проекта LIKe9 (http://like9.jimblog.me)

Простая библиотека чтения значений простого микрофона.
 
 Особенности:
	- Чтение значений с заданным интервалом (таймер сохраняет интервал даже при переполнении millis())
	- Фильтрация значений / устранение шумов (упрощённый Калман для одномерного случая)
	[спасибо, Alex Gyver: https://github.com/AlexGyver/GyverLibs]
 
	- Автоматическая настройка под текущий шумовой фон
	- Настройка параметров фильтрации
 
	- Получение исходных значений (0-1023)
	- Получение адаптированных фильтрованных значений (0-255)
 */

#ifndef LK9mic_h
	#define LK9mic_h
	#if (ARDUINO >=100)
		#include "Arduino.h"
	#else
		#include "WProgram.h"
	#endif
	
	// Умолчания:
	#define LK9MIC_INTERVAL 10		// Интервал чтения значений (millis 10 = 0.01 сек.)
	#define LK9MIC_FILTER_MSR 10.		// Разброс чтений для фильтра
	#define LK9MIC_FILTER_ERR 10.		// Разброс оценки чтений для фильтра
	#define LK9MIC_FILTER_GNE 1.		// Коэффицент скорости изменения значений для фильтра
	#define LK9MIC_SND_SAMPLES 100		// Размер выборки для нахождения пределов min-max
						// Чем больше размер выборки, тем плавнее будет происходить адаптация чтений под изменяющийся
						// общий звуковой фон. Не рекомендуется делать выборку слишком большой. 50-150 значений - оптимум.

	class LK9mic  {
		public:
			LK9mic(uint8_t pin);									// Объявление класса (номер входа на плате)

			void set(uint32_t interval);					// Настройка только интервала чтения (остальное будет взято по умолчанию)
			void set(uint32_t interval, float fltr_measure, float fltr_q);	// Настройка интервала чтения, размера выборки и фильтра: разброс значений, коэффицент скорости изменения значений (разброс оценки будет назначен равным разбросу значений)
			void set(uint32_t interval, float fltr_measure, float fltr_estimate, float fltr_q);
											// Настройка интервала чтения, размера выборки и фильтра: разброс значений, разброс оценки, коэффицент скорости изменения значений
		
			bool update(bool force = false);				// Вызов обновления чтений (true - для форсирования встроенного таймера)
		
			uint8_t get();							// Получить фильтрованные адаптированне значения (0-255)
			uint16_t getRaw();						// Получение исходные значения (0-1023)
			uint16_t getRawAdopted();					// Получение адаптированные исходные значения (0-1023)
		
		private:
			// Немного локальных переменных:
			uint8_t _pin;

			uint32_t _interval = LK9MIC_INTERVAL;
			uint32_t _now = 0;
			uint32_t _timer = 0;
		
			void swap (uint16_t *xp, uint16_t *yp);
			uint16_t _sndData[LK9MIC_SND_SAMPLES];
			uint16_t _sndData_Counter = 0;
		
			uint8_t _sndCurrent = 0;
			uint16_t _sndReadings = 0;
			uint16_t _sndAdopted = 0;
			uint16_t _sndLimit_Min = 0;
			uint16_t _sndLimit_Mid = 0;
			uint16_t _sndLimit_Max = 0;
		
			float filter(float value);
			float _fltr_measure = LK9MIC_FILTER_MSR;
			float _fltr_estimate = LK9MIC_FILTER_ERR;
			float _fltr_q = LK9MIC_FILTER_GNE;
			float _fltr_current_estimate = 0.0;
			float _fltr_last_estimate = 0.0;
			float _fltr_kalman_gain = 0.0;
	};
#endif
