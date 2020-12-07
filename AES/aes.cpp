#include "aes.h"

//s盒
const byte sBox[] = {
        /* 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f     */
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, /*0*/
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, /*1*/
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, /*2*/
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, /*3*/
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, /*4*/
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, /*5*/
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, /*6*/
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, /*7*/
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, /*8*/
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, /*9*/
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, /*a*/
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, /*b*/
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, /*c*/
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, /*d*/
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, /*e*/
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  /*f*/
};

//逆 s 盒
const byte InverseSBox[] = {
        /* 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f     */
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, /*0*/
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, /*1*/
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, /*2*/
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, /*3*/
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, /*4*/
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, /*5*/
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, /*6*/
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, /*7*/
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, /*8*/
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, /*9*/
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, /*a*/
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, /*b*/
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, /*c*/
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, /*d*/
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, /*e*/
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d  /*f*/
};

//列混淆矩阵
const byte MixCol[][4] = {
        02, 03, 01, 01,
        01, 02, 03, 01,
        01, 01, 02, 03,
        03, 01, 01, 02};

//逆列混淆矩阵
const byte InverseMixCol[][4] = {
        0x0e, 0x0b, 0x0d, 0x09,
        0x09, 0x0e, 0x0b, 0x0d,
        0x0d, 0x09, 0x0e, 0x0b,
        0x0b, 0x0d, 0x09, 0x0e};

//异或轮常数
byte Rcon[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36};

aes::aes(const byte m[], const byte k[], int nb, int nk) : Nk(nk), Nb(nb), Nr(GetRounds(nk, nb)) {
    memcpy(message, m, 4 * Nb);
    memcpy(key, k, 4 * Nk);
    KeyExpansion();
    //初始化 messageMatrix 矩阵
    for (int i = 0; i < Nb; i++)
        for (int j = 0; j < 4; j++)
            messageMatrix[i][j] = message[4 * i + j];
}

const int aes::GetRounds(int nk, int nb) //确定轮数
{
    switch (nk) {
        case 8:
            return 14;
        case 6:
            if (nb == 8)
                return 14;
            else
                return 12;
        case 4:
            return nk + nb + 2;
        default:
            return -1;
    }
}

//GF(2^8)乘法
byte aes::GF28Mul(byte multiplier, byte multiplicand) {
    byte result = 0;
    for (int i = 0; i < 8; i++) {
        if (multiplier & 1)
            result = result ^ (multiplicand << i);
        multiplier = multiplier >> 1;
    }
    return result;
}

//字节替代
void aes::SubBytes(byte m[], int n) {
    for (int i = 0; i < n; i++)
        m[i] = sBox[m[i]];
}

//字节替代
void aes::SubBytes(byte state[][4]) {
    for (int i = 0; i < Nb; i++)
        for (int j = 0; j < 4; j++)
            state[i][j] = sBox[state[i][j]];
}

//逆S盒变换
void aes::InverseSubBytes(byte state[][4]) {
    for (int i = 0; i < Nb; i++)
        for (int j = 0; j < 4; j++)
            state[i][j] = InverseSBox[state[i][j]];
}

//行移位
void aes::ShiftRows(byte state[][4]) {
    int C[3] = {1, 2, 3};
    byte *temp = new byte[Nb];
    if (Nb == 8) {
        C[1] = 3;
        C[2] = 4;
    }
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < Nb; j++)
            /*temp[(j + Nb - C[i - 1]) % Nb] = state[i][j];*/
            temp[(j + C[i - 1]) % Nb] = state[j][i];
        for (int j = 0; j < Nb; j++)
            state[j][i] = temp[j];
    }
    delete[] temp;
}

//逆行移位
void aes::InverseShiftRows(byte state[][4]) {
    int C[3] = {1, 2, 3};
    byte *temp = new byte[Nb];
    if (Nb == 8) {
        C[1] = 3;
        C[2] = 4;
    }
    for (int i = 1; i < 4; i++) {
        for (int j = 0; j < Nb; j++)
/*            temp[j] = state[i][(j + Nb - C[i - 1]) % Nb];*/
            temp[(j + Nb - C[i - 1]) % Nb] = state[j][i];
        for (int j = 0; j < Nb; j++)
            state[j][i] = temp[j];
    }
    delete[] temp;
}

//列移位
void aes::RotByte(byte q[]) {
    byte temp = q[0];
    q[0] = q[1];
    q[1] = q[2];
    q[2] = q[3];
    q[3] = temp;
}

//列混淆
void aes::MixColumns(byte state[][4]) {
    byte b[4] = {0};
    for (int i = 0; i < Nb; i++) {
        b[0] = b[1] = b[2] = b[3] = 0;
        for (int j = 0; j < 4; j++) {
            b[0] = GF28Mul(MixCol[0][j], messageMatrix[i][j]) ^ b[0];
            b[1] = GF28Mul(MixCol[1][j], messageMatrix[i][j]) ^ b[1];
            b[2] = GF28Mul(MixCol[2][j], messageMatrix[i][j]) ^ b[2];
            b[3] = GF28Mul(MixCol[3][j], messageMatrix[i][j]) ^ b[3];
        }
        for (int j = 0; j < 4; j++)
            messageMatrix[i][j] = b[j];
    }
}

