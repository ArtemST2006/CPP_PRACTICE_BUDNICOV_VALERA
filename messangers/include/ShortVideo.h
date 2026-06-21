#pragma once

#include "Content.h"
#include "Video.h"
#include <string>

class ShortVideo : public Content {
public:
    ShortVideo(Video* video, std::string description);
    ~ShortVideo() override;

    ShortVideo(const ShortVideo&) = delete;
    ShortVideo& operator=(const ShortVideo&) = delete;

    const Video* getVideo() const { return video; }
    const std::string& getDescription() const { return description; }

    std::string getType() const override;
    std::string getSummary() const override;

private:
    Video* video;
    std::string description;
};
