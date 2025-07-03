#include "MerkelMain.h"
#include "CSVReader.h"
#include <iostream>
#include <limits>

MerkelMain::MerkelMain(std::string filename) : orderBook(filename) {}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();

    while (true) {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print Exchange Stats" << std::endl;
    std::cout << "3: Make an offer" << std::endl;
    std::cout << "4: Make a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "==========" << std::endl;

    std::cout << "Current time: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - Your aim is to make money" << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);

        std::cout << "Product: " << p << std::endl;

        if (entries.empty())
        {
            std::cout << "No asks found for " << p << " at " << currentTime << std::endl;
        }
        else
        {
            std::cout << "Asks seen: " << entries.size() << std::endl;
            std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
            std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
        }

        std::cout << std::endl;
    }
}

void MerkelMain::enterOffer()
{
    std::cout << "Make an offer. Enter: Product,Price,Amount (e.g., ETH/BTC,200,0.5)" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "Invalid input format MerkelMain::enterOffer. Please enter: Product,Price,Amount" << std::endl;
        return;
    }

    try {
        OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1], // price
            tokens[2], // amount
            currentTime,
            tokens[0], // product
            OrderBookType::ask
        );

        orderBook.insertOrder(obe);
         // Insert the order into the order book

        // Optional: print confirmation
        std::cout << "Offer created for " << obe.product
                  << " price: " << obe.price
                  << " amount: " << obe.amount << std::endl;

        // Note: You can insert this into your order book here if you implement an addOrder method

    } catch (const std::exception& e) {
        std::cout << "Error creating offer MerkelMain::enterOffer: " << e.what() << std::endl;
        return; // Exit if there's an error
    }
}


void MerkelMain::enterBid()
{
    std::cout << "Make a bid. Enter: Product,Price,Amount (e.g., ETH/BTC,200,0.5)" << std::endl;
    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3) {
        std::cout << "Invalid input format MerkelMain::enterBid. Please enter: Product,Price,Amount" << std::endl;
        return;
    }

    try {
        OrderBookEntry obe = CSVReader::stringsToOBE(
            tokens[1], // price
            tokens[2], // amount
            currentTime,
            tokens[0], // product
            OrderBookType::bid  // This is the key difference - bid instead of ask
        );

        orderBook.insertOrder(obe);
        // Insert the order into the order book

        // Optional: print confirmation
        std::cout << "Bid created for " << obe.product
                  << " price: " << obe.price
                  << " amount: " << obe.amount << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Error creating bid MerkelMain::enterBid: " << e.what() << std::endl;
        return; // Exit if there's an error
    }
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next timeframe" << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption = 0; // Initialize to a default value
    std::string line;
    std::cout << "Type in 1-6: ";
    std::getline(std::cin, line);
    
    try {
        userOption = std::stoi(line);
    }
    catch(const std::exception& e) {
        std::cout << "Invalid input. Please enter a number." << std::endl;
        userOption = 0; // Set to invalid option to trigger error message
    }

    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 1) printHelp();
    else if (userOption == 2) printMarketStats();
    else if (userOption == 3) enterOffer();
    else if (userOption == 4) enterBid();
    else if (userOption == 5) printWallet();
    else if (userOption == 6) gotoNextTimeframe();
    else std::cout << "Invalid choice. Choose from 1-6" << std::endl;

    std::cout << std::endl;
}
