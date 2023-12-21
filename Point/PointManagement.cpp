//
// Created by 沈嘉瑞 on 2023.12.21.
//

#include "PointManagement.h"
////构造函数
//默认构造函数
PointManagement::PointManagement():points(),startTime(0),endTime(0){}

////展示方法
//分治法查找最近点对
void PointManagement::DividePoint(){
    cout<<"开始使用分治法查找最近点对..."<<endl;
    startTime = clock();
    pair<Point, Point> closestPointPairResult = divideAndConquerPoints(points);
    endTime = clock();
    printf("分治法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"点对结果为:("<<closestPointPairResult.first<<")和("<<closestPointPairResult.second<<")"<<endl;
    cout<<"距离为:"<<pointsDistance(closestPointPairResult.first,closestPointPairResult.second)<<endl;
}
//自己的算法查找最近点对
void PointManagement::MyPointAlgorithm(){
    cout<<"开始使用自己优化的算法查找最近点对..."<<endl;
    startTime = clock();
    pair<Point, Point> closestPointPairResult = divideAndConquerPoints(points);
    endTime = clock();
    printf("算法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"点对结果为:("<<closestPointPairResult.first<<")和("<<closestPointPairResult.second<<")"<<endl;
    cout<<"距离为:"<<pointsDistance(closestPointPairResult.first,closestPointPairResult.second)<<endl;
}
//枚举算法
void PointManagement::BruteForcePoint(){
    cout<<"开始使用枚举法查找最近点对..."<<endl;
    startTime = clock();
    pair<Point, Point> closestPointPairResult = divideAndConquerPoints(points);
    endTime = clock();
    printf("枚举法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"点对结果为:("<<closestPointPairResult.first<<")和("<<closestPointPairResult.second<<")"<<endl;
    cout<<"距离为:"<<pointsDistance(closestPointPairResult.first,closestPointPairResult.second)<<endl;
}

////更新数据方法
//再次随机生成n个
void PointManagement::AutoUpdatePoints() {
    int n = inputN();
    //创建临时变量，确保完成前原有数据不被更改
    vector<Point> tempPoints;
    for (int i = 0; i < n; ++i) {
        Point tempPoint;
        while (isPointExistIn(tempPoint, tempPoints)) {
            tempPoint = Point();
        }
        tempPoints.push_back(tempPoint);
        if (n>=10000) progressBar(i,n);//展示进度
    }
    cout << "是否要要将生成的数据保存文件\"" << n << "个点数据\"?(0-否,1-是):";
    if (inputInt() == 1) {
        string fileName = to_string(n) + "个点数据.txt";
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            for (Point p: tempPoints) {
                outFile << p << endl;
            }
            outFile.close();
            cout << "数据已保存到文件\"" << n << "点个数据.txt\"" << endl;
        } else {
            cout << "无法打开文件进行输出，文件输出失败，程序继续" << endl;
        }
    }
    points = tempPoints;
    cout<< n <<"个点数据生成完成"<<endl;
}
//自己输入n个
void PointManagement::InputUpdatePoints(){
    int n = inputN();
    //创建临时变量，确保完成前原有数据不被更改
    vector<Point> tempPoints;
    cout<<"是否展示输入提示(0-否,1-是):";
    int c = inputInt();
    for (int i = 0; i < n; ++i) {
        if (c == 1) cout<<"请输入第"<<i+1<<"个点点坐标(x y):";
        tempPoints.push_back(Point(inputDouble(),inputDouble()));
    }
    points = tempPoints;
    cout<< n <<"个点数据生成完成"<<endl;
}

////////私有方法
//////比较算法
////分治法方法
//主分治法
pair<Point, Point> PointManagement::divideAndConquerPoints(const vector<Point>& tempPoints)const {
    int size = tempPoints.size();
    //递归到规模小于等于3的时候直接使用枚举算法解决
    if (size <= 3) {
        return bruteForceClosestPairPoints(tempPoints);
    }
    //先分为左右两部分，计算出两部分的最小值
    int mid = size / 2;
    vector<Point> tempLeftPoints(tempPoints.begin(), tempPoints.begin() + mid);
    vector<Point> tempRightPoints(tempPoints.begin() + mid, tempPoints.end());
    pair<Point, Point> leftClosestPointPair = divideAndConquerStripPoints(tempLeftPoints);
    pair<Point, Point> rightClosesPointtPair = divideAndConquerStripPoints(tempRightPoints);
    double delta = min(pointsDistance(leftClosestPointPair.first, leftClosestPointPair.second),pointsDistance(rightClosesPointtPair.first, rightClosesPointtPair.second));
    //再计算中线附近垂直带状区域
    vector<Point> strip;
    for (const Point &p: tempPoints) {
        if (fabs(p.x - tempPoints[mid].x) < delta) {
            strip.push_back(p);
        }
    }
    //根据y排列
    sort(strip.begin(), strip.end(), comparePointY);
    try {
        pair<Point, Point> stripClosestPointsPair = divideAndConquerStripPoints(strip);
        if (pointsDistance(stripClosestPointsPair.first, stripClosestPointsPair.second) < delta) {
            return stripClosestPointsPair;
        }
    }catch (exception e){}
    return (pointsDistance(leftClosestPointPair.first, leftClosestPointPair.second) < pointsDistance(rightClosesPointtPair.first, rightClosesPointtPair.second)) ? leftClosestPointPair : rightClosesPointtPair;
}
//中心区域查找
pair<Point, Point> PointManagement::divideAndConquerStripPoints(const vector<Point>& tempPoints)const{
    int size = tempPoints.size();
    if (size<=1){
        throw myExpection("只有一个点");
    }
    double minDistance = numeric_limits<double>::infinity();
    pair<Point, Point> closestPointPair;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i + 1; j < size && (tempPoints[j].y - tempPoints[i].y) < minDistance; ++j) {
            double distance = pointsDistance(tempPoints[i], tempPoints[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestPointPair = make_pair(tempPoints[i], tempPoints[j]);
            }
        }
    }
    return closestPointPair;
}
////对枚举算法进行优化，即可得到时间复杂度为O(n)的算法!
pair<Point, Point> PointManagement::narrowingDownPoints(const vector<Point>& tempPoints)const{
    int size = tempPoints.size();
    double minDistance = numeric_limits<double>::infinity();
    pair<Point, Point> closestPointPair;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if (points[j].x-points[i].x>minDistance){//若右边超过了，则直接终止此轮程序
                break;
            } else if (fabs(points[i].y-points[j].y)>minDistance){//若竖直方向超出，则直接排除
                continue;
            } else {
                double distance = pointsDistance(points[i], points[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestPointPair = make_pair(points[i], points[j]);
                }
            }
        }
    }
    return closestPointPair;
}
////纯枚举算法
pair<Point, Point> PointManagement::bruteForceClosestPairPoints(const vector<Point>& tempPoints)const{
    int size = tempPoints.size();
    double minDistance = numeric_limits<double>::infinity();
    pair<Point, Point> closestPointPair;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            double distance = pointsDistance(points[i], points[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestPointPair = make_pair(points[i], points[j]);
            }
        }
    }
    return closestPointPair;
}

//////小工具
//输入n
int PointManagement::inputN(){
    cout<<"请输入点的个数:";
    int n=inputInt();
    while (n<=1){
        cout<<"点数量过少,请重新输入:"<<endl;
        n=inputInt();
    }
    cout<<"开始生成点数据..."<<endl;
    return n;
}
//比较点是否存在与点集中
bool PointManagement::isPointExistIn(const Point& point,const vector<Point>& tempPoints) const{
    for (Point p:tempPoints) {
        if (p == point) {
            return true;
        }
    }
    return false;
};
