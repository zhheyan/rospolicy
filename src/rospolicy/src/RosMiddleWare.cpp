/*
 * @Author: your name
 * @Date: 2022-03-15 19:20:30
 * @LastEditTime: 2022-03-24 20:30:01
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
    
RoboState RosMiddleWare::GetFsmState(FsmState l_AckState){
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
    // 导航任务进行中、
    if(NaviAck == l_AckState){  
        if()
    }
    
    return INTERFACE_OK;
    

}
