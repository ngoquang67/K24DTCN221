#include "Wallet.h"
#include "Utils.h"

void to_json(json& j, const TransactionRecord& t) {
    j = json{
        {"transactionId", t.transactionId},
        {"fromWalletId", t.fromWalletId},
        {"toWalletId", t.toWalletId},
        {"amount", t.amount},
        {"timestamp", Utils::time_point_to_string(t.timestamp)},
        {"isSuccessful", t.isSuccessful}
    };
}

void from_json(const json& j, TransactionRecord& t) {
    j.at("transactionId").get_to(t.transactionId);
    j.at("fromWalletId").get_to(t.fromWalletId);
    j.at("toWalletId").get_to(t.toWalletId);
    j.at("amount").get_to(t.amount);
    t.timestamp = Utils::string_to_time_point(j.at("timestamp").get<std::string>());
    j.at("isSuccessful").get_to(t.isSuccessful);
}

void to_json(json& j, const Wallet& w) {
    j = json{
        {"walletId", w.walletId},
        {"balance", w.balance},
        {"transactionHistory", w.transactionHistory}
    };
}

void from_json(const json& j, Wallet& w) {
    j.at("walletId").get_to(w.walletId);
    j.at("balance").get_to(w.balance);
    j.at("transactionHistory").get_to(w.transactionHistory);
}