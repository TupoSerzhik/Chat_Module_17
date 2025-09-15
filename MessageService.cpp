#include "MessageService.h"
#include <iostream>

MessageService::MessageService(AuthManager& authManager) : authManager(authManager) {}

bool MessageService::sendPrivateMessage(const std::string& sender, const std::string& recipient, const std::string& message) {
    User* recipientUser = authManager.findUser(recipient);
    if (!recipientUser) {
        std::cout << " Пользователь '" << recipient << "' не найден!\n";
        return false;
    }

    std::string fullMessage = " От " + sender + ": " + message;
    recipientUser->addMessage(fullMessage);
    std::cout << " Сообщение отправлено пользователю '" << recipient << "'\n";
    return true;
}

void MessageService::broadcastMessage(const std::string& sender, const std::string& message) {
    std::string fullMessage = "📢 РАССЫЛКА от " + sender + ": " + message;

    // Отправляем сообщение всем пользователям
    for (auto& user : authManager.getUsers()) {
        if (user.getUsername() != sender) { // Не отправляем себе
            const_cast<User&>(user).addMessage(fullMessage);
        }
    }

    std::cout << " Сообщение отправлено всем пользователям\n";
}