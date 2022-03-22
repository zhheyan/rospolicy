/*
 * @Author: lanplustech_hy
 * @Date: 2022-02-28 23:26:45
 * @LastEditTime: 2022-03-22 04:23:03
 * @LastEditors: Please set LastEditors
 * @Description: 通信平台文件，用于协议层注册,注册时会针对不同协议初始化数据缓冲
 * @FilePath: /catkin_ws/src/rospolicy/include/CommunPlatform.h
 */
#ifndef __COMMUNPLATFORM_H_
#define __COMMUNPLATFORM_H_

#include <thread>
#include <stdio.h>
#include <ros/ros.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <geometry_msgs/Twist.h>

#include "Common.h"
#include "Tcpwarpper.h"
#include "RosMessage.h"

class ThreadCommun
{
    pthread_t parseid;
    public:
    int ParseTcpThread(){
        if(pthread_create(&parseid, NULL, parseTcp_thread, (void*)this)!=0)
        {
            return -1;
        }
        return 0;
    }
    private:
        
        static void* parseTcp_thread(void * arg){
            ThreadCommun *ptr = (ThreadCommun *)arg;
            ptr->parseTcp_task();
        }

        virtual void parseTcp_task() = 0;
};

class CommunPlatform:ThreadCommun
{
private:
    /* data */
    ros::NodeHandle nh;
    ros::Publisher turtle_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    
public:
    TcpWarpper *m_tcpwarpper;
    //MqttWarpper * m_mqttwarpper;
    
    CommunPlatform();
    ~CommunPlatform();
    bool PublishTcpMsg(std::string);
    std::string PublishTcpMsg(FsmState _fsmstate);
    bool PublishMqttMsg(std::pair<std::string, std::string>);

private:
    bool RegisterProtol(); //
    bool UnRegisterProtol();
    bool InitProtol();
    void parseTcp_task();

};




#endif