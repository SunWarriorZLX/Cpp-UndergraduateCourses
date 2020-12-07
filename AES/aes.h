
#ifndef AES_AES_H
#define AES_AES_H

#include <iostream>
#include <iomanip>

#ifndef debug
#define debug
#endif
using std::cout;
using std::endl;
using std::hex;
using std::memcpy;
using std::setw;
using std::setfill;

typedef unsigned char byte;

class aes {
private:
    byte message[32];
    byte secret[32];
    byte messageMatrix[8][4];
    byte key[32];
    byte w[120][4];
    const int Nb; //消息长度
    const int Nk; //密钥长度
    const int Nr; //轮数

public:
    aes(const byte m[], const byte k[], int nb, int nk);

    void SubBytes(byte m[], int n);                   //字节替代
    void SubBytes(byte state[][4]);                   //字节替代
    void InverseSubBytes(byte state[][4]);            //逆S盒变换
    void ShiftRows(byte state[][4]);                  //行移位
    void InverseShiftRows(byte state[][4]);           //逆行移
    void MixColumns(byte state[][4]);                 //列混淆
    void InverseMixColumns(byte state[][4]);          //逆列混淆
    void KeyExpansion();                              //密钥扩展
    byte GF28Mul(byte multiplier, byte multiplicand); //GF(2^8)乘法
    void RotByte(byte q[]);                           //列移位
    void AddRoundKey(byte state[][4], byte W[4]);   //轮密钥加
    const int GetRounds(int nk, int nb);                    //确认Nr
    void print(byte state[][4], int begins = 0);

    void printS();

    void print();

    void encrypt(); //加密
    void decrypt(); //解密
    ~aes();
};

#endif
