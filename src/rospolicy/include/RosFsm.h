/*
 * @Author: your name
 * @Date: 2022-03-16 20:31:49
 * @LastEditTime: 2022-03-22 02:39:53
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/RosFsm.h
 */
#ifndef __ROSFSM_H_
#define __ROSFSM_H_

#include <functional>
#include <string>
#include <ros/ros.h>
#include <atomic>
#include <std_msgs/String.h>

#include "Common.h"

class NaviFsm
{
private:
    /* data */
    ros::NodeHandle _n;
    ros::Subscriber _sub;
public:
    std::atomic_int NaviState;
    NaviFsm(){
        _sub = _n.subscribe("aaa", 1000, &NaviFsm::CallbackNavi, this);
    }
    ~NaviFsm(){
        
    }
    
    void CallbackNavi(const std_msgs::String::ConstPtr& msg){

        std::cout << msg->data << std::endl;
        if(msg->data == "ok"){
            NaviState = NAVI_RUNNING;
            std::cout << NaviState;
        }
    }
    
};

class ControlFsm
{
private:
    /* data */
    ros::NodeHandle _n;
    ros::Subscriber _sub;
public:
    std::atomic_int ControlState;
    ControlFsm(){
        _sub = _n.subscribe("bbb", 1000, &ControlFsm::CallbackControl, this);
    }
    ~ControlFsm(){
        
    }
    
    void CallbackControl(const std_msgs::String::ConstPtr& msg){

        std::cout << msg->data << std::endl;
        if(msg->data == "ok") {
            ControlState = NAVI_SUCCESS;
            std::cout << ControlState;
        }
    }
};


class DockFsm
{
private:
    /* data */
    ros::NodeHandle _n;
    ros::Subscriber _sub;    /* data */

public:
    std::atomic_int DockState;
    DockFsm(){
        _sub = _n.subscribe("ccc", 1000, &DockFsm::CallbackDock, this);
    }
    ~DockFsm(){
        
    }

    void CallbackDock(const std_msgs::String::ConstPtr& msg){
        std::cout << msg->data << std::endl;
        if(msg->data == "ok"){
            DockState = NAVI_SUCCESS;
            std::cout << DockState;
        }
    }
};

class SensorFsm
{
private:
    /* data */
    ros::NodeHandle _n;
    ros::Subscriber _sub;
public:
    std::atomic_int SensorState;
    SensorFsm(){
        _sub = _n.subscribe("/power", 1000, &SensorFsm::CallbackSensor, this);
    }
    ~SensorFsm();
    
    void CallbackSensor(const std_msgs::String::ConstPtr& msg){

        std::cout << msg->data << std::endl;
        if(msg->data == "ok") {
            SensorState = NAVI_SUCCESS;
            std::cout << SensorState;
        }
    }
};

#endif