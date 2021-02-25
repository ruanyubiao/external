#ifndef FACE_THREADLOOP_H
#define FACE_THREADLOOP_H

#include <chrono>
#include <future>
#include <thread>
#include <cstdio>
#include <utility>
#include <sstream>
#include <cstdlib>

using Task = std::function<void()>;

class Runnable {
public:
    void sleep_second(int second) {
        std::this_thread::sleep_for(std::chrono::seconds(second));
    }

    void sleep_millisecond(int millisecond) {
        std::this_thread::sleep_for(std::chrono::milliseconds(millisecond));
    }

    void sleep_microsecond(int microsecond) {
        std::this_thread::sleep_for(std::chrono::microseconds(microsecond));
    }

    virtual void run() = 0;
};

class ThreadLoop {
public:
    ThreadLoop(std::shared_ptr<Runnable> looper) : mLooper(looper) {
    }

    ThreadLoop(const Task &func) {
        mTaskList.push_back(func);
    }


    void start() {
        mThread = std::thread([this]() { this->loop(this->mExitSignal.get_future()); });
        mThread.detach();
    }

    void stop() { mExitSignal.set_value(); }

    virtual ~ThreadLoop() {
        printf("destroy %s\n", __func__);
    }

    void loop(std::future<void> exitListner) {
        printf("start %s, %ld\n", __func__, getThreadID());
        do {
            if (mLooper) {
                mLooper->run();
            }

            if (!mTaskList.empty()) {
                for (auto &func : mTaskList) {
                    func();
                }
            }

        } while (exitListner.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout);
        printf("exit %s\n", __func__);
    }

private:
    int64_t getThreadID() {
        std::stringstream ss;
        ss << std::this_thread::get_id();
        std::string result;
        ss >> result;
        return std::strtol(result.c_str(), nullptr, 10);
    }

private:
    std::vector<Task> mTaskList{};
    std::shared_ptr<Runnable> mLooper;
    std::thread mThread;
    std::promise<void> mExitSignal;
};


#endif //FACE_THREADLOOP_H
