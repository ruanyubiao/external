#ifndef FACE_THREADLOOP_H
#define FACE_THREADLOOP_H

#include <chrono>
#include <future>
#include <thread>
#include <cstdio>
#include <utility>
#include <sstream>
#include <cstdlib>
#include "log.h"


class ThreadLoop {
public:
    ThreadLoop() = default;

    explicit ThreadLoop(std::function<void()> func, int sleep_ms = 1) : m_task(std::move(func)), m_sleep_ms(sleep_ms) {
    }


    void set_task(std::function<void()> func) {
        m_task = std::move(func);
    }

    void set_sleep_ms(int sleep_ms) {
        m_sleep_ms = sleep_ms;
    }

    void start() {
        m_thread = std::thread(&ThreadLoop::loop, this);
//        m_thread.detach();
    }

    void stop() {
        m_thread_stop = true;
    }

    ~ThreadLoop() {
        CCLOG("ThreadLoop::destroy {}", __func__, get_thread_id());
        if (m_thread.joinable()) {
            m_thread.join();
        }
    }

    void loop() {
        CCLOG("ThreadLoop::start {}, {}", __func__, get_thread_id());
        while (!m_thread_stop) {
            m_task();
            if (m_sleep_ms > 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(m_sleep_ms));
            }
        }
        CCLOG("ThreadLoop::exit {}", __func__, get_thread_id());
    }

    ThreadLoop(const ThreadLoop &) = delete;

    ThreadLoop &operator=(const ThreadLoop &) = delete;

private:
    int64_t get_thread_id() {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::string result;
        ss >> result;
        return std::strtol(result.c_str(), nullptr, 10);
    }

private:
    std::function<void()> m_task;
    int m_sleep_ms = 1;
    bool m_thread_stop = false;
    std::thread m_thread;
};


#endif //FACE_THREADLOOP_H
