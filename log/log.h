#ifndef __EXTERNAL_LOG_H__
#define __EXTERNAL_LOG_H__

#include <memory>
#include "spdlog/spdlog.h"

namespace logex {

    class Log {
    public:
        static Log *getInstance() {
            static Log _log;
            return &_log;
        }

    public:
        Log();

        template<typename FormatString, typename... Args>
        void trace(const FormatString &fmt, Args &&...args) {
            mLogger->trace(fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void debug(const FormatString &fmt, Args &&...args) {
            mLogger->debug(fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void info(const FormatString &fmt, Args &&...args) {
            mLogger->info(fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void warn(const FormatString &fmt, Args &&...args) {
            mLogger->warn(fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void error(const FormatString &fmt, Args &&...args) {
            mLogger->error(fmt, std::forward<Args>(args)...);
        }

        template<typename FormatString, typename... Args>
        void critical(const FormatString &fmt, Args &&...args) {
            mLogger->critical(fmt, std::forward<Args>(args)...);
        }

    private:
        std::shared_ptr<spdlog::logger> mLogger;
    };
}

#define CCLOGTRACE(...) logex::Log::getInstance()->trace(__VA_ARGS__)
#define CCLOGDEBUG(...) logex::Log::getInstance()->debug(__VA_ARGS__)
#define CCLOGINFO(...) logex::Log::getInstance()->info(__VA_ARGS__)
#define CCLOGWARN(...) logex::Log::getInstance()->warn(__VA_ARGS__)
#define CCLOGERROR(...) logex::Log::getInstance()->error(__VA_ARGS__)
#define CCLOGCRITICAL(...) logex::Log::getInstance()->critical(__VA_ARGS__)

#define CCLOG(...) CCLOGINFO(__VA_ARGS__)

#endif //__EXTERNAL_LOG_H__
