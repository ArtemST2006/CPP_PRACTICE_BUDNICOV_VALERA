#include "Date.h"
#include "Image.h"
#include "Video.h"
#include "PostMessage.h"
#include "LongVideo.h"
#include "ShortVideo.h"
#include "Published.h"
#include "Telegram.h"
#include "Max.h"
#include "RuTube.h"
#include "VKClips.h"

#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

static int readInt(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        int v;
        if (std::cin >> v) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return v;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Нужно целое число." << std::endl;
    }
}

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static Content* buildPostMessage() {
    std::string text = readLine("Текст поста: ");
    PostMessage* post = new PostMessage(text);
    while (true) {
        std::cout << "Добавить вложение? 1=Изображение, 2=Видео, 0=готово: ";
        int c = readInt("");
        if (c == 0) break;
        try {
            if (c == 1) {
                std::string fn = readLine("  имя файла (image.png): ");
                int w = readInt("  ширина: ");
                int h = readInt("  высота: ");
                post->addAttachment(new Image(fn, w, h));
            } else if (c == 2) {
                std::string fn = readLine("  имя файла (video.mp4): ");
                int d = readInt("  длительность (сек): ");
                post->addAttachment(new Video(fn, d));
            } else {
                std::cout << "Неизвестный выбор." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка вложения: " << e.what() << std::endl;
        }
    }
    return post;
}

static Content* buildLongVideo() {
    std::string fn = readLine("Имя файла видео (video.mp4): ");
    int dur = readInt("Длительность видео (сек, обычно >60): ");
    std::string desc = readLine("Описание видео: ");
    Video* v = new Video(fn, dur);
    return new LongVideo(v, desc);
}

static Content* buildShortVideo() {
    std::string fn = readLine("Имя файла клипа (clip.mp4): ");
    int dur = readInt("Длительность клипа (сек, обычно <=60): ");
    std::string desc = readLine("Описание клипа: ");
    Video* v = new Video(fn, dur);
    return new ShortVideo(v, desc);
}

static Date readDate() {
    std::cout << "Дата публикации:" << std::endl;
    int d = readInt("  день (1..31): ");
    int m = readInt("  месяц (1..12): ");
    int y = readInt("  год: ");
    int h = readInt("  час (0..23): ");
    int mi = readInt("  минута (0..59): ");
    return Date(d, m, y, h, mi);
}

static std::vector<Service*> pickServices(const std::string& contentType, const std::string& account) {
    std::vector<std::string> options;
    if (contentType == "PostMessage") {
        options.push_back("Telegram");
        options.push_back("Max");
    } else if (contentType == "LongVideo") {
        options.push_back("RuTube");
    } else if (contentType == "ShortVideo") {
        options.push_back("VKClips");
    }

    std::cout << "Совместимые сервисы для типа " << contentType << ":" << std::endl;
    for (std::size_t i = 0; i < options.size(); ++i) {
        std::cout << "  " << (i + 1) << ") " << options[i] << std::endl;
    }
    std::cout << "Введите номера через пробел (0 = выход без публикации): ";

    std::string line;
    std::getline(std::cin, line);
    std::vector<int> picks;
    std::string num;
    for (char ch : line) {
        if (ch == ' ' || ch == '\t' || ch == ',') {
            if (!num.empty()) { picks.push_back(std::stoi(num)); num.clear(); }
        } else if (ch >= '0' && ch <= '9') {
            num.push_back(ch);
        }
    }
    if (!num.empty()) picks.push_back(std::stoi(num));

    std::vector<Service*> result;
    for (int p : picks) {
        if (p == 0) continue;
        if (p < 1 || p > static_cast<int>(options.size())) {
            std::cout << "Пропущен номер вне диапазона: " << p << std::endl;
            continue;
        }
        const std::string& name = options[p - 1];
        if (name == "Telegram") result.push_back(new Telegram(account));
        else if (name == "Max") result.push_back(new Max(account));
        else if (name == "RuTube") result.push_back(new RuTube(account));
        else if (name == "VKClips") result.push_back(new VKClips(account));
    }
    return result;
}

static void runPublishScenario(std::vector<Published>& history) {
    std::cout << "\n=== Новая публикация ===" << std::endl;
    std::cout << "Тип контента: 1=PostMessage, 2=LongVideo (RuTube), 3=ShortVideo (VKClips): ";
    int kind = readInt("");

    Content* content = nullptr;
    try {
        if (kind == 1)      content = buildPostMessage();
        else if (kind == 2) content = buildLongVideo();
        else if (kind == 3) content = buildShortVideo();
        else { std::cout << "Неизвестный тип." << std::endl; return; }
    } catch (const std::exception& e) {
        std::cout << "Ошибка построения контента: " << e.what() << std::endl;
        delete content;
        return;
    }

    Date date;
    try {
        date = readDate();
    } catch (const std::exception& e) {
        std::cout << "Ошибка даты: " << e.what() << std::endl;
        delete content;
        return;
    }

    std::string account = readLine("Имя аккаунта/канала: ");
    std::vector<Service*> services = pickServices(content->getType(), account);

    if (services.empty()) {
        std::cout << "Сервисы не выбраны, контент уничтожен." << std::endl;
        delete content;
        return;
    }

    std::cout << "Подтвердить публикацию? (Y/n, Enter = да): ";
    std::string yn;
    std::getline(std::cin, yn);
    if (!yn.empty() && (yn[0] == 'n' || yn[0] == 'N' || yn.rfind("\xD0\xBD", 0) == 0 || yn.rfind("\xD0\x9D", 0) == 0)) {
        std::cout << "Отменено." << std::endl;
        for (Service* s : services) delete s;
        delete content;
        return;
    }

    bool anySuccess = false;
    for (Service* s : services) {
        try {
            Published p = s->publish(content, date);
            std::cout << "OK: " << p << std::endl;
            history.push_back(p);
            anySuccess = true;
        } catch (const std::invalid_argument& e) {
            std::cout << "Несовместимый контент (" << s->getName() << "): " << e.what() << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Сбой публикации (" << s->getName() << "): " << e.what() << std::endl;
        }
    }

    for (Service* s : services) delete s;
    if (!anySuccess) {
        delete content;
    }
}

static void runFailureDemo(std::vector<Published>& history) {
    std::cout << "\n=== Демо: исключение при несовместимом типе ===" << std::endl;
    Video* v = new Video("demo.mp4", 120);
    LongVideo* lv = new LongVideo(v, "Демонстрационное длинное видео");
    Telegram tg("demo");
    try {
        Published p = tg.publish(lv, Date(1, 1, 2026, 12, 0));
        history.push_back(p);
    } catch (const std::invalid_argument& e) {
        std::cout << "Поймано std::invalid_argument: " << e.what() << std::endl;
    }

    std::cout << "\n=== Демо: сбой API при account=\"fail\" ===" << std::endl;
    Telegram bad("fail");
    PostMessage* pm = new PostMessage("test");
    try {
        Published p = bad.publish(pm, Date(1, 1, 2026, 12, 0));
        history.push_back(p);
    } catch (const std::runtime_error& e) {
        std::cout << "Поймано std::runtime_error: " << e.what() << std::endl;
    }

    delete lv;
    delete pm;
}

static void printHistory(const std::vector<Published>& history) {
    std::cout << "\n=== История публикаций (" << history.size() << ") ===" << std::endl;
    for (std::size_t i = 0; i < history.size(); ++i) {
        std::cout << (i + 1) << ". " << history[i] << std::endl;
    }
}

int main() {
    std::vector<Published> history;
    std::vector<Content*> ownedContent;

    std::cout << "=== messangers: публикация во множество сервисов ===" << std::endl;

    while (true) {
        std::cout << "\nГлавное меню:" << std::endl;
        std::cout << "  1) Опубликовать контент" << std::endl;
        std::cout << "  2) Показать историю" << std::endl;
        std::cout << "  3) Демо исключений" << std::endl;
        std::cout << "  0) Выход" << std::endl;
        int choice = readInt("Выбор: ");

        if (choice == 0) break;
        else if (choice == 1) {
            std::size_t before = history.size();
            runPublishScenario(history);
            if (history.size() > before) {
                ownedContent.push_back(const_cast<Content*>(history.back().getContent()));
            }
        }
        else if (choice == 2) printHistory(history);
        else if (choice == 3) runFailureDemo(history);
        else std::cout << "Неизвестный пункт меню." << std::endl;
    }

    printHistory(history);

    for (Content* c : ownedContent) delete c;

    std::cout << "Завершение программы." << std::endl;
    return 0;
}
