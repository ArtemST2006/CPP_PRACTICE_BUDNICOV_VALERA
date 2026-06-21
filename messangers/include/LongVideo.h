#pragma once

#include "Content.h"
#include "Video.h"
#include <string>

class LongVideo : public Content {
public:
    LongVideo(Video* video, std::string description);
    ~LongVideo() override;

    LongVideo(const LongVideo&) = delete;
    LongVideo& operator=(const LongVideo&) = delete;

    const Video* getVideo() const { return video; }
    const std::string& getDescription() const { return description; }

    std::string getType() const override;
    std::string getSummary() const override;

private:
    Video* video;
    std::string description;
};
