#pragma once

#include "Image.h"

// Наследник Image - создаёт изображение заполненное чёрным цветом
class TemplateImage : public Image {
public:
    TemplateImage(int w, int h);
};
