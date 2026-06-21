#pragma once

#include "Attachment.h"

class Image : public Attachment {
public:
    Image(std::string filename, int width, int height);

    int getWidth() const { return width; }
    int getHeight() const { return height; }

    std::string getKind() const override;
    std::string getInfo() const override;

private:
    int width;
    int height;
};
