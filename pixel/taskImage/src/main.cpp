#include <iostream>
#include "../include/Image.h"
#include "../include/TemplateImage.h"

int main() {
    std::cout << "=== Создаём Image a(4,4) ===" << std::endl;
    Image a(4, 4);
    std::cout << "Живых объектов: " << Image::getCount() << std::endl;

    a(0, 0) = {255, 0, 0};
    a(1, 0) = {0, 255, 0};
    a(2, 0) = {0, 0, 255};
    a(3, 0) = {200, 100, 50};

    std::cout << "\n=== Копирующий конструктор: Image b = a ===" << std::endl;
    Image b = a;
    std::cout << "Живых объектов: " << Image::getCount() << std::endl;

    std::cout << "\n=== Перемещающий конструктор: Image c = std::move(a) ===" << std::endl;
    Image c = std::move(a);
    std::cout << "Живых объектов: " << Image::getCount() << std::endl;
    std::cout << "a.getWidth() после move: " << a.getWidth() << std::endl;

    std::cout << "\n=== Копирующее присваивание: d = b ===" << std::endl;
    Image d(4, 4);
    d = b;
    std::cout << "Живых объектов: " << Image::getCount() << std::endl;

    std::cout << "\n=== Перемещающее присваивание: e = std::move(b) ===" << std::endl;
    Image e(4, 4);
    e = std::move(b);
    std::cout << "Живых объектов: " << Image::getCount() << std::endl;

    std::cout << "\n=== operator+ (c + d) ===" << std::endl;
    Image sum = c + d;
    std::cout << "Живых объектов: " << Image::getCount() << std::endl;

    std::cout << "\n=== operator== ===" << std::endl;
    std::cout << "c == d: " << (c == d ? "true" : "false") << std::endl;
    std::cout << "c == c: " << (c == c ? "true" : "false") << std::endl;

    std::cout << "\n=== operator<< ===" << std::endl;
    std::cout << c;

    std::cout << "\n=== TemplateImage t(3,3) ===" << std::endl;
    TemplateImage t(3, 3);
    std::cout << "Живых объектов: " << Image::getCount() << std::endl;
    std::cout << t;

    std::cout << "\n=== Проверка clamp: 200+100 должен дать 255 ===" << std::endl;
    Image x(1, 1);
    Image y(1, 1);
    x(0, 0) = {200, 100, 50};
    y(0, 0) = {100, 200, 210};
    Image z = x + y;
    std::cout << "r: " << (int)z(0,0).r << " (ожидаем 255)" << std::endl;
    std::cout << "g: " << (int)z(0,0).g << " (ожидаем 255)" << std::endl;
    std::cout << "b: " << (int)z(0,0).b << " (ожидаем 255)" << std::endl;

    std::cout << "\n=== Конец main ===" << std::endl;
    return 0;
}
