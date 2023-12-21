//
// Created by 沈嘉瑞 on 2023.12.21.
//

#include "Triangle.h"

////构造函数
//随机生成三个顶点以生成三角形
Triangle::Triangle():A(),B(),C(){
    while (A==B || B==C || C==A || isPointOnSegment(A,B,C) || isPointOnSegment(A,C,B) || isPointOnSegment(B,C,A)) C = Point();
    makeSides();
}
//传入三个顶点的六个值来生成三角形
Triangle::Triangle(double x1,double y1,double x2,double y2,double x3,double y3):A(x1,y1),B(x2,y2),C(x3,y3){
    if (A==B || B==C || C==A || isPointOnSegment(A,B,C) || isPointOnSegment(A,C,B) || isPointOnSegment(B,C,A)) throw exception();
}
//传入三个顶点来生成三角形
Triangle::Triangle(const Point& p,const Point& q,const Point& r):A(p),B(p),C(r){
    if (A==B || B==C || C==A || isPointOnSegment(A,B,C) || isPointOnSegment(A,C,B) || isPointOnSegment(B,C,A)) throw exception();
}
//复制构造函数
Triangle::Triangle(const Triangle& t):A(t.A),B(t.B),C(t.C),a(t.a),b(t.b),c(t.c){}

////方法
//获得线段左端点x
double Triangle::left()const{
    return min({A.x,B.x,C.x});
}
//获得线段右端点x
double Triangle::right()const{
    return max({A.x,B.x,C.x});
}
//获得线段下端点y
double Triangle::down()const{
    return min({A.y,B.y,C.y});
}
//获得线段上端点y
double Triangle::up()const{
    return max({A.y,B.y,C.y});
}
//根据点构造线段
void Triangle::makeSides(){
    a = LineSegment(B,C);
    b = LineSegment(A,C);
    c = LineSegment(A,B);
}
//判断点是否在三角形内
bool Triangle::pointIsInTest(const Point& p) const{
    int r1 = orientation(A,B,p),r2 = orientation(B,C,p),r3 = orientation(C,A,p);
    //内部
    if (r1==r2 && r2==r3) return true;
    //点上
    if (isPointOnSegment(A,B,p) || isPointOnSegment(B,C,p) || isPointOnSegment(C,A,p)) return true;
    return false;
}

//重载输出流函数。这里为了方便输出到文件，不加其他标识。
ostream& operator<<(ostream& out,const Triangle& t){
    return out<<t.A<<" "<<t.B<<" "<<t.C;
}
//重载大于（包含）
bool operator>(const Triangle& tl,const Triangle& tr){
    return tl.pointIsInTest(tr.A) && tl.pointIsInTest(tr.B) && tl.pointIsInTest(tr.C);
}
//重载小于（被包含）
bool operator<(const Triangle& tl,const Triangle& tr){
    return tr.pointIsInTest(tl.A)&&tr.pointIsInTest(tl.B)&&tr.pointIsInTest(tl.C);
}
//判断三角形是否有边相交
bool isTriangleIntersect(const Triangle& tl,const Triangle& tr){
    return (isLineSegmentIntersect(tl.a,tr.a)||isLineSegmentIntersect(tl.a,tr.b)||isLineSegmentIntersect(tl.a,tr.c)||isLineSegmentIntersect(tl.b,tr.a)||isLineSegmentIntersect(tl.b,tr.b)||isLineSegmentIntersect(tl.b,tr.c)||isLineSegmentIntersect(tl.c,tr.a)||isLineSegmentIntersect(tl.c,tr.b)||isLineSegmentIntersect(tl.c,tr.c));
}
//判断三角形是否重叠
bool isTriangleOverlap(const Triangle& tl, const Triangle& tr){
    return isTriangleIntersect(tl,tr) || tl<tr || tl>tr;
}
//用于传入sort进行左端比较排序
bool compareTriangleLeftX(const Triangle& tl, const Triangle& tr){
    return tl.left()<tr.left();
}
//计算三角形之间的距离
double trianglesDistance(const Triangle& tl,const Triangle& tr){
    //如果重叠，返回0
    if (isTriangleOverlap(tl, tr)) return 0.0;
    double
    d1 = lineSegmentsDistance(tl.a,tr.a),
    d2 = lineSegmentsDistance(tl.a,tr.b),
    d3 = lineSegmentsDistance(tl.a,tr.c),
    d4 = lineSegmentsDistance(tl.b,tr.a),
    d5 = lineSegmentsDistance(tl.b,tr.b),
    d6 = lineSegmentsDistance(tl.b,tr.c),
    d7 = lineSegmentsDistance(tl.c,tr.a),
    d8 = lineSegmentsDistance(tl.c,tr.b),
    d9 = lineSegmentsDistance(tl.c,tr.c);
    return min({d1,d2,d3,d4,d5,d6,d7,d8,d9});
}