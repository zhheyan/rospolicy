/*
 * @Author: your name
 * @Date: 2022-03-21 02:57:48
 * @LastEditTime: 2022-03-27 22:55:05
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/src/Message.cpp
 */


#include "Message.h"

std::string TcpControl(RoboState stat){
    Json::Value _TcpControlMsg;
    Json::FastWriter _writer;
    _TcpControlMsg["type"] = "response";
    _TcpControlMsg["command"] = "/api/joy_control";
    _TcpControlMsg["uuid"] = "";
    _TcpControlMsg[""] = "";
    switch (stat)
    {
        case INTERFACE_OK:
            _TcpControlMsg["status"] = "OK";
            _TcpControlMsg["error_msg"] = "";
            break;
        case ESTOP_OPEN:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "Estop Open";
            break;
        case NAVI_RUNNING:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "Navi Plan Is Running";
            break;
        case CHIN_FEATURE_START:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "DockIn Start Searching Feature";
            break;
        case CHIN_INFRARED_START:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "DockIn Start Searching Infrared";
            break;
        case CHIN_DOCK_START:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "DockIn Start Auto Dock To Charging Pile";
            break;
        case CHOUT_DOCK_START:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "DockOut Start";
            break;
        case UNKNOWMSG:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "recv unknow msg";
            break;
        case UNKNOWTYPE:
            _TcpControlMsg["status"] = "fail";
            _TcpControlMsg["error_msg"] = "recv unknow type";
            break;

        default:
            break;
    }
    
    std::string data = _writer.write(_TcpControlMsg);
    return data;
}

std::string TcpDock(RoboState stat){
    Json::Value _TcpDockMsg;
    Json::FastWriter _writer;
    _TcpDockMsg["type"] = "response";
    _TcpDockMsg["command"] = "/api/dock_control";
    _TcpDockMsg["uuid"] = "";
    _TcpDockMsg[""] = "";
    switch (stat)
    {
        case INTERFACE_OK:
            _TcpDockMsg["status"] = "OK";
            _TcpDockMsg["error_msg"] = "";
            break;
        case ESTOP_OPEN:
            _TcpDockMsg["status"] = "fail";
            _TcpDockMsg["error_msg"] = "Estop Open";
            break;
        case NAVI_RUNNING:
            _TcpDockMsg["status"] = "fail";
            _TcpDockMsg["error_msg"] = "Navi Plan Is Running";
            break;
        case CHIN_FEATURE_START:
            _TcpDockMsg["status"] = "fail";
            _TcpDockMsg["error_msg"] = "DockIn Start Searching Feature";
            break;
        case CHIN_INFRARED_START:
            _TcpDockMsg["status"] = "fail";
            _TcpDockMsg["error_msg"] = "DockIn Start Searching Infrared";
            break;
        case CHIN_DOCK_START:
            _TcpDockMsg["status"] = "fail";
            _TcpDockMsg["error_msg"] = "DockIn Start Auto Dock To Charging Pile";
            break;
        case CHOUT_DOCK_START:
            _TcpDockMsg["status"] = "fail";
            _TcpDockMsg["error_msg"] = "DockOut Start";
            break;

        default:
            break;
    }
    
    std::string data = _writer.write(_TcpDockMsg);
    return data;
}

std::string TcpNavi(RoboState stat){
    Json::Value _TcpNaviMsg;
    Json::FastWriter _writer;
    
}

std::string TcpError(RoboState stat){

    Json::Value _TcpErrorMsg;
    Json::FastWriter _writer;
    _TcpErrorMsg["type"] = "response";
    _TcpErrorMsg["command"] = "/api/dock_control";
    _TcpErrorMsg["uuid"] = "";
    _TcpErrorMsg[""] = "";
    switch (stat)
    {
        case INTERFACE_OK:
            _TcpErrorMsg["status"] = "OK";
            _TcpErrorMsg["error_msg"] = "";
            break;

        default:
            break;
    }
    
    std::string data = _writer.write(_TcpErrorMsg);
    return data;
}