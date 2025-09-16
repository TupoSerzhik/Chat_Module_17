#include "User.h"
#include "SHA1.h"
#include <iostream>

User::User(const std::string& username, const std::string& passwordHash)
    : username(username), passwordHash(passwordHash)
{
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPasswordHash() const 
{
    return passwordHash;
}

bool User::verifyPassword(const std::string& password) const 
{
    SHA1 sha1;
    return passwordHash == sha1.hash(password);
}

void User::addMessage(const std::string& message)
{
    messages.push_back(message);
}

std::vector<std::string> User::getMessages() const 
{
    return messages;
}

void User::clearMessages() 
{
    messages.clear();
}