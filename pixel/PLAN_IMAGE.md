# План разработки: Image / Pixel / TemplateImage

## Контекст

В директории `/Users/andrejvorobev/Documents/GitHub/CPP_PRACTICE_BUDNICOV_VALERA/pixel/` лежит ТЗ `C__Practice_Image.pdf` (новое задание про изображения), но существующий `PLAN.md` описывает другое задание (Тамагочи) — он не соответствует текущему ТЗ.

Нужно создать отдельный markdown-файл с планом разработки именно для задания из PDF — проект с классами `Pixel`, `Image`, `TemplateImage` (динамическая память, Rule of 5, перегрузка операторов, наследование, static/const).

**Файл плана**: `/Users/andrejvorobev/Documents/GitHub/CPP_PRACTICE_BUDNICOV_VALERA/pixel/PLAN_IMAGE.md` (отдельно от существующего `PLAN.md`).

## Описание задания (из PDF)

Реализовать класс `Image`, хранящий изображение как динамический массив пикселей (`Pixel`). Реализовать класс `TemplateImage`, наследник `Image`, создающий изображение, полностью заполненное чёрным цветом.

## Требования (из ТЗ)

1. Класс `Pixel` (red, green, blue).
2. `Image` с динамической памятью (хранит пиксели).
3. Rule of 5 для `Image`.
4. Методы доступа к пикселям по координатам + перегрузка `operator()`.
5. Перегрузка операторов: `+`, `==`, `<<`.
6. Использовать `static` и `const`.
7. `TemplateImage` с вызовом базового конструктора.
8. В `main()` показать разницу copy vs move.
9. Терминал должен печатать `Inside Copy Constructor`, `Inside Move Constructor` и т.д.
10. Работа в ветке `myname/task-image`, поддиректории `taskImage`.

## Структура проекта

```
pixel/
├── C__Practice_Image.pdf    # ТЗ
├── PLAN_IMAGE.md            # этот план
└── taskImage/
    ├── README.md            # декомпозиция
    ├── main.cpp             # демонстрация copy vs move
    ├── Pixel.h              # struct Pixel
    ├── Image.h              # объявление Image
    ├── Image.cpp            # реализация Image
    ├── TemplateImage.h      # наследник
    ├── TemplateImage.cpp
    └── Makefile
```

## Дизайн классов

### `Pixel`

```cpp
struct Pixel {
    unsigned char r, g, b;   // 0..255
};
```

### `Image`

**Поля:**
- `int width;`
- `int height;`
- `Pixel* data;` — динамический массив `width * height`
- `static int count;` — счётчик живых объектов

**Rule of 5:**
- `Image(int w, int h)` — конструктор с параметрами, выделяет `new Pixel[w*h]`, печатает `Inside Constructor`, `++count`
- `~Image()` — `delete[] data`, печатает `Inside Destructor`, `--count`
- `Image(const Image& other)` — копирующий конструктор: `new Pixel[...]` + поэлементное копирование, печатает `Inside Copy Constructor`, `++count`
- `Image& operator=(const Image& other)` — копирующее присваивание: проверка self-assign, `delete[] old`, `new`, копирование, печатает `Inside Copy Assignment`
- `Image(Image&& other) noexcept` — перемещающий конструктор: `data = other.data; other.data = nullptr;` + обнулить размеры, печатает `Inside Move Constructor`, `++count`
- `Image& operator=(Image&& other) noexcept` — перемещающее присваивание: self-check, `delete[] old`, перенос указателя + обнуление, печатает `Inside Move Assignment`

**Доступ к пикселям:**
- `Pixel& at(int x, int y);`
- `const Pixel& at(int x, int y) const;`
- `Pixel& operator()(int x, int y);`
- `const Pixel& operator()(int x, int y) const;`

**Перегрузки операторов:**
- `Image operator+(const Image& other) const;` — поэлементное сложение каналов с насыщением до 255 (clamp). Требует совпадения размеров.
- `bool operator==(const Image& other) const;` — равенство размеров и всех пикселей.
- `friend std::ostream& operator<<(std::ostream& os, const Image& img);` — печать размеров и/или ASCII-превью.

