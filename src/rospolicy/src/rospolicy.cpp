/*
 * @Author: your name
 * @Date: 2022-02-28 23:34:10
 * @LastEditTime: 2022-03-30 03:10:35
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

    
#if 0 //数据库测试代码 查询导航点A的相关信息
    std::string l_TarName = "A";
    geometry_msgs::Pose l_pose;

    std::cout << "11111 " << GetTargetParam(l_TarName, l_pose) << std::endl;        
    std::cout << "##### "  << l_TarName << std::endl;
    std::cout << "posit x " << l_pose.position.x << std::endl;
    std::cout << "posit y " << l_pose.position.y << std::endl;
    std::cout << "posit z " << l_pose.position.z << std::endl;
    std::cout << "posit x " << l_pose.orientation.x << std::endl;
    std::cout << "posit y " << l_pose.orientation.y << std::endl;
    std::cout << "posit z " << l_pose.orientation.z << std::endl;
    std::cout << "posit z " << l_pose.orientation.w << std::endl;

#endif

#if 0
    std::string l_TarName = "ATT";
    geometry_msgs::Pose l_pose;
    l_pose.position.x = 1.7;
    l_pose.position.y = 1.000008;
    l_pose.position.z = 1.9;
    l_pose.orientation.x = 1.1;
    l_pose.orientation.y = 1.2;
    l_pose.orientation.z = 1.3;
    l_pose.orientation.w = 1;
    std::cout << InsertTargetParam(l_TarName, l_pose) << std::endl;
    
#endif

#if 0 //删除导航点信息
    DeleteTargetParam("ATT");
#endif
    //CommunPlatform RosCommun; //init communplatformdnn


    
    ros::spin();
    return 0;
}
