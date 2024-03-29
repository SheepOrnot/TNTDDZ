#ifndef THREADPOOL_H
#define THREADPOOL_H


#include <vector>
#include <utility>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>
#include <future>
template<typename T>
class SafeQueue
{
private:
    std::queue<T> safequeue_queue;
    std::mutex safequeue_mutex;
public:
    SafeQueue(){}
    ~SafeQueue(){}
    SafeQueue(SafeQueue &&other){}

    bool empty()
    {
        std::unique_lock<std::mutex>lock(safequeue_mutex);
        return safequeue_queue.empty();
    }
    int size()
    {
        std::unique_lock<std::mutex>lock(safequeue_mutex);
        return safequeue_queue.size();
    }
    void add(T &t)
    {
        std::unique_lock<std::mutex>lock(safequeue_mutex);
        safequeue_queue.emplace(t);
    }
    bool take(T &t)
    {
        std::unique_lock<std::mutex>lock(safequeue_mutex);
        if(safequeue_queue.empty()) return false;
        t = std::move(safequeue_queue.front());
        safequeue_queue.pop();
        return true;
    }
};


class ThreadPool
{
public:
    ThreadPool(const int ThreadSize = 4)
    {
        pool_threads = std::vector<std::thread>(ThreadSize);
        onwork = true;
        for(int i = 0; i < pool_threads.size(); i++)
        {
            pool_threads.at(i) = std::thread(ThreadNote(i,this));
        }
    }
    ~ThreadPool()
    {
        while(!pool_queue.empty())
        {
            conditional_lock.notify_all();
            std::unique_lock<std::mutex>shout_lock(shutdown_mutex);
            shutdown_lock.wait(shout_lock);
        }
        onwork = false;
        for(int i = 0; i < pool_threads.size(); i++)
            if(pool_threads.at(i).joinable())
            {
                pool_threads.at(i).join();
            }
    }
    ThreadPool(const ThreadPool &)=delete;
    ThreadPool(ThreadPool &&)=delete;
    ThreadPool &operator=(const ThreadPool &)=delete;
    ThreadPool &&operator=(ThreadPool &&)=delete;
    //禁止拷贝

    void shutdown()
    {
        onwork = false;
        conditional_lock.notify_all();
        for(int i = 0; i < pool_threads.size(); i++)
            if(pool_threads.at(i).joinable())
            {
                pool_threads.at(i).join();
            }
    }

    template<typename F,typename... Args>
    auto submit(F &&f,Args &&...args)->std::future<decltype(f(args...))>
    {
        std::function<decltype(f(args...))()> fnc=std::bind(std::forward<F>(f),std::forward<Args>(args)...);
        auto task_ptr=std::make_shared<std::packaged_task<decltype(f(args...))()>>(fnc);
        std::function<void()>task=[task_ptr]()
        {
            (*task_ptr)();
        };
        pool_queue.add(task);
        conditional_lock.notify_one();
        return task_ptr->get_future();
    }

private:
    bool onwork;
    std::vector<std::thread> pool_threads;
    SafeQueue<std::function<void()>> pool_queue;
    std::mutex conditional_mutex;
    std::condition_variable conditional_lock;
    std::mutex shutdown_mutex;
    std::condition_variable shutdown_lock;

    class ThreadNote
    {
    private:
        int id;
        ThreadPool *pool;

    public:
        ThreadNote(const int id,ThreadPool *pool):id(id),pool(pool){}

        void operator()()
        {
            while(pool->onwork)
            {
                {
                    std::unique_lock<std::mutex>lock(pool->conditional_mutex);
                    if(pool->pool_queue.empty())
                    {
                        pool->conditional_lock.wait(lock);
                    }
                }
                std::function<void()> fnc;
                if(pool->pool_queue.take(fnc)) fnc();
                pool->shutdown_lock.notify_all();
            }
        }
    };

};

#endif // THREADPOOL_H
