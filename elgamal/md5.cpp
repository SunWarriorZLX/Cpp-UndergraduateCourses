#include "md5.h"

/*四个基本逻辑函数*/
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x)<<(n))|((x)>>(32-(n))))/*循环左移位*/

/*常数表T*/
const unsigned int T[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613,
                            0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
                            0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,
                            0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                            0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122,
                            0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
                            0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
                            0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb,
                            0xeb86d391

};

/*左循环移动位数*/
const int S[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
                   5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
                   21, 6, 10, 15, 21, 6, 10, 15, 21
};

/*四个MD缓冲区的初始值*/
const unsigned int InitialA = 0x67452301, InitialB = 0xEFCDAB89, InitialC = 0x98BADCFE, InitialD = 0x10325476;

const string HEX = "0123456789ABCDEF";

md5::md5(string &Plaintext) {
    group_nums = ((Plaintext.length() + 1) / 64) + 1;
    padded = Padding(Plaintext);
    A = 0, B = 0, C = 0, D = 0;
};

/*对消息填充*/
unsigned int *md5::Padding(string &Plaintext) {
    unsigned int num = ((Plaintext.length() + 8) / 64) + 1;
    unsigned int *_padded = new unsigned int[num * 16];
    for (int i = 0; i < num * 16; i++)
        _padded[i] = 0;
    for (unsigned i = 0; i < Plaintext.length(); i++) {
        _padded[i / 4] = ((unsigned int) Plaintext[i] << ((i % 4) * 8)) | _padded[i / 4];
    }
    _padded[Plaintext.length() / 4] = (0x80 << ((Plaintext.length() % 4) * 8)) | _padded[Plaintext.length() / 4];
    unsigned long length = Plaintext.length() * 8;/*用64位类型保存消息长度，相当于将消息长度对2^64取模*/
    _padded[num * 16 - 2] = (unsigned int) (length & 0x00000000FFFFFFFF);/*小端对齐，低字节保存低位*/
    _padded[num * 16 - 1] = (unsigned int) ((length & 0xFFFFFFFF00000000) >> 16);/*高位*/
    return _padded;
};

/*轮处理*/
void md5::Loop(unsigned int X[], int group) {
    unsigned int k, temp, f;
    unsigned int a = A, b = B, c = C, d = D;
    for (unsigned int i = 0; i < 64; i++) {
        if (i < 16) {
            f = F(B, C, D);
            k = i;
        } else if (i < 32) {
            f = G(B, C, D);
            k = (5 * i + 1) % 16;
        } else if (i < 48) {
            f = H(B, C, D);
            k = (3 * i + 5) % 16;
        } else {
            f = I(B, C, D);
            k = (7 * i) % 16;
        }
        k += 16 * group;
        temp = D;
        D = C;
        C = B;
        B = B + ROTATE_LEFT((A + f + X[k] + T[i]), S[i]);
        A = temp;
    }
    A += a;
    B += b;
    C += c;
    D += d;
}

string md5::getMD5() {
    cout << "--------------- MD5 ----------------" << endl;
    A = InitialA;
    B = InitialB;
    C = InitialC;
    D = InitialD;
    for (int i = 0; i < group_nums; i++) {
        Loop(padded, i);
    }
    MD5 = TransformToString(A) + TransformToString(B) + TransformToString(C) + TransformToString(D);
    cout << "MD5:";
    cout << MD5 << endl;
    cout << "------------ finished --------------" << endl;
    return MD5;
}

string md5::TransformToString(unsigned int a) {
    int b;
    string str1;
    string str = "";
    for (int i = 0; i < 4; i++) {
        str1 = "";
        b = ((a >> i * 8) % (1 << 8)) & 0xff;   //逆序处理每个字节
        for (int j = 0; j < 2; j++) {
            str1.insert(0, 1, HEX[b % 16]);
            b = b / 16;
        }
        str += str1;
    }
    return str;
}

md5::~md5() {
    delete[]padded;
}


