/*
* 简单的同步日志示例
*
*/

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // 用于文件输出的sink
#include "spdlog/async.h" // 异步日志支持
#include <memory>
#include <iostream>

int main() {

    // 创建一个指向文件的日志器，文件名为 logs/basic-log.txt，并截断文件（即每次运行清空）
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt", true);
    spdlog::set_default_logger(file_logger); // 设置为默认日志器

    //设置打印文件、函数、行号
    //spdlog::set_pattern("[%Y-%m-%d %H:%M:%S] [%l] [%s:%#] %v");
    spdlog::set_level(spdlog::level::info); // 设置日志级别为info

    file_logger->set_pattern("[%H:%M:%S] %v");

    SPDLOG_INFO("this is a");

    int file_size = 128;
    //std::string filename = "data.bin";
    //spdlog::info("File '{}' created, size: {} KB", filename, file_size);
    spdlog::info("This log message will be written to the file");
    spdlog::shutdown(); // 确保刷新所有缓冲的日志

    return 0;
}