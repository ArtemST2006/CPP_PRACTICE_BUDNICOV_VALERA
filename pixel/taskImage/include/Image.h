#pragma once

#include <iostream>
#include "Pixel.h"

class Image {
private:
    int width;
    int height;
    Pixel* data;
    static int count;

public:
    Image(int w, int h);
    ~Image();
    Image(const Image& other);
    Image& operator=(const Image& other);
    Image(Image&& other) noexcept;
    Image& operator=(Image&& other) noexcept;

    Pixel& at(int x, int y);
    const Pixel& at(int x, int y) const;
    Pixel& operator()(int x, int y);
    const Pixel& operator()(int x, int y) const;

    Image operator+(const Image& other) const;
    bool operator==(const Image& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Image& img);

    int getWidth() const;
    int getHeight() const;
    static int getCount();
};
