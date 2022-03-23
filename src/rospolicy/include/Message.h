/*
 * @Author: your name
 * @Date: 2022-03-21 02:57:40
 * @LastEditTime: 2022-03-23 03:37:39
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/Message.h
 */


#ifndef __MESSAGE_H_
#define __MESSAGE_H_


#include <jsoncpp/json/json.h>
#include "RosFsm.h"


class TcpMessage
{
private:
    Json::Value _TcpNaviMsg;
    Json::Value _TcpControlMsg;
    Json::Value _TcpDockMsg;
    
    Json::FastWriter _writer;
    /* data */
public:
    std::string TcpNavi();
    std::string TcpControl();
    std::string TcpDock();
};


#endif