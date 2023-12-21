//
// Created by 沈嘉瑞 on 2023.12.21.
//

#include "Management.h"

//用户界面
void Management::Welcome(){
    cout << "\n欢迎使用" << endl;
    cout<<"你可以随时输入'q'来退出某个当前操作。"<<endl;
    cout<<"----------任意输入以开始----------"<<endl;
    inputString();
}
void Management::DoMenu(){
    int nSelection = -1;
    do {
        cout<<"\n ------最近对问题菜单------"<<endl;
        cout<<" 1.最近点对问题"<<endl;
        cout<<" 2.最近线段对问题"<<endl;
        cout<<" 3.最近三角形对问题"<<endl;
        cout<<" 0.退出当前程序"<<endl;
        cout<<" -----------------------"<<endl;
        cout<<"请选择菜单项编号(0-3):";
        nSelection = -1;
        try {
            nSelection = inputInt();
            switch (nSelection) {
                case 1: {
                    DoPoinit();
                    break;
                }
                case 2: {
                    DoLineSegment();
                    break;
                }
                case 3:{
                    DoTriangle();
                    break;
                }
                case 0: {
                    ExitApp();
                    return;
                }
                default: {
                    cout<<"您输入的序号错误。";
                    break;
                }
            }
        } catch (const exception &e) {
            cout << e.what() << endl;
        }
        if (nSelection != 0) {
            cout<<"继续操作请按1，关闭程序请按0:";
            fflush(stdin);//清除输入流缓存
            nSelection = -1;
            try {
                nSelection = inputInt();
                if (nSelection == 0) {
                    ExitApp();
                }
            }catch  (const exception& e){
                cout<<e.what()<<endl;
            }
        }
    } while (nSelection != 0);
}

////三种形状选择二级菜单
void Management::DoPoinit(){
    int nSelection = -1;
    do {
        cout<<"\n -----最近点对问题菜单-----"<<endl;
        cout<<" 1.输入新点集数据"<<endl;
        cout<<" 2.输出所有点集数据"<<endl;
        cout<<" 3.查找最近点对"<<endl;
        cout<<" 0.退出当前菜单层"<<endl;
        cout<<" -----------------------"<<endl;
        cout<<"请选择菜单项编号(0-3):";
        nSelection = -1;
        try {
            nSelection = inputInt();
            switch (nSelection) {
                case 1: {
                    inputPointsMenu();
                    break;
                }
                case 2: {
                    outputPointsMenu();
                    break;
                }
                case 3:{
                    closestPointPairMenu();
                    break;
                }
                case 0: {
                    return;
                }
                default: {
                    cout<<"您输入的序号错误。";
                    break;
                }
            }
        } catch (const exception &e) {
            cout << e.what() << endl;
        }
        if (nSelection != 0) {
            cout<<"继续操作请按1，退出当前菜单层请按0:";
            fflush(stdin);//清除输入流缓存
            nSelection = -1;
            try {
                nSelection = inputInt();
                if (nSelection == 0) {
                    return;
                }
            }catch  (const exception& e){
                cout<<e.what()<<endl;
            }
        }
    } while (nSelection != 0);
}
void Management::DoLineSegment(){}
void Management::DoTriangle(){

}
void Management::ExitApp(){
    cout<<"\n欢迎再次使用，再见。"<<endl;
}

//////二级菜单
////点二级菜单
//输入点集
void Management::inputPointsMenu(){
    cout<<"\n请选择输入点集的方法(0-自动输入,1-自动输入):";
    try {
        switch (inputInt()) {
            case 0: {
                pointManagement.AutoUpdatePoints();
                break;
            }
            case 1: {
                pointManagement.InputUpdatePoints();
                break;
            }
            default: {
                cout<<"您输入的序号错误。";
                return;
            }
        }
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
    return;
}
//输出点集
void Management::outputPointsMenu() {
    cout<<"\n请选择输出点集的方法(0-输出到文件,1-输出到控制台):";
    try {
        switch (inputInt()) {
            case 0: {
                pointManagement.OutputPointsToFile();
                break;
            }
            case 1: {
                pointManagement.OutputPointsToScreen();
                break;
            }
            default: {
                cout<<"您输入的序号错误。";
                return;
            }
        }
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
    return;
}
//最近点对
void Management::closestPointPairMenu(){
    cout<<"\n查找最近点对的算法有\n";
    cout<<"1.分治法(O(nlogn))"<<endl;
    cout<<"2.优化的算法(O(n))"<<endl;
    cout<<"3.枚举法(O(n^2))"<<endl;
    cout<<"4.都来一遍"<<endl;
    cout<<"请选择:"<<endl;
    try {
        switch (inputInt()) {
            case 1: {
                pointManagement.DividePoint();
                break;
            }
            case 2: {
                pointManagement.MyPointAlgorithm();
                break;
            }
            case 3:{
                pointManagement.BruteForcePoint();
                break;
            }
            case 4:{
                pointManagement.DividePoint();
                cout<<endl;
                pointManagement.MyPointAlgorithm();
                cout<<endl;
                pointManagement.BruteForcePoint();
                break;
            }
            default: {
                cout<<"您输入的序号错误。";
                return;
            }
        }
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
    return;
}

////线段二级菜单
//输入线段集
void Management::inputLineSegmentsMenu(){}
//输出线段集
void Management::outputLineSegmentsMenu() {}
//最近线段对
void Management::closestLineSegmentPairMenu(){}

////三角形二级菜单
//输入三角形集
void Management::inputTrianglesMenu(){}
//输出三角形集
void Management::outputTrianglesMenu() {}
//最近三角形对
void Management::closestTrianglePairMenu(){}