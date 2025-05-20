#include "WalletService.h"
#include "DataStorage.h"
#include "AuthService.h"
#include <iostream>

bool WalletService::transferPoints(UserAccount& fromUser, long long toWalletId, double amount) {
    if (fromUser.isLocked) {
        std::cout << "Your account is locked.\n";
        return false;
    }
    auto wallets = DataStorage::loadWallets();
    if (wallets.find(fromUser.walletId) == wallets.end() || wallets.find(toWalletId) == wallets.end()) {
        std::cout << "Invalid wallet ID.\n";
        return false;
    }
    if (wallets[fromUser.walletId].balance < amount) {
        std::cout << "Insufficient balance.\n";
        return false;
    }
    std::string otp = AuthService::generateOtp(fromUser);
    std::cout << "Enter OTP to confirm transfer: ";
    std::string inputOtp;
    std::cin >> inputOtp;
    if (!AuthService::verifyOtp(fromUser, inputOtp)) {
        std::cout << "Invalid OTP.\n";
        TransactionRecord record(Utils::generateUniqueId(), fromUser.walletId, toWalletId, amount, false);
        wallets[fromUser.walletId].transactionHistory.push_back(record);
        wallets[toWalletId].transactionHistory.push_back(record);
        DataStorage::saveWallets(wallets);
        return false;
    }
    wallets[fromUser.walletId].balance -= amount;
    wallets[toWalletId].balance += amount;
    TransactionRecord record(Utils::generateUniqueId(), fromUser.walletId, toWalletId, amount, true);
    wallets[fromUser.walletId].transactionHistory.push_back(record);
    wallets[toWalletId].transactionHistory.push_back(record);
    DataStorage::saveWallets(wallets);
    std::cout << "Transfer successful.\n";
    return true;
}

double WalletService::getBalance(long long walletId) {
    auto wallets = DataStorage::loadWallets();
    if (wallets.find(walletId) != wallets.end()) {
        return wallets[walletId].balance;
    }
    return 0.0;
}

std::vector<TransactionRecord> WalletService::getTransactionHistory(long long walletId) {
    auto wallets = DataStorage::loadWallets();
    if (wallets.find(walletId) != wallets.end()) {
        return wallets[walletId].transactionHistory;
    }
    return std::vector<TransactionRecord>();
}

bool WalletService::adminDeposit(UserAccount& admin, long long toWalletId, double amount) {
    if (admin.role != UserRole::ADMIN_USER) {
        std::cout << "Only admins can deposit points.\n";
        return false;
    }
    auto wallets = DataStorage::loadWallets();
    if (wallets.find(toWalletId) == wallets.end()) {
        std::cout << "Invalid wallet ID.\n";
        return false;
    }
    wallets[toWalletId].balance += amount;
    TransactionRecord record(Utils::generateUniqueId(), -1, toWalletId, amount, true); // -1 for master wallet
    wallets[toWalletId].transactionHistory.push_back(record);
    DataStorage::saveWallets(wallets);
    std::cout << "Deposit successful.\n";
    return true;
}