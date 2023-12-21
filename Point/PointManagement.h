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
    clock_t startTime,endTime;

public:
    ////构造函数
    //默认构造函数
    PointManagement();

    ////展示方法
    //分治法查找最近点对
    void DividePoint();
    //自己的算法查找最近点对
    void MyPointAlgorithm();
    //暴力算法
    void BruteForcePoint();

    ////更新数据方法
    //再次随机生成n个
    void AutoUpdatePoints(int);
    //自己输入n个
    void InputUpdatePoints(int);

private:
    ////分治法方法
    //主分治法
    pair<Point, Point> divideAndConquerPoints(const vector<Point>& points);
    //中心区域查找
    pair<Point, Point> divideAndConquerStripPoints(const vector<Point>& points);

    ////自己想出来的算法，O(n)时间复杂度！
    pair<Point, Point> narrowingDownPoints(const vector<Point>& points);

    ////纯暴力算法
    pair<Point, Point> bruteForceClosestPairPoints(const vector<Point>& points);
};

#endif //NEAREST_SHAPE_POINTMANAGEMENT_H