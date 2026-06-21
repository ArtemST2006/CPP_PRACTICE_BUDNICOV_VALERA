#include "Image.h"
#include <stdexcept>
#include <string>
#include <utility>

Image::Image(std::string fname, int w, int h) : Attachment(std::move(fname)), width(w), height(h) {
    if (w <= 0 || h <= 0) throw std::invalid_argument("Размеры изображения должны быть положительными");
}

std::string Image::getKind() const {
    return "Image";
}

std::string Image::getInfo() const {
    return "Image " + filename + " " + std::to_string(width) + "x" + std::to_string(height);
}
