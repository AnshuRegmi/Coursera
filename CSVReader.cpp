#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <iostream>
#include <fstream>
#include <sstream>

CSVReader::CSVReader() {}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> orderBookEntries;
    std::ifstream csvFile{csvFilename};
    std::string line;

    if (csvFile.is_open()) {
        while (std::getline(csvFile, line)) {
            try {
                OrderBookEntry obe = CSVReader::stringsToOBE(tokenise(line, ','));
                orderBookEntries.push_back(obe);
            } catch (const std::exception& e) {
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }
        }
    }

    std::cout << "CSVReader::readCSV read " << orderBookEntries.size() << " entries" << std::endl;
    return orderBookEntries;
}

std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream stream(csvLine);

    while (std::getline(stream, token, separator)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Parses CSV line tokens into an OrderBookEntry object
OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    if (tokens.size() != 5) {
        std::cout << "Bad Line" << std::endl;
        throw std::runtime_error("Incorrect number of tokens");
    }

    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    } catch (const std::exception& e) {
        std::cout << "Error converting to double: " << tokens[3] << ", " << tokens[4] << std::endl;
        throw;
    }

    return OrderBookEntry{
        price,
        amount,
        tokens[0], // timestamp
        tokens[1], // product
        OrderBookEntry::stringToOrderBookType(tokens[2])
    };
}

// Creates OrderBookEntry from individual string values (used for manual offers)
OrderBookEntry CSVReader::stringsToOBE(std::string product,
                                       std::string price,
                                       std::string amount,
                                       std::string timestamp,
                                       OrderBookType orderType)
{
    double priceValue, amountValue;
    try {
        priceValue = std::stod(price);
        amountValue = std::stod(amount);
    } catch (const std::exception& e) {
        std::cout << "CSVReader::stringsToOBE Bad Float! " << price << " or " << amount << std::endl;
        throw;
    }

    return OrderBookEntry{
        priceValue,
        amountValue,
        timestamp,
        product,
        orderType
    };
}