#include "../include/Image.h"
#include <iostream>
#include <stdexcept>

int Image::count = 0;

Image::Image(int w, int h) : width(w), height(h), data(new Pixel[w * h]) {
    std::cout << "Inside Constructor" << std::endl;
    ++count;
}

Image::~Image() {
    delete[] data;
    std::cout << "Inside Destructor" << std::endl;
    --count;
}

Image::Image(const Image& other) : width(other.width), height(other.height), data(new Pixel[other.width * other.height]) {
    std::cout << "Inside Copy Constructor" << std::endl;
    for (int i = 0; i < width * height; ++i) {
        data[i] = other.data[i];
    }
    ++count;
}

Image& Image::operator=(const Image& other) {
    std::cout << "Inside Copy Assignment" << std::endl;
    if (this == &other) {
        return *this;
    }
    delete[] data;
    width = other.width;
    height = other.height;
    data = new Pixel[width * height];
    for (int i = 0; i < width * height; ++i) {
        data[i] = other.data[i];
    }
    return *this;
}

Image::Image(Image&& other) noexcept : width(other.width), height(other.height), data(other.data) {
    std::cout << "Inside Move Constructor" << std::endl;
    other.data = nullptr;
    other.width = 0;
    other.height = 0;
    ++count;
}

Image& Image::operator=(Image&& other) noexcept {
    std::cout << "Inside Move Assignment" << std::endl;
    if (this == &other) {
        return *this;
    }
    delete[] data;
    width = other.width;
    height = other.height;
    data = other.data;
    other.data = nullptr;
    other.width = 0;
    other.height = 0;
    return *this;
}

Pixel& Image::at(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Координаты пикселя вне диапазона");
    }
    return data[y * width + x];
}

const Pixel& Image::at(int x, int y) const {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::out_of_range("Координаты пикселя вне диапазона");
    }
    return data[y * width + x];
}

Pixel& Image::operator()(int x, int y) {
    return at(x, y);
}

const Pixel& Image::operator()(int x, int y) const {
    return at(x, y);
}

Image Image::operator+(const Image& other) const {
    if (width != other.width || height != other.height) {
        throw std::invalid_argument("Размеры изображений должны совпадать");
    }
    Image result(width, height);
    for (int i = 0; i < width * height; ++i) {
        int r = data[i].r + other.data[i].r;
        int g = data[i].g + other.data[i].g;
        int b = data[i].b + other.data[i].b;
        // clamp до 255
        result.data[i].r = (unsigned char)(r > 255 ? 255 : r);
        result.data[i].g = (unsigned char)(g > 255 ? 255 : g);
        result.data[i].b = (unsigned char)(b > 255 ? 255 : b);
    }
    return result;
}

bool Image::operator==(const Image& other) const {
    if (width != other.width || height != other.height) {
        return false;
    }
    for (int i = 0; i < width * height; ++i) {
        if (data[i].r != other.data[i].r ||
            data[i].g != other.data[i].g ||
            data[i].b != other.data[i].b) {
            return false;
        }
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const Image& img) {
    os << "Image [" << img.width << "x" << img.height << "]" << std::endl;
    int preview = img.width * img.height;
    if (preview > 9) preview = 9;
    for (int i = 0; i < preview; ++i) {
        os << "  pixel[" << i << "] = ("
           << (int)img.data[i].r << ", "
           << (int)img.data[i].g << ", "
           << (int)img.data[i].b << ")" << std::endl;
    }
    if (img.width * img.height > 9) {
        os << "  ..." << std::endl;
    }
    return os;
}

int Image::getWidth() const { return width; }
int Image::getHeight() const { return height; }
int Image::getCount() { return count; }
