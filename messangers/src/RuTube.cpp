#include "RuTube.h"
#include "Request.h"
#include "Response.h"
#include <stdexcept>
#include <utility>

RuTube::RuTube(std::string a) : Service(std::move(a)) {}

std::string RuTube::getName() const {
    return "RuTube";
}

Published RuTube::publish(Content* content, Date date) {
    if (content == nullptr) {
        throw std::invalid_argument("RuTube: контент не может быть пустым");
    }
    if (content->getType() != "LongVideo") {
        throw std::invalid_argument("RuTube принимает только LongVideo, получено: " + content->getType());
    }
    if (accountName.empty()) {
        throw std::runtime_error("RuTube API error: пустое имя канала");
    }

    Request req("https://rutube.ru/api/video/upload", content->getSummary());
    Response resp = accountName == "fail" ? Response(502, "Bad Gateway") : Response(200, "OK");

    if (!resp.isOk()) {
        throw std::runtime_error("RuTube API error: " + std::to_string(resp.getStatusCode()) + " " + resp.getMessage());
    }
    (void)req;
    return Published(content, getName(), accountName, date);
}
