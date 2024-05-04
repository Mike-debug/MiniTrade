cmake_minimum_required(VERSION 3.16)
project(miniTrade)
set(CMAKE_CXX_STANDARD 14)

add_executable(miniTrade main.cpp)

set(WEB_SOCKET_INCLUDE_DIR C:/Users/Mike_Wei/CLionProjects/websocketpp-0.8.2)
set(BOOST_INCLUDE_DIR C:/Users/Mike_Wei/CLionProjects/boost_1_85_0)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "C:/Users/Mike_Wei/program/vcpkg/downloads/tools/cmake-3.24.0-windows/cmake-3.24.0-windows-i386/share/cmake-3.24/Modules/FindOpenSSL.cmake")
find_package(OpenSSL REQUIRED)

target_include_directories(miniTrade PRIVATE
        ${WEB_SOCKET_INCLUDE_DIR}
        ${BOOST_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(miniTrade PRIVATE C:/Users/Mike_Wei/CLionProjects/boost_1_85_0/stage/lib/libboost_random-vc143-mt-x64-1_85.lib)

target_link_libraries(miniTrade PRIVATE OpenSSL::SSL OpenSSL::Crypto)