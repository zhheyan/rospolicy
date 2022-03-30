/*
 * @Author: your name
 * @Date: 2022-03-28 22:45:58
 * @LastEditTime: 2022-03-30 03:10:06
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

int getcallback(void *data,int args_num,char **argv,char **argc){
    std::pair<bool, geometry_msgs::Pose> * l_ret;
    l_ret = (std::pair<bool, geometry_msgs::Pose> *)data;
    l_ret->first = true;
    std::cout<< "callback" << std::endl;
    for (int i = 0; i < args_num; i++)
    {
        std::string l_temp = argc[i];
        if("PositionX" == l_temp) l_ret->second.position.x = atof(argv[i]);
        if("PositionY" == l_temp) l_ret->second.position.y = atof(argv[i]);
        if("PositionZ" == l_temp) l_ret->second.position.z = atof(argv[i]);
        if("OrientationX" == l_temp) l_ret->second.orientation.x = atof(argv[i]);
        if("OrientationY" == l_temp) l_ret->second.orientation.y = atof(argv[i]);
        if("OrientationZ" == l_temp) l_ret->second.orientation.z = atof(argv[i]);
        if("OrientationW" == l_temp) l_ret->second.orientation.w = atof(argv[i]);

        std::cout << argv[i] << " " << argc[i]<< std::endl;
    }
    
   return 0;
}

/**
 * @description:    获取数据库点位信息, 下发导航点任务时查询
 * @param {string} l_TarName
 * @return {*} return参数
 */
//
RoboState GetTargetParam(std::string &l_TarName, geometry_msgs::Pose& l_pose){   //入参为点位名称
    sqlite3 *db;
    char *errMsg = nullptr;    
    int rc = sqlite3_open("/home/lanpu/catkin_ws/src/rospolicy/src/Robo.db", &db);
    if(rc){
        ROS_ERROR_STREAM("Open DataBase Fail");
    }
    ROS_INFO_STREAM("Open DataBase Success");
    std::string sql = "SELECT * FROM TargetList WHERE TargetName = \"" + l_TarName + "\"";

    std::pair<bool, geometry_msgs::Pose> l_param;
    
    geometry_msgs::Pose l_temp;
    l_param.first = false;
    l_param.second = l_temp;
    
    std::cout << "enter " << l_param.first << std::endl;
    sqlite3_exec(db,sql.c_str(),getcallback,(void *)&l_param,&errMsg);
    std::cout << "ending " << l_param.first << std::endl;
    std::cout << "posit x " << l_param.second.position.x << std::endl;
    std::cout << "posit y " << l_param.second.position.y << std::endl;
    std::cout << "posit z " << l_param.second.position.z << std::endl;
    std::cout << "orientation x " << l_param.second.orientation.x << std::endl;
    std::cout << "orientation y " << l_param.second.orientation.y << std::endl;
    std::cout << "orientation z " << l_param.second.orientation.z << std::endl;
    std::cout << "orientation w " << l_param.second.orientation.w << std::endl;
    if(!errMsg){ //sq语句执行正常
        if(l_param.first){
            ROS_INFO_STREAM("Get Target Param success");
            l_pose = l_param.second;
            sqlite3_close(db);
            return SEARCHOK;    // 此返回值代表已获取到数据库中导航点信息，并保存在入参geometry_msgs中
        }
        else
        {
            ROS_INFO_STREAM("Known TargetName");
            sqlite3_close(db);
            return UNKNOWTARGET;    // 此返回值代表未获取到数据库中导航点信息，入参无实际意义   
        }
    }
    else{   //sq语句执行异常
        ROS_ERROR_STREAM("GetTargetParam SQL ERROR");
        return SQLERROR;
    }
    
    
}


int insertcallback(void *data,int args_num,char **argv,char **argc){
    bool* l_ret;
    l_ret = (bool *)data;
    *l_ret = true;
    std::cout<< "callback" << std::endl;
    return 0;
}

