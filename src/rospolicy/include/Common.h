/*
 * @Author: your name
 * @Date: 2022-03-13 19:36:59
 * @LastEditTime: 2022-03-22 03:53:16
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


enum RoboState
{
    NAVI_IDLE = 1,              // Idle navigation
    NAVI_RUNNING,               // running navigation
    NAVI_SUCCESS,               // finish navigation
    NAVI_FAIL,                  // fail navigation
    NAVI_CANCEL,                // cancel navigation

    CHIN_FEATURE_START = 10,    // find Charge Pile
    CHIN_FEATURE_SUCCESS,       // find Charge Pile, Success
    CHIN_FEATURE_FAIL,          // find Charge Pile, Fail
    CHIN_INFRARED_START,        // find infrared
    CHIN_INFRARED_SUCCESS,      // find infrared success
    CHIN_INFRARED_FAIL,         // find infrared fail
    CHIN_DOCK_START,            // start auto dock
    CHIN_DOCK_FAIL,             // auto dock fail
    CHIN_DOCK_SUCCESS,          // auto dock success
    
    CHOUT_DOCK_START = 20,      // start leave pile 
    CHOUT_DOCK_FAIL,            // leave pile fail
    CHOUT_DOCK_SUCCESS,          // leave pile success    

    ESTOP_OPEN = 30,            // estop open 
    ESTOP_LOSE
};

enum FsmState{
    ControlBanned = 100,        // Banned control
    ControlAcccept,             // Allow control
    NaviBanned,                 // Banned Navid
    NaviAccept,                 // Allow Navi
    DockBanned,                 // Banned Docking
    DockAccept,                 // Allow Docking
    UnKnowMsg,                  // Msg format error
    UnKnowType                  // Msg Type Error
};


#endif