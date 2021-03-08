#include "log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"

namespace logex {

    Log::Log() {

        try {
            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_level(spdlog::level::trace);

            // Create a file rotating logger with 5mb size max and 3 rotated files
            auto size = 1024 * 1024 * 5;
            auto files = 30;
            auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/default.log", size, files);
            file_sink->set_level(spdlog::level::trace);

            auto err_file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/error.log", size, files);
            err_file_sink->set_level(spdlog::level::err);

            spdlog::sinks_init_list sinks = {console_sink, file_sink, err_file_sink};
            mLogger = std::make_shared<spdlog::logger>("default", begin(sinks), end(sinks));
            // 设置日志格式
            mLogger->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] %v");
            // 设置日志记录级别
            mLogger->set_level(spdlog::level::trace);
            //设置当触发 trace 或更严重的错误时立刻刷新日志到 disk
            mLogger->flush_on(spdlog::level::trace);

            //set multi_sinks logger as default logger
            spdlog::set_default_logger(mLogger);
            //spdlog::register_logger(mLogger);


            //std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/default.log", 0, 0)
        }
        catch (const spdlog::spdlog_ex &ex) {
            //std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }


    };


}