#include <iostream>
#include <map>
#include <fstream>
#include <iomanip>
#include "Huffman_Code.h"

void LoadSource(map<unsigned char, double> &M, unsigned int &count, string &path);

void print(map<unsigned char, double> M);

void WriteCodeResultToDat(map<unsigned char, string> table, unsigned int count, string path);

void Decode(map<string, unsigned char> intable/*译码表(编码表的逆映射)*/, unsigned int count);

string GetBinary(unsigned char ch);

int main() {
    map<unsigned char, double> M;
    unsigned int count;
    string path;
    LoadSource(M, count, path);
    vector<HuffNode *> T;
    map<unsigned char, double>::iterator p;
    for (p = M.begin(); p != M.end(); p++) {
        HuffNode *temp = new HuffNode;
        temp->s = p->first;
        temp->code = "";
        temp->weight = p->second;
        temp->right = NULL;
        temp->left = NULL;
        T.push_back(temp);
    }
    BuildHffTree(T);
    map<unsigned char, string> CodeTable;
    map<string, unsigned char> InCodeTable;
    GetCodeTable(CodeTable, InCodeTable, T.back());
    WriteCodeResultToDat(CodeTable, count, path);
    Decode(InCodeTable,count);
}

void LoadSource(map<unsigned char, double> &M, unsigned int &count, string &path) {
    cout << "请输入文件路径" << endl;
    cin >> path;
    ifstream in;
    char ch;
    string s;
//    unsigned int count = 0;
    in.open(path, ios::beg);
    while (!in.eof()) {
        in.get(ch);
        M[ch]++;
        count++;
    }
    map<unsigned char, double>::iterator p;
    for (p = M.begin(); p != M.end(); p++) {
        p->second = p->second / count;
    }
    in.close();
}

void print(map<unsigned char, double> M) {
    map<unsigned char, double>::iterator p;
    cout << "信源符号" << setw(8) << "概率" << endl;
    for (p = M.begin(); p != M.end(); p++)
        cout << hex << (int) p->first << setw(16) << p->second << endl;
}


//通过已有的编码映射方法，对图片编码，并写入.dat文件
void WriteCodeResultToDat(map<unsigned char, string> table, unsigned int count, string path) {
    map<unsigned char, string>::iterator p;
    ofstream fo;
    ifstream fi;

    /**************************打开文件**************************/
    fo.open("/Users/zhanglixuan/Desktop/HufCodeResult.ZLXzip", ios::out | ios::trunc);
    if (!fo.is_open()) {
        cout << "ZLXzip file open error";
        exit(0);
    }
    fi.open(path, ios::beg);
    if (!fi.is_open()) {
        cout << "\"" << path << "\"";
        cout << "open error";
        exit(0);
    }
    /**************************打开文件**************************/
//    int pos;
//    pos = path.find_last_of("\\");
    string name = path.substr(path.find_last_of("/") + 1) + '#';
    string buffer = "";
    char read;
    for (int j = 0; j < name.size(); j++) {
        buffer += table[name[j]];
        while (buffer.size() >= 8) {
            unsigned char ch = 0;
            for (int i = 0; i < 8; i++) {
                ch = ch * 2;
                ch = ch + (buffer[i] - '0');
            }
            buffer.erase(0, 8);
            fo.put(ch);
        }
    }
    for (unsigned int j = 0; j <= count; j++) {
        fi.get(read);
        buffer += table[read];
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
    fi.close();
}

//译码
void Decode(map<string, unsigned char> intable/*译码表(编码表的逆映射)*/, unsigned int count) {
    ifstream fin;
    ofstream fo;
    /**************************打开文件**************************/
    fin.open("/Users/zhanglixuan/Desktop/HufCodeResult.ZLXzip", ios::beg | ios::in);
    if (!fin.is_open()) {
        cout << "dat file open error";
        exit(0);
    }
    /**************************打开文件**************************/
    bool flag;
    unsigned char ch;
    string buffer1 = "";
    string buffer2 = "";
    string name;
    for (bool flag2 = true; flag2;) {
        int i = 0;
        flag = false;
        while (!flag) {
            fin >> noskipws >> ch;
            buffer1 += GetBinary(ch);
            for (; i < buffer1.size(); i++) {
                buffer2 += buffer1[i];
                if (intable.find(buffer2) != intable.end()) {
                    name += intable[buffer2];
                    if (intable[buffer2] == '#')
                        flag2 = false;
                    buffer1.erase(0, i + 1);
                    buffer2.clear();
                    flag = true;
                    break;
                }
            }
        }
    }
    name = "/Users/zhanglixuan/Desktop/#" + name;
    name.erase(name.size() - 1, 1);
    fo.open(name, ios::beg | ios::out);
    for (int j = 0; j < count; j++) {
        int i = 0;
        flag = false;
        while (!flag) {
            fin >> noskipws >> ch;
//                    cout << ch;
            buffer1 += GetBinary(ch);
            for (; i < buffer1.size(); i++) {
                buffer2 += buffer1[i];
                if (intable.find(buffer2) != intable.end()) {
                    fo.put(intable[buffer2]);
                    buffer1.erase(0, i + 1);
                    buffer2.clear();
                    flag = true;
                    break;
                }
            }
        }
        cout<<j<<" "<<count<<endl;
    }
    fin.close();
    fo.close();
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