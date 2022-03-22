/*
 * @Author: your name
 * @Date: 2022-03-15 19:20:41
 * @LastEditTime: 2022-03-22 00:00:45
 * @LastEditors: Please set LastEditors
 * @Description: 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * @FilePath: /catkin_ws/src/rospolicy/include/RosMiddleWare.h
 */


#ifndef __ROSMIDDLEWARE_H_
#define __ROSMIDDLEWARE_H_

#include <ros/ros.h>
#include "RosFsm.h"

class RosMiddleWare: public NaviFsm, public ControlFsm, public DockFsm
{
private:
    /* data */
public:

    RosMiddleWare();
    ~RosMiddleWare();
    void FsmRun(int);
};




#endif