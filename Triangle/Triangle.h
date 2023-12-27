//
// Created by AlexGrandbell on 2023.12.21.
//

#ifndef NEAREST_SHAPE_TRIANGLE_H
#define NEAREST_SHAPE_TRIANGLE_H

#include "../LineSegment/LineSegment.h"

struct Triangle {
    ////顶点坐标与三边。对应
    Point A,B,C;
    LineSegment a,b,c;

    ////构造函数
    //随机生成三个顶点以生成三角形
    Triangle();
    //随机在l范围的正方形区域生成
    Triangle(double);
    //在输入的范围区域生成
    Triangle(double xl,double xr,double yd,double yu);
    //传入三个顶点的六个值来生成三角形
    Triangle(double ,double ,double ,double ,double ,double );
    //传入三个顶点来生成三角形
    Triangle(const Point&,const Point&,const Point&);
    //复制构造函数
    Triangle(const Triangle&);

    ////方法
    //获得线段左端点x
    double left()const;
    //获得线段右端点x
    double right()const;
    //获得线段下端点y
    double down()const;
    //获得线段上端点y
    double up()const;
    //根据点构造线段
    void makeSides();
    //判断点是否在三角形内
    bool pointIsInTest(const Point& p) const;
};

//重载输出流函数
ostream& operator<<(ostream& out,const Triangle& t);
//重载大于（包含）
bool operator>(const Triangle& tl,const Triangle& tr);
//重载小于（被包含）
bool operator<(const Triangle& tl,const Triangle& tr);
//判断三角形是否有边相交
bool isTriangleIntersect(const Triangle& tl,const Triangle& tr);
//判断三角形是否重叠（用这个判断最终重叠）
bool isTriangleOverlap(const Triangle& tl, const Triangle& tr);
//用于传入sort进行左端比较排序
bool compareTriangleLeftX(const Triangle& tl, const Triangle& tr);
//用于传入sort进行左端比较排序
bool compareTriangleBottomY(const Triangle& tl, const Triangle& tr);
//计算三角形之间的距离
double trianglesDistance(const Triangle& tl,const Triangle& tr);

#endif //NEAREST_SHAPE_TRIANGLE_H