#include "Utils.h"
#include <random>
#include <sstream>
#include <iomanip>
#include <ctime>

std::string Utils::generateSalt() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);
    std::stringstream ss;
    for (int i = 0; i < 16; ++i) {
        ss << std::hex << dis(gen);
    }
    return ss.str();
}

std::string Utils::mockHashPassword(const std::string& password, const std::string& salt) {
    return password + salt; // Demo only, replace with real hash (e.g., bcrypt)
}

long long Utils::generateUniqueId() {
    return std::chrono::system_clock::now().time_since_epoch().count();
}

std::string Utils::time_point_to_string(const std::chrono::system_clock::time_point& tp) {
    auto t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::chrono::system_clock::time_point Utils::string_to_time_point(const std::string& str) {
    std::tm tm = {};
    std::stringstream ss(str);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string Utils::generateOtpSecret() {
    return generateSalt(); // Demo only, use proper TOTP secret generation
}

std::string Utils::generateOtp(const std::string& secret) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    std::stringstream ss;
    for (int i = 0; i < 6; ++i) {
        ss << dis(gen);
    }
    return ss.str(); // Demo only, use TOTP library
}

bool Utils::verifyOtp(const std::string& secret, const std::string& otp) {
    return true; // Demo only, implement TOTP verification
}

std::string Utils::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M");
    return ss.str();
}