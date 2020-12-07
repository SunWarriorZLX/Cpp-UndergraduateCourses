#ifndef LEXICAL_LEXICAL_H
#define LEXICAL_LEXICAL_H

#include <string>
#include <vector>
#include <fstream>
#include <istream>
#include <iostream>

#define N 4//算术运算符的个数
#define M 6//关系运算符的个数
using namespace std;

struct T_id {
    string s;
    int id;
};//存储字符和对应的id
struct T_point {
    string s;
    int type;//类型编码
    int point;//指针
    int Row;
    int Col;
};

bool IsLetter(char s);

bool IsCR(char s);

bool IsDigital(char s);

bool IsBlank(char s);

bool IsKeyWord(string str, vector<T_id> KeyWordTable);

bool IsArithmetic_operator(string str, T_id *Arithmetic_operatorTable);

bool IsRelational_operator(string str, T_id *Relational_operatorTable);

bool IsBounder(string str, vector<T_id> BounderTable);

void GetKeyWord(vector<T_id> &KeyWordTable);

void GetBounder(vector<T_id> &BounderTable);

void Load(string &str);

void GetChar();

void LoadedLetter();

void LoadedDigital();

void LoadedBounder();

void LoadedArithmetic();

void LoadedRelational();

void Lexical();

void print(T_point t);

#endif
