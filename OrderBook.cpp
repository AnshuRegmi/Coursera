#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
/** construct, reading a csv data file*/
    OrderBook::OrderBook(std::string filename)
    {
        orders = CSVReader::readCSV(filename);
    }
/** return vector of all know products in dataset*/
    std::vector<std::string> OrderBook::getKnownProducts()
    {
            std::vector<std::string> products;

            std::map<std::string, bool> prodMap;
            for(OrderBookEntry& e : orders)
            {
                prodMap[e.product] = true;
            }
            //now flatten the map to a vector of strings
            for(auto const& e : prodMap)
            {
                products.push_back(e.first);
            }

            return products;
    }
    /**  */
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp)
        {
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}

    double OrderBook:: getHighPrice(std::vector<OrderBookEntry>& orders)
    {
        double max = orders[0].price;
        for(OrderBookEntry& e : orders)
        {
            if(e.price > max)
            {
                max = e.price;
            }
        }
        return max;
    }

double OrderBook:: getLowPrice(std::vector<OrderBookEntry>& orders)
    {
        double min = orders[0].price;
        for(OrderBookEntry& e : orders)
        {
            if(e.price < min)
            {
                min = e.price;
            }
        }
        return min;
    }
        std::string OrderBook:: getEarliestTime()
    {
        return orders[0].timestamp;
    }

            std::string OrderBook::getNextTime(std::string timestamp)
            {
                std::string next_timestamp = "";
                for(OrderBookEntry& e : orders)
                {
                    if (e.timestamp > timestamp)
                    {
                        next_timestamp = e.timestamp;
                        break;
                    }
                }

                if (next_timestamp=="")
                    {
                    next_timestamp = orders[0].timestamp;
                    }
                return next_timestamp;
            }


void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(),OrderBookEntry::compareByTimestamp );
}


               
// void OrderBook::printAllTimestamps()
// {
//     std::cout << "\n[DEBUG] All unique timestamps in dataset:\n";
//     std::string last = "";
//     for (OrderBookEntry& e : orders)
//     {
//         if (e.timestamp != last)
//         {
//             std::cout << e.timestamp << std::endl;
//             last = e.timestamp;
//         }
//     }
// }


std::vector<OrderBookEntry>OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
    std::vector<OrderBookEntry>asks=getOrders(OrderBookType::ask,
                                                             product,
                                                              timestamp);
    std::vector<OrderBookEntry>bids=getOrders(OrderBookType::bid,
                                                                product,
                                                                timestamp);
     std::vector<OrderBookEntry>sales;

     std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);

     std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

     for(OrderBookEntry& ask: asks)
     {
        for (OrderBookEntry& bid : bids)
        {
            if(bid.price >= ask.price)
            {
                OrderBookEntry sale{ask.price,0, timestamp, product ,OrderBookType::sale};
                
                if (bid.amount == ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount = 0; // Bid fully matched
                    break;
                }
                if (bid.amount> ask.amount)
                {
                    sale.amount = ask.amount;
                    sales.push_back(sale);
                    bid.amount -= ask.amount; // Bid partially matched
                    break;
                }
                {

                }
                if (bid.amount<ask.amount)
                {
                    sale.amount = bid.amount;
                    sales.push_back(sale);
                    ask.amount -= bid.amount; // Ask partially matched
                    bid.amount = 0; // Bid fully matched
                    continue;
                }
            }
        }
     }
     return sales; 
}