#include "VKClips.h"
#include "Request.h"
#include "Response.h"
#include <stdexcept>
#include <utility>

VKClips::VKClips(std::string a) : Service(std::move(a)) {}

std::string VKClips::getName() const {
    return "VKClips";
}

Published VKClips::publish(Content* content, Date date) {
    if (content == nullptr) {
        throw std::invalid_argument("VKClips: контент не может быть пустым");
    }
    if (content->getType() != "ShortVideo") {
        throw std::invalid_argument("VKClips принимает только ShortVideo, получено: " + content->getType());
    }
    if (accountName.empty()) {
        throw std::runtime_error("VKClips API error: пустое имя канала");
    }

    Request req("https://vk.com/clips/api/upload", content->getSummary());
    Response resp = accountName == "fail" ? Response(504, "Gateway Timeout") : Response(200, "OK");

    if (!resp.isOk()) {
        throw std::runtime_error("VKClips API error: " + std::to_string(resp.getStatusCode()) + " " + resp.getMessage());
    }
    (void)req;
    return Published(content, getName(), accountName, date);
}
