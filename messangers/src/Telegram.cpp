#include "Telegram.h"
#include "Request.h"
#include "Response.h"
#include <stdexcept>
#include <utility>

Telegram::Telegram(std::string a) : Service(std::move(a)) {}

std::string Telegram::getName() const {
    return "Telegram";
}

Published Telegram::publish(Content* content, Date date) {
    if (content == nullptr) {
        throw std::invalid_argument("Telegram: контент не может быть пустым");
    }
    if (content->getType() != "PostMessage") {
        throw std::invalid_argument("Telegram принимает только PostMessage, получено: " + content->getType());
    }
    if (accountName.empty()) {
        throw std::runtime_error("Telegram API error: пустое имя аккаунта");
    }

    Request req("https://api.telegram.org/bot/sendMessage", content->getSummary());
    Response resp = accountName == "fail" ? Response(503, "Service Unavailable") : Response(200, "OK");

    if (!resp.isOk()) {
        throw std::runtime_error("Telegram API error: " + std::to_string(resp.getStatusCode()) + " " + resp.getMessage());
    }
    (void)req;
    return Published(content, getName(), accountName, date);
}
