/*
 * @Author: your name
 * @Date: 2022-03-15 19:20:30
 * @LastEditTime: 2022-03-28 00:55:13
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/src/RosMiddleWare.cpp
 */
#include "RosMiddleWare.h"


RosMiddleWare::RosMiddleWare(/* args */)
{
    std::cout << "a";
}

RosMiddleWare::~RosMiddleWare()
{
    std::cout << "b";
}

/**
 * @description:获取机器人各节点状态，并反馈上层 
 * @param {FsmState} l_AckState
 * NaviState
 * ControlState
 * DockState
 * SensorState
 * @return {*}
 */
    
RoboState RosMiddleWare::GetFsmState(RoboState l_AckState){
    // 仅当导航空闲、急停关闭、回充空闲情况下，才可执行手动控制
    if(ControlAck == l_AckState){   // 控制请求
        if(ESTOP_OPEN == EStopState){ // 急停打开状态 返回
            return EStopState;
        }
        else if(NAVI_RUNNING == NaviState){ // 导航中状态 返回 
            return NaviState;
        }
        // 任何回充阶段开始后都禁止手动控制
        else if((CHIN_FEATURE_START== DockState)|(CHIN_INFRARED_START == DockState)|(CHIN_DOCK_START == DockState)|(CHOUT_DOCK_START == DockState)){
            return DockState;
        }
        else return INTERFACE_OK;
    }
    // 接收到导航请求
    if(NaviAck == l_AckState){  
        if(ESTOP_OPEN == EStopState){ // 急停打开状态 返回 禁止导航任务
            return EStopState;
        }
        else if(NAVI_RUNNING == NaviState){ // 导航中状态 返回 禁止导航任务 
            return NaviState;
        }
        // 任何回充阶段开始后都禁止下发导航任务
        else if((CHIN_FEATURE_START== DockState)|(CHIN_INFRARED_START == DockState)|(CHIN_DOCK_START == DockState)|(CHOUT_DOCK_START == DockState)){
            return DockState;
        }
        else return INTERFACE_OK;
    }
    // 接收到回充任务
    if(DockAck == l_AckState){  
        if(ESTOP_OPEN == EStopState){ // 急停打开状态 返回 禁止回充任务
            return EStopState;
        }
        else if(NAVI_RUNNING == NaviState){ // 导航中状态 返回 禁止回充任务 
            return NaviState;
        }
        // 任何回充阶段开始后都禁止继续下发回充任务
        else if((CHIN_FEATURE_START== DockState)|(CHIN_INFRARED_START == DockState)|(CHIN_DOCK_START == DockState)|(CHOUT_DOCK_START == DockState)){
            return DockState;
        }
        else return INTERFACE_OK;
    }
    
    return INTERFACE_OK;
    

}
bool RosMiddleWare::PublishControlCmd(std::string l_anglev, std::string l_linev){
    
    geometry_msgs::Twist vel_msgs;
    vel_msgs.linear.x = stod(l_linev);
    vel_msgs.angular.z = stod(l_anglev);
    Control_vel_pub.publish(vel_msgs);
}

bool RosMiddleWare::PublishNaviCmd(std::string l_TargetName){   //按导航点名称发布导航任务
    
}

bool RosMiddleWare::PublishNaviCmd(std::string l_x, std::string l_y, std::string l_angle){

}