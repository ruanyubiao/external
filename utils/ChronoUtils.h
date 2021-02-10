#ifndef __CHRONO_UTILS_H__
#define __CHRONO_UTILS_H__

#include <cstdint>
#include <chrono>
#include <ctime>    // std::time_t, struct std::tm, std::localtime
#include <iomanip>  // std::put_time
#include <string>
#include <sstream>

namespace ChronoUtils {

    /*
     * steady_clock 是单调的时钟，相当于教练手中的秒表；只会增长，适合用于记录程序耗时；
     * system_clock 是系统的时钟；因为系统的时钟可以修改；甚至可以网络对时； 所以用系统时间计算时间差可能不准。
     * high_resolution_clock 是当前系统能够提供的最高精度的时钟；它也是不可以修改的。相当于 steady_clock 的高精度版本。
     */

    /**
     * Returns the steady clock time in nanoseconds
     */
    inline int64_t get_steady_time_ns() {
        return std::chrono::time_point_cast<std::chrono::nanoseconds>(
                std::chrono::steady_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the steady clock time in microrseconds
     */
    inline int64_t get_steady_time_us() {
        return std::chrono::time_point_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the steady clock time in milliseconds
     */
    inline int64_t get_steady_time_ms() {
        return std::chrono::time_point_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the steady clock time in seconds
     */
    inline int64_t get_steady_time_s() {
        return std::chrono::time_point_cast<std::chrono::seconds>(
                std::chrono::steady_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the system time in nanoseconds
     */
    inline int64_t get_system_time_ns() {
        return std::chrono::time_point_cast<std::chrono::nanoseconds>(
                std::chrono::system_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the system time in microseconds
     */
    inline int64_t get_system_time_us() {
        return std::chrono::time_point_cast<std::chrono::microseconds>(
                std::chrono::system_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the system time in milliseconds
     */
    inline int64_t get_system_time_ms() {
        return std::chrono::time_point_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the system time in seconds
     */
    inline int64_t get_system_time_s() {
        return std::chrono::time_point_cast<std::chrono::seconds>(
                std::chrono::system_clock::now()).time_since_epoch().count();
    }

    /**
     * Returns the system time in windows time format
     */
    inline int64_t get_windows_time_ms() {
        static constexpr int64_t WIN_UNIX_DELTA = 0xA9730B66800LL;
        return (get_system_time_ms() + WIN_UNIX_DELTA);
    }

    /**
     * Returns the system time in mac time format
     */
    inline int64_t get_mac_time_ms() {
        static constexpr int64_t MAC_UNIX_DELTA = 0x1E4F3397400LL;
        return (get_system_time_ms() + MAC_UNIX_DELTA);
    }

    /*
        http://www.cplusplus.com/reference/iomanip/put_time/
        specifier	Replaced by	Example
        %a	Abbreviated weekday name *	Thu
        %A	Full weekday name *	Thursday
        %b	Abbreviated month name *	Aug
        %B	Full month name *	August
        %c	Date and time representation *	Thu Aug 23 14:55:02 2001
        %C	Year divided by 100 and truncated to integer (00-99)	20
        %d	Day of the month, zero-padded (01-31)	23
        %D	Short MM/DD/YY date, equivalent to %m/%d/%y	08/23/01
        %e	Day of the month, space-padded ( 1-31)	23
        %F	Short YYYY-MM-DD date, equivalent to %Y-%m-%d	2001-08-23
        %g	Week-based year, last two digits (00-99)	01
        %G	Week-based year	2001
        %h	Abbreviated month name * (same as %b)	Aug
        %H	Hour in 24h format (00-23)	14
        %I	Hour in 12h format (01-12)	02
        %j	Day of the year (001-366)	235
        %m	Month as a decimal number (01-12)	08
        %M	Minute (00-59)	55
        %n	New-line character ('\n')
        %p	AM or PM designation	PM
        %r	12-hour clock time *	02:55:02 pm
        %R	24-hour HH:MM time, equivalent to %H:%M	14:55
        %S	Second (00-61)	02
        %t	Horizontal-tab character ('\t')
        %T	ISO 8601 time format (HH:MM:SS), equivalent to %H:%M:%S	14:55:02
        %u	ISO 8601 weekday as number with Monday as 1 (1-7)	4
        %U	Week number with the first Sunday as the first day of week one (00-53)	33
        %V	ISO 8601 week number (00-53)	34
        %w	Weekday as a decimal number with Sunday as 0 (0-6)	4
        %W	Week number with the first Monday as the first day of week one (00-53)	34
        %x	Date representation *	08/23/01
        %X	Time representation *	14:55:02
        %y	Year, last two digits (00-99)	01
        %Y	Year	2001
        %z	ISO 8601 offset from UTC in timezone (1 minute=1, 1 hour=100)
        If timezone cannot be termined, no characters	+100
        %Z	Timezone name or abbreviation *
        If timezone cannot be termined, no characters	CDT
        %%	A % sign	%
     */
    inline std::string get_system_time(std::string format = std::string("%Y-%m-%d %H:%M:%S")) {
        auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), format.c_str());
        return ss.str();
    }


    class Timer {
    public:
        Timer() : m_begin(std::chrono::high_resolution_clock::now()) {}

        void reset() {
            m_begin = std::chrono::high_resolution_clock::now();
        }

        template<typename T=std::chrono::milliseconds>
        int64_t elapsed() const {
            return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_begin).count();
        }

        int64_t elapsed_ns() const {
            return elapsed<std::chrono::nanoseconds>();
        }

        int64_t elapsed_us() const {
            return elapsed<std::chrono::microseconds>();
        }

        int64_t elapsed_ms() const {
            return elapsed<std::chrono::milliseconds>();
        }

        int64_t elapsed_s() const {
            return elapsed<std::chrono::seconds>();
        }


    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
    };


}

#endif //__CHRONO_UTILS_H__
