#include "aes.h"
#include <iostream>

using std::cout;
using std::endl;
byte GF28Mul(byte multiplier, byte multiplicand) {
    byte result = 0;
    for (int i = 0; i < 8; i++) {
        if (multiplier & 1)
            result = result ^ (multiplicand << i);
        multiplier = multiplier >> 1;
    }
    return result;
}
int main() {
    int b[4];
    b[0]=GF28Mul(0x03,0x4d);
    b[1]=GF28Mul(0x01,0x93);
    b[2]=GF28Mul(0x01,0xfc);
    b[3]=GF28Mul(0x02,0xc8);
    b[0]=b[0]^b[1]^b[2]^b[3];
    cout<<hex<<b[0];
}