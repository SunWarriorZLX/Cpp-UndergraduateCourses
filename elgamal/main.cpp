#include <iostream>
#include <string>
#include "md5.h"
#include "elgamal.h"

using namespace std;

int main() {
    string message;
    string MD5;
    cout << "Please input message:" << endl;
    cin >> message;
    /*计算HASH值*/
    md5 a(message);
    cout << "message:" << message<<endl;
    MD5 = a.getMD5();
    /*计算HASH值*/

    /*elgamal签名*/
    vector<unsigned long int> key;
    elgamal b;
    key=b.Sign(MD5);
    /*elgamal签名*/

    /*elgamal签名验证*/
    b.test(key,MD5);
    /*elgamal签名验证*/

    return 0;
}