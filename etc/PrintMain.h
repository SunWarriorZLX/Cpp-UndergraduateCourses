#include <queue>
#include <iostream>
#include <iomanip>
using namespace std;
class PrintPascalTriangle
{
private:
    void print_initialize_NextRow(queue<int> CurrentRow, queue<int> NextRownt, int TotalRowNum, int CurrentRowNum = 1)
    {
        if (CurrentRowNum > TotalRowNum)
            return;
        int temp;
        for (int i = 1; i < CurrentRowNum + 2; i++)
        {
            if (CurrentRow.front()) //元素非零时打印
                cout << setw(8) << CurrentRow.front() << setw(8);

            //先将队首出队，然后与出队后的队首相加（杨辉三角下一行的元素等于前一行的相邻两个元素相加），所得值即为下一行的元素
            temp = CurrentRow.front();
            CurrentRow.pop();
            NextRownt.push(temp + CurrentRow.front());
        }
        cout << endl;
        NextRownt.push(0); //每行元素都以 0 开头和结尾
        print_initialize_NextRow(NextRownt, CurrentRow, TotalRowNum, CurrentRowNum + 1);
        return;
    }

public:
    void print(int TotalRowNum)
    {
        queue<int> CurrentRow, NextRow; //分别用两个队列储存。本次打印的行元素，和下一行的元素
        CurrentRow.push(0);
        CurrentRow.push(1);
        CurrentRow.push(0); //将本次打印的行初始化为 0 1 0
        NextRow.push(0);    //下一行初始化为 0
        print_initialize_NextRow(CurrentRow, NextRow, TotalRowNum);
        return;
    }
};