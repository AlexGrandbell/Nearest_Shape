//
// Created by AlexGrandbell on 2023.12.21.
//

#include "Point.h"

////其他函数
//重载输出流。这里为了方便输出到文件，不加其他标识。
ostream& operator<<(ostream& out,const Point& p){
    return out<<p.x<<" "<<p.y;
}
//重载等于
bool operator==(const Point& pl,const Point& pr){
    return (fabs(pl.x-pr.x)<=1e-9)&&(fabs(pl.y-pr.y)<=1e-9);
}
//用于传入sort进行比较排序
bool comparePointX(const Point& pl, const Point& pr) {
    return pl.x < pr.x;
}
//用于传入sort进行比较排序
bool comparePointY(const Point& pl, const Point& pr) {
    return pl.y < pr.y;
}
//点之间距离计算
double pointsDistance(const Point& pl, const Point& pr) {
    return hypot(pl.x - pr.x, pl.y - pr.y);
}