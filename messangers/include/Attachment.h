#pragma once

#include <string>

class Attachment {
public:
    Attachment(std::string filename);
    virtual ~Attachment() {}

    const std::string& getFilename() const { return filename; }

    virtual std::string getKind() const = 0;
    virtual std::string getInfo() const = 0;

protected:
    std::string filename;
};
