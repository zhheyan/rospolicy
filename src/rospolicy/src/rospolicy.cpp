/*
 * @Author: your name
 * @Date: 2022-02-28 23:34:10
 * @LastEditTime: 2022-03-29 01:41:29
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/src/rospolicy.cpp
 */

#include <ros/ros.h>

#include "RoboSqlite.h"
#include "CommunPlatform.h"
#include "RosMiddleWare.h"
#include "RosFsm.h"
//

int main(int argc, char **argv){

    //init communication platform

    ros::init(argc, argv, "lppolicy");

    ros::NodeHandle nh;
    std::string l_TarName = "A";
    geometry_msgs::Pose l_pose;
    
    GetTargetParam(l_TarName, l_pose);

    CommunPlatform RosCommun; //init communplatformdnn
    //aaa.PublishTcpMsg("@@@@@@@@@@2");
    //aaa.publishTcp("AAAAAAAAAAaa");

    ros::spin();
    return 0;
}
