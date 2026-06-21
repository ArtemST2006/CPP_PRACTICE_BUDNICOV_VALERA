#include "PostMessage.h"
#include <utility>

PostMessage::PostMessage(std::string t) : text(std::move(t)) {}

PostMessage::~PostMessage() {
    for (Attachment* a : attachments) {
        delete a;
    }
}

void PostMessage::addAttachment(Attachment* att) {
    attachments.push_back(att);
}

std::string PostMessage::getType() const {
    return "PostMessage";
}

std::string PostMessage::getSummary() const {
    std::string s = "PostMessage: \"" + text + "\" (" + std::to_string(attachments.size()) + " вложений)";
    return s;
}
