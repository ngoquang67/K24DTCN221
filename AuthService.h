#include "AuthService.h"
#include "DataStorage.h"
#include "Utils.h"
#include "Constants.h"
#include <iostream>

bool AuthService::registerUser(const std::string& username, const std::string& password, const std::string& fullName,
                              const std::string& email, const std::string& phone, UserRole role, bool autoPass) {
    auto users = DataStorage::loadUsers();
    if (users.find(username) != users.end()) {
        std::cout << "Username already exists.\n";
        return false;
    }
    long long walletId = Utils::generateUniqueId();
    UserAccount user(username, password, fullName, email, role, phone, walletId, autoPass);
    user.isOtpEnabled = true;
    user.otpSecretKey = Utils::generateOtpSecret();
    users[username] = user;
    DataStorage::saveUsers(users);
    Wallet wallet(walletId, 0.0);
    auto wallets = DataStorage::loadWallets();
    wallets[walletId] = wallet;
    DataStorage::saveWallets(wallets);
    std::cout << "User registered successfully. Wallet ID: " << walletId << "\n";
    if (autoPass) {
        std::cout << "Auto-generated password: " << password << ". Please change it on first login.\n";
    }
    return true;
}

bool AuthService::login(const std::string& username, const std::string& password, UserAccount& user) {
    auto users = DataStorage::loadUsers();
    auto it = users.find(username);
    if (it == users.end() || it->second.isLocked) {
        std::cout << "Invalid username or account is locked.\n";
        return false;
    }
    user = it->second;
    if (user.failedLoginAttempts >= Constants::MAX_LOGIN_ATTEMPTS) {
        user.isLocked = true;
        users[username] = user;
        DataStorage::saveUsers(users);
        std::cout << "Account locked due to too many failed attempts.\n";
        return false;
    }
    if (Utils::mockHashPassword(password, user.salt) == user.hashedPassword) {
        user.failedLoginAttempts = 0;
        users[username] = user;
        DataStorage::saveUsers(users);
        return true;
    }
    user.failedLoginAttempts++;
    users[username] = user;
    DataStorage::saveUsers(users);
    std::cout << "Invalid password. Attempts left: " << (Constants::MAX_LOGIN_ATTEMPTS - user.failedLoginAttempts) << "\n";
    return false;
}

bool AuthService::changePassword(UserAccount& user, const std::string& oldPassword, const std::string& newPassword) {
    if (Utils::mockHashPassword(oldPassword, user.salt) != user.hashedPassword) {
        std::cout << "Old password is incorrect.\n";
        return false;
    }
    user.hashedPassword = Utils::mockHashPassword(newPassword, user.salt);
    user.isPasswordAutoGenerated = false;
    user.updatedAt = std::chrono::system_clock::now();
    auto users = DataStorage::loadUsers();
    users[user.username] = user;
    DataStorage::saveUsers(users);
    std::cout << "Password changed successfully.\n";
    return true;
}

std::string AuthService::generateOtp(const UserAccount& user) {
    if (!user.isOtpEnabled) return "";
    std::string otp = Utils::generateOtp(user.otpSecretKey);
    std::cout << "OTP generated (valid for 30 seconds): " << otp << "\n";
    return otp;
}

bool AuthService::verifyOtp(const UserAccount& user, const std::string& otp) {
    return Utils::verifyOtp(user.otpSecretKey, otp);
}