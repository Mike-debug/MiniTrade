#include <cstdlib>
#include <iostream>
#include <string>

#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <utility>

#include <json/json.h>

#include "infrastructure/webSocket"

#include "CommonUtils/jsonSpecificUtils"
#include "infrastructure/testNest"

int main() {
    using namespace std;
    auto diffDelay = testnet::getTimeDelay();
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
