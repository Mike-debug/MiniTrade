cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME miniTrade)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/CommonUtils/generateSignature.cpp
        ${CMAKE_SOURCE_DIR}/CommonUtils/getTimeStamp.cpp
        ${CMAKE_SOURCE_DIR}/infrastructure/testNet.cpp
        ${CMAKE_SOURCE_DIR}/infrastructure/webSocket.cpp
        ${CMAKE_SOURCE_DIR}/config/jsonSpecificUtils.cpp
        ${CMAKE_SOURCE_DIR}/config/config.cpp
        ${CMAKE_SOURCE_DIR}/config/Sync.cpp
        main.cpp
)

#[[----------------------------------------personal setting----------------------------------------]]
set(WEB_SOCKET_INCLUDE_DIR C:/Users/Mike_Wei/CLionProjects/websocketpp-0.8.2)

find_package(Boost 1.84.0 REQUIRED COMPONENTS system thread date_time log log_setup program_options random)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

find_package(OpenSSL REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

#[[----------------------------------------include and link rules----------------------------------------]]
target_include_directories(${PROJECT_NAME} PRIVATE
        ${WEB_SOCKET_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)
