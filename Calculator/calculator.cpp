//
// Created by 张力炫 on 2020/6/29.
//

#include "calculator.h"

map<char, map<char, bool>> predictTable;
vector<char> Oper;
vector<double> nums;

//判断是否为数字
bool IsNum(char ch) {
    return ch >= '0' && ch <= '9';
}

/* 判断是否为有效运算符 */
bool IsOperator(char s) {
    return s == '*' || s == '/' || s == '+' || s == '-' || s == '(' || s == ')' || s == '%' || s == '|' ||
           s == '&' | s == '!';
}

//是否在后面的字符中找到右括号
bool findRightBracket(int pos, string input) {
    for (int i = pos; i < input.size(); i++)
        if (input[pos] == ')')
            return true;
    return false;
}

//交换两个字符变量的值
void swap(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

//初始化预测分析表
void initialize_predictTable() {
    //+
    predictTable['+']['+'] = false;
    predictTable['+']['-'] = false;
    predictTable['+']['*'] = false;
    predictTable['+']['/'] = false;
//    predictTable['+']['%'] = false;
    predictTable['+']['!'] = true;
    predictTable['+']['|'] = false;
    predictTable['+']['&'] = false;
    predictTable['+']['N'] = true;
    predictTable['+']['('] = true;
    predictTable['+'][')'] = false;
    predictTable['+']['#'] = false;

    //-
    predictTable['-']['+'] = false;
    predictTable['-']['-'] = false;
    predictTable['-']['*'] = false;
    predictTable['-']['/'] = false;
//    predictTable['-']['%'] = false;
    predictTable['-']['!'] = true;
    predictTable['-']['|'] = false;
    predictTable['-']['&'] = false;
    predictTable['-']['N'] = true;
    predictTable['-']['('] = true;
    predictTable['-'][')'] = false;
    predictTable['-']['#'] = false;

    //*
    predictTable['*']['+'] = false;
    predictTable['*']['-'] = false;
    predictTable['*']['*'] = false;
    predictTable['*']['/'] = false;
//    predictTable['*']['%'] = false;
    predictTable['*']['!'] = true;
    predictTable['*']['|'] = false;
    predictTable['*']['&'] = false;
    predictTable['*']['N'] = true;
    predictTable['*']['('] = true;
    predictTable['*'][')'] = false;
    predictTable['*']['#'] = false;

    // '/'
    predictTable['/']['+'] = false;
    predictTable['/']['-'] = false;
    predictTable['/']['*'] = false;
    predictTable['/']['/'] = false;
//    predictTable['/']['%'] = false;
    predictTable['/']['!'] = true;
    predictTable['/']['|'] = false;
    predictTable['/']['&'] = false;
    predictTable['/']['N'] = true;
    predictTable['/']['('] = true;
    predictTable['/'][')'] = false;
    predictTable['/']['#'] = false;

/*
    //%
    predictTable['%']['+'] = false;
    predictTable['%']['-'] = false;
    predictTable['%']['*'] = false;
    predictTable['%']['/'] = false;
    predictTable['%']['%'] = false;
    predictTable['%']['!'] = true;
    predictTable['%']['|'] = false;
    predictTable['%']['&'] = false;
    predictTable['%']['N'] = true;
    predictTable['%']['('] = true;
    predictTable['%'][')'] = false;
    predictTable['%']['#'] = false;*/

    // !
    predictTable['!']['+'] = false;
    predictTable['!']['-'] = false;
    predictTable['!']['*'] = false;
    predictTable['!']['/'] = false;
//    predictTable['!']['%'] = false;
    predictTable['!']['!'] = true;
    predictTable['!']['|'] = false;
    predictTable['!']['&'] = false;
    predictTable['!']['N'] = true;
    predictTable['!']['('] = true;
    predictTable['!'][')'] = false;
    predictTable['!']['#'] = false;

    // ||
    predictTable['|']['+'] = false;
    predictTable['|']['-'] = false;
    predictTable['|']['*'] = false;
    predictTable['|']['/'] = false;
//    predictTable['|']['%'] = false;
    predictTable['|']['!'] = true;
    predictTable['|']['|'] = false;
    predictTable['|']['&'] = false;
    predictTable['|']['N'] = true;
    predictTable['|']['('] = true;
    predictTable['|'][')'] = false;
    predictTable['|']['#'] = false;

    // &&
    predictTable['&']['+'] = false;
    predictTable['&']['-'] = false;
    predictTable['&']['*'] = false;
    predictTable['&']['/'] = false;
//    predictTable['&']['%'] = false;
    predictTable['&']['!'] = true;
    predictTable['&']['|'] = false;
    predictTable['&']['&'] = false;
    predictTable['&']['N'] = true;
    predictTable['&']['('] = true;
    predictTable['&'][')'] = false;
    predictTable['&']['#'] = false;

    // NUM
    predictTable['N']['+'] = true;
    predictTable['N']['-'] = true;
    predictTable['N']['*'] = true;
    predictTable['N']['/'] = true;
//    predictTable['N']['%'] = true;
    predictTable['N']['!'] = false;
    predictTable['N']['|'] = true;
    predictTable['N']['&'] = true;
    predictTable['N']['N'] = true;
    predictTable['N']['('] = false;
    predictTable['N'][')'] = true;
    predictTable['N']['#'] = true;

    // (
    predictTable['(']['+'] = false;
    predictTable['(']['-'] = false;
    predictTable['(']['*'] = false;
    predictTable['(']['/'] = false;
//    predictTable['(']['%'] = false;
    predictTable['(']['!'] = true;
    predictTable['(']['|'] = false;
    predictTable['(']['&'] = false;
    predictTable['(']['N'] = true;
    predictTable['(']['('] = true;
    predictTable['('][')'] = false;
    predictTable['(']['#'] = false;

    // )
    predictTable[')']['+'] = true;
    predictTable[')']['-'] = true;
    predictTable[')']['*'] = true;
    predictTable[')']['/'] = true;
//    predictTable[')']['%'] = true;
    predictTable[')']['!'] = false;
    predictTable[')']['|'] = true;
    predictTable[')']['&'] = true;
    predictTable[')']['N'] = false;
    predictTable[')']['('] = false;
    predictTable[')'][')'] = true;
    predictTable[')']['#'] = true;

    // #
    predictTable['#']['+'] = false;
    predictTable['#']['-'] = false;
    predictTable['#']['*'] = false;
    predictTable['#']['/'] = false;
//    predictTable['#']['%'] = true;
    predictTable['#']['!'] = false;
    predictTable['#']['|'] = false;
    predictTable['#']['&'] = false;
    predictTable['#']['N'] = false;
    predictTable['#']['('] = false;
    predictTable['#'][')'] = false;
    predictTable['#']['#'] = false;
}

//判断表达式是否出错
bool IsError(string input) {
    initialize_predictTable();
    char ch;
    char ch_next;

    if (IsNum(input[0]))//'N' 代表数字
        ch = 'N';
    else ch = input[0];

    for (int i = 1; i < input.size(); i++) {
        if (IsNum(input[i]))
            ch_next = 'N';
        else ch_next = input[i];

        if (ch == '(' && !findRightBracket(i, input))
            return false;
        if (!predictTable[ch][ch_next])
            return false;
        swap(ch, ch_next);
    }
    return true;
}

void LoadOperAndNums(string input) {
    for (int i = 0; i < input.size(); i++) {
        if (IsOperator(input[i]))
            Oper.push_back(input[i]);
        else if (IsNum(input[i])) {
            double sum = 0;
            vector<double> temp;
            temp.clear();
            while (IsNum(input[i])) {
                temp.push_back(input[i] - '0');
                i++;
            }
            i--;
            reverse(temp.begin(), temp.end());
            while (!temp.empty()) {
                sum = sum + temp.back() * pow(10, temp.size() - 1);
                temp.pop_back();
            }
            nums.push_back(sum);
        }
    }
    Oper.push_back('#');
    reverse(Oper.begin(), Oper.end());
    reverse(nums.begin(), nums.end());
}

int GetLevel(char s) {
    switch (s) {
        case '(':
            return 6;
        case '!':
            return 5;
        case '*':
        case '/':
            return 4;
        case '+':
        case '-':
            return 3;
        case '|':
        case '&':
            return 2;
        case ')':
            return 0;
        default: return 1;
    }
}

double operation(char Operator, double NumsLeft, double NumsRight)
{
    switch (Operator)
    {
        case '!':{
            nums.push_back(NumsRight);
            return !NumsLeft;
        }
        case '|':
            return NumsLeft||NumsRight;
        case '&':
            return NumsRight&&NumsLeft;
        case '/':
            return NumsLeft / NumsRight;
        case '*':
            return NumsLeft * NumsRight;
        case '+':
            return NumsLeft + NumsRight;
        case '-':
            return NumsLeft - NumsRight;
    }
}

/* bool IsPreviousMinus 用于标记上一个运算符是否为‘ - ’，用于避免连续两数相减时类似 -x-y 变为 -(x-y)的情况，
出现问题的根本原因在于递归时运算符一定出栈；但在运算次序变化时，运算数不一定出栈 */
void Processing(bool IsPreviousMinus=false)
{
    /* 栈内元素全空，即所有运算符已经出栈，返回上一层（注：运算符全空，
    不等价于运算结束（有可能只是某一分支运算结束） */
    if (Oper.empty())
        return;

    /* 运算符栈，栈头和栈尾均为'#'，若是栈头的'#'直接出栈处理；
    若是栈尾的'#'，为保证访问不越界，保留栈尾'#' */
    if (Oper.back() == '#')
    {
        Oper.pop_back();
        if (Oper.empty())
        {
            Oper.push_back('#');
            return;
        }
    }
    if (Oper.back() == '(') /* '('d的优先级最高，递归跳入'()'内的运算 */
    {
        Oper.pop_back();
        Processing();
        return;
    }
    if (Oper.back() == ')') /* '()'内运算结束，返回 */
    {
        Oper.pop_back();
        return;
    }

    char OperTemp; /* 临时存放出栈的运算符和运算数 */
    double NumTemp;
    OperTemp = Oper.back();
    NumTemp = nums.back();
    Oper.pop_back();
    nums.pop_back();
    /* 当前运算级高于或等于下一运算级，进行当前的运算 */
    if (GetLevel(OperTemp) >= GetLevel(Oper.back()))
    {

        NumTemp = operation(OperTemp, NumTemp, nums.back());
        nums.pop_back();
        nums.push_back(NumTemp);
        if (IsPreviousMinus) //若前一次运算为减法，则返回
        {
            IsPreviousMinus = false;
            return;
        }
    }
    else
    {
        if (OperTemp == '-')    /* 记录上一个运算符 */
            IsPreviousMinus = true;
        Processing(IsPreviousMinus);
        Oper.push_back(OperTemp);
        nums.push_back(NumTemp);
    }
    Processing(IsPreviousMinus);
};

double GetResult(string input)
{
    LoadOperAndNums(input);
    while (nums.size()>1)
    {
        Processing();
    }
    return nums.back();
}
