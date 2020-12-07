#include "Queue.h"
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;
class PrintPascalTriangle
{
public:
    void print(int TotalRowNum)
    {
        Queue<int> CurrentRow, NextRow; //分别用两个队列储存。本次打印的行元素，和下一行的元素
        CurrentRow.append(0);
        CurrentRow.append(1);
        CurrentRow.append(0); //将本次打印的行初始化为 0 1 0
        NextRow.append(0);    //下一行初始化为 0
        print_initialize_NextRow(CurrentRow, NextRow, TotalRowNum);
        return;
    }

    void print_initialize_NextRow(Queue<int> CurrentRow, Queue<int> NextRownt, int TotalRowNum, int CurrentRowNum = 1)
    {
        if (CurrentRowNum > TotalRowNum)
            return;
        int temp;
        for (int i = 1; i < CurrentRowNum + 2; i++)
        {
            if (CurrentRow.getFront())//元素非零时打印
                cout << setw(8) << CurrentRow.getFront() << setw(8);

            //先将队首出队，然后与出队后的队首相加（杨辉三角下一行的元素等于前一行的相邻两个元素相加），所得值即为下一行的元素
            temp = CurrentRow.getFront();
            CurrentRow.deleteFront();
            NextRownt.append(temp + CurrentRow.getFront());
        }
        cout << endl;
        NextRownt.append(0);//每行元素都以 0 开头和结尾
        print_initialize_NextRow(NextRownt, CurrentRow, TotalRowNum, CurrentRowNum + 1);
        return;
    }
};
