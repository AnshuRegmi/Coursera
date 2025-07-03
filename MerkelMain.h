#pragma once
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include <vector>
#include "Wallet.h"

class MerkelMain {
public:
    MerkelMain(std::string filename);
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterBid();
    void enterOffer();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);


    std::string currentTime;
    OrderBook orderBook;

    Wallet wallet; // User's wallet to hold currencies
};