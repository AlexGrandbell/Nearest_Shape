//
// Created by AlexGrandbell on 2023.12.21.
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
void LineSegementManagement::OutputLineSegmentsToFile() {
    cout << "请输入文件名(无需加.txt):";
    string fileName = inputString() + ".txt";
    cout << "开始覆盖线段集数据到文件\"" << fileName << "\"" << endl;
    ofstream outFile(fileName);
    if (lineSegments.size() > 0) {
        vector<LineSegment> tempLineSegments = lineSegments;
        //打乱
        random_device rd;
        mt19937 gen(rd());
        shuffle(tempLineSegments.begin(), tempLineSegments.end(), gen);
        if (outFile.is_open()) {
            for (LineSegment l: tempLineSegments) {
                outFile <<setprecision(25)<< l << endl;
            }
            outFile.close();
            cout << "数据已保存到文件\"" << fileName << "\"" << endl;
        } else {
            cout << "无法打开文件进行输出，文件输出失败，程序继续" << endl;
        }
    } else {
        cout << "没有数据，无需输出" << endl;
    }
}
//输出到屏幕
void LineSegementManagement::OutputLineSegmentsToScreen(){
    cout << "开始输出线段集数据" << endl;
    vector<LineSegment> tempLineSegments = lineSegments;
    //打乱
    random_device rd;
    mt19937 gen(rd());
    shuffle(tempLineSegments.begin(),tempLineSegments.end(),gen);
    if (tempLineSegments.size() > 0) {
        for (LineSegment l: tempLineSegments) {
            cout << setprecision(25)<<l << endl;
        }
        cout << "线段集数据输出完成，共" << tempLineSegments.size() << "条线段" << endl;
    } else {
        cout << "没有数据，无需输出" << endl;
    }
}

////更新数据方法
//再次随机生成n个
void LineSegementManagement::AutoUpdateLineSegments(){
    int n = inputLineSegmentN();
    cout<<"是否需要不相交数据(0-否,1-是):";
    bool canSameLineSegment = (inputInt() == 1);
    //创建临时变量，确保完成前原有数据不被更改
    vector<LineSegment> tempLineSegments;
    LineSegment tempLineSegment;
    for (int i = 0; i < n; ++i) {
        do {
            tempLineSegment = LineSegment(n);
        }while (canSameLineSegment && isLineSegmentIntersectWith(tempLineSegment,tempLineSegments));
        tempLineSegments.push_back(tempLineSegment);
        if (n>=100) progressBar(i,n);//展示进度
    }
    lineSegments = tempLineSegments;
    sort(lineSegments.begin(),lineSegments.end(), compareLineLeftX);//重要排序，不能删除
    cout<< n <<"条线段数据生成完成"<<endl;
}
//自己输入
void LineSegementManagement::InputUpdateLineSegments(){
    int n = inputLineSegmentN();
    //创建临时变量，确保完成前原有数据不被更改
    vector<LineSegment> tempLineSegments;
    cout<<"是否展示输入提示(0-否,1-是):";
    int c = inputInt();
    for (int i = 0; i < n; ++i) {
        if (c == 1) cout<<"请输入第"<<i+1<<"条线段坐标(x y):";
        double x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        tempLineSegments.push_back(LineSegment(x1,y1,x2,y2));
    }
    lineSegments= tempLineSegments;
    sort(lineSegments.begin(),lineSegments.end(), compareLineLeftX);//重要排序，不能删除
    cout<< n <<"条线段数据生成完成"<<endl;
}

////比较算法
//缩小域算法
pair<LineSegment, LineSegment> LineSegementManagement::narrowingDownClosestPairLineSegments(const vector<LineSegment>& tempLineSegments)const{
    int size = lineSegments.size();
    if (size <= 1){
        throw myExpection("线段太少");
    }
    double minDistance = numeric_limits<double>::infinity();
    pair<LineSegment, LineSegment> closestLineSegmentPair;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if ((lineSegments[j].left()-lineSegments[i].right())>minDistance){//若右边超过了，说明接下来的线段都不可能更近了，则直接终止此轮程序
                break;
            } else if (!(((lineSegments[j].down() - lineSegments[i].up()) >= minDistance) || ((lineSegments[i].down() - lineSegments[j].up()) >= minDistance))) {//若竖直方向超出，则直接排除，减少计算
                double distance = lineSegmentsDistance(lineSegments[i], lineSegments[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestLineSegmentPair = make_pair(lineSegments[i], lineSegments[j]);
                }
                if (minDistance == 0) return closestLineSegmentPair;
            }
        }
    }
    return closestLineSegmentPair;
}
//枚举算法
pair<LineSegment, LineSegment> LineSegementManagement::bruteForceClosestPairLineSegments(const vector<LineSegment>& tempLineSegments)const{
    int size = lineSegments.size();
    if (size <= 1){
        throw myExpection("线段太少");
    }
    double minDistance = numeric_limits<double>::infinity();
    pair<LineSegment, LineSegment> closestLineSegmentPair;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            double distance = lineSegmentsDistance(lineSegments[i], lineSegments[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestLineSegmentPair = make_pair(lineSegments[i], lineSegments[j]);
            }
            if (minDistance == 0) return closestLineSegmentPair;
        }
    }
    return closestLineSegmentPair;
}

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
bool LineSegementManagement::isLineSegmentIntersectWith(const LineSegment& newTempLineSegment,const vector<LineSegment>& tempLineSegments)const{
    for (const auto& tempLineSegment : tempLineSegments) {
        if (isLineSegmentIntersect(newTempLineSegment, tempLineSegment)) {
            return true;
        }
    }
    return false;
}