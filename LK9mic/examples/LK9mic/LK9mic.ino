/*
  LK9mic
      by Vladimir Gorshunin aka Jim (http://jimblog.me)
      для проекта LIKe9 (http://like9.jimblog.me)

  Простая библиотека чтения значений простого микрофона.

  Особенности:
      - Чтение значений с заданным интервалом (таймер сохраняет интервал даже при переполнении millis())
      - Фильтрация значений / устранение шумов

      - Автоматическая настройка под текущий шумовой фон
      - Настройка параметров фильтрации

      - Получение исходных значений (0-1023)
      - Получение адаптированных фильтрованных значений (0-255)
*/

// Включение библиотеки LK9analog в скетч:
#include "LK9mic.h"

/*
  Определение констант...
    Не обязательно определять те константы, значения которых будут использованы по умолчанию.
    Для примера, все константы определены с их значениями по умолчанию.
*/
#define MIC_PIN A0              // Вход (аналоговый) сигнала на плате

#define MIC_INTERVAL 10        // Интервал чтения значений (millis 10 = 0.01 sec.)
#define MIC_FILTER_MSR 10.     // Разброс чтений для фильтра
#define MIC_FILTER_ERR 10.     // Разброс оценки чтений для фильтра
#define MIC_FILTER_GNE 1.      // Коэффицент скорости изменения значений для фильтра

/*
  Объявление класса объекта с передачей ему номера входа сигнала на плате:
*/
LK9mic dev1(MIC_PIN);
/*
  Можно объявить сколько угодно объектов (несколько микрофонов).
      ... Во всяком случае, пока хватает аналоговых входов на плате.
  Каждый из объектов может иметь свой собственный набор параметров.
  Можно задать им всем разные интервалы чтения, разные параметры фильтрации и т.п.

      LK9mic dev2(MIC2_PIN);
      LK9mic dev3(MIC3_PIN);
      LK9mic dev4(MIC4_PIN);
      LK9mic dev5(MIC5_PIN);
      и т.д.
*/

void setup() {
  Serial.begin(9600);

  /*
    Если планируется использовать все значения параметров по их умолчанию,
    то тут вообще можно ничего не делать.
    Но, для примера, зададим все параметры вручную:
  */
  dev1.set(MIC_INTERVAL, MIC_FILTER_MSR, MIC_FILTER_ERR, MIC_FILTER_GNE);

  /*
    Можно задавать только некоторые параметры, оставляя прочие по умолчанию.

    Только интервал чтения:
        dev1.set(MIC_INTERVAL);

    Интервал чтения, разброс чтений для фильтра и коэффицент скорости изменения значений.
    В этом случае, разброс оценки для фильтра будет приравнен к разбросу чтений:
        dev1.set(MIC_INTERVAL, MIC_FILTER_MSR, MIC_FILTER_GNE);
  */
}

void loop() {
  /*
    Для обновления значений используется функция update().
    Частота вызова этой функции, в общем случае - чем чаще, тем лучше.

    Непосредственно чтение значений и сопутствующие этому расчеты будут происходить с интервалом,
    заданным для таймера. Во всех остальных случаях, код "пролетит" дальше без задержек.

    Функция вернет логическое true, если в процессе вызова произошло чтение параметров.

    Если необходимо форсировать встроенный таймер объекта, необходимо вызвать функцию
    обновления, с параметром true:

      dev1.update(true);

    В этом случае, внутренний таймер будет сброшен (и начнет отсчет интервала с начала), чтение
    и сопутствующие расчеты значений произведутся НЕМЕДЛЕННО.

    Обновить чтение параметров по таймеру (если функция вернула true, значит произошло чтение и обработка значений (истек заданный интервал)):
  */
  if (dev1.update()) {
    /*
       Если произошло чтение и обработака значений, то их можно получить в адаптированном отфильтрованном виде:

           dev1.get();

      Фильтрация сигнала по Кальману (для одномерного случая). Параметры фильтрации настраиваются по желанию и обстоятельствам (см. выше)

      Функция возвращает некий условный "уровень громкости" сигнала в диапазоне 0-255 (byte). Для большинства
      обычных микрофонов, используемых в проектах для Arduino, максимальный уровень громкости никогда не будет
      достигнут. Но в диапазоне от 0 до 60-80 единиц громкости, можно действовать вполне уверенно.

      Считывать значения можно когда угодно и в любом месте кода. Но необходимо помнить, что новые значения
      будут даны только после срабатывания внутреннего таймера. Во всех остальных случаях будет возвращено
      последнее обработанное и сохраненное значение.
    */

    // Вывод для графика:
    Serial.print(dev1.get());
    Serial.print("\n");

    /*
      Мембрана микрофона колеблется, как вперед, так и назад, в соответствие с давлением на нее звуковых волн.
      Как следствие, если взять средний уровень этого диапазона колебаний, то получаемые значения, условно,
      можно считать "отрицательными" и "пложительными", относительно этого среднего уровня. Для последующей
      обработки значений удобнее "развернуть" все "отрицательные" значения в облась "положительных". Т.о. вы
      будете получать значение текущей громкости и интенсивности сигнала.

      Для получения такого рода адаптированного сигнала, используйте функцию:

           dev1.getRawAdopted();

      Без фильтрации.

      Поскольку "среднее значение" динамически подстраивается под текущий шумовой фон и характеристики
      используемого микрофона, то функция вычитает это "среднее" из общего значения и т.о., получаемый
      диапазон значений в своем минимуме всегда будет 0, каким бы не был текущий шумовой фон. Теоретически
      верхний предел в этом случае будет 512 (половина от общего 0-1023), но большинства обычных микрофонов,
      используемых в проектах для Arduino это значение, конечно, будет меньше.
    */

    /*
       Так же, всегда можно получить и необработанные исходные значения - буквально те, что выдал микрофон (0-1023):

           dev1.getRaw();
    */
  }
}
