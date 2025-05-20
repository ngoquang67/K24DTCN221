#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <string>
#include "UserAccount.h"

class AuthService {
public:
    static bool registerUser(const std::string& username, const std::string& password, const std::string& fullName,
                            const std::string& email, const std::string& phone, UserRole role, bool autoPass);
    static bool login(const std::string& username, const std::string& password, UserAccount& user);
    static bool changePassword(UserAccount& user, const std::string& oldPassword, const std::string& newPassword);
    static std::string generateOtp(const UserAccount& user);
    static bool verifyOtp(const UserAccount& user, const std::string& otp);
};

#endif // AUTHSERVICE_H