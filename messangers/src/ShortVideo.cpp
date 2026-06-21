#include "ShortVideo.h"
#include <utility>
#include <stdexcept>

ShortVideo::ShortVideo(Video* v, std::string d) : video(v), description(std::move(d)) {
    if (v == nullptr) throw std::invalid_argument("ShortVideo требует ненулевой Video*");
}

ShortVideo::~ShortVideo() {
    delete video;
}

std::string ShortVideo::getType() const {
    return "ShortVideo";
}

std::string ShortVideo::getSummary() const {
    return "ShortVideo: \"" + description + "\" [" + video->getInfo() + "]";
}
