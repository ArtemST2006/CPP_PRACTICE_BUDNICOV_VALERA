#pragma once

#include "Content.h"
#include "Attachment.h"
#include <string>
#include <vector>

class PostMessage : public Content {
public:
    PostMessage(std::string text);
    ~PostMessage() override;

    PostMessage(const PostMessage&) = delete;
    PostMessage& operator=(const PostMessage&) = delete;

    void addAttachment(Attachment* att);

    const std::string& getText() const { return text; }
    const std::vector<Attachment*>& getAttachments() const { return attachments; }

    std::string getType() const override;
    std::string getSummary() const override;

private:
    std::string text;
    std::vector<Attachment*> attachments;
};
