//
// Created by Mike_Wei on 5/4/2024.
//


#include <CommonUtils/getTimeStamp>

unsigned long long getTimeStamp(long long diff) {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 将时间点转换为毫秒
    auto duration = now.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    // 输出 13 位时间戳
    return millis - diff;
}

// 函数将13位时间戳转换为日期时间字符串
std::string timestampToString(long long timestamp) {
    // 将13位时间戳转换为std::chrono::milliseconds类型
    std::chrono::milliseconds ms(timestamp);

    // 使用std::chrono::system_clock将std::chrono::milliseconds类型转换为时间点
    std::chrono::system_clock::time_point tp(ms);

    // 将时间点转换为时间结构体
    std::time_t t = std::chrono::system_clock::to_time_t(tp);

    // 使用std::put_time将时间结构体格式化为日期时间字符串
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

// 获取当前日期时间字符串
std::string getCurrentDateTimeString() {
    // 获取当前时间点
    auto now = std::chrono::system_clock::now();

    // 将时间点转换为时间结构体
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    // 使用std::put_time将时间结构体格式化为日期时间字符串
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S");

    return oss.str();
}

std::string getTimeStampStr() {
    return std::to_string(getTimeStamp()) + ": ";
}

