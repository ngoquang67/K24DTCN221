#include "DataStorage.h"
#include "Constants.h"
#include "Utils.h"
#include <fstream>
#include <filesystem>

std::map<std::string, UserAccount> DataStorage::loadUsers() {
    std::map<std::string, UserAccount> users;
    std::ifstream file(Constants::USER_DATA_FILE);
    if (file.is_open()) {
        json j;
        file >> j;
        for (const auto& item : j) {
            UserAccount user = item;
            users[user.username] = user;
        }
        file.close();
    }
    return users;
}

void DataStorage::saveUsers(const std::map<std::string, UserAccount>& users) {
    json j;
    for (const auto& pair : users) {
        j.push_back(pair.second);
    }
    std::ofstream file(Constants::USER_DATA_FILE);
    file << j.dump(4);
    file.close();
    backupData("users");
}

std::map<long long, Wallet> DataStorage::loadWallets() {
    std::map<long long, Wallet> wallets;
    std::ifstream file(Constants::WALLET_DATA_FILE);
    if (file.is_open()) {
        json j;
        file >> j;
        for (const auto& item : j) {
            Wallet wallet = item;
            wallets[wallet.walletId] = wallet;
        }
        file.close();
    }
    return wallets;
}

void DataStorage::saveWallets(const std::map<long long, Wallet>& wallets) {
    json j;
    for (const auto& pair : wallets) {
        j.push_back(pair.second);
    }
    std::ofstream file(Constants::WALLET_DATA_FILE);
    file << j.dump(4);
    file.close();
    backupData("wallets");
}

void DataStorage::backupData(const std::string& type) {
    std::string source = (type == "users") ? Constants::USER_DATA_FILE : Constants::WALLET_DATA_FILE;
    std::string backupDir = Constants::BACKUP_DIR;
    std::filesystem::create_directories(backupDir);
    std::string timestamp = Utils::getCurrentTimestamp();
    std::string backupFile = backupDir + type + "_" + timestamp + ".json";
    std::filesystem::copy_file(source, backupFile, std::filesystem::copy_options::overwrite_existing);
}