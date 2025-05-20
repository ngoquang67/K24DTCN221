#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <chrono>

class Utils {
public:
    static std::string generateSalt();
    static std::string mockHashPassword(const std::string& password, const std::string& salt);
    static long long generateUniqueId();
    static std::string time_point_to_string(const std::chrono::system_clock::time_point& tp);
    static std::chrono::system_clock::time_point string_to_time_point(const std::string& str);
    static std::string generateOtpSecret();
    static std::string generateOtp(const std::string& secret);
    static bool verifyOtp(const std::string& secret, const std::string& otp);
    static std::string getCurrentTimestamp();
};

#endif // UTILS_H