#ifndef __EXTERNAL_LOG_H__
#define __EXTERNAL_LOG_H__

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
//#include "spdlog/sinks/rotating_file_sink.h"

class Log {
public:
    static Log *getInstance() {
        static Log _log;
        return &_log;
    }

public:
    Log() {
        std::vector<spdlog::sink_ptr> sinks;
        //设置为异步日志，同步纯文件日志 3W/s，控制台日志 3k/s
        //spdlog::set_async_mode(32768);  // 必须为 2 的幂

        sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/face.log", 0, 0));
        mLogger = std::make_shared<spdlog::logger>("face", begin(sinks), end(sinks));
        spdlog::register_logger(mLogger);

        //设置 logger 格式
        // 13:28:19.324  613090  [E]  message
        // mLogger->set_pattern("%T.%e  %t  [%L]  %v");

        //设置 logger 格式
        // with timestamp, thread_id, filename and line number
        // 2020-12-30 15:46:56.681969 <thread 91920> [info] message
        mLogger->set_pattern("%Y-%m-%d %H:%M:%S.%f <thread %t> [%l] %v");

        // 设置日志记录级别
        mLogger->set_level(spdlog::level::trace);
        //设置当触发 trace 或更严重的错误时立刻刷新日志到 disk
        mLogger->flush_on(spdlog::level::trace);
    };

    inline ~Log() {
        spdlog::drop_all();
    };

    inline auto getLogger() { return mLogger; }

private:
    std::shared_ptr<spdlog::logger> mLogger;
};


#define CCLOGTRACE(...) Log::getInstance()->getLogger()->trace(__VA_ARGS__)
#define CCLOGDEBUG(...) Log::getInstance()->getLogger()->debug(__VA_ARGS__)
#define CCLOGINFO(...) Log::getInstance()->getLogger()->info(__VA_ARGS__)
#define CCLOGWARN(...) Log::getInstance()->getLogger()->warn(__VA_ARGS__)
#define CCLOGERROR(...) Log::getInstance()->getLogger()->error(__VA_ARGS__)
#define CCLOGCRITICAL(...) Log::getInstance()->getLogger()->critical(__VA_ARGS__)

#define CCLOG(...) CCLOGINFO(__VA_ARGS__)

#endif //__EXTERNAL_LOG_H__
