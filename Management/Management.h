//
// Created by 沈嘉瑞 on 2023.12.21.
//

#ifndef NEAREST_SHAPE_MANAGEMENT_H
#define NEAREST_SHAPE_MANAGEMENT_H

#include "../Point/PointManagement.h"
#include "../LineSegment/LineSegementManagement.h"
#include "../Triangle/TriangleManagement.h"

class Management {
private:
    //三个形状集合
    PointManagement pointManagement;
    LineSegementManagement lineSegementManagement;
    TriangleManagement triangleManagement;
public:
    //构造函数
    Management():pointManagement(), lineSegementManagement(), triangleManagement(){};

    //用户界面
    void Welcome();
    void DoMenu();
private:
    //三种形状选择二级菜单
    void DoPoinit();
    void DoLineSegment();
    void DoTriangle();
    void ExitApp();

    //////二级菜单
    ////点二级菜单
    //输入点集
    void inputPointsMenu();
    //输出点集
    void outputPointsMenu();
    //最近点对
    void closestPointPairMenu();

    ////线段二级菜单
    //输入线段集
    void inputLineSegmentsMenu();
    //输出线段集
    void outputLineSegmentsMenu();
    //最近线段对
    void closestLineSegmentPairMenu();

    ////三角形二级菜单
    //输入三角形集
    void inputTrianglesMenu();
    //输出三角形集
    void outputTrianglesMenu();
    //最近三角形对
    void closestTrianglePairMenu();
};

#endif //NEAREST_SHAPE_MANAGEMENT_H