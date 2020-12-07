/*
    关键字 1;
    分界符 2;
    算术运算符 3;
    关系运算符 4;
    无符号数 5;
    标识符 6。
*/

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
vector<T_id> KeyWord;//关键字表
vector<T_id> Bounder;//界符表

//算术运算符表
T_id Arithmetic_operator[N] = {
        {"+", 0x10},
        {"-", 0x11},
        {"*", 0x20},
        {"/", 0x21}
};

//关系运算符表
T_id Relational_operator[M] = {
        {"<",  0x00},
        {"<=", 0x01},
        {"=",  0x02},
        {">",  0x03},
        {">=", 0x04},
        {"<>", 0x05}
};

char ch;
int row = 1;//行
int col = 1;//列
int point = -1;
string SourceBuffer;//源代码缓冲区
vector<T_point> Word_Table;
vector<T_point> Key_Word_Table;
vector<T_point> UnsInt_Table;
vector<T_point> Bounder_Table;
vector<T_point> Arithmetic_Table;

//判断是否为字母
bool IsLetter(char s) {
    return (s >= 65 && s <= 90) || (s >= 97 && s <= 122);
}

bool IsCR(char s) {
    return s == '\n';
}

//判断是否为数字
bool IsDigital(char s) {
    return (s >= 48 && s <= 57);
}

//判断是否为空格
bool IsBlank(char s = ch) {
    return s == ' ';
}

//判断是否为关键字
bool IsKeyWord(string str, vector<T_id> KeyWordTable) {
    vector<T_id>::iterator p;
    for (p = KeyWordTable.begin(); p < KeyWordTable.end(); p++)
        if (str == p->s)
            return true;
    return false;
}

//判断是否为算术运算符
bool IsArithmetic_operator(string str, T_id *Arithmetic_operatorTable) {
    for (int i = 0; i < N; i++)
        if (Arithmetic_operatorTable[i].s == str)
            return true;
    return false;
}

//判断是否为关系运算符
bool IsRelational_operator(string str, T_id *Relational_operatorTable) {
    for (int i = 0; i < M; i++)
        if (Relational_operatorTable[i].s == str)
            return true;
    return false;
}

//判断是否为界符
bool IsBounder(string str, vector<T_id> BounderTable) {
    vector<T_id>::iterator p;
    for (p = BounderTable.begin(); p < BounderTable.end(); p++)
        if (str == p->s)
            return true;
    return false;
}

//读取关键字
void GetKeyWord(vector<T_id> &KeyWordTable) {
    ifstream in("LoadKeyWord.txt", ios::in);
    if (!in) {
        cout << " open file error " << endl;
        exit(1);
    }
    string buffer;
    while (buffer != "KeyWord" && !in.eof())
        in >> buffer;
    T_id temp;
    while (!in.eof()) {
        in >> temp.s;
        in >> temp.id;
        KeyWordTable.push_back(temp);
    }
    in.close();
    return;
}

//读取界符
void GetBounder(vector<T_id> &BounderTable) {
    ifstream in("LoadBounder.txt", ios::in);
    if (!in) {
        cout << " open file error " << endl;
        exit(1);
    }
    string buffer;
    while (buffer != "KeyWord" && !in.eof())
        in >> buffer;
    T_id temp;
    while (!in.eof()) {
        in >> temp.s;
        in >> temp.id;
        BounderTable.push_back(temp);
    }
    in.close();
    return;
}

//将部分源程序读入单个缓冲区*/
void Load(string &str) {
    getline(cin, str, '#');
    str += '#';
}

void GetChar() {
    point++;
    ch = SourceBuffer[point];
}

//处理单词
void LoadedLetter() {
    T_point t;
    t.point = point;
    t.s = "";
    t.Row = row;
    t.Col = col;
    col++;
    while (IsLetter(ch) || IsDigital(ch)) {
        t.s += ch;
        GetChar();
    }
    if (IsKeyWord(t.s, KeyWord)) {
        t.type = 1;
        Key_Word_Table.push_back(t);
        cout << t.s << " (" << t.type << "," << t.s << ") " << "关键字 (" << t.Row << "," << t.Col << endl;
    } else {
        t.type = 6;
        Word_Table.push_back(t);
        cout << t.s << " (" << t.type << "," << t.s << ") " << "标识符 (" << t.Row << "," << t.Col << endl;
    }
    point--;
}

//处理数字
void LoadedDigital() {
    T_point t;
    t.point = point;
    t.s = "";
    t.Row = row;
    t.Col = col;
    col++;
    while (IsDigital(ch)) {
        t.s += ch;
        GetChar();
    }
    t.type = 5;
    UnsInt_Table.push_back(t);
    cout << t.s << " (" << t.type << "," << t.s << ") " << "无符号数 (" << t.Row << "," << t.Col << endl;
    point--;
}

//处理界符
void LoadedBounder() {
    T_point t;
    t.point = point;
    t.type = 2;
    t.s = ch;
    t.Col = col;
    t.Row = row;
    col++;
    cout << t.s << " (" << t.type << "," << t.s << ") " << "界符 (" << t.Row << "," << t.Col << endl;
    Bounder_Table.push_back(t);

}

//处理算术运算符
void LoadedArithmetic() {
    if (ch == '/') {
        GetChar();
        if (ch == '*') {
            point = SourceBuffer.find_first_of("*/", point);
            return;
        }
        point--;
    }
    T_point t;
    t.point = point;
    t.type = 3;
    t.s = ch;
    t.Col = col;
    t.Row = row;
    col++;
    cout << t.s << " (" << t.type << "," << t.s << ") " << "算术运算符 (" << t.Row << "," << t.Col << endl;
    Arithmetic_Table.push_back(t);

}

//处理关系运算符
void LoadedRelational() {
    T_point t;
    t.s = ch;
    switch (ch) {
        case '<': {
            GetChar();
            if (ch == '>')
                t.s = "<>";
            else if (ch == '=')
                t.s = "<=";
            else
                point--;
            break;
        }
        case '>': {
            GetChar();
            if (ch == '=')
                t.s = ">=";
            else
                point--;
            break;
        }
        case '=': {
            GetChar();
            if (ch == '=')
                t.s = "==";
            else
                point--;
            break;
        }
        default:
            break;
    }
    t.point = point;
    t.type = 4;
    t.Col = col;
    t.Row = row;
    col++;
    cout << t.s << " (" << t.type << "," << t.s << ") " << "关系运算符 (" << t.Row << "," << t.Col << endl;
}

void Lexical() {
    Load(SourceBuffer);
    string t;
    for (GetChar(); ch != '#';) {
        if (IsBlank(ch))
            continue;
        else if (ch == '\n') {
            row++;
            col = 1;
        }
        if (IsLetter(ch)) LoadedLetter();
        else if (IsDigital(ch)) LoadedDigital();
        else if (IsBounder(t = ch, Bounder)) LoadedBounder();
        else if (IsArithmetic_operator(t = ch, Arithmetic_operator)) LoadedArithmetic();
        else if (IsRelational_operator(t = ch, Relational_operator)) LoadedRelational();
        GetChar();
    }
}