#include "Attachment.h"
#include <utility>

Attachment::Attachment(std::string f) : filename(std::move(f)) {}
