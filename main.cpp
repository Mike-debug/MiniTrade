#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <json/json.h>

#include "infrastructure/webSocket"

#include "CommonUtils/jsonSpecificUtils"
#include "commonUtils.h"

using namespace std;

pair<double, double> getTimeDelay() {
    websocket_endpoint endpoint;

    std::string input{"connect wss://testnet.binance.vision/ws-api/v3"};

    int id = endpoint.connect(input.substr(8));
    if (id != -1) {
        std::cout << "> Created connection with id " << id << std::endl;
    }

    int done = 5;
    while (done > 0) {
        Sleep(2000);
        --done;
        input = "send 0 {\"id\":1,\"method\":\"time\"}\n";
        std::stringstream ss(input);

        std::string cmd;
        std::string message;

        ss >> cmd >> id;
        std::getline(ss, message);

        endpoint.send(id, message);
    }
    Sleep(2000);
    auto msgs = endpoint.get_metadata(id)->getMst();
    auto msgNum = msgs.size() & (~0x01);
    vector<unsigned long long> timeStamps{};
    cout << "msgNum: " << msgNum << endl;
    // 创建 JSON 对象
    Json::Value root;

    // 解析 JSON 字符串
    Json::Reader reader;
    for (int i{0}; i < msgNum; ++i) {
        if (!(i & (0x01))) {
            timeStamps.emplace_back(stoull(msgs.at(i).substr(3, 13)));
        } else {
            timeStamps.emplace_back(stoull(msgs.at(i).substr(3, 13)));
            reader.parse(msgs.at(i).substr(18), root);
            timeStamps.emplace_back(stoull(root["result"]["serverTime"].asString()));
        }
    }
    printVector(timeStamps);

    double diff{};
    double delay{};
    for (int i{0}; i < timeStamps.size(); i += 3) {
        diff += (timeStamps[i] + timeStamps[i + 1] - 2 * timeStamps[i + 2]) * 0.5;
        delay += (timeStamps[i + 1] - timeStamps[i]) * 0.5;
    }
    diff /= (timeStamps.size() / 3);
    delay /= (timeStamps.size() / 3);

    auto ret = make_pair(diff, delay);
    printPair(ret);

    input = "close 0";
    std::stringstream ss(input);

    std::string cmd;
    int close_code = websocketpp::close::status::normal;
    std::string reason;

    ss >> cmd >> id >> close_code;
    std::getline(ss, reason);

    endpoint.close(id, close_code, reason);
    Sleep(2000);
    return ret;
}

int main() {
    auto diffDelay = getTimeDelay();
    DIFF = diffDelay.first;

    bool done = false;
    std::string input;
    websocket_endpoint endpoint;

    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            done = true;
        } else if (input == "help") {
            std::cout
                    << "\nCommand List:\n"
                    << "connect <ws uri>\n"
                    << "send <connection id> <message>\n"
                    << "close <connection id> [<close code:default=1000>] [<close reason>]\n"
                    << "show <connection id>\n"
                    << "help: Display this help text\n"
                    << "quit: Exit the program\n"
                    << std::endl;
        } else if (input.substr(0, 7) == "connect") {
            int id = endpoint.connect(input.substr(8));
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        } else if (input.substr(0, 4) == "send") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            std::string message;

            ss >> cmd >> id;
            std::getline(ss, message);

            endpoint.send(id, message);
        } else if (input.substr(0, 5) == "trade") {
            std::stringstream ss(input);

            std::string cmd;
            int id;

            ss >> cmd >> id;
            std::string message = std::move(getTradeMsgExample());
            cout << message << endl;

            endpoint.send(id, message);
        } else if (input.substr(0, 5) == "close") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            int close_code = websocketpp::close::status::normal;
            std::string reason;

            ss >> cmd >> id >> close_code;
            std::getline(ss, reason);

            endpoint.close(id, close_code, reason);
        } else if (input.substr(0, 4) == "show") {
            int id = atoi(input.substr(5).c_str());

            connection_metadata::ptr metadata = endpoint.get_metadata(id);
            if (metadata) {
                std::cout << *metadata << std::endl;
            } else {
                std::cout << "> Unknown connection id " << id << std::endl;
            }
        } else {
            std::cout << "> Unrecognized Command" << std::endl;
        }
    }

    return 0;
}

