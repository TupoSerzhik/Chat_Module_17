#pragma once

#include <string>
#include <vector>
#include "User.h"
#include "SHA1.h"

class AuthManager {
private:
    std::vector<User> users;
    SHA1 sha1;

    std::string hashPassword(const std::string& password) const;

public:
    AuthManager();
    bool registerUser(const std::string& username, const std::string& password);
    User* login(const std::string& username, const std::string& password);
    User* findUser(const std::string& username);
    const std::vector<User>& getUsers() const;
    void listUsers() const;
};