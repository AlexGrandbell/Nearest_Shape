//
// Created by AlexGrandbell on 2023.12.21.
//

#ifndef NEAREST_SHAPE_POINT_H
#define NEAREST_SHAPE_POINT_H

#include "../Tool/Tool.h"

class Point {
public:
    ////坐标
    double x, y;

    ////构造函数
    //随机构造函数，生成一个x、y的范围为0-100的随机点
    Point():x(randomDouble()),y(randomDouble()){};
    //随机构造函数，生成xl,xr,yd,yu范围内的随机点
    Point(double xl,double xr,double yd,double yu):x(randomDouble(xl,xr)),y(randomDouble(yd,yu)){}
    //随机构造函数，生成距离原点l的正方形区域内的随机点
    Point(double l):x(randomDouble(-l,l)),y(randomDouble(-l,l)){}
    //手动构造函数
    Point(double x1,double y1):x(x1),y(y1){}
    //复制构造函数
    Point(const Point& a) :x(a.x),y(a.y){}
};

//重载输出流。这里为了方便输出到文件，不加其他标识。
ostream& operator<<(ostream&,const Point&);
//重载等于
bool operator==(const Point&,const Point&);
//用于传入sort进行比较排序
bool comparePointX(const Point &p1, const Point &p2);
//用于传入sort进行比较排序
bool comparePointY(const Point&, const Point&);
//点之间距离计算
double pointsDistance(const Point&, const Point&);

#endif //NEAREST_SHAPE_POINT_H