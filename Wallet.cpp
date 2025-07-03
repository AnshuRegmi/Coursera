#include "Wallet.h"
#include <iostream>
#include <stdexcept>

Wallet::Wallet() 
{
    // Constructor - currencies map is automatically initialized as empty
}

void Wallet::insertCurrency(std::string type, double amount)
{
    // Check if amount is negative - throw exception if so
    if (amount < 0) {
        throw std::runtime_error("Cannot insert negative amount");
    }
    
    double balance;
    
    // Check if currency already exists in the wallet
    if (currencies.count(type) == 0) {
        // Currency doesn't exist yet, initialize balance to 0
        balance = 0;
    } else {
        // Currency exists, get current balance
        balance = currencies[type];
    }
    
    // Add the new amount to the balance
    balance += amount;
    
    // Store the updated balance back in the map
    currencies[type] = balance;
}

// Implement removeCurrency function (example implementation)
void Wallet::removeCurrency(std::string type, double amount)
{
    if (amount < 0) {
        throw std::runtime_error("Cannot remove negative amount");
    }
    if (currencies.count(type) == 0 || currencies[type] < amount) {
        throw std::runtime_error("Not enough currency to remove");
    }
    std::cout << "Removing " << amount << " of " << type << std::endl;
    currencies[type] -= amount;
    if (currencies[type] == 0) 
    {
        std::cout<<"No Currency for"<<type<<std::endl;
        currencies.erase(type);
    }
}

bool Wallet::containsCurrency(std::string type, double amount)
{
    // Check if the currency exists in the wallet
    if (currencies.count(type) == 0) {
        // Currency doesn't exist, return false immediately
        return false;
    }
    
    // Currency exists, check if we have at least the required amount
    return currencies[type] >= amount;
}

std::string Wallet::toString() const
{
    std::string result = "Wallet contents:\n";
    
    if (currencies.empty()) {
        result += "Wallet is empty\n";
    } else {
        for (const auto& pair : currencies) {
            result += pair.first + ": " + std::to_string(pair.second) + "\n";
        }
    }
    
    return result;
}