/**
 * @description: 添加导航点接口 用户调用标定点位时调用此接口  标定点位分为当前位置标定和指定位置标定
 *                                                     当前位置标定时，pose数据由ros中间件提供
 *                                                     制定位置标定时，pose由用户接口调用时传入
 * @param {*}
 * @return {*}
 */
RoboState InsertTargetParam(std::string l_TarName, geometry_msgs::Pose& l_pose){   //入参为任意点位坐标及朝向
    sqlite3 *db;
    char *errMsg = nullptr;
    int rc = sqlite3_open("/home/lanpu/catkin_ws/src/rospolicy/src/Robo.db", &db);
    if(rc){
        ROS_ERROR_STREAM("Open DataBase Fail");
    }
    ROS_INFO_STREAM("Open DataBase Success");
    //查询点位信息，不存在则调用insert，存在则调用update
    std::string sql = "SELECT * FROM TargetList WHERE TargetName = \"" + l_TarName + "\"";

    bool l_ret = false;
    sqlite3_exec(db,sql.c_str(),insertcallback,(void *)&l_ret,&errMsg);

    if(l_ret){  //查询到数据库中点位参数
        ROS_INFO_STREAM("Update Target Param");
        std::string sql = "UPDATE TargetList SET PositionX = " + std::to_string(l_pose.position.x) + "," + \
                                               " PositionY = " + std::to_string(l_pose.position.y) + "," + \
                                               " PositionZ = " + std::to_string(l_pose.position.z) + "," + \
                                               " OrientationX = " + std::to_string(l_pose.orientation.x) + "," + \
                                               " OrientationY = " + std::to_string(l_pose.orientation.y) + "," + \
                                               " OrientationZ = " + std::to_string(l_pose.orientation.z) + "," + \
                                               " OrientationW = " + std::to_string(l_pose.orientation.w) + \
                                               " WHERE TargetName = '" +l_TarName + "'";
        std::cout << sql << std::endl;
        sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);


        if(!errMsg){ //sq语句执行正常
            return UPDATEOK;    // 此返回值代表已获取到数据库中导航点信息，并保存在入参geometry_msgs中
        }
        else{   //sq语句执行异常
            ROS_ERROR_STREAM("InsertTargetParam SQL ERROR");
            return SQLERROR;
        }
    }
    else{       //数据库中不存在点位参数
        ROS_INFO_STREAM("Insert Target Param");
        std::string sql = "INSERT INTO TargetList VALUES (\"" + l_TarName + "\"," + \
                                                    std::to_string(l_pose.position.x) + "," +\
                                                    std::to_string(l_pose.position.y) + "," +\
                                                    std::to_string(l_pose.position.z) + "," +\
                                                    std::to_string(l_pose.orientation.x) + "," +\
                                                    std::to_string(l_pose.orientation.y) + "," +\
                                                    std::to_string(l_pose.orientation.z) + "," +\
                                                    std::to_string(l_pose.orientation.w) + ")";

        std::cout << sql << std::endl;
        sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);
        sqlite3_close(db);
        if(!errMsg){ //sq语句执行正常
            return INSERTOK;    
        }
        else{   //sq语句执行异常
            ROS_ERROR_STREAM("InsertTargetParam SQL ERROR");
            return SQLERROR;
        }
    }
}

RoboState DeleteTargetParam(std::string l_TarName){   //入参为任意点位id
    sqlite3 *db;
    char *errMsg = nullptr;    
    int rc = sqlite3_open("/home/lanpu/catkin_ws/src/rospolicy/src/Robo.db", &db);
    if(rc){
        ROS_ERROR_STREAM("Searching Target Param Fail");
    }
    ROS_INFO_STREAM("Open DataBase Success");
    std::string sql = "DELETE FROM TargetList WHERE TargetName = \"" + l_TarName + "\"";
    std::cout << sql << std::endl;
    sqlite3_exec(db, sql.c_str(), NULL, NULL, &errMsg);
    sqlite3_close(db);

    if(!errMsg){ //sq语句执行正常
        return INSERTOK;    
    }
    else{   //sq语句执行异常
        ROS_ERROR_STREAM("DeleteTargetParam SQL ERROR");
        return SQLERROR;
    }

}

#endif