#include"./jsonSpecificUtils"


static std::string getAdjustedTimeStamp(long long diff) {
    static std::string timeStampStr;
    timeStampStr = std::to_string(getTimeStamp(diff));
    if (cfg::ifLog) {
        std::cout << "timestamp is " << timeStampStr << std::endl;
        std::cout << "DIFF is " << diff << std::endl;
    }
    return timeStampStr;
}

std::string makePayLoad(const Json::Value &jsonObj) {
    // 获取 JSON 对象中的所有键
    std::vector<std::string> keys = jsonObj.getMemberNames();
    std::sort(keys.begin(), keys.end());
    std::string retPayLoad{};
    for (const auto &k: keys) {
        if (k == "signature") { continue; }
        retPayLoad += k + "=" + jsonObj[k].asString() + "&";
    }
    // 检查字符串是否为空
    if (!retPayLoad.empty()) {
        // 删除最后一个字符
        retPayLoad.erase(retPayLoad.size() - 1);
    }
    return retPayLoad;
}

std::string jsonObj2StringWithoutBlank(const Json::Value &jsonObj) {
    // 构建 JSON 写入器，并设置缩进为空字符串
    static Json::StreamWriterBuilder builder{};
    builder["indentation"] = ""; // 禁用缩进
    // 将 JSON 对象转换为字符串
    std::string jsonString = Json::writeString(builder, jsonObj);
    return jsonString;
}

std::string getCancelMsgFromConfig(const std::string &orderId, const std::string &symbol,
                                   long long diff) {
    auto request = cfg::cancelRequest;
    auto timsStamp = getAdjustedTimeStamp(diff);
    request["id"] = timsStamp;
    if (!symbol.empty()) {
        request["params"]["symbol"] = symbol;
    }
    request["params"]["timestamp"] = timsStamp;
    request["params"]["origClientOrderId"] = orderId;
    request["params"]["apiKey"] = cfg::public_key;
    auto payLoad = makePayLoad(request["params"]);
    request["params"]["signature"] = calculateHMAC(payLoad, cfg::private_key);
    auto jsonString = jsonObj2StringWithoutBlank(request);
    if (cfg::ifLog) {
        std::cout << "getCancelMsgFromConfig:" << std::endl;
        std::cout << jsonString << std::endl;
    }
    return jsonString;
}

bool isNumeric(const std::string &str) {
    std::istringstream iss(str);
    double num;
    iss >> std::noskipws >> num; // 设置不跳过空白字符

    // 检查是否转换成功并且到达了流的末尾
    return iss.eof() && !iss.fail();
}

std::string getTradeMsgFromConfig(bool sell,
                                  const std::string &symbol,
                                  const std::string &price,
                                  long long diff) {
    auto request = cfg::tradeRequest;
    auto timsStamp = getAdjustedTimeStamp(diff);
    request["id"] = timsStamp;
    if (!symbol.empty()) {
        request["params"]["symbol"] = symbol;
    }
    request["params"]["timestamp"] = timsStamp;
    request["params"]["side"] = sell ? "SELL" : "BUY";
    if (!isNumeric(price)) {
        request["params"]["price"] = sell ? cfg::sellPrice : cfg::buyPrice;
    } else {
        request["params"]["price"] = price;
    }
    auto payLoad = makePayLoad(request["params"]);
    request["params"]["apiKey"] = cfg::public_key;
    request["params"]["signature"] = calculateHMAC(payLoad, cfg::private_key);
    auto jsonString = jsonObj2StringWithoutBlank(request);
    if (cfg::ifLog) {
        std::cout << "getTradeMsgFromConfig:" << std::endl;
        std::cout << jsonString << std::endl;
        std::cout << "payLoad:" << std::endl;
        std::cout << payLoad << std::endl;
    }
    return jsonString;
}

