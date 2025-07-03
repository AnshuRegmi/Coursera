#include <iostream>
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"

int main()
{
   MerkelMain app{"Data.csv"};
    app.init();
// CSVReader::readCSV("Data.csv");

}



















//     std::vector<OrderBookEntry>orders;

//     orders.push_back(OrderBookEntry{3000,
//                         0.02,
//                         "2020/03/17 17:01:24.884492", 
//                         "BTC/USDT",
//                         OrderBookType::bid }     );


//     orders.push_back(OrderBookEntry{2000,
//                         0.02,
//                         "2020/03/17 17:01:24.884492", 
//                         "BTC/USDT",
//                         OrderBookType::bid }     );


//     // std::cout <<" The price is" <<orders[1].price<<std::endl;
    
//     for(OrderBookEntry& order : orders)
// {
//     std::cout <<" The price is " << order.price << std::endl;

// }

// for(unsigned int i =0; i<orders.size(); ++i)
// {
//     std::cout <<" The price is " << orders[i].price << std::endl;

// }



//     return 0;
// }
//     // double price = 5319.450228;
//     // double amount = 0.00020075;
//     // std::string timestamp{"2020/03/17 17:01:24.884492"};
//     // std::string product{"BTC/USDT"};
//     // OrderBookType orderType = OrderBookType::ask;

// std::vector<double> prices;
// std::vector<double> amounts;
// std::vector<std::string> timestamps;
// std::vector<std::string> products;
// std::vector<OrderBookType> orderTypes;



// prices.push_back(5000.01);
// amounts.push_back(0.001);
// timestamps.push_back("2020/03/17 17:01:24.884492");
// products.push_back("BTC/USDT");
// orderTypes.push_back(OrderBookType::bid);

// prices.push_back(10.01);
// amounts.push_back(0.001);
// timestamps.push_back("2020/03/17 17:01:24.884492");
// products.push_back("BTC/USDT");
// orderTypes.push_back(OrderBookType::ask);

// std::cout<<"prices:"<< prices[0]<< std:: endl;
// std::cout<<"prices:"<< prices[1]<< std:: endl;



//     // while (true) {
//     //     printMenu();                       // Display the menu
//     //     int userOption = getUserOption();  // Get user choice
//     //     processUserOption(userOption);     // Process the choice
//     // }