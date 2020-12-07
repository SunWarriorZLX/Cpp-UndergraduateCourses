#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <algorithm>
#include <map>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "Huffman_Code.h"
#include "Fano_Code.h"

//请不要同时定义Huffman和Fano

/*

//启用霍夫曼编码
#ifndef Huffman
#define Huffman
#endif
*/



//启用费诺编码
#ifndef Fano
#define Fano
#endif



using namespace cv;
using namespace std;

void WriteCodeResultToTxt(map<unsigned char, string> table, Mat m);

void WriteCodeResultToDat(map<unsigned char, string> table, Mat m);

void Decode(map<string, unsigned char> intable, Mat m);

string GetBinary(unsigned char ch);


int main() {
    Mat im = imread("/Users/zhanglixuan/Desktop/lena.bmp", IMREAD_COLOR);
    Mat im2(im.size(), CV_8UC3);
    double m[256] = {0};//每个信源符号出现的次数（概率）
    vector<HuffNode *> mart;
    vector<Source> source;
    map<unsigned char, string> codeTable;//编码表
    map<string, unsigned char> InCodeTable;//译码表

    /*计算每一个信源符号出现的概率*/
    for (int Col = 0; Col < im.cols; Col++)
        for (int Row = 0; Row < im.rows; Row++)
            for (int Depth = 0; Depth < im.channels(); Depth++) {
                m[im.at<Vec3b>(Col, Row)[Depth]]++;
            }
    for (int i = 0; i < 256; i++)
        m[i] /= (im.total() * im.channels());

    /*为每一个信源符号初始化一个叶子节点*/
    for (int i = 0; i < 256; i++) {
        HuffNode *temp = new HuffNode;
        Source temp2;
        temp->right = NULL;
        temp->left = NULL;
        temp->s = i;            //叶子节点的s为信源符号（0-255），根结点s为-1
        temp->weight = m[i];    //叶子节点的配重为对应信源符号的出现次数（概率）
        temp2.weight = m[i];
        temp2.s = i;
        temp2.code = "";
        mart.push_back(temp);
        source.push_back(temp2);
    }

#ifdef Huffman
    //霍夫曼编码
    BuildHffTree(mart);//建立霍夫曼树
    GetCodeTable(codeTable, InCodeTable, mart[0]);//通过霍夫曼树获取编码表和译码表
    GetCodingEfficiency(codeTable, m);
    WriteCodeResultToDat(codeTable, im);    //将图像编码并写入文件
    Decode(InCodeTable, im2);               //译码
#endif

#ifdef Fano
    //费诺编码
    GetCodeTable_Fano(codeTable, InCodeTable, source, 0, source.size(), 1);
    GetCodingEfficiency(codeTable, m);
    WriteCodeResultToDat(codeTable, im);
    Decode(InCodeTable, im2); //译码
#endif

    imshow("Decode", im2);
    waitKey(0);
    destroyAllWindows();
    return 0;
}

//通过已有的编码映射方法，对图片编码，并写入.txt文件
void WriteCodeResultToTxt(map<unsigned char, string> table, Mat m) {
    ofstream fo;
    fo.open("/Users/zhanglixuan/CLionProjects/OpenCV_Demo/HufCodeResult.txt", ios::out | ios::app);
    if (!fo.is_open()) {
        cout << "txt file open error";
        exit(0);
    }
    map<unsigned char, string>::iterator p;
    string buffer = "";
    for (int Col = 0; Col < m.cols; Col++)
        for (int Row = 0; Row < m.rows; Row++)
            for (int Depth = 0; Depth < m.channels(); Depth++) {
                buffer += table[m.at<Vec3b>(Col, Row)[Depth]];
                while (buffer.size() >= 8) {
                    unsigned char ch = 0;
                    for (int i = 0; i < 8; i++) {
                        ch = ch * 2;
                        ch = ch + (buffer[i] - '0');
                    }
                    buffer.erase(0, 8);
                    cout << ch;
                    fo << ch;
                }
            }
    if (!buffer.empty()) {
        while (buffer.size() != 8)
            buffer += '0';
        unsigned char ch = 0;
        for (int i = 0; i < 8; i++) {
            ch = ch * 2;
            ch = ch + (buffer[i] - '0');
        }
        cout << ch;
        fo << ch;
    }
    fo.close();
}

