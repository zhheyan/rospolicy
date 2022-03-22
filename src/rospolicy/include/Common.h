/*
 * @Author: your name
 * @Date: 2022-03-13 19:36:59
 * @LastEditTime: 2022-03-17 00:04:01
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/common.h
 */

#ifndef __COMMON_H_
#define __COMMON_H_

#include <queue>
#include <iostream>
#include <mutex>
#include <memory>
#include <condition_variable>


/**
 * @description:
 * @param {*}
 * @return {*}
 */
template<typename T> 
class ThreadSafe_Queue
{
private:
    mutable std::mutex m_mut;
    std::queue <T> m_queue;
    std::condition_variable m_data_cond;

public:
    ThreadSafe_Queue() {}
    ThreadSafe_Queue(const ThreadSafe_Queue&) = delete;
    void push(T data)
    {
        std::lock_guard<std::mutex> lg(m_mut);
        m_queue.push(data);
        m_data_cond.notify_all();
    }
    void WaitPop(T& t)
    {
        std::unique_lock<std::mutex> ul(m_mut);
        m_data_cond.wait(ul, [this] {return !m_queue.empty(); });
        t = m_queue.front();
        m_queue.pop();
    }
    std::shared_ptr<T> WaitPop()
    {
        std::unique_lock<std::mutex> ul(m_mut);
        m_data_cond.wait(ul, [this] {return !m_queue.empty(); });

        std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
        m_queue.pop();
        return res;
    }
    bool TryPop(T& t)
    {
        std::lock_guard<std::mutex> lg(m_mut);
        if (m_queue.empty())
            return false;

        t = m_queue.front();
        m_queue.pop();
        return true;
    }

    std::shared_ptr<T> TryPop()
    {
        std::lock_guard<std::mutex> lg(m_mut);
        if (m_queue.empty())
            return std::shared_ptr<T>();
        std::shared_ptr<T> res(std::make_shared<T>(m_queue.front()));
        m_queue.pop();
        return res;
    }

    bool IsEmpty()
    {
        std::lock_guard<std::mutex> lg(m_mut);
        return m_queue.empty();
    }

};




#endif