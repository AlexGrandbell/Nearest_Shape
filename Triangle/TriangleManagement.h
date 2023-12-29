//
// Created by AlexGrandbell on 2023.12.21.
//

#ifndef NEAREST_SHAPE_TRIANGLEMANAGEMENT_H
#define NEAREST_SHAPE_TRIANGLEMANAGEMENT_H

#include "Triangle.h"

class TriangleManagement {
private:
    //三角形集元素
    vector<Triangle> triangles;
    //运行计时工具
    clock_t startTime,endTime;
public:
    ////构造函数
    //默认构造函数
    TriangleManagement();

    ////展示方法
    //分治法查找最近点对
    void DivideTriangle();
    //自己的算法查找最近线段对
    void MyTriangleAlgorithm();
    //枚举算法
    void BruteForceTriangle();
    //时间下限
    void MinTime();

    ////输出方法
    //输出到文件
    void OutputTrianglesToFile();
    //输出到屏幕
    void OutputTrianglesToScreen();

    ////更新数据方法
    //再次随机生成n个
    void AutoUpdateTriangles();
    //由于三角形较难生成不重叠，此处额外提供有规律地生成不重叠数据
    void RegularlyUpdateTriangles();
    //自己输入
    void InputUpdateTriangles();
    //中心区域查找
    pair<Triangle, Triangle> divideClosestPairStripTriangles(const vector<Triangle>& tempTriangles)const;
private:
    ////比较算法
    //缩小域算法
    pair<Triangle, Triangle> narrowingDownClosestPairTriangles(const vector<Triangle>& tempTriangles)const;
    //分治算法
    pair<Triangle,Triangle>divideClosestPairTriangles(const vector<Triangle>& tempTriangles)const;
    //枚举算法
    pair<Triangle, Triangle> bruteForceClosestPairTriangles(const vector<Triangle>& tempTriangles)const;
    //遍历所有三角形
    void travelAllTriangles()const;

    ////小工具
    //输入n
    int inputTriangleN();
    //比较插入线段后是否相交
    bool isTriangleOverlapOn(const Triangle& tempTriangle,const vector<Triangle>& tempTriangles)const;
};

#endif //NEAREST_SHAPE_TRIANGLEMANAGEMENT_H
