/*
 * @Author: your name
 * @Date: 2022-03-01 17:36:29
 * @LastEditTime: 2022-03-22 03:47:15
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/src/Tcpwarpper.cpp
 */
#include "Tcpwarpper.h"

#define MYPORT  31001
#define BUFFER_SIZE 1024

TcpWarpper::TcpWarpper()
{
    CreateSock(31001);
    ListenThread();
    SendThread();
    ROS_INFO_STREAM("Initing TcpProtol");
}

TcpWarpper::~TcpWarpper()
{
    ROS_INFO_STREAM("End TcpProtol");
}

int TcpWarpper::CreateSock(int port){
    _port = port;
    _addrLen = sizeof(struct sockaddr);
    /*
    协议域 : AF_INET(IPV4) AF_INET6(IPV6) AF_LOCAL AF_ROUTE 等等
    socket类型 : SOCK_STREAM(TCP) SOCK_DGRAM(UDP) 等等
    0 : 表示协议域和socket类型选择默认的协议, 通常是0
    */
   
    _serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if(_serverfd < 0){
        ROS_ERROR_STREAM("Inin Tcp fail, Create Sock Fail");
        return -1;
    }
    /*
    应用协议 : SOL_SOCKET(套接字) IPPROTO_TCP IPPROTO_IP...
    设置项 : SO_REUSEADDR(是否可以重用bind的地址)...
    opt : 一些设置项指的是开关...
    */
    int opt = 1;
    ret = setsockopt(_serverfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));

    if(ret < 0){
        ROS_ERROR_STREAM("Inin Tcp fail, Create Sock Fail");
        close(_serverfd);
        return -1;
    }

    memset(&_serv_addr, 0, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _serv_addr.sin_port = htons(_port);
    
    ret = bind(_serverfd,(struct sockaddr*)&_serv_addr, sizeof(_serv_addr));
    if(ret < 0){
        ROS_ERROR_STREAM("Init Tcp Fail, Bind Fail");
        close(_serverfd);
        return -1;
    }

    ret = listen(_serverfd, 12);
    if(ret < 0){
        ROS_ERROR_STREAM("Init Tcp Fail, Listen Fail");
        close(_serverfd);
        return -1;
    }
    TcpProtolInitFlag = true;
    ROS_INFO_STREAM("Waiting For Connected");
    
}
void TcpWarpper::accept_task(){
    while (ros::ok())
    {
        pthread_t id;
        memset(&_client_addr, 0x0, sizeof(struct sockaddr_in));
        ROS_INFO_STREAM("Waiting For Connnecting");
        _client_fds = accept(_serverfd, (struct sockaddr *)(&_client_addr), (socklen_t *)&_addrLen);
        clientset.insert(_client_fds);
        RecvThread();
    }

}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void TcpWarpper::recv_task(){
    int _tmpfd = _client_fds;
    char buf[MAX_BUF];
    std::string l_RecvTcpMsg;
    while (ros::ok())
    {
        memset(&buf, 0x0, sizeof(buf));
        ret = recv(_tmpfd, buf, sizeof(buf), 0);
        if(ret > 0){
            l_RecvTcpMsg = buf;
            std::cout << "Recv Tcp Msg" << l_RecvTcpMsg<<std::endl;
            _TcpRecvBuf.push(l_RecvTcpMsg);
        }
        else if(ret == 0){
            /* 无可用数据 或者 对等方已经按序结束 */
            ROS_ERROR_STREAM("Client Close");
            clientset.erase(_tmpfd);
            close(_tmpfd);
            break;
        }
        else if(ret < 0){
            ROS_ERROR_STREAM("Client ERROR");
            clientset.erase(_tmpfd);
            close(_tmpfd);
            break;
        }
    }
}
void TcpWarpper::send_task(){
    
    std::shared_ptr<std::string> l_SendTcpMsg;
    char l_tmpSendTcpMsg[1024];
    char *l_tmp = l_tmpSendTcpMsg;
    while (ros::ok())
    {
        l_SendTcpMsg = _TcpSendBuf.WaitPop();

        if(!clientset.empty()){
            for(it = clientset.begin(); it!=clientset.end(); ++it){
                memcpy(l_tmpSendTcpMsg, (*l_SendTcpMsg).c_str(), strlen((*l_SendTcpMsg).c_str()));
                // l_tmp = const_cast<char *>((*l_SendTcpMsg).c_str());
                ret = send(*it, l_tmpSendTcpMsg, strlen(l_tmpSendTcpMsg), 0);
            }
        }
        else{
            ROS_INFO_STREAM("no slient drop msg");
        }
    }

}
bool TcpWarpper::CloseSock(){

}
