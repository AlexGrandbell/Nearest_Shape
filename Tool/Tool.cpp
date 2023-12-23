//
// Created by AlexGrandbell on 2023.11.02.
//

#include "Tool.h"

double inputDouble(){
    return doubleNumberTest(inputString());
}

int inputInt(){
    return intNumberTest(inputString());
}

string inputString(){
    string tmp;
    fflush(stdin);
    cin>>tmp;
    exitTest(tmp);
    return tmp;
}

//double转换
double doubleNumberTest(string num){
    double tempDouble = 0;
    istringstream iss(num);
    if (iss >> tempDouble) {
        return tempDouble;
    } else {
        throw myExpection("在需要输入小数的地方输入的不是一个数字，操作失败！");
    }
};

int intNumberTest(string num){
    int tempDouble = 0;
    std::istringstream iss(num);
    if (iss >> tempDouble) {
        return tempDouble;
    } else {
        throw myExpection("在需要输入整数的地方输入的不是一个数字，操作失败！");
    }
}

//随机整数
int generateRandomInt(int low,int high) {
    // 使用随机设备生成种子
    random_device rd;
    // 使用 mt19937 引擎和生成的种子初始化随机数生成器
    mt19937 gen(rd());
    // 定义均匀分布
    uniform_int_distribution<> dis(low, high);

    // 生成随机整数
    int randomInt = dis(gen);
    return randomInt;
}

//整数位数
int getDigitCount(int number) {
    // 将整数转换为字符串
    string numberString = to_string(abs(number));
    // 获取字符串的长度，即位数
    int digitCount = static_cast<int>(numberString.length());
    return digitCount;
}

void exitTest(string s){
    if (s == "q"){
        throw myExpection("已手动退出进程。");
    }
}

void progressBar(int i,int num){
    if (i == num-1){
        cout<<"\n";
        cout.flush();
    } else if (i == (int)(num * 0.9)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.8)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.7)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.6)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.5)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.4)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.3)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.2)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.1)){
        cout<<"_";
        cout.flush();
    } else if (i == (int)(num * 0.05)){
        cout<<"_";
        cout.flush();
    }
}
//随机数构建器
random_device rd;
mt19937 gen(rd());

double randomDouble(double low,double high){
    uniform_real_distribution<double> dis(low, high);
    return dis(gen);
}