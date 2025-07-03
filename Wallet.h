#pragma once
#include <string>
#include <map>
#include "Wallet.h"
#include <sstream>

class Wallet
{
public:
    Wallet();
    void insertCurrency(std::string type, double amount);
        void removeCurrency(std::string type, double amount);
   
    bool containsCurrency(std::string type, double amount);
    std::string toString() const;
    bool isEmpty();
    std::map<std::string, double> getCurrencies();

private:
    std::map<std::string, double> currencies; // Maps currency type to amount
};

