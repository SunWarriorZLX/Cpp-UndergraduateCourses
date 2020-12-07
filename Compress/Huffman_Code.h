//
// Created by 张力炫 on 2020/6/1.
//

/*
    功能：通过给出的 "信源符号-该符号的概率" ，
    计算每个信源符号对应的霍夫曼编码结果，
    返回一个 "信源符号-霍夫曼编码" 的映射方法。
*/


#ifndef OPENCV_DEMO_HUFFMAN_CODE_H
#define OPENCV_DEMO_HUFFMAN_CODE_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;

//霍夫曼节点
struct HuffNode {
    double weight;          //信源符号的概率
    HuffNode *left, *right; //左右叶子节点
    int s;                  //信源符号
    string code;            //该信源符号的编码
};

bool compare(const HuffNode *a, const HuffNode *b);

void BuildHffTree(vector<HuffNode *> &source);

void buildHffTree(vector<HuffNode *> &source);

void print(map<unsigned char, string> CodeTable);

double GetAverageCodeLength(map<unsigned char, string> CodeTable, double *M/*概率矩阵*/);

double GetCodingEfficiency(map<unsigned char, string> CodeTable, double *M/*概率矩阵*/);

void print(vector<HuffNode *> source);

void GetCodeTable(map<unsigned char, string> &CodeTable, map<string, unsigned char> &InCodeTable, HuffNode *source);

bool IsUnique(map<unsigned char, string> &CodeTable);

#endif //OPENCV_DEMO_HUFFMAN_CODE_H
