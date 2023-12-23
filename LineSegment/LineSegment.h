//
// Created by AlexGrandbell on 2023.12.21.
//

#ifndef NEAREST_SHAPE_LINESEGMENT_H
#define NEAREST_SHAPE_LINESEGMENT_H

#include "../Point/Point.h"

struct LineSegment {
    ////端点坐标
    Point start,end;

    ////构造函数
    //随机生成0-100范围内的两个端点以构造线段
    LineSegment();
    //随机生成l正方形范围内的两个端点以构造线段
    LineSegment(double);
    //手动输入两个点的坐标
    LineSegment(double,double,double,double);
    //传入两个点作为两个端点
    LineSegment(const Point&,const Point&);
    //复制构造函数
    LineSegment(const LineSegment&);

    ////方法
    //获得线段左端点x
    double left()const;
    //获得线段右端点x
    double right()const;
    //获得线段下端点y
    double down()const;
    //获得线段上端点y
    double up()const;
    //获得线段长度
    double length()const;
};

//重载输出流函数
ostream& operator<<(ostream& out,const LineSegment& ls);
//重载等于
bool operator==(const LineSegment& lsl,const LineSegment& lsr);
//用于传入sort进行左端比较排序
bool compareLineLeftX(const LineSegment& lsl, const LineSegment& lsr);

////工具函数
//相交判断辅助函数，使用向量叉乘原理,检查r是否在pq构成的直线的一侧、另一侧和共线
int orientation(const Point& p, const Point& q, const Point& r);
//根据两边之和等于第三点判断点r是否在线段pq上
bool isPointOnSegment(const Point& p, const Point& q, const Point& r);
//判断线段是否相交
bool isLineSegmentIntersect(const LineSegment& ls1, const LineSegment& ls2);
//通过三角函数判断点是否在线段投影区内(垂足判断)
bool isPointAboveLineSegment(const Point& C,const LineSegment& ls);
//计算点与线段的距离
double lineAndPointDistance(const Point& p,const LineSegment& ls);
//计算线段之间的距离
double lineSegmentsDistance(const LineSegment& ls1,const LineSegment& ls2);
//判断与已有线段是否相交
bool isAnyLineSegmentIntersect(const vector<LineSegment>& lss, const LineSegment& newLS);

#endif //NEAREST_SHAPE_LINESEGMENT_H