#pragma once

#include <future>
#include <queue>
#include <functional>
#include <thread>

class ThreadPool
{
    using task = std::function<void()>;

public:
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;

    explicit ThreadPool(size_t __size)
        : size_(__size)
        , alive(true)
    {
        for (size_t i = 0; i < __size; i++)
        {
            threads.emplace_back([this]()
            {
                std::unique_lock<std::mutex> lock(mutex_);

                while(alive)
                {
                    if(!tasks.empty())
                    {
                        auto current_task = tasks.front();
                        tasks.pop();

                        lock.unlock();

                        current_task();
                    }
                    else
                    {
                        is_any_tasks.wait(lock);
                    }
                }
            });
        }
    }

    ~ThreadPool()
    {
        alive = false;

        is_any_tasks.notify_all();
        for (size_t i = 0; i < size_; i++)
        {
            threads[i].join();
        }        
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
    {
        auto task = std::make_shared<std::packaged_task<decltype(func(args...))()>>
        (
            std::bind(func, args...)
        );

        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks.emplace([task]()
            {
                (*task)();
            });
        }

        is_any_tasks.notify_one();

        return task->get_future();
    }

private:
    std::vector<std::thread> threads;
    std::queue<task> tasks;

    std::condition_variable is_any_tasks;
    std::atomic_bool alive;
    std::mutex mutex_;

    size_t size_;
};