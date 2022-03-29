/*
 * @Author: your name
 * @Date: 2022-03-28 22:45:58
 * @LastEditTime: 2022-03-29 08:06:32
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/RoboSqlite.cpp
 */

#ifndef __ROBOSQLITE_H_
#define __ROBOSQLITE_H_





#include <ros/ros.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "geometry_msgs/PoseStamped.h"
#include "Common.h"

/**
 * @description: 
 * @param {*}
 * @return {*} return *data ,data为pair参数类型，first代表回调是否触发，即数据库中能否查询到点位置信息
 *                                             second类型为geometry_msgs 代表数据库中的点位信息
 */

int callback(void *data,int args_num,char **argv,char **argc){
    std::pair<bool, geometry_msgs::Pose> * l_ret;
    l_ret = (std::pair<bool, geometry_msgs::Pose> *)data;
    l_ret->first = true;
    std::cout<< "callback" << std::endl;
    for (int i = 0; i < args_num; i++)
    {
        if("PositionX" == argc[i]) l_ret->second.position.x = atof(argv[i]);
        if("PositionY" == argc[i]) l_ret->second.position.y = atof(argv[i]);
        if("PositionZ" == argc[i]) l_ret->second.position.z = atof(argv[i]);

        std::cout << argv[i] << " " << argc[i]<< std::endl;
    }
    
   
   return 0;
}

/**
 * @description:    获取数据库点位信息, 下发导航任务时查询
 * @param {string} l_TarName
 * @return {*} return参数
 */
//
RoboState GetTargetParam(std::string l_TarName, geometry_msgs::Pose& l_pose){   //入参为点位名称
    sqlite3 *db;
    char *errMsg;    
    int rc = sqlite3_open("/home/lanpu/catkin_ws/src/rospolicy/src/Robo.db", &db);
    std::cout << rc << std::endl;
    if(rc){
        ROS_ERROR_STREAM("Searching Target Param Fail");
    }
    ROS_INFO_STREAM("Open DataBase Success");
    std::string sql = "SELECT * FROM TargetList WHERE TargetName = \"" + l_TarName + "\"";
    //std::string sql = "SELECT id FROM TargetList"; 
 
    std::pair<bool, geometry_msgs::Pose> l_param;
    l_param.first = false;
    l_param.second = l_pose;
    std::cout << "1 " << l_param.first << std::endl;
    sqlite3_exec(db,sql.c_str(),callback,(void *)&l_param,&errMsg);
    std::cout << "2 " << l_param.first << std::endl;
    std::cout << "posit x " << l_param.second.position.x << std::endl;
    std::cout << "posit y " << l_param.second.position.y << std::endl;
    std::cout << "posit z " << l_param.second.position.z << std::endl;
    std::cout << "orientation x " << l_param.second.orientation.x << std::endl;
    std::cout << "orientation y " << l_param.second.orientation.y << std::endl;
    std::cout << "orientation z " << l_param.second.orientation.z << std::endl;
    std::cout << "orientation w " << l_param.second.orientation.w << std::endl;

    sqlite3_close(db);
}



/**
 * @description: 
 * @param {*}
 * @return {*}
 */
RoboState InsertTargetParam(std::string l_TarName, geometry_msgs::Pose& l_pose){   //入参为任意点位坐标及朝向


}


#endif