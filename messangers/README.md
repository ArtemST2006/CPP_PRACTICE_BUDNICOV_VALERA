# messangers

Публикация контента одновременно во множество соцсетей.

## Что сделано

### Базовая часть (оценка 4)

- Иерархия `Content`: `PostMessage`, `LongVideo`, `ShortVideo`.
- Иерархия `Attachment`: `Image` (ширина, высота), `Video` (длительность в секундах).
- Иерархия `Service`: `Telegram`, `Max`, `RuTube`, `VKClips` с виртуальным методом `publish(Content*, Date)`.
- Структура `Date` для запланированной публикации с `operator<<`.
- Класс `Published` хранит опубликованный контент, имя сервиса, аккаунт и дату; имеет `operator<<` для печати истории.
- Исключения при несовместимом типе контента (`std::invalid_argument`) и при сбое API (`std::runtime_error`).
- Грамотное распределение по `.cpp/.h` — каждый класс в своих двух файлах в `include/` и `src/`.
- Интерактивное меню в `main.cpp`: выбор типа, ввод вложений, выбор сервисов, подтверждение, демо исключений.

### Опциональные пункты (+3 балла)

- **+1**: Выбор аккаунта/канала для публикации (`main.cpp` запрашивает имя аккаунта перед выбором сервисов).
- **+1**: Указание запланированного времени публикации (`Date(день, месяц, год, час, минута)`).
- **+1**: Просмотр истории публикаций (через перегрузку `operator<<` у `Published`, пункт меню "Показать историю").

### Что не делалось

Расширение через `Publisher`-иерархию (`MessengerPublisher`, `LongVideoPublisher`, `ShortVideoPublisher`), расширенный `Response` со статус-кодами enum, `Request` с заголовками, редактирование опубликованного контента — пропущено осознанно.

## Целевая оценка

**4 + 3 = 7**

## Сборка и запуск

```bash
make
./messangers
```

Требуется `g++` с поддержкой C++17.

## Структура

```
include/   заголовки (Content, PostMessage, LongVideo, ShortVideo,
           Attachment, Image, Video, Service, Telegram, Max, RuTube,
           VKClips, Date, Request, Response, Published)
src/       реализации + main.cpp
Makefile   сборка
```

## Сценарии

- Опубликовать `PostMessage` в Telegram и Max одновременно (выбор номеров через пробел).
- Опубликовать `LongVideo` в RuTube.
- Опубликовать `ShortVideo` в VKClips.
- Демо исключений: попытка опубликовать `LongVideo` в Telegram → `std::invalid_argument`; публикация с аккаунтом `fail` → `std::runtime_error`.
- Просмотр истории всех успешных публикаций.
