//
// Created by AlexGrandbell on 2023.12.21.
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
    //枚举算法
    void BruteForcePoint();

    ////输出方法
    //输出到文件
    void OutputPointsToFile();
    //输出到屏幕
    void OutputPointsToScreen();

    ////更新数据方法
    //再次随机生成
    void AutoUpdatePoints();
    //自己输入
    void InputUpdatePoints();

    //中心区域查找
    pair<Point, Point> divideClosestPairStripPoints(const vector<Point>& tempPoints)const;
private:
    //////比较算法
    ////分治法方法
    //主分治法
    pair<Point, Point> divideClosestPairPoints(const vector<Point>& tempPoints)const;
    ////自己想出来的算法
    pair<Point, Point> narrowingDownClosestPairPoints(const vector<Point>& tempPoints)const;
    ////纯枚举算法
    pair<Point, Point> bruteForceClosestPairPoints(const vector<Point>& tempPoints)const;

    //////小工具
    //输入n
    int inputPointN();
    //比较点是否存在
    bool isPointExistIn(const Point& newTempPoint,const vector<Point>& tempPoints)const;
};

#endif //NEAREST_SHAPE_POINTMANAGEMENT_H