//
// Created by Mike_Wei on 5/5/2024.
//

#ifndef MINITRADE_CONFIG_H
#define MINITRADE_CONFIG_H

#include <string>
#include <fstream>
#include <iostream>
#include <json/json.h>

const std::string CONFIG_PATH{R"(..\config.json)"};

namespace cfg {
    bool ifLog = true;
    unsigned int autoTradeNum = 2;
    unsigned long long diffTickerTime = 1000;

    std::string sellPrice{};
    std::string buyPrice{};

    std::string public_key{};
    std::string private_key{};
    std::string testnet_url{};
    std::string future_url{};

    Json::Value tradeRequest{};
    Json::Value cancelRequest{};
    Json::Value ticker{};
    Json::Value subscribeFutureRequest{};
    Json::Value subscribeFutureResponse{};
    Json::Value subscribeSpotRequest{};
    Json::Value subscribeSpotResponse{};
    Json::Value allOrdersRequest{};
    Json::Value allOrdersResponse{};
    Json::Value accountStatusResquest{};
    Json::Value accountStatusResponse{};
    Json::Value exchangeInfoRequest{};

    bool refreshConfig();

    bool printConfig();

}

bool cfg::refreshConfig() {
    // 读取 JSON 文件
    std::ifstream file(CONFIG_PATH);

    if (!file.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return false;
    }

    // 读取文件内容到字符串
    std::string jsonString((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
    file.close();

    // 解析 JSON 字符串为 JSON 对象
    Json::Value jsonObject;
    Json::Reader jsonReader;
    if (!jsonReader.parse(jsonString, jsonObject)) {
        std::cerr << "Failed to parse JSON." << std::endl;
        return false;
    }
    std::cout << "Config:\n" << jsonObject << std::endl;

    if (jsonObject.isMember("ifLog")) {
        ifLog = jsonObject["ifLog"].asBool();
    }

    if (jsonObject.isMember("autoTradeNum")) {
        autoTradeNum = jsonObject["autoTradeNum"].asUInt();
    }

    if (jsonObject.isMember("diffTickerTime")) {
        diffTickerTime = jsonObject["diffTickerTime"].asUInt64();
    }

    if (jsonObject.isMember("sellPrice")) {
        sellPrice = jsonObject["sellPrice"].asString();
    }
    if (jsonObject.isMember("buyPrice")) {
        buyPrice = jsonObject["buyPrice"].asString();
    }
    if (jsonObject.isMember("public_key")) {
        public_key = jsonObject["public_key"].asString();
    }
    if (jsonObject.isMember("private_key")) {
        private_key = jsonObject["private_key"].asString();
    }
    if (jsonObject.isMember("testnet_url")) {
        testnet_url = jsonObject["testnet_url"].asString();
    }
    if (jsonObject.isMember("future_url")) {
        future_url = jsonObject["future_url"].asString();
    }

    if (jsonObject.isMember("tradeRequest")) { tradeRequest = jsonObject["tradeRequest"]; }
    if (jsonObject.isMember("cancelRequest")) { cancelRequest = jsonObject["cancelRequest"]; }
    if (jsonObject.isMember("ticker")) { ticker = jsonObject["ticker"]; }
    if (jsonObject.isMember(
            "subscribeFutureRequest")) { subscribeFutureRequest = jsonObject["subscribeFutureRequest"]; }
    if (jsonObject.isMember(
            "subscribeFutureResponse")) { subscribeFutureResponse = jsonObject["subscribeFutureResponse"]; }
    if (jsonObject.isMember("subscribeSpotRequest")) { subscribeSpotRequest = jsonObject["subscribeSpotRequest"]; }
    if (jsonObject.isMember("subscribeSpotResponse")) { subscribeSpotResponse = jsonObject["subscribeSpotResponse"]; }
    if (jsonObject.isMember("allOrdersRequest")) { allOrdersRequest = jsonObject["allOrdersRequest"]; }
    if (jsonObject.isMember("allOrdersResponse")) { allOrdersResponse = jsonObject["allOrdersResponse"]; }
    if (jsonObject.isMember("accountStatusResquest")) { accountStatusResquest = jsonObject["accountStatusResquest"]; }
    if (jsonObject.isMember("accountStatusResponse")) { accountStatusResponse = jsonObject["accountStatusResponse"]; }
    if (jsonObject.isMember("exchangeInfoRequest")) { exchangeInfoRequest = jsonObject["exchangeInfoRequest"]; }


    return true;
}

bool cfg::printConfig() {
    std::cout << "ifLog: " << ifLog << std::endl;
    std::cout << "autoTradeNum: " << autoTradeNum << std::endl;
    std::cout << "diffTickerTime: " << diffTickerTime << std::endl;
    std::cout << "sellPrice: " << sellPrice << std::endl;
    std::cout << "buyPrice: " << buyPrice << std::endl;
    std::cout << "api_key: " << public_key << std::endl;
    std::cout << "private_key: " << private_key << std::endl;
    std::cout << "testnet_url: " << testnet_url << std::endl;
    std::cout << "future_url: " << future_url << std::endl;
    std::cout << "tradeRequest: " << tradeRequest << std::endl;
    std::cout << "cancelRequest: " << cancelRequest << std::endl;
    std::cout << "ticker: " << ticker << std::endl;
    std::cout << "subscribeFutureRequest: " << subscribeFutureRequest << std::endl;
    std::cout << "subscribeFutureResponse: " << subscribeFutureResponse << std::endl;
    std::cout << "subscribeSpotRequest: " << subscribeSpotRequest << std::endl;
    std::cout << "subscribeSpotResponse: " << subscribeSpotResponse << std::endl;
    std::cout << "allOrdersRequest: " << allOrdersRequest << std::endl;
    std::cout << "allOrdersResponse: " << allOrdersResponse << std::endl;
    std::cout << "accountStatusResquest: " << accountStatusResquest << std::endl;
    std::cout << "accountStatusResponse: " << accountStatusResponse << std::endl;
    std::cout << "exchangeInfoRequest: " << exchangeInfoRequest << std::endl;
    return true;
}

#endif //MINITRADE_CONFIG_H
