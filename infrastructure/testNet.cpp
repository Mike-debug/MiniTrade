#include"./testNet"

int testnet::connect_url(websocket_endpoint &endpoint, std::string &testnet_binance_url) {
    /* connect */
    int id = endpoint.connect(testnet_binance_url);
    if (id != -1) {
        std::cout << "> Created connection with id " << id << std::endl;
    } else {
        exit(0);
    }
    return id;
}

void testnet::test_ws_connect(websocket_endpoint &endpoint, int connect_id = 0, int testNum = 5) {
    /* test net */
    std::string input{};
    while (testNum > 0) {
        Sleep(2000);
        --testNum;
        input = "{\"id\":1,\"method\":\"time\"}\n";
        endpoint.send(connect_id, input);
    }
    Sleep(2000);
}

int testnet::disconnect(websocket_endpoint &endpoint, int connect_id, std::string reason) {
    /* close */
    int close_code = websocketpp::close::status::normal;
    endpoint.close(connect_id, close_code, std::move(reason));
    Sleep(2000);
    return close_code;
}

std::pair<double, double> testnet::calculateTimeDiffDelay(websocket_endpoint &endpoint, int connect_id) {
    using namespace std;

    /* get msg record */
    auto msgs = endpoint.get_metadata(connect_id)->getMst();
    if (cfg::ifLog) {
        printf("msgs\n");
        printVector(msgs);
    }
    /* forfeit the failed tests */
    auto msgNum = msgs.size() & (~0x01);
    if (cfg::ifLog) { printf("msgNum: %llu\n", msgNum); }

    /* parse timestamps */
    vector<unsigned long long> timeStamps = getTimeStamps(msgs, msgNum);
    if (cfg::ifLog) {
        printf("timeStamps:\n");
        printVector(timeStamps);
    }
    /*  calculate the diff and delay */
    auto ret = calculateTimeDiffDelaySub(timeStamps);

    return ret;
}

std::vector<unsigned long long> testnet::getTimeStamps(const std::vector<std::string> &msgs, unsigned int msgNum) {
    std::vector<unsigned long long> timeStamps{};
    // 创建 JSON 对象
    Json::Value root;
    // 解析 JSON 字符串
    Json::Reader reader;
    for (int i{0}; i < msgNum; i += 2) {
        unsigned long long localSentTime{};
        unsigned long long localRecvTime{};
        unsigned long long SeverSentTime{};
        try {
            localSentTime = stoull(msgs.at(i).substr(3, 13));
            localRecvTime = stoull(msgs.at(i + 1).substr(3, 13));
            reader.parse(msgs.at(i + 1).substr(18), root);
            SeverSentTime = stoull(root["result"]["serverTime"].asString());
        } catch (...) {
            std::cout << "exception while parsing time stamps" << std::endl;
            continue;
        }
        timeStamps.push_back(localSentTime);
        timeStamps.push_back(localRecvTime);
        timeStamps.push_back(SeverSentTime);
    }
    return timeStamps;
}

std::pair<double, double> testnet::calculateTimeDiffDelaySub(const std::vector<unsigned long long> &timeStamps) {
    double diff{0.};
    double delay{0.};
    for (int i{0}; i < timeStamps.size(); i += 3) {
        diff += (
            static_cast<long long>(timeStamps[i])
            + static_cast<long long>(timeStamps[i + 1])
            - (static_cast<long long>(timeStamps[i + 2]) << 1)
        ) * 0.5;
        delay += (static_cast<long long>(timeStamps[i + 1]) - static_cast<long long>(timeStamps[i])) >> 1;
    }
    diff /= (timeStamps.size() / 3);
    delay /= (timeStamps.size() / 3);
    auto ret = std::make_pair(diff, delay);
    return ret;
}

std::pair<double, double> testnet::getTimeDelay() {
    websocket_endpoint endpoint;
    std::string testnet_binance_url{"wss://testnet.binance.vision/ws-api/v3"};

    /* connect */
    int id = connect_url(endpoint, testnet_binance_url);

    /* test net */
    test_ws_connect(endpoint, id, 5);

    /* calculate diff and delay */
    auto ret = calculateTimeDiffDelay(endpoint, id);

    /* close */
    disconnect(endpoint, id);
    return ret;
}

