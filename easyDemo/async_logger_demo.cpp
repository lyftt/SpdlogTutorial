/*
* 简单的异步日志示例
*
*/

#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h" // 用于文件输出的sink
#include "spdlog/async.h" // 异步日志支持
#include <memory>
#include <iostream>

int main() {
    
    // 1. 初始化异步线程池（8192条日志的队列，1个工作线程）
    spdlog::init_thread_pool(8192, 1);
    
    // 2. 创建文件sink（自动创建文件，非轮转）
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("async_demo.log", true);
    
    // 3. 创建异步日志器（关联线程池）
    auto async_log = std::make_shared<spdlog::async_logger>(
        "async_log", 
        file_sink, 
        spdlog::thread_pool(),
        spdlog::async_overflow_policy::block
    );
    
    // 4. 设置日志格式（简化格式）
    async_log->set_pattern("[%H:%M:%S] %v");
    
    // 5. 注册为全局默认日志器（所有spdlog::info()调用都指向它）
    spdlog::set_default_logger(async_log);
    
        // 6. 测试日志输出
    spdlog::info("启动异步日志系统!");
    
    // 多线程测试
    for (int i = 0; i < 10; ++i) {
        spdlog::info("异步日志测试消息 {}", i);
    }
    
    // 7. 程序结束前清空日志缓存
    spdlog::shutdown();
            
    return 0
}