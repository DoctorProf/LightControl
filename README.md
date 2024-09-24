Составляющая цвета всегда должна иметь тип int
`r: int g: int b: int`

# Mode
тут должно быть описание структуры хранения режима

# Info
Содержит общую информацию о текущем состоянии

Пример ответа:
```
{
    "current_brightness": 60,
    "current_mode": 0,
    "enable": 0
}
```

# App - Server methods

`getInfo()` - Возвращает все данные текущего состояния

---

`toggle()` - Переключить ленту (устнановить выкл если сейчас вкл и наоборот)

`setState(state)` - Установить ленту в режим вкл если 1 и выкл если 0

---

`setBrightness(brightness)` - Установить яркость

`setSpeed(speed)` - Установить скорость

`getSpeed()` - Получить скорость

---

`createMode(mode: Mode) -> modeId` - Создание нового режима

`getModes() -> list[mode]` - Получить список доступных режимов 

`selectMode(modeId)` - Выбрать режим

`getModeInfo(modeId)` - Получить информацию о режиме (кастомные параметры, название)

# Code / Blocks methods

`setLedColor(ledIndex, r, g, b)` - Установить цвет пикселя

`setStripColor(r, g, b)` - Установить цвет всей ленты

`setFade(ledIndex1, ledIndex2, r1, g1, b1, r2, g2, b2)` - Установить градиент для отрезка

`setSegmentColor(ledIndex1, ledIndex2, r, g, b)` - Установить цвет для сегмента

`setStepColor(step, offset, r1, g1, b1, r2, g2, b2)` - Установить чередование цветов

# Server - controller request methods

`setLedColors(colors=[r, g, b, r, g, b, ...]) POST` - Установить цвета светодиодов (передаем массив значений цвета для каждого светодиода в виде набора байт) 

`setStripColor(r, g, b) GET` - Залить всю ленту одним цветом
