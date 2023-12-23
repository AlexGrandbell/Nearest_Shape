//
// Created by 沈嘉瑞 on 2023.12.21.
//

#ifndef NEAREST_SHAPE_LINESEGEMENTMANAGEMENT_H
#define NEAREST_SHAPE_LINESEGEMENTMANAGEMENT_H

#include "LineSegment.h"

class LineSegementManagement {
private:
    //线段集元素
    vector<LineSegment> lineSegments;
    //运行计时工具
    clock_t startTime,endTime;

public:
    ////构造函数
    //默认构造函数
    LineSegementManagement();

    ////展示方法
    //自己的算法查找最近线段对
    void MyLineSegmentAlgorithm();
    //枚举算法
    void BruteForceLineSegment();

    ////输出方法
    //输出到文件
    void OutputLineSegmentsToFile();
    //输出到屏幕
    void OutputLineSegmentsToScreen();

    ////更新数据方法
    //再次随机生成n个
    void AutoUpdateLineSegments();
    //自己输入
    void InputUpdateLineSegments();

private:
    ////比较算法
    //O(n)时间复杂度算法
    pair<LineSegment, LineSegment> narrowingDownClosestPairLineSegments(const vector<LineSegment>& tempLineSegments)const;
    //枚举算法
    pair<LineSegment, LineSegment> bruteForceClosestPairLineSegments(const vector<LineSegment>& tempLineSegments)const;

    ////小工具
    //输入n
    int inputLineSegmentN();
    //比较插入线段后是否相交
    bool isLineSegmentIntersectWith(const LineSegment& tempLineSegment,const vector<LineSegment>& tempLineSegments)const;
};


#endif //NEAREST_SHAPE_LINESEGEMENTMANAGEMENT_H
