//
// Created by AlexGrandbell on 2023.12.21.
//

#include "LineSegment.h"

//随机生成两个端点以构造线段
LineSegment::LineSegment():start(),end() {
    while (start == end) end = Point();
}
//随机生成l正方形范围内的两个端点以构造线段
LineSegment::LineSegment(double l):start(l),end(l){
    while (start == end) end = Point(l);
}
//手动输入两个点的坐标
LineSegment::LineSegment(double x1,double y1,double x2,double y2):start(x1,y1),end(x2,y2){
    while (start == end) end = Point();
}
//传入两个点作为两个端点
LineSegment::LineSegment(const Point& p1,const Point& p2):start(p1),end(p2){
    while (start == end) end = Point();
}
//复制构造函数
LineSegment::LineSegment(const LineSegment& ls):start(ls.start),end(ls.end){}

////方法
//获得线段左端点x
double LineSegment::left()const{
    return min(start.x,end.x);
}
//获得线段右端点x
double LineSegment::right()const{
    return max(start.x,end.x);
}
//获得线段下端点y
double LineSegment::down()const{
    return min(start.y,end.y);
}
//获得线段上端点y
double LineSegment::up()const{
    return max(start.y,end.y);
}
//获得线段长度
double LineSegment::length()const{
    return pointsDistance(start,end);
}

////其他函数
//重载输出流函数。这里为了方便输出到文件，不加其他标识。
ostream& operator<<(ostream& out,const LineSegment& ls) {
    return out << ls.start << " " << ls.end;
}
//重载等于
bool operator==(const LineSegment& lsl,const LineSegment& lsr) {
    return (lsl.start == lsr.start && lsl.end == lsr.end) || (lsl.start == lsr.end && lsl.end == lsr.start);
}
//用于传入sort进行左端比较排序
bool compareLineLeftX(const LineSegment& lsl, const LineSegment&lsr){
    return lsl.left()<lsr.left();
}

////工具函数
//相交判断辅助函数，使用向量叉乘原理,检查r是否在pq构成的直线的一侧、另一侧和共线
int orientation(const Point& p, const Point& q, const Point& r) {
    double val = (q.x - p.x) * (r.y - q.y) - (q.y - p.y) * (r.x - q.x);//向量叉乘坐标运算
    if (fabs(val) < 1e-6) return 0; // 共线
    return (val > 0) ? 1 : 2; // 1逆时针2顺时针
}
//根据两边之和是否等于线段长度判断点r是否在线段pq上
bool isPointOnSegment(const Point& p, const Point& q, const Point& r) {
    if (fabs(pointsDistance(p,q)-(pointsDistance(p,r)+ pointsDistance(q,r)))<1e-6){
        return true;
    }
    return false;
}
//判断线段是否相交
bool isLineSegmentIntersect(const LineSegment& ls1, const LineSegment& ls2){
    Point p1,q1,p2,q2;
    p1 = ls1.start;
    q1 = ls1.end;
    p2 = ls2.start;
    q2 = ls2.end;
    // 用跨立法检查两线段是否相交（此外还有矩形重合法）
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    //一般情况
    if (o1 != o2 && o3 != o4) {
        return true; // 有交点
    }

    //特殊重合情况
    if (isPointOnSegment(p1,q1,p2)) return true;
    if (isPointOnSegment(p1,q1,q2)) return true;
    if (isPointOnSegment(p2,q2,p1)) return true;
    if (isPointOnSegment(p2,q2,q1)) return true;

    return false; // 无交点
}
//通过三角函数判断点是否在线段投影区内(垂足判断):三点构成的三角形两个角是否有钝角角pqr,角qpr。使用cos检测
bool isPointAboveLineSegment(const Point& C,const LineSegment& ls){
    Point A = ls.start,B=ls.end;
    double c = ls.length();
    double a = pointsDistance(B, C);
    double b = pointsDistance(C, A);
    // 计算三个角的余弦值
    double cosB = (c * c + a * a - b * b) / (2 * c * a);
    double cosA = (b * b + c * c - a * a) / (2 * b * c);
    // 判断是否存在余弦值小于零的情况，即是否存在钝角
    return !(cosA <= 0 || cosB <= 0);
}
//计算点与线段的距离
double lineAndPointDistance(const Point& p,const LineSegment& ls){
    //如果在垂直阴影区域内就计算垂直距离
    if(isPointAboveLineSegment(p,ls)){
        // 计算线段的方向向量
        double dx = ls.end.x - ls.start.x;
        double dy = ls.end.y - ls.start.y;
        // 计算从线段起点到点的向量
        double vx = p.x - ls.start.x;
        double vy = p.y - ls.start.y;
        //解决潜在的除0错误
        double denominator = dx * dx + dy * dy;
        if (denominator < 1e-6) {
            //转换为点到点的距离
            return pointsDistance(ls.start,p);
        }
        double projectionLength = (vx * dx + vy * dy) / denominator;
        // 计算投影点的坐标
        double projectionX = ls.start.x + projectionLength * dx;
        double projectionY = ls.start.y + projectionLength * dy;
        // 计算从点到投影点的向量
        double distanceX = p.x - projectionX;
        double distanceY = p.y - projectionY;
        // 计算垂线段的长度
        double distance = hypot(distanceX, distanceY);
        return distance;
    } else{
        //否则返回与端点距离最小
        return min(pointsDistance(p,ls.start), pointsDistance(p,ls.end));
    }
}
//计算线段之间的距离
double lineSegmentsDistance(const LineSegment& ls1,const LineSegment& ls2){
    //如果相交，返回0
    if (isLineSegmentIntersect(ls1, ls2)){
        return 0.0;
    }
    //否则计算四个端点到另一条线段的直线的距离最小值
    double d1,d2,d3,d4;
    d1 = lineAndPointDistance(ls1.start,ls2);
    d2 = lineAndPointDistance(ls1.end,ls2);
    d3 = lineAndPointDistance(ls2.start,ls1);
    d4 = lineAndPointDistance(ls2.end,ls1);
    return min({d1,d2,d3,d4});
}
//判断与已有线段是否相交
bool isAnyLineSegmentIntersect(const vector<LineSegment>& lss, const LineSegment& newLS) {
    for (const auto& ls : lss) {
        if (isLineSegmentIntersect(newLS, ls)) {
            return true;
        }
    }
    return false;
}