#include "Max.h"
#include "Request.h"
#include "Response.h"
#include <stdexcept>
#include <utility>

Max::Max(std::string a) : Service(std::move(a)) {}

std::string Max::getName() const {
    return "Max";
}

Published Max::publish(Content* content, Date date) {
    if (content == nullptr) {
        throw std::invalid_argument("Max: контент не может быть пустым");
    }
    if (content->getType() != "PostMessage") {
        throw std::invalid_argument("Max принимает только PostMessage, получено: " + content->getType());
    }
    if (accountName.empty()) {
        throw std::runtime_error("Max API error: пустое имя аккаунта");
    }

    Request req("https://api.max.ru/messages/send", content->getSummary());
    Response resp = accountName == "fail" ? Response(500, "Internal Server Error") : Response(200, "OK");

    if (!resp.isOk()) {
        throw std::runtime_error("Max API error: " + std::to_string(resp.getStatusCode()) + " " + resp.getMessage());
    }
    (void)req;
    return Published(content, getName(), accountName, date);
}
