#pragma once

#include "Attachment.h"

class Video : public Attachment {
public:
    Video(std::string filename, int durationSeconds);

    int getDurationSeconds() const { return durationSeconds; }

    std::string getKind() const override;
    std::string getInfo() const override;

private:
    int durationSeconds;
};
