//
// Created by AlexGrandbell on 2023.11.02.
//

#ifndef FAMILY_TREE_TOOL_H
#define FAMILY_TREE_TOOL_H
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>
using namespace std;

//异常处理
class myExpection:public exception{
public:
    myExpection(const char* message):errorMessage(message){}
    const char * what() const noexcept override{
        return errorMessage.c_str();
    }
private:
    string errorMessage;
};

//工具
double inputDouble();
int inputInt();
string inputString();
double doubleNumberTest(string);
int intNumberTest(string);
void exitTest(string);
int generateRandomInt(int,int);
int getDigitCount(int);
void progressBar(int,int);
double randomDouble(double=0.0,double=100.0);

#endif //FAMILY_TREE_TOOL_H
