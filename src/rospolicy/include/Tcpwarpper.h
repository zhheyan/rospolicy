/*
 * @Author: lanplustech_hy
 * @Date: 2022-03-01 17:36:38
 * @LastEditTime: 2022-03-23 04:07:22
 * @LastEditors: Please set LastEditors
 * @Description: 通信层tcp协议
 * @FilePath: /catkin_ws/src/rospolicy/include/TcpWarpper.h
 */
#ifndef __TCPWARPPER_H_
#define __TCPWARPPER_H_

#include <iostream>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <ros/ros.h>
#include <pthread.h>
#include <unordered_set>
#include <chrono>
#include <thread>
#include <chrono>

#include "Common.h"
#include "Message.h"

#define MAXCLiNUM 12
#define MAX_BUF 4096



class Thread
{
    public:
    int clientfd;
    int ListenThread(){
        if(pthread_create(&acceptid, NULL, accept_thread, (void*)this)!=0)
        {
            return -1;
        }
        return 0;
    }
    int RecvThread(){
        pthread_t recvpid;
        if(pthread_create(&recvpid, NULL, recv_thread, (void*)this) !=0)
        {
            return -1;
        }

        return 0;
    }
    int SendThread(){
        pthread_t recvpid;
        if(pthread_create(&recvpid, NULL, send_thread, (void*)this) !=0)
        {
            return -1;
        }

        return 0;
    }
    private:
        
        pthread_t acceptid;

        static void* accept_thread(void * arg){
            Thread *ptr = (Thread *)arg;
            ptr->accept_task();
        }
        static void* recv_thread(void * arg){
            Thread *ptr = (Thread *)arg;
            ptr->recv_task();
        }
        static void* send_thread(void * arg){
            Thread *ptr = (Thread *)arg;
            ptr->send_task();
        }

        virtual void accept_task() = 0;
        virtual void recv_task() = 0;
        virtual void send_task() = 0;
};

class TcpWarpper:public Thread
{
private:
    std::atomic<bool> TcpProtolInitFlag;
    /* data */
    int _serverfd;                // 服务器文件描述符
    struct sockaddr_in _serv_addr;   

    int _client_fds;              // 客户端文件描述符集合
    struct sockaddr_in _client_addr;

    std::unordered_set<int> clientset; 
    std::unordered_set<int>::iterator it;
               //接受缓冲区
    int _port, _maxfd, _i, _acceptfd;
    int _addrLen;
    int ret;

public:
    friend class CommunPlatform;
    ThreadSafe_Queue <std::string> _TcpRecvBuf;
    ThreadSafe_Queue <std::string> _TcpSendBuf;

    TcpWarpper();
    ~TcpWarpper();
    void accept_task();
    void recv_task(); 
    void send_task();
    int CreateSock(int);
    int StartListen();
    bool CloseSock();
};

#endif