#ifndef ELGAMAL_MD5_H
#define ELGAMAL_MD5_H

#include <string>
#include <iostream>

using namespace std;

class md5 {
private:
    unsigned int *padded;
    unsigned int group_nums;
    unsigned int A, B, C, D;
    string MD5;
public:
    md5(string &Plaintext);

    unsigned int *Padding(string &Plaintext);//填充函数
    void Loop(unsigned int X[], int group);//轮处理
    string getMD5();

    string TransformToString(unsigned int s);//将结果转换为字符串
    ~md5();
};

#endif