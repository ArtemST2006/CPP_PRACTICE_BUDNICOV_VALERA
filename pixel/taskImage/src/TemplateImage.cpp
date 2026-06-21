#include "../include/TemplateImage.h"

TemplateImage::TemplateImage(int w, int h) : Image(w, h) {
    for (int i = 0; i < w * h; ++i) {
        at(i % w, i / w) = {0, 0, 0};
    }
}
