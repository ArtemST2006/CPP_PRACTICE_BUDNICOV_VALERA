#include "Video.h"
#include <stdexcept>
#include <string>
#include <utility>

Video::Video(std::string fname, int d) : Attachment(std::move(fname)), durationSeconds(d) {
    if (d <= 0) throw std::invalid_argument("Длительность видео должна быть положительной");
}

std::string Video::getKind() const {
    return "Video";
}

std::string Video::getInfo() const {
    return "Video " + filename + " " + std::to_string(durationSeconds) + "s";
}
