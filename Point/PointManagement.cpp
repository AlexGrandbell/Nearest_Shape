//
// Created by 沈嘉瑞 on 2023.12.21.
//

#include "PointManagement.h"
////构造函数
//默认构造函数
PointManagement::PointManagement():points(),startTime(0),endTime(0){}

////展示方法
//分治法查找最近点对
void PointManagement::DividePoint(){}
//自己的算法查找最近点对
void PointManagement::MyPointAlgorithm(){}
//暴力算法
void PointManagement::BruteForcePoint(){}

////更新数据方法
//再次随机生成n个
void PointManagement::AutoUpdatePoints(int n){}
//自己输入n个
void PointManagement::InputUpdatePoints(int n){}

//////私有方法
////分治法方法
//主分治法
pair<Point, Point> PointManagement::divideAndConquerPoints(const vector<Point>& points){}
//中心区域查找
pair<Point, Point> PointManagement::divideAndConquerStripPoints(const vector<Point>& points){}
////自己想出来的算法，O(n)时间复杂度！
pair<Point, Point> PointManagement::narrowingDownPoints(const vector<Point>& points){}
////纯暴力算法
pair<Point, Point> PointManagement::bruteForceClosestPairPoints(const vector<Point>& points){}