#include <cstdlib>
#include <iostream>
#include <string>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <utility>

#include "infrastructure/webSocket"
#include "infrastructure/testNet"

void updateDiff();

int manualOp();

void checkoutConnectId(int cnctId);

int autoOp();

int main() {
    using namespace std;

    printf("0 - manul op;    1 - auto op\n");
    int choice{};
    cin >> choice;
    if (choice == 0) {
        manualOp();
    } else if (choice == 1) {
        autoOp();
    } else {
        cout << "illegal choice" << endl;
    }
    return 0;
}

void updateDiff() {
    using namespace std;
    auto diffDelay = testnet::getTimeDelay();
    if (cfg::ifLog) {
        std::cout << "diff and delay" << std::endl;
        printPair(diffDelay);
        cout << "DIFF before: " << DIFF << endl;
    }
    DIFF = static_cast<long long>(diffDelay.first);
    if (cfg::ifLog) {
        cout << "DIFF after: " << DIFF << endl;
    }
}

int manualOp() {
    cfg::refreshConfig();

    using namespace std;
    updateDiff();

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
        } else if (input == "connect") {
            int id = endpoint.connect(cfg::testnet_url);
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        } else if (input == "connectf") {
            int id = endpoint.connect(cfg::future_url);
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        } else if (input != "connect" && input.substr(0, 7) == "connect") {
            int id = endpoint.connect(input.substr(8));
            if (id != -1) {
                std::cout << "> Created connection with id " << id << std::endl;
            }
        } else if (input.substr(0, 9) == "spotprice") {
            std::stringstream ss(input);

            std::string cmd;
            int id;

            ss >> cmd >> id;

            if (endpoint.get_metadata(id)->get_url() != cfg::future_url) {
                std::cout << "on a wrong connection" << std::endl;
                continue;
            }
            std::string message = std::move(getTicker(false));
            endpoint.send(id, message);
        } else if (input.substr(0, 11) == "futureprice") {
            std::stringstream ss(input);

            std::string cmd;
            int id;

            ss >> cmd >> id;

            if (endpoint.get_metadata(id)->get_url() != cfg::future_url) {
                std::cout << "on a wrong connection" << std::endl;
                continue;
            }
            std::string message = std::move(getTicker());
            endpoint.send(id, message);
        } else if (input.substr(0, 4) == "sell") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            std::string price;

            ss >> cmd >> id >> price;
            if (endpoint.get_metadata(id)->get_url() != cfg::testnet_url) {
                std::cout << "on a wrong connection" << std::endl;
                continue;
            }

            std::string message = std::move(getTradeMsgFromConfig(true, price, DIFF));

            endpoint.send(id, message);
        } else if (input.substr(0, 3) == "buy") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            std::string price;

            ss >> cmd >> id >> price;
            if (endpoint.get_metadata(id)->get_url() != cfg::testnet_url) {
                std::cout << "on a wrong connection" << std::endl;
                continue;
            }
            std::string message = std::move(getTradeMsgFromConfig(false, price, DIFF));

            endpoint.send(id, message);
        } else if (input.substr(0, 6) == "cancel") {
            std::stringstream ss(input);

            std::string cmd;
            int id;
            std::string orderId;

            ss >> cmd >> id >> orderId;
            if (endpoint.get_metadata(id)->get_url() != cfg::testnet_url) {
                std::cout << "on a wrong connection" << std::endl;
                continue;
            }

            std::string message = std::move(getCancelMsgFromConfig(orderId, DIFF));
            cout << message << endl;

            endpoint.send(id, message);
        } else if (input.substr(0, 13) == "refreshConfig") {
            cfg::refreshConfig();
        } else if (input.substr(0, 10) == "showConfig") {
            cfg::printConfig();
        } else if (input.substr(0, 10) == "updateDiff") {
            updateDiff();
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

void checkoutConnectId(int cnctId) {
    if (cnctId != -1) {
        std::cout << "> Created connection with id " << cnctId << std::endl;
    } else {
        std::cout << "> Failed to connect the price net " << cnctId << std::endl;
        exit(0);
    }
}

int autoOp() {
    using namespace std;
    cfg::refreshConfig();
    updateDiff();

    websocket_endpoint endpoint_stk;
    websocket_endpoint endpoint_ftk;
    websocket_endpoint endpoint_std;
    websocket_endpoint endpoint_ftd;

    int endpoint_stk_id = endpoint_stk.connect(cfg::future_url);
    checkoutConnectId(endpoint_stk_id);
    int endpoint_ftk_id = endpoint_ftk.connect(cfg::future_url);
    checkoutConnectId(endpoint_ftk_id);
    int endpoint_std_id = endpoint_std.connect(cfg::testnet_url);
    checkoutConnectId(endpoint_std_id);
    /* no related api of ws */
    /*int endpoint_ftd_id = endpoint_ftd.connect(cfg::testnet_url);
    checkoutConnectId(endpoint_ftd_id);*/

    std::string message = std::move(getTicker(false));
    endpoint_stk.send(endpoint_stk_id, message);

    message = std::move(getTicker());
    endpoint_ftk.send(endpoint_ftk_id, message);

    std::string price{};
    message = std::move(getTradeMsgFromConfig(false, price, DIFF));
    message = std::move(getTradeMsgFromConfig(true, price, DIFF));
    endpoint_std.send(endpoint_std_id, message);
    /*endpoint_ftd.send(endpoint_std_id, message);*/

    int close_code = websocketpp::close::status::normal;
    std::string reason{};
    endpoint_stk.close(endpoint_stk_id, close_code, reason);
    endpoint_ftk.close(endpoint_ftk_id, close_code, reason);
    endpoint_std.close(endpoint_std_id, close_code, reason);
    /*endpoint_ftd.close(endpoint_ftd_id, close_code, reason);*/

    return 0;
}