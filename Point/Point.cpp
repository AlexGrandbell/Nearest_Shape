//
// Created by 沈嘉瑞 on 2023.12.21.
//

#include "Point.h"

////其他函数
//重载输出流。这里为了方便输出到文件，不加其他标识。
ostream& operator<<(ostream& out,const Point& p){
    return out<<p.x<<" "<<p.y;
}
//重载等于
bool operator==(const Point& pl,const Point& pr){
    return (fabs(pl.x-pl.x)<=1e-9)&&(fabs(pl.y-pl.y)<=1e-9);
}
//用于传入sort进行比较排序
bool comparePointX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}
//用于传入sort进行比较排序
bool comparePointY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

//点之间距离计算
double pointsDistance(const Point& p1, const Point& p2) {
    return hypot(p1.x - p2.x, p1.y - p2.y);
}