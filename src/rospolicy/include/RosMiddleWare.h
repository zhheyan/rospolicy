/*
 * @Author: your name
 * @Date: 2022-03-15 19:20:41
 * @LastEditTime: 2022-03-28 22:45:28
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
    ros::Publisher Control_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    /* data */
public:
    RosMiddleWare();
    ~RosMiddleWare();
    RoboState GetFsmState(RoboState l_AckState);
    std::string GetRoboState();
    bool PublishControlCmd(std::string, std::string);
    
    bool PublishNaviCmd(std::string l_TargetName); //数据库接口发布导航点
    bool PublishNaviCmd(std::string l_x, std::string l_y, std::string l_angle); //默认接口发布导航点
    
    
};




#endif