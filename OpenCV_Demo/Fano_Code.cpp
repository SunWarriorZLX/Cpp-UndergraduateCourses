//
// Created by 张力炫 on 2020/6/17.
//

#include "Fano_Code.h"

bool compare(Source a, Source b) {
    return a.weight > b.weight;
}

//构建费诺编码表
void GetCodeTable_Fano(map<unsigned char, string> &CodeTable, map<string, unsigned char> &InCodeTable,
                       vector<Source> &source, int Begin, int End, double total) {
    if (End - Begin == 2)
    {
        source[Begin].code += '0';
        source[Begin + 1].code += '1';
        CodeTable[source[Begin].s] = source[Begin].code;
        CodeTable[source[Begin + 1].s] = source[Begin + 1].code;
        InCodeTable[source[Begin].code] = source[Begin].s;
        InCodeTable[source[Begin + 1].code] = source[Begin + 1].s;
        return;
    }
    if (End - Begin == 1) //解决部分信源符号概率过大的情况
    {
        CodeTable[source[Begin].s] = source[Begin].code;
        InCodeTable[source[Begin].code] = source[Begin].s;
        return;
    }
    sort(source.begin() + Begin, source.begin() + End, compare);
    double temp = 0;
    int Boundary;

    //从上往下累加，直到累加和大于总概率的二分之一，然后比较"大于二分之一"和"小于二分之一"的距离，选择更接近二分之一的结果
    for (int i = Begin; i < End; i++) {
        temp = temp + source[i].weight;
        if (temp >= total / 2) {
            if (fabs(temp - source[i].weight - total / 2) >= fabs(temp - total / 2))
                Boundary = i + 1;
            else if (fabs(temp - source[i].weight - total / 2) < fabs(temp - total / 2)) {
                Boundary = i;
                temp = temp - source[i].weight;
                break;
            }
        }
    }
    for (int i = Begin; i < Boundary; i++)
        source[i].code += '0';
    for (int i = Boundary; i < End; i++)
        source[i].code += '1';
    GetCodeTable_Fano(CodeTable, InCodeTable, source, Begin, Boundary, temp);
    GetCodeTable_Fano(CodeTable, InCodeTable, source, Boundary, End, total - temp);
}