//逆列混淆
void aes::InverseMixColumns(byte state[][4]) {
    byte b[4] = {0};
    for (int i = 0; i < Nb; i++) {
        b[0] = b[1] = b[2] = b[3] = 0;
        for (int j = 0; j < 4; j++) {
            b[0] = GF28Mul(InverseMixCol[0][j], messageMatrix[i][j]) ^ b[0];
            b[1] = GF28Mul(InverseMixCol[1][j], messageMatrix[i][j]) ^ b[1];
            b[2] = GF28Mul(InverseMixCol[2][j], messageMatrix[i][j]) ^ b[2];
            b[3] = GF28Mul(InverseMixCol[3][j], messageMatrix[i][j]) ^ b[3];
        }
        for (int j = 0; j < 4; j++)
            messageMatrix[i][j] = b[j];
    }
}

//密钥扩展
void aes::KeyExpansion() {
    byte temp[4];
    //填充w1-w4
    for (int i = 0; i < Nk; i++)
        for (int j = 0; j < 4; j++)
            w[i][j] = key[4 * i + j];
    for (int i = Nk; i < Nb * (Nr + 1); i++) {
        for (int j = 0; j < 4; j++)
            temp[j] = w[i - 1][j];
        if (i % Nk == 0) {
            RotByte(temp);
            SubBytes(temp, 4);
            for (int k = 0; k < 4; k++) {
                temp[k] = temp[k] ^ Rcon[(i / Nk) - 1];
            }
        } else if (i % 4 == 0 && Nk == 8) {
            SubBytes(temp, 4);
        }
        for (int j = 0; j < 4; j++)
            w[i][j] = w[i - Nk][j] ^ temp[j];
    }
}

//轮密钥加
void aes::AddRoundKey(byte state[][4], byte K[4]) {
    for (int i = 0; i < Nb; i++)
        for (int j = 0; j < 4; j++)
            state[i][j] = state[i][j] ^ K[j];
    //print(K);
}

void aes::print() {
    cout << "message: ";
    for (int i = 0; i < 4 * Nb; i++)
        cout << hex << setw(2) << setfill('0') << (int) message[i];
    cout << endl
         << "key: ";
    for (int i = 0; i < 4 * Nk; i++)
        cout << hex << setw(2) << setfill('0') << (int) key[i];
    cout << endl;
}

void aes::printS() {
    cout << "secret: ";
    for (int i = 0; i < 4 * Nb; i++)
        cout << hex << setw(2) << setfill('0') << (int) secret[i];
    cout << endl
         << "key: ";
    for (int i = 0; i < 4 * Nk; i++)
        cout << hex << setw(2) << setfill('0') << (int) key[i];
    cout << endl;
}

void aes::print(byte state[][4], int begins) {
    for (int i = 0; i < 4; i++) {
        for (int j = begins; j < begins + Nb; j++)
            cout << hex << setw(2) << setfill('0') << (int) state[j][i] << " ";
        cout << endl;
    }
}

//加密
void aes::encrypt() {
    cout << "-------------- encrypt --------------" << endl;
    print();
#ifdef debug
    cout << "-------------- round 0 --------------" << endl;
#endif
#ifdef debug
    cout << "message:" << endl;
    print(messageMatrix);
    cout << "round key 0:" << endl;
    print(w, 0);
#endif
    AddRoundKey(messageMatrix, w[0]);
#ifdef debug
    cout << "AddRoundKey:" << endl;
    print(messageMatrix);
#endif
    for (int i = 1; i <= Nr; i++) {
#ifdef debug
        cout << "-------------- round " << i << " --------------" << endl;
        cout << "message:" << endl;
        print(messageMatrix);
#endif
        SubBytes(messageMatrix);
#ifdef debug
        cout << "SubBytes:" << endl;
        print(messageMatrix);
#endif
        ShiftRows(messageMatrix);
#ifdef debug
        cout << "ShiftRows:" << endl;
        print(messageMatrix);
#endif
        if (i != Nr) {
            MixColumns(messageMatrix);
#ifdef debug
            cout << "MixColumns:" << endl;
            print(messageMatrix);
#endif
        }
#ifdef debug
        cout << "round key " << i << ":" << endl;
        print(w, i);
#endif
        AddRoundKey(messageMatrix, w[i]);
#ifdef debug
        cout << "AddRoundKey:" << endl;
        print(messageMatrix);
#endif
    }
    for (int i = 0; i < Nb; i++)
        for (int j = 0; j < 4; j++)
            secret[4 * i + j] = messageMatrix[i][j];
    cout << "------------ encrypt end -------------" << endl;
    printS();
}

//解密
void aes::decrypt() {
    cout << "------------- dencrypt --------------" << endl;
    printS();

    for (int i = Nr; i >= 1; i--) {
#ifdef debug
        cout << "-------------- round " << i << " --------------" << endl;
        cout << "message:" << endl;
        print(messageMatrix);

        cout << "round key " << i << ":" << endl;
        print(w, i);
#endif
        AddRoundKey(messageMatrix, w[i]);
#ifdef debug
        cout << "AddRoundKey:" << endl;
        print(messageMatrix);
#endif
        if (i != Nr) {
            InverseMixColumns(messageMatrix);
#ifdef debug
            cout << "InverseMixColumns:" << endl;
            print(messageMatrix);
#endif
        }
        InverseShiftRows(messageMatrix);
#ifdef debug
        cout << "InverseShiftRows:" << endl;
        print(messageMatrix);
#endif
        InverseSubBytes(messageMatrix);
#ifdef debug
        cout << "InverseSubBytes:" << endl;
        print(messageMatrix);
#endif
    }
    AddRoundKey(messageMatrix, w[0]);
    cout << "------------ dencrypt end ------------" << endl << "messageMatrix:" << endl;
    print(messageMatrix);
}

aes::~aes() {
}