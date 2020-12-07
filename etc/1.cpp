#ifndef ELGAMAL_ELGAMAL_H
#define ELGAMAL_ELGAMAL_H

#include <cmath>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class elgamal {
private:
    unsigned int p;//大素数
    unsigned int g;//生成元
    unsigned int x;//用户密钥
    unsigned int y;//用户公钥
    unsigned int k;//随机数k
    unsigned int Inck;//k的逆元
public:
    elgamal();

    ~elgamal();

    bool IsPrime(unsigned int num);//判断素数
    bool IsPrimitive(unsigned int g, unsigned int m);//判断是否为原根
    unsigned int QuickMod(unsigned int b, unsigned int n, unsigned int m, unsigned int result = 1);//模重复平方根算法
    unsigned int QuickMod(unsigned int b,string H,unsigned int m);//模重复平方根(Hash)
    unsigned int ExGCD(unsigned int a, unsigned int b, unsigned int &x, unsigned int &y);//拓展GCD求逆元,x是a的逆元
    vector<unsigned int> Factorization(unsigned int n);//分解质因数
    unsigned int GetHex(char s);//字符转16进制数字
    unsigned int mod(string s, unsigned int m);//大数取模，默认从左到右->高位到低位
    vector<unsigned int> Sign(string H);//签名
    bool test(vector<unsigned int> key,string H);//验证签名
};


#endif //ELGAMAL_ELGAMAL_H
