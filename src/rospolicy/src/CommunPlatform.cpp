/*
 * @Author: lanplustech_hy 
 * @Date: 2022-03-08 00:50:52 
 * @Last Modified by:   lanplustech_hy 
 * @Last Modified time: 2022-03-08 00:50:52 
 */
#include "Tcpwarpper.h"
#include "CommunPlatform.h"


CommunPlatform::CommunPlatform(){
    ROS_INFO_STREAM("Init Communcation OK");
    InitProtol();
    ParseTcpThread();
}


CommunPlatform::~CommunPlatform(){
    ROS_INFO_STREAM("End Communcation OK");
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    v.clear();
    int pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while ((-1 != pos2)|(pos2 < s.size()))
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

bool CommunPlatform::InitProtol(){
    m_tcpwarpper = new TcpWarpper();
    if(m_tcpwarpper->TcpProtolInitFlag){
        ROS_INFO_STREAM("InitTcpProtol Success");
        return true;
    }
    return false;
    
}
bool CommunPlatform::PublishTcpMsg(std::string msg){
    m_tcpwarpper->_TcpSendBuf.push(msg);
    return true;
}

bool CommunPlatform::PublishMqttMsg(std::pair<std::string, std::string>){
    return true;
}

void CommunPlatform::parseTcp_task(){
    std::shared_ptr<std::string> l_TcpRecvmsg;
    std::vector<std::string> l_Msgvector;
    int l_ret;
    ros::NodeHandle nh;
    ros::Publisher turtle_vel_pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    while (true)
    {

        std::cout << "CommunPlatform" << std::endl;
        l_TcpRecvmsg = m_tcpwarpper->_TcpRecvBuf.WaitPop();
        std::cout << "CommunPlatform  " <<*l_TcpRecvmsg << std::endl;


        l_ret = (*l_TcpRecvmsg).find("/api"); //check tcp msg
        if(0 == l_ret){  //
            SplitString(*l_TcpRecvmsg, l_Msgvector, "/");
            
            if("api" == l_Msgvector[1]){
                if("joy_control" == l_Msgvector[2]){
                    std::string l_anglev, l_linev;
                    if("angular_velocity"==l_Msgvector[3].substr(0, l_Msgvector[3].find("="))){
                        l_anglev = l_Msgvector[3].substr(l_Msgvector[3].find("=")+1, l_Msgvector[3].size());
                        l_linev = l_Msgvector[4].substr(l_Msgvector[4].find("=")+1, l_Msgvector[4].size());
                        ROS_INFO_STREAM(" << td::endl;");
                        std::cout << l_anglev << std::endl;
                        std::cout << l_linev << std::endl;


                        geometry_msgs::Twist vel_msgs;
                        vel_msgs.linear.x = stod(l_linev);
                        vel_msgs.angular.z = stod(l_anglev);
                        turtle_vel_pub.publish(vel_msgs);
                    }
                }
                
            }
            
        }
        if(l_ret < 0 | l_ret > 1024){
            PublishTcpMsg("ERROR");
            continue;
        }
    }
    
    
}