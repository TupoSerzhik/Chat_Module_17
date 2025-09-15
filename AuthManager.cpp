#include "AuthManager.h"
#include <iostream>

AuthManager::AuthManager() {
    // Добавляем тестовых пользователей
    users.push_back(User("admin", sha1.hash("admin123")));
    users.push_back(User("user1", sha1.hash("password1")));
    users.push_back(User("user2", sha1.hash("password2")));
}

std::string AuthManager::hashPassword(const std::string& password) const {
    return sha1.hash(password);
}

bool AuthManager::registerUser(const std::string& username, const std::string& password) {
    // Проверяем, существует ли пользователь
    for (const auto& user : users) {
        if (user.getUsername() == username) {
            return false;
        }
    }

    // Создаем нового пользователя
    users.push_back(User(username, hashPassword(password)));
    return true;
}

User* AuthManager::login(const std::string& username, const std::string& password) {
    for (auto& user : users) {
        if (user.getUsername() == username && user.verifyPassword(password)) {
            return &user;
        }
    }
    return nullptr;
}

User* AuthManager::findUser(const std::string& username) {
    for (auto& user : users) {
        if (user.getUsername() == username) {
            return &user;
        }
    }
    return nullptr;
}

const std::vector<User>& AuthManager::getUsers() const {
    return users;
}

void AuthManager::listUsers() const {
    std::cout << "\n--- Зарегистрированные пользователи ---\n";
    for (const auto& user : users) {
        std::cout << "- " << user.getUsername() << "\n";
    }
}