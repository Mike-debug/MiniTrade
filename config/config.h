//
// Created by Mike_Wei on 5/5/2024.
//

#ifndef MINITRADE_CONFIG_H
#define MINITRADE_CONFIG_H

#include <string>
#include <fstream>
#include <iostream>
#include <json/json.h>

extern const std::string CONFIG_PATH;

namespace cfg {
    extern bool ifLog;
    extern unsigned int autoTradeNum;
    extern unsigned long long diffTickerTime;

    extern std::string sellPrice;
    extern std::string buyPrice;

    extern std::string public_key;
    extern std::string private_key;
    extern std::string testnet_url;
    extern std::string future_url;

    extern Json::Value tradeRequest;
    extern Json::Value cancelRequest;
    extern Json::Value ticker;
    extern Json::Value subscribeFutureRequest;
    extern Json::Value subscribeFutureResponse;
    extern Json::Value subscribeSpotRequest;
    extern Json::Value subscribeSpotResponse;
    extern Json::Value allOrdersRequest;
    extern Json::Value allOrdersResponse;
    extern Json::Value accountStatusResquest;
    extern Json::Value accountStatusResponse;
    extern Json::Value exchangeInfoRequest;

    bool refreshConfig();

    bool printConfig();

}


#endif //MINITRADE_CONFIG_H
