/*
 * @Author: your name
 * @Date: 2022-03-15 19:20:41
 * @LastEditTime: 2022-03-30 04:46:16
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/RosMiddleWare.h
 */


#ifndef __ROSMIDDLEWARE_H_
#define __ROSMIDDLEWARE_H_

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include "RosFsm.h"

class RosMiddleWare: public NaviFsm, public ControlFsm, public DockFsm, public SensorFsm, public EStopFsm
{
private:
    ros::NodeHandle nh;
    // 速度发布句柄
    ros::Publisher Control_cmd_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    // 导航任务发布句柄
    ros::Publisher Navi_cmd_pub = nh.advertise<geometry_msgs::PoseStamped>("//move_base_simple/goal", 1);
    /* data */
public:
    RosMiddleWare();
    ~RosMiddleWare();
    RoboState GetFsmState(RoboState l_AckState);
    std::string GetRoboState();
    bool PublishControlCmd(std::string, std::string);
    
    bool PublishNaviCmd(std::string l_TargetName); //数据库接口发布导航点
    bool PublishNaviCmd(std::string l_x, std::string l_y, std::string l_angle); //默认接口发布导航点
    bool CancelNaviCmd();

    bool PublishDockCmd(std::string l_ChargeName); //回充任务下发
    bool CancelDockCmd(std::string l_ChargeName); //回充任务取消
    
    bool PublishEstopCmd(bool l_EstopStat);     //急停任务下发 入参true打开 false关闭
    
    
    
};




#endif