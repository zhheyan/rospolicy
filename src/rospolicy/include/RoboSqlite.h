/*
 * @Author: your name
 * @Date: 2022-03-28 22:45:58
 * @LastEditTime: 2022-03-29 01:40:35
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/RoboSqlite.cpp
 */

#ifndef __ROBOSQLITE_H_
#define __ROBOSQLITE_H_




#include <sqlite3.h>
#include <ros/ros.h>
#include "geometry_msgs/PoseStamped.h"
#include "Common.h"


/**
 * @description:    获取数据库点位信息, 下发导航任务时查询
 * @param {string} l_TarName
 * @return {*}
 */
//
RoboState GetTargetParam(std::string l_TarName, geometry_msgs::Pose& l_pose){   //入参为点位名称
    sqlite3 *db;
    int rc = sqlite3_open("./Robo.db", &db);
    if(rc != SQLITE_OK){
        ROS_ERROR_STREAM("Searching Target Param Fail");
    }
    
}


/**
 * @description: 
 * @param {*}
 * @return {*}
 */
RoboState InsertTargetParam(std::string l_TarName, geometry_msgs::Pose& l_pose){   //入参为任意点位坐标及朝向


}


#endif