std::string getTradeFutureMsgFromConfig(bool sell,
                                        const std::string &symbol,
                                        const std::string &price,
                                        long long diff) {
    auto request = cfg::tradeRequest;
    auto timsStamp = getAdjustedTimeStamp(diff);
    request["id"] = timsStamp;
    if (!symbol.empty()) {
        request["params"]["symbol"] = symbol;
    }
    request["params"]["timestamp"] = timsStamp;
    request["params"]["side"] = sell ? "SELL" : "BUY";
    if (!isNumeric(price)) {
        request["params"]["price"] = sell ? cfg::sellPrice : cfg::buyPrice;
    } else {
        request["params"]["price"] = price;
    }
    request["params"]["apiKey"] = cfg::public_key;
    auto payLoad = makePayLoad(request["params"]);
    request["params"]["signature"] = calculateHMAC(payLoad, cfg::private_key);
    auto jsonString = jsonObj2StringWithoutBlank(request);
    if (cfg::ifLog) {
        std::cout << "getTradeFutureMsgFromConfig:" << std::endl;
        std::cout << jsonString << std::endl;
        std::cout << "payLoad:" << std::endl;
        std::cout << payLoad << std::endl;
    }
    return jsonString;
}

std::string getAllOrdersMsgFromConfig(
    const std::string &symbol,
    const std::string &startTime,
    const std::string &endTime,
    const std::string &limit,
    long long diff
) {
    auto request = cfg::allOrdersRequest;
    auto timsStamp = getAdjustedTimeStamp(diff);
    request["id"] = timsStamp;
    if (!symbol.empty()) {
        request["params"]["symbol"] = symbol;
    }
    if (!endTime.empty()) {
        request["params"]["endTime"] = endTime;
    } else {
        request["params"]["endTime"] = timsStamp;
    }
    if (!startTime.empty()) {
        request["params"]["startTime"] = startTime;
    } else {
        auto five_days_ago_timsStamp = getAdjustedTimeStamp((24 * 60 * 60 - 1) * 1000);
        request["params"]["startTime"] = five_days_ago_timsStamp;
    }

    if (!limit.empty()) {
        request["params"]["limit"] = limit;
    }
    request["params"]["timestamp"] = timsStamp;
    request["params"]["apiKey"] = cfg::public_key;
    auto payLoad = makePayLoad(request["params"]);
    request["params"]["signature"] = calculateHMAC(payLoad, cfg::private_key);
    auto jsonString = jsonObj2StringWithoutBlank(request);
    if (cfg::ifLog) {
        std::cout << "getAllOrdersMsgFromConfig:" << std::endl;
        std::cout << jsonString << std::endl;
    }
    return jsonString;
}

std::string getAccountStatusMsgFromConfig(long long diff) {
    auto request = cfg::allOrdersRequest;
    auto timsStamp = getAdjustedTimeStamp(diff);
    request["id"] = timsStamp;
    request["params"]["timestamp"] = timsStamp;
    request["params"]["apiKey"] = cfg::public_key;
    auto payLoad = makePayLoad(request["params"]);
    request["params"]["signature"] = calculateHMAC(payLoad, cfg::private_key);
    auto jsonString = jsonObj2StringWithoutBlank(request);
    if (cfg::ifLog) {
        std::cout << "getAccountStatusMsgFromConfig:" << std::endl;
        std::cout << jsonString << std::endl;
    }
    return jsonString;
}

std::string getExchangeInfoMsgFromConfig(long long diff) {
    auto request = cfg::exchangeInfoRequest;
    auto timsStamp = getAdjustedTimeStamp(diff);
    request["id"] = timsStamp;
    auto jsonString = jsonObj2StringWithoutBlank(request);
    if (cfg::ifLog) {
        std::cout << "getAccountStatusMsgFromConfig:" << std::endl;
        std::cout << jsonString << std::endl;
    }
    return jsonString;
}

std::string getTicker(bool ifFuture) {
    auto request = ifFuture ? cfg::subscribeFutureRequest : cfg::subscribeSpotRequest;
    auto jsonString = jsonObj2StringWithoutBlank(request);
    if (cfg::ifLog) {
        std::cout << "getTicker:" << std::endl;
        std::cout << jsonString << std::endl;
    }
    return jsonString;
}