**Static / const:**
- `static int count;` — определение в `Image.cpp`: `int Image::count = 0;`
- `static int getCount();`
- `int getWidth() const;`
- `int getHeight() const;`

### `TemplateImage : public Image`

```cpp
class TemplateImage : public Image {
public:
    TemplateImage(int w, int h);   // : Image(w, h) и заполнение data[i] = {0,0,0}
};
```

Вызов базового конструктора через initializer list. В теле — цикл заполнения чёрным.

## `main.cpp` — демонстрация (требование ТЗ п.8)

Сценарии:
1. Создать `Image a(4, 4)`, заполнить пиксели через `a(x, y) = {...};`
2. Копирование: `Image b = a;` → ожидаем `Inside Copy Constructor`.
3. Перемещение: `Image c = std::move(a);` → ожидаем `Inside Move Constructor`. После — `a.data == nullptr`.
4. Копирующее присваивание: `Image d(2,2); d = b;` → `Inside Copy Assignment`.
5. Перемещающее присваивание: `Image e(2,2); e = std::move(b);` → `Inside Move Assignment`.
6. `operator+`: `Image sum = c + d;` (одинаковые размеры).
7. `operator==`: `c == d`.
8. `operator<<`: `std::cout << c;`
9. `TemplateImage t(3, 3);` — все пиксели `{0,0,0}`. Вывести через `<<`.
10. `Image::getCount()` — печать счётчика на разных стадиях.

## Makefile

```make
CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -O2

SRC=main.cpp Image.cpp TemplateImage.cpp
OBJ=$(SRC:.cpp=.o)

image: $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f image *.o
```

## Этапы реализации

1. Ветка и директория: `git checkout -b myname/task-image`, `mkdir taskImage`.
2. `Pixel.h` — struct.
3. `Image.h` + `Image.cpp` — Rule of 5, доступ, операторы, static.
4. `TemplateImage.h/.cpp` — наследник.
5. `main.cpp` — все сценарии п.8 ТЗ.
6. `Makefile`.
7. `README.md` — декомпозиция (требование ТЗ).
8. Сборка и прогон.

## Соответствие требованиям

| Требование ТЗ | Реализация |
|---|---|
| `Pixel` r,g,b | `struct Pixel` |
| Динамическая память | `Pixel* data; new[]/delete[]` |
| Rule of 5 | 5 спец-методов в `Image` |
| `at(x,y)` + `operator()` | const/non-const пары |
| `operator+`, `==`, `<<` | реализованы в `Image` |
| `static count` + `getCount` | счётчик объектов |
| `const` методы | `getWidth/getHeight/at const/...` |
| `TemplateImage` + базовый конструктор | `: Image(w,h)` + заполнение `{0,0,0}` |
| copy vs move в main | сценарии 2,3,4,5 |
| Логи в терминал | `cout` в каждом спец-методе |

## Критические файлы (создаются)

- `/Users/andrejvorobev/Documents/GitHub/CPP_PRACTICE_BUDNICOV_VALERA/pixel/PLAN_IMAGE.md` — этот план (копия итогового документа, основной артефакт текущей задачи).
- Далее (на этапе реализации): `taskImage/Pixel.h`, `taskImage/Image.{h,cpp}`, `taskImage/TemplateImage.{h,cpp}`, `taskImage/main.cpp`, `taskImage/Makefile`, `taskImage/README.md`.

## Verification

Текущая задача — создать только `PLAN_IMAGE.md`:
- Проверить наличие файла: `ls pixel/PLAN_IMAGE.md`.
- Прочитать содержимое — должно соответствовать пунктам ТЗ из PDF.
- Существующий `PLAN.md` (Тамагочи) не трогается.

После одобрения реализации (отдельная сессия):
- `cd taskImage && make` — собрать.
- `./image` — запустить, проверить порядок логов: Constructor → Copy Constructor → Move Constructor → ... → Destructor.
- Убедиться, что `Image::getCount()` корректно растёт/убывает.
- Проверить clamp в `operator+` (200+100 = 255).

## Примечание об области правок

В рамках текущей задачи создаётся **только** markdown-файл с планом. Исходный код C++ (`Image`, `TemplateImage` и т.д.) **не пишется** в этой сессии — реализация выполняется отдельно после одобрения плана.
