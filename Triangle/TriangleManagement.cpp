//
// Created by AlexGrandbell on 2023.12.21.
//

#include "TriangleManagement.h"

////构造函数
//默认构造函数
TriangleManagement::TriangleManagement():triangles(),startTime(0),endTime(0){}

////展示方法
void TriangleManagement::DivideTriangle(){
    cout<<"开始使用分治法查找最近三角形对..."<<endl;
    startTime = clock();
    pair<Triangle, Triangle> closestTrianglePairResult = divideClosestPairTriangles(triangles);
    endTime = clock();
    printf("分治算法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"三角形对结果为:("<<closestTrianglePairResult.first<<")和("<<closestTrianglePairResult.second<<")"<<endl;
    cout<<"距离为:"<<trianglesDistance(closestTrianglePairResult.first,closestTrianglePairResult.second)<<endl;
}
//自己的算法查找最近三角形对
void TriangleManagement::MyTriangleAlgorithm(){
    cout<<"开始使用自己优化的算法查找最近三角形对..."<<endl;
    startTime = clock();
    pair<Triangle, Triangle> closestTrianglePairResult = narrowingDownClosestPairTriangles(triangles);
    endTime = clock();
    printf("算法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"三角形对结果为:("<<closestTrianglePairResult.first<<")和("<<closestTrianglePairResult.second<<")"<<endl;
    cout<<"距离为:"<<trianglesDistance(closestTrianglePairResult.first,closestTrianglePairResult.second)<<endl;
}
//枚举算法
void TriangleManagement::BruteForceTriangle(){
    cout<<"开始使用枚举法查找最近三角形对..."<<endl;
    startTime = clock();
    pair<Triangle, Triangle> closestTrianglePairResult = bruteForceClosestPairTriangles(triangles);
    endTime = clock();
    printf("算法结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
    cout<<"三角形对结果为:("<<closestTrianglePairResult.first<<")和("<<closestTrianglePairResult.second<<")"<<endl;
    cout<<"距离为:"<<trianglesDistance(closestTrianglePairResult.first,closestTrianglePairResult.second)<<endl;
}
//时间下限
void TriangleManagement::MinTime(){
    cout<<"开始测试时间下限..."<<endl;
    startTime = clock();
    for (int i = 0;i<triangles.size()-1;i++) {
        trianglesDistance(triangles[i],triangles[i+1]);
    }
    endTime = clock();
    printf("测试结束，运行时间%f秒",((double)(endTime - startTime)) / CLOCKS_PER_SEC);
}

////输出方法
//输出到文件
void TriangleManagement::OutputTrianglesToFile() {
    cout << "请输入文件名(无需加.txt):";
    string fileName = inputString() + ".txt";
    cout << "开始覆盖三角形集数据到文件\"" << fileName << "\"" << endl;
    ofstream outFile(fileName);
    if (triangles.size() > 0) {
        vector<Triangle> tempTriangles = triangles;
        //打乱
        random_device rd;
        mt19937 gen(rd());
        shuffle(tempTriangles.begin(), tempTriangles.end(), gen);
        if (outFile.is_open()) {
            for (Triangle l: tempTriangles) {
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
void TriangleManagement::OutputTrianglesToScreen(){
    cout << "开始输出三角形集数据" << endl;
    vector<Triangle> tempTriangles = triangles;
    //打乱
    random_device rd;
    mt19937 gen(rd());
    shuffle(tempTriangles.begin(),tempTriangles.end(),gen);
    if (tempTriangles.size() > 0) {
        for (Triangle l: tempTriangles) {
            cout << setprecision(25)<< l << endl;
        }
        cout << "三角形集数据输出完成，共" << tempTriangles.size() << "个三角形" << endl;
    } else {
        cout << "没有数据，无需输出" << endl;
    }
}

////更新数据方法
//再次随机生成n个
void TriangleManagement::AutoUpdateTriangles(){
    int n = inputTriangleN();
    cout<<"是否需要不重叠数据(0-否,1-是):";
    bool canSameTriangle = (inputInt() == 1);
    //创建临时变量，确保完成前原有数据不被更改
    vector<Triangle> tempTriangles;
    Triangle tempTriangle;
    for (int i = 0; i < n; ++i) {
        do {
            tempTriangle = Triangle(n);
        }while (canSameTriangle && isTriangleOverlapOn(tempTriangle,tempTriangles));
        tempTriangles.push_back(tempTriangle);
        if (n>=100) progressBar(i,n);//展示进度
    }
    triangles = tempTriangles;
    sort(triangles.begin(),triangles.end(), compareTriangleLeftX);//重要排序，不能删除
    cout<< n <<"个三角形数据生成完成"<<endl;
}
//有规律自动生成不重叠
void TriangleManagement::RegularlyUpdateTriangles(){
    int n = inputTriangleN();
    //创建临时变量，确保完成前原有数据不被更改
    vector<Triangle> tempTriangles1;
    int numOfBlock = n/10;
    numOfBlock = (int)sqrt(numOfBlock);
    double low = -100* numOfBlock;
    double high = -low;
    n=numOfBlock*numOfBlock*10;
    cout<<"受限于生成方式，将产生"<<n<<"个不重叠的三角形数据"<<endl;
    for (int i = 0; i < numOfBlock; ++i) {
        for (int j = 0; j < numOfBlock; ++j) {
            vector<Triangle> tempTriangles;
            Triangle tempTriangle;
            double xl = low + 100 * i;
            double xr = xl + 100;
            double yu = high - 100 * j;
            double yd = yu - 100;
            for (int k = 0; k < 10; ++k) {
                do {
                    tempTriangle = Triangle(xl, xr, yd, yu);
                } while (isTriangleOverlapOn(tempTriangle, tempTriangles));
                tempTriangles.push_back(tempTriangle);
            }
            for (Triangle t: tempTriangles) {
                tempTriangles1.push_back(t);
            }
        }
        progressBar(i,numOfBlock);
    }
    triangles= tempTriangles1;
    sort(triangles.begin(),triangles.end(), compareTriangleLeftX);//重要排序，不能删除
    cout<< n <<"个三角形数据生成完成"<<endl;
}
//自己输入
void TriangleManagement::InputUpdateTriangles(){
    int n = inputTriangleN();
    //创建临时变量，确保完成前原有数据不被更改
    vector<Triangle> tempTriangles;
    cout<<"是否展示输入提示(0-否,1-是):";
    int c = inputInt();
    for (int i = 0; i < n; ++i) {
        if (c == 1) cout<<"请输入第"<<i+1<<"个三角形坐标(x y):";
        double x1,y1,x2,y2,x3,y3;
        cin>>x1>>y1>>x2>>y2>>x3>>y3;
        tempTriangles.push_back(Triangle(x1,y1,x2,y2,x3,y3));
    }
    triangles= tempTriangles;
    sort(triangles.begin(),triangles.end(), compareTriangleLeftX);//重要排序，不能删除
    cout<< n <<"个三角形数据生成完成"<<endl;
}

////比较算法
pair<Triangle, Triangle> TriangleManagement::narrowingDownClosestPairTriangles(const vector<Triangle>& tempTriangles)const{
    int size = triangles.size();
    if (size <= 1){
        throw myExpection("三角形太少");
    }
    double minDistance = numeric_limits<double>::infinity();
    pair<Triangle, Triangle> closestTrianglePair;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if ((triangles[j].left()-triangles[i].right())>minDistance){//若右边超过了，说明接下来的三角形都不可能更近了，则直接终止此轮程序
                break;
            } else if (!(((triangles[j].down() - triangles[i].up()) >= minDistance) || ((triangles[i].down() - triangles[j].up()) >= minDistance))) {
                //若竖直方向超出，则直接排除，减少计算
                double distance = trianglesDistance(triangles[i], triangles[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestTrianglePair = make_pair(triangles[i], triangles[j]);
                }
                if (minDistance == 0) return closestTrianglePair;
            }
        }
    }
    return closestTrianglePair;
}
//中心区域查找
pair<Triangle, Triangle> TriangleManagement::divideClosestPairStripTriangles(const vector<Triangle>& tempTriangles)const{
    int size = tempTriangles.size();
    if (size <= 1){
        throw myExpection("三角形太少");
    }
    double minDistance = numeric_limits<double>::infinity();
    pair<Triangle, Triangle> closestTrianglePair;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            if ((tempTriangles[j].down()-tempTriangles[i].up())>minDistance){//若竖直方向超出，则直接排除，减少计算
                break;
            } else {
                double distance = trianglesDistance(tempTriangles[i], tempTriangles[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestTrianglePair = make_pair(tempTriangles[i], tempTriangles[j]);
                }
                if (minDistance == 0) return closestTrianglePair;
            }
        }
    }
    return closestTrianglePair;
}
//主分治算法
pair<Triangle,Triangle> TriangleManagement::divideClosestPairTriangles(const vector<Triangle>& tempTriangles)const{
    int size = tempTriangles.size();
    //递归到规模小于等于3的时候直接使用枚举算法解决
    if (size <= 3) {
        return bruteForceClosestPairTriangles(tempTriangles);
    }
    //先分为左右两部分，计算出两部分的最小值
    int mid = size / 2;
    double midX = tempTriangles[mid].left();
    vector<Triangle> tempLeftTriangles,tempRightTriangles;
    for (int i = 0; i < size; ++i) {
        if (tempTriangles[i].left()<=midX) tempLeftTriangles.push_back(tempTriangles[i]);
        if (tempTriangles[i].right()>=midX) tempRightTriangles.push_back(tempTriangles[i]);
    }
    if (tempLeftTriangles.size() == size || tempRightTriangles.size()==size){
        return divideClosestPairStripTriangles(tempTriangles);
    }
    sort(tempLeftTriangles.begin(),tempLeftTriangles.end(), compareTriangleLeftX);
    sort(tempRightTriangles.begin(),tempRightTriangles.end(), compareTriangleLeftX);
    pair<Triangle, Triangle> leftClosestTrianglePair = divideClosestPairTriangles(tempLeftTriangles);//递归调用自己
    pair<Triangle, Triangle> rightClosesTrianglePair = divideClosestPairTriangles(tempRightTriangles);
    double delta = min(trianglesDistance(leftClosestTrianglePair.first, leftClosestTrianglePair.second),
                       trianglesDistance(rightClosesTrianglePair.first, rightClosesTrianglePair.second));
    //再计算中线附近垂直带状区域
    vector<Triangle> strip;
    for (const Triangle &t: tempTriangles) {
        if (!(t.left()-midX>delta || midX-t.right()>delta)) {
            strip.push_back(t);
        }
    }
    try {
        //根据y排列
        sort(strip.begin(), strip.end(), compareTriangleBottomY);
        pair<Triangle, Triangle> stripClosestTrianglesPair = divideClosestPairStripTriangles(strip);
        if (trianglesDistance(stripClosestTrianglesPair.first, stripClosestTrianglesPair.second) < delta) {
            return stripClosestTrianglesPair;
        }
    }catch (exception e){}
    return (trianglesDistance(leftClosestTrianglePair.first, leftClosestTrianglePair.second) <
    trianglesDistance(rightClosesTrianglePair.first, rightClosesTrianglePair.second)) ?
    leftClosestTrianglePair :
    rightClosesTrianglePair;
}
//枚举算法
pair<Triangle, Triangle> TriangleManagement::bruteForceClosestPairTriangles(const vector<Triangle>& tempTriangles)const{
    int size = triangles.size();
    if (size <= 1){
        throw myExpection("三角形太少");
    }
    double minDistance = numeric_limits<double>::infinity();
    pair<Triangle, Triangle> closestTrianglePair;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            double distance = trianglesDistance(triangles[i], triangles[j]);
            if (distance < minDistance) {
                minDistance = distance;
                closestTrianglePair = make_pair(triangles[i], triangles[j]);
            }
            if (minDistance == 0) return closestTrianglePair;
        }
    }
    return closestTrianglePair;
}
//遍历时间下限
void TriangleManagement::travelAllTriangles()const{
    int size = triangles.size();
    if (size <= 1){
        throw myExpection("三角形太少");
    }
    for (int i = 0;i<size-1;i++) {
        trianglesDistance(triangles[i],triangles[i+1]);
    }
}

////小工具
//输入n
int TriangleManagement::inputTriangleN(){
    cout<<"请输入三角形的个数:";
    int n=inputInt();
    while (n<=1){
        cout<<"三角形数量过少,请重新输入:"<<endl;
        n=inputInt();
    }
    cout<<"开始生成三角形数据..."<<endl;
    return n;
}
//比较插入三角形后是否相交
bool TriangleManagement::isTriangleOverlapOn(const Triangle& newTempTriangle,const vector<Triangle>& tempTriangles)const{
    for (const auto& tempTriangle : tempTriangles) {
        if (isTriangleOverlap(newTempTriangle, tempTriangle)) {
            return true;
        }
    }
    return false;
}