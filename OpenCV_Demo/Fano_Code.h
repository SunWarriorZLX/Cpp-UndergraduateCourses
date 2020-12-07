//
// Created by 张力炫 on 2020/6/17.
//

#ifndef OPENCV_DEMO_FANO_CODE_H
#define OPENCV_DEMO_FANO_CODE_H

#include <string>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

struct Source {
    int s;          //信源符号
    double weight;  //概率
    string code;    //编码
};

bool compare(Source a, Source b);

void GetCodeTable_Fano(map<unsigned char, string> &CodeTable, map<string, unsigned char> &InCodeTable,
                       vector<Source> &source, int Begin, int End, double total);

#endif //OPENCV_DEMO_FANO_CODE_H
