/*
 * @Author: your name
 * @Date: 2022-03-21 02:57:40
 * @LastEditTime: 2022-03-27 19:58:34
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/Message.h
 */


#ifndef __MESSAGE_H_
#define __MESSAGE_H_


#include <jsoncpp/json/json.h>
#include "RosFsm.h"

std::string TcpNavi(RoboState stat);
std::string TcpControl(RoboState stat);
std::string TcpDock(RoboState stat);
std::string TcpError(RoboState stat);



#endif