#pragma once

#include <string>
#include <vector>
#include "User.h"
#include "AuthManager.h"

class MessageService
{
private:
    AuthManager& authManager;

public:
    MessageService(AuthManager& authManager);
    bool sendPrivateMessage(const std::string& sender, const std::string& recipient, const std::string& message);
    void broadcastMessage(const std::string& sender, const std::string& message);
};