#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include <chrono>
#include "../json.hpp"

using json = nlohmann::json;

struct TransactionRecord {
    long long transactionId;
    long long fromWalletId;
    long long toWalletId;
    double amount;
    std::chrono::system_clock::time_point timestamp;
    bool isSuccessful;

    TransactionRecord(long long tId, long long fromId, long long toId, double amt, bool success)
        : transactionId(tId), fromWalletId(fromId), toWalletId(toId), amount(amt),
          timestamp(std::chrono::system_clock::now()), isSuccessful(success) {}
};

class Wallet {
public:
    long long walletId;
    double balance;
    std::vector<TransactionRecord> transactionHistory;

    Wallet(long long wId, double bal = 0.0) : walletId(wId), balance(bal) {}
};

void to_json(json& j, const TransactionRecord& t);
void from_json(const json& j, TransactionRecord& t);
void to_json(json& j, const Wallet& w);
void from_json(const json& j, Wallet& w);

#endif // WALLET_H