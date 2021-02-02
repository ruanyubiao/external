#ifndef __CHRONO_UTILS_H__
#define __CHRONO_UTILS_H__

#include <cstdint>
#include <chrono>

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
    inline int64_t mac_time_ms() {
        static constexpr int64_t MAC_UNIX_DELTA = 0x1E4F3397400LL;
        return (get_system_time_ms() + MAC_UNIX_DELTA);
    }

    /**
     * Returns a time point for the current time. See timediff_ms, timediff_s
     * @return A time point is returned
     */
    inline std::chrono::time_point<std::chrono::steady_clock> time_diff_start() {
        return std::chrono::steady_clock::now();
    }

    /**
     * Returns the difference between the current time point and the given in milliseconds
     * @param start - Time point returned by a previous call to time_diff_start()
     * @return Difference between the current time and given @p start in milliseconds
     */
    inline int64_t time_diff_stop_ms(const std::chrono::time_point<std::chrono::steady_clock> &start) {
        return std::chrono::duration_cast<std::chrono::milliseconds, int64_t>(
                std::chrono::steady_clock::now() - start).count();
    }

    /**
     * Returns the difference between the current time point and the given in seconds as int64_t
     * @param start - Time point returned by a previous call to time_diff_start()
     * @return Difference between the current time and given @p start as a int64_t in seconds
     */
    inline int64_t time_diff_stop_s(const std::chrono::time_point<std::chrono::steady_clock> &start) {
        return std::chrono::duration_cast<std::chrono::seconds, int64_t>(
                std::chrono::steady_clock::now() - start).count();

        // return std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
    }
}

#endif //__CHRONO_UTILS_H__
