#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

class CSVReader {
public:
    CSVReader();

    static std::vector<OrderBookEntry> readCSV(std::string csvFilename);
    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    // This function is for use in MerkelMain, when manually creating OrderBookEntry
    static OrderBookEntry stringsToOBE(std::string price,
                                       std::string amount,
                                       std::string timestamp,
                                       std::string product,
                                    OrderBookType orderType
                                      );

private:
    // Used internally when reading CSV lines
    static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
};
