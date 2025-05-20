#ifndef WALLETSERVICE_H
#define WALLETSERVICE_H

#include <string>
#include "Wallet.h"
#include "UserAccount.h"

class WalletService {
public:
    static bool transferPoints(UserAccount& fromUser, long long toWalletId, double amount);
    static double getBalance(long long walletId);
    static std::vector<TransactionRecord> getTransactionHistory(long long walletId);
    static bool adminDeposit(UserAccount& admin, long long toWalletId, double amount);
};

#endif // WALLETSERVICE_H