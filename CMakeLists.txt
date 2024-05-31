cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME miniTrade)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/CommonUtils/generateSignature.cpp
        ${CMAKE_SOURCE_DIR}/CommonUtils/getTimeStamp.cpp
        main.cpp
)

#[[----------------------------------------personal setting----------------------------------------]]
include_directories(C:/Users/Mike_Wei/CLionProjects/test001/commonUtils)

#set(WEB_SOCKET_INCLUDE_DIR C:/Users/Mike_Wei/CLionProjects/websocketpp-0.8.2)
#set(BOOST_INCLUDE_DIR C:/Users/Mike_Wei/CLionProjects/boost_1_85_0)

#set(CMAKE_MODULE_PATH
#        ${CMAKE_MODULE_PATH}
#        "C:/Users/Mike_Wei/program/vcpkg-2024.04.26/downloads/tools/cmake-3.24.0-windows/cmake-3.24.0-windows-i386/share/cmake-3.24/Modules/FindOpenSSL.cmake")

find_package(Boost  REQUIRED COMPONENTS system thread date_time log log_setup program_options random)
#find_package(Boost  REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system Boost::thread Boost::date_time Boost::log Boost::log_setup Boost::program_options)
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})

find_package(OpenSSL REQUIRED)

#set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Users/Mike_Wei/program/vcpkg-2024.04.26/packages/jsoncpp_x64-windows/share/jsoncpp/")
find_package(jsoncpp CONFIG REQUIRED)
#find_package(jsoncpp CONFIG 1.9.5 REQUIRED)


#set(BOOST_LIB_DIR C:/Users/Mike_Wei/CLionProjects/boost_1_85_0/stage/lib)
#set(COMMON_UTILS_LIB_DIR C:/Users/Mike_Wei/CLionProjects/MiniTrade/CommonUtils/build/Release)

#[[----------------------------------------include and link rules----------------------------------------]]
target_include_directories(${PROJECT_NAME} PRIVATE
        ${WEB_SOCKET_INCLUDE_DIR}
#        ${BOOST_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

#target_link_libraries(${PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR}/libboost_random-vc143-mt-x64-1_85.lib)
#target_link_libraries(${PROJECT_NAME} PRIVATE ${BOOST_LIB_DIR}/libboost_random-vc143-mt-gd-x64-1_85.lib)

#target_link_libraries(${PROJECT_NAME} PRIVATE ${COMMON_UTILS_LIB_DIR}/CommonUtils.lib)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

target_link_libraries(${PROJECT_NAME} PRIVATE JsonCpp::JsonCpp)
