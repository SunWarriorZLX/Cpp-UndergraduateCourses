#include <iostream>
#include <cmath>
#include "LinkedListStack.h"
using std::cin;
using std::cout;
using std::endl;
using std::pow;

class ExpressionSolver
{
private:
    stack<char> Operator;
    stack<double> nums;
public:
    bool IsOperator(char s) /* 判断是否为有效运算符 */
    {
        return s == '*' || s == '/' || s == '+' || s == '-' || s == '(' || s == ')' || s == '%';
    }
    bool IsNums(char s) /* 判断是否为有效运算数 */
    {
        return s - '0' >= 0 && s - '0' <= 9;
    }

    /* 分别读取运算符和运算数，并初始化运算符栈、运算数栈 */
    ExpressionSolver(char *s)
    {
        /* 用于临时储存，由字符型转化的单个数字（没有保留进位）的运算数 */
        stack<double> temp;
        double sum;
        Operator.push_back('#'); /* 运算符栈栈头插入 ‘#’ 防止越界 */
        for (int i = 0; s[i];)
        {
            /* 
            //此方法仅适用于个位数表达式的初始化
            if (s[i] - '0' >= 0 && s[i] - '0' <= 9)
                nums.push_back(s[i] - '0');
            else
                Operator.push_back(s[i]);    
            */

            if (IsOperator(s[i])) /* 防止将'\0'视为合法运算符 */
                Operator.push_back(s[i++]);

            if (IsNums(s[i]))
            {
                sum = 0;
                /* 由高位到低位读取连续的数字 */
                for (; IsNums(s[i]); i++)
                    temp.push_back(s[i] - '0');
                temp.reverse(); /* 反转，将高位放到栈顶，_size-1代表其位数 */
                for (; temp.size();)
                    /* 若pow()与temp.pop_back()交换位置，则应将size()-1 改为size() */
                    sum = sum + temp.pop_back() * pow(10, temp.size());
                nums.push_back(sum);
            }
        }
        Operator.push_back('#'); /* 防止越界 */
        /* cout << nums.getTop() << endl; */

        /* 将运算符和运算数的顺序反转 */
        Operator.reverse();
        nums.reverse();

        /*
        //打印元素（用于测试）
        Operator.printElem();
        nums.printElem();
        */
    }
    ~ExpressionSolver(){
    };

    /* 判断运算符优先级，数字越大优先级越高 */
    int GetPriorityLevel(char s)
    {
        switch (s)
        {
        case '(':
            return 4;
        case '/':
        /* case '%':(若运算数类型为整形，可选择性保留) */
        case '*':
            return 3;
        case '+':
        case '-':
            return 2;
        case '#':
            return 1;
        case ')':
            return 0;
        default:
            throw error_code("worng operator");
        }
    };

    /* 将字符映射到对应运算符的操作 */
    double operation(char Operator, double NumsLeft, double NumsRight)
    {
        switch (Operator)
        {
        case '/':
            return NumsLeft / NumsRight;
        case '*':
            return NumsLeft * NumsRight;
        case '+':
            return NumsLeft + NumsRight;
        case '-':
            return NumsLeft - NumsRight;
        default:
            throw error_code("operation error");
        }
    }
    void Processing(bool IsPreviousMinus=false)    
    /* bool IsPreviousMinus 用于标记上一个运算符是否为‘ - ’，用于避免连续两数相减时类似 -x-y 变为 -(x-y)的情况，
    出现问题的根本原因在于递归时运算符一定出栈；但在运算次序变化时，运算数不一定出栈 */
    {
        /* 栈内元素全空，即所有运算符已经出栈，返回上一层（注：运算符全空，
        不等价于运算结束（有可能只是某一分支运算结束） */
        if (Operator.isEmpty())
            return;

        /* 运算符栈，栈头和栈尾均为'#'，若是栈头的'#'直接出栈处理；
        若是栈尾的'#'，为保证访问不越界，保留栈尾'#' */
        if (Operator.getTop() == '#')
        {
            Operator.pop_back();
            if (Operator.isEmpty())
            {
                Operator.push_back('#');
                return;
            }
        }
        if (Operator.getTop() == '(') /* '('d的优先级最高，递归跳入'()'内的运算 */
        {
            Operator.pop_back();
            Processing();
            return;
        }
        if (Operator.getTop() == ')') /* '()'内运算结束，返回 */
        {
            Operator.pop_back();
            return;
        }
        
        char OperTemp; /* 临时存放出栈的运算符和运算数 */
        double NumTemp;
        OperTemp = Operator.pop_back();
        NumTemp = nums.pop_back();
        /* 当前运算级高于或等于下一运算级，进行当前的运算 */
        if (GetPriorityLevel(OperTemp) >= GetPriorityLevel(Operator.getTop()))
        {
            NumTemp = operation(OperTemp, NumTemp, nums.pop_back());
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
            Operator.push_back(OperTemp);
            nums.push_back(NumTemp);
        }
        Processing(IsPreviousMinus);
    };
    int GetResult()
    {
        while (nums.size()>1)
        {
            Processing();
        }
        return nums.getTop();
    }
};
