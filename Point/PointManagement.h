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

    ////输出方法
    //输出到文件，需要输入文件名
    void OutputPointsToFile();
    //输出到屏幕
    void OutputPointsToScreen();

    ////更新数据方法
    //再次随机生成n个
    void AutoUpdatePoints();
    //自己输入n个
    void InputUpdatePoints();

private:
    //////比较算法
    ////分治法方法
    //主分治法
    pair<Point, Point> divideAndConquerPoints(const vector<Point>& points)const;
    //中心区域查找
    pair<Point, Point> divideAndConquerStripPoints(const vector<Point>& points)const;

    ////自己想出来的算法，O(n)时间复杂度！
    pair<Point, Point> narrowingDownPoints(const vector<Point>& points)const;

    ////纯暴力算法
    pair<Point, Point> bruteForceClosestPairPoints(const vector<Point>& points)const;

    //////小工具
    //输入n
    int inputN();
    //比较点是否存在
    bool isPointExistIn(const Point& p,const vector<Point>& ps)const;
};

#endif //NEAREST_SHAPE_POINTMANAGEMENT_H