//
// Created by 沈嘉瑞 on 2023.12.21.
//

#ifndef NEAREST_SHAPE_POINTMANAGEMENT_H
#define NEAREST_SHAPE_POINTMANAGEMENT_H

#include "Point.h"

class PointManagement {
private:
    //点集元素
    vector<Point> points;
    //运行计时工具
    clock_t start_time,end_time;
    double time_used;
public:
    ////构造函数
    //默认构造函数
    PointManagement();
    //自动生成n个点的构造函数，同时保存文件
    PointManagement(int);

    ////方法
    //分治法查找最近点对

};


#endif //NEAREST_SHAPE_POINTMANAGEMENT_H