//通过已有的编码映射方法，对图片编码，并写入.dat文件
void WriteCodeResultToDat(map<unsigned char, string> table, Mat m) {
    map<unsigned char, string>::iterator p;
    ofstream fo;

    /**************************打开文件**************************/
    fo.open("/Users/zhanglixuan/CLionProjects/OpenCV_Demo/HufCodeResult.dat", ios::out | ios::trunc);
    if (!fo.is_open()) {
        cout << "dat file open error";
        exit(0);
    }
    /**************************打开文件**************************/


    string buffer = "";
    for (int Col = 0; Col < m.cols; Col++)
        for (int Row = 0; Row < m.rows; Row++)
            for (int Depth = 0; Depth < m.channels(); Depth++) {
                buffer += table[m.at<Vec3b>(Col, Row)[Depth]];//先将信源符号->二进制编码的映射结果存储到缓冲区buffer

//                cout << m.at<Vec3b>(Col, Row)[Depth] << " " << table[m.at<Vec3b>(Col, Row)[Depth]] << endl;

                /* 每次截取buffer中8个字节（即8位二进制数），计算出该8位二进制数对应的 unsigned char，输出至.dat文件 */
                while (buffer.size() >= 8) {
                    unsigned char ch = 0;
                    for (int i = 0; i < 8; i++) {
                        ch = ch * 2;
                        ch = ch + (buffer[i] - '0');
                    }
                    buffer.erase(0, 8);
//                    cout << ch;
                    fo << ch;
                }
            }

    //处理buffer中剩下的二进制编码
    if (!buffer.empty()) {
        while (buffer.size() != 8)
            buffer += '0';
        unsigned char ch = 0;
        for (int i = 0; i < 8; i++) {
            ch = ch * 2;
            ch = ch + (buffer[i] - '0');
        }
//        cout << ch;
        fo << ch;
    }
    fo.close();
}

//译码
void Decode(map<string, unsigned char> intable/*译码表(编码表的逆映射)*/, Mat m) {
    ifstream fin;

    /**************************打开文件**************************/
    fin.open("/Users/zhanglixuan/CLionProjects/OpenCV_Demo/HufCodeResult.dat", ios::beg | ios::in);
    if (!fin.is_open()) {
        cout << "dat file open error";
        exit(0);
    }
    /**************************打开文件**************************/

    bool flag;
    unsigned char ch;
    string buffer1 = "";
    string buffer2 = "";
    for (int Col = 0; Col < m.cols; Col++)
        for (int Row = 0; Row < m.rows; Row++)
            for (int Depth = 0; Depth < m.channels(); Depth++) {
                int i = 0;
                flag = false;
                while (!flag) {
                    fin >> noskipws >> ch;
//                    cout << ch;
                    buffer1 += GetBinary(ch);
                    for (; i < buffer1.size(); i++) {
                        buffer2 += buffer1[i];
                        if (intable.find(buffer2) != intable.end()) {
                            m.at<Vec3b>(Col, Row)[Depth] = intable[buffer2];
                            buffer1.erase(0, i + 1);
                            buffer2.clear();
                            flag = true;
                            break;
                        }
                    }
                }
            }
    fin.close();
}

/* unsigned char->8位'0'、'1'字符串 */
string GetBinary(unsigned char ch) {
    string result;
    int i = 8;  //排除高位为多个0的情况，设置循环次数为8
    while (i) {
        result += ch % 2 + '0';
        ch /= 2;
        i--;
    }
    reverse(result.begin(), result.end());
    return result;
}