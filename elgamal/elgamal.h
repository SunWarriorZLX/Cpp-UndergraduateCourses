#ifndef ELGAMAL_ELGAMAL_H
#define ELGAMAL_ELGAMAL_H

#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

class elgamal {
private:
    int p;//大素数
    int g;//生成元
    int x;//用户密钥
    int y;//用户公钥
    int k;//随机数k
    int Inck;//k的逆元
public:
    elgamal();

    ~elgamal();

    bool IsPrime(int num);//判断素数
    bool IsPrimitive(int G, int m);//判断是否为原根
    int QuickMod(unsigned long b, int n, int m, unsigned long result = 1);//模重复平方根算法
    int QuickMod(unsigned long b, string H, int m);//模重复平方根(Hash)
    int ExGCD(int a, int b, int &x, int &y);//拓展GCD求逆元,x是a的逆元
    vector<int> Factorization(int n);//分解质因数
    int GetHex(char s);//字符转16进制数字
    int mod(string s, int m);//大数取模，默认从左到右->高位到低位
    vector<unsigned long int> Sign(string H);//签名
    unsigned long GetS(string H,unsigned long r,unsigned long InK);
    bool test(vector<unsigned long int> key, string H);//验证签名
};


#endif //ELGAMAL_ELGAMAL_H
