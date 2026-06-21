#include "LongVideo.h"
#include <utility>
#include <stdexcept>

LongVideo::LongVideo(Video* v, std::string d) : video(v), description(std::move(d)) {
    if (v == nullptr) throw std::invalid_argument("LongVideo требует ненулевой Video*");
}

LongVideo::~LongVideo() {
    delete video;
}

std::string LongVideo::getType() const {
    return "LongVideo";
}

std::string LongVideo::getSummary() const {
    return "LongVideo: \"" + description + "\" [" + video->getInfo() + "]";
}
