//
// Created by 沈嘉瑞 on 2023.12.21.
//

#include "LineSegementManagement.h"

////构造函数
//默认构造函数
LineSegementManagement::LineSegementManagement():lineSegments(),startTime(0),endTime(0){}

////展示方法
//自己的算法查找最近线段对
void LineSegementManagement::MyLineSegmentAlgorithm(){
    cout<<"开始使用自己优化的算法查找最近线段对..."<<endl;
    startTime = clock();
    pair<LineSegment, LineSegment> closestLineSegmentPairResult = narrowingDownClosestPairLineSegments(lineSegments);
    endTime = clock();
    printf("算法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"线段对结果为:("<<closestLineSegmentPairResult.first<<")和("<<closestLineSegmentPairResult.second<<")"<<endl;
    cout<<"距离为:"<<lineSegmentsDistance(closestLineSegmentPairResult.first,closestLineSegmentPairResult.second)<<endl;
}
//枚举算法
void LineSegementManagement::BruteForceLineSegment(){
    cout<<"开始使用枚举法查找最近线段对..."<<endl;
    startTime = clock();
    pair<LineSegment, LineSegment> closestLineSegmentPairResult = bruteForceClosestPairLineSegments(lineSegments);
    endTime = clock();
    printf("算法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"线段对结果为:("<<closestLineSegmentPairResult.first<<")和("<<closestLineSegmentPairResult.second<<")"<<endl;
    cout<<"距离为:"<<lineSegmentsDistance(closestLineSegmentPairResult.first,closestLineSegmentPairResult.second)<<endl;
}

////输出方法
//输出到文件
void LineSegementManagement::OutputLineSegmentsToFile(){
    cout<<"请输入文件名:";
    string fileName = inputString();
    cout<<"开始覆盖线段集数据到文件\""<<fileName<<"\""<<endl;
    ofstream outFile(fileName);
    if (lineSegments.size()>0) {
        if (outFile.is_open()) {
            for (LineSegment l: lineSegments) {
                outFile << l << endl;
            }
            outFile.close();
            cout << "数据已保存到文件\"" << fileName << "\"" << endl;
        } else {
            cout << "无法打开文件进行输出，文件输出失败，程序继续" << endl;
        }
    } else{
        cout<<"没有数据，无需输出"<<endl;
    }
}
//输出到屏幕
void LineSegementManagement::OutputLineSegmentsToScreen(){
    cout << "开始输出线段集数据" << endl;
    if (lineSegments.size() > 0) {
        for (LineSegment l: lineSegments) {
            cout << l << endl;
        }
        cout << "线段集数据输出完成，共" << lineSegments.size() << "条线段" << endl;
    } else {
        cout << "没有数据，无需输出" << endl;
    }
}

////更新数据方法
//再次随机生成n个
void LineSegementManagement::AutoUpdateLineSegments(){
    int n = inputLineSegmentN();
    cout<<"是否需要不重复数据(0-否,1-是):";
    bool canSameLineSegment = (inputInt() == 0);
    //创建临时变量，确保完成前原有数据不被更改
    vector<LineSegment> tempLineSegments;
    for (int i = 0; i < n; ++i) {
        LineSegment tempLineSegment;
        while (canSameLineSegment && isLineSegmentIntersectWith(tempLineSegment,tempLineSegments)) {
            tempLineSegment = LineSegment();
        }
        tempLineSegments.push_back(tempLineSegment);
        if (n>=10000) progressBar(i,n);//展示进度
    }
    cout << "是否要要将生成的数据保存到文件\"" << n << "条线段数据\"?(0-否,1-是):";
    if (inputInt() == 1) {
        string fileName = to_string(n) + "条线段数据.txt";
        ofstream outFile(fileName);
        if (outFile.is_open()) {
            for (LineSegment ls: tempLineSegments) {
                outFile << ls << endl;
            }
            outFile.close();
            cout << "数据已保存到文件\"" << n << "条线段数据.txt\"" << endl;
        } else {
            cout << "无法打开文件进行输出，文件输出失败，程序继续" << endl;
        }
    }
    lineSegments = tempLineSegments;
    sort(lineSegments.begin(),lineSegments.end(), compareLineLeftX);//重要排序，不能删除
    cout<< n <<"条线段数据生成完成"<<endl;
}
//有规律的生成
void LineSegementManagement::RegularlyUpdateLineSegments(){

}
//自己输入
void InputUpdateLineSegments(){}

////比较算法
//O(n)时间复杂度算法
pair<LineSegment, LineSegment> LineSegementManagement::narrowingDownClosestPairLineSegments(const vector<LineSegment>& tempLineSegments)const{}
//枚举算法
pair<LineSegment, LineSegment> LineSegementManagement::bruteForceClosestPairLineSegments(const vector<LineSegment>& tempLineSegments)const{}

////小工具
//输入n
int LineSegementManagement::inputLineSegmentN(){
    cout<<"请输入线段的个数:";
    int n=inputInt();
    while (n<=1){
        cout<<"线段数量过少,请重新输入:"<<endl;
        n=inputInt();
    }
    cout<<"开始生成线段数据..."<<endl;
    return n;
}
//比较插入线段后是否相交
bool LineSegementManagement::isLineSegmentIntersectWith(const LineSegment& tempLineSegment,const vector<LineSegment>& tempLineSegments)const{}