#pragma once

#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string passwordHash;
    std::vector<std::string> messages;

public:
    User(const std::string& username, const std::string& passwordHash);

    std::string getUsername() const;
    std::string getPasswordHash() const;
    bool verifyPassword(const std::string& password) const;
    void addMessage(const std::string& message);
    std::vector<std::string> getMessages() const;
    void clearMessages();
};