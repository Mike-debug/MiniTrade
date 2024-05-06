cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME CommonUtils)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME} generateSignature.cpp getTimeStamp.cpp)

#[[----------------------------------------personal setting----------------------------------------]]
include_directories("./")
set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        "C:/Users/Mike_Wei/program/vcpkg/downloads/tools/cmake-3.24.0-windows/cmake-3.24.0-windows-i386/share/cmake-3.24/Modules/FindOpenSSL.cmake")
find_package(OpenSSL REQUIRED)

#[[----------------------------------------include and link rules----------------------------------------]]
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
