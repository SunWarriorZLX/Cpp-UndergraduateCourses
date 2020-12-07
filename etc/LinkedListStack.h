
#include "error_code.h"
#include <cstdlib>
#include <iostream>
#define defT template <typename T>
using std::cout;
using std::endl;
defT struct node
{
    T elem;
    node *next;
};

defT class stack
{
private:
    int count;
    node<T> *top;

    void reserve_operation(node<T> *TopNode, node<T> *NextNode) //反转函数具体操作过程
    {
        top = TopNode;
        if (!NextNode)
            return;
        node<T> *temp = NextNode->next;
        NextNode->next = TopNode; //每次递归将下一个元素指向前一个元素
        reserve_operation(NextNode, temp);
    };

    //链表快速排血具体操作流程
    void QuickSortRecur(node<int> *head, node<int> *end, node<int> *HeadPrevious = NULL, node<int> *EndNext = NULL)
    //HeadPrevious 和 EndNext用于连接两个分组
    {
        if (head == end) //分组只剩一个元素时返回
            return;
        node<int> *current = head->next; //当前元素
        node<int> *NewHead = head;
        node<int> *CurrentPrevious = head; //当前元素的前一个元素

        //每次位置变动，只改变 next 指针的内容，变动时将 current 指向原本的头结点，current 变成新的头节点
        while (current != EndNext)
        {

            if (current->elem > head->elem)
            {
                CurrentPrevious->next = current->next;
                current->next = NewHead;
                NewHead = current;
                current = CurrentPrevious->next;
            }
            else
            {
                CurrentPrevious = current;
                current = current->next;
            }
        }
        if (HeadPrevious)
            HeadPrevious->next = NewHead;
        else
            top = NewHead; //保证top指针永远指向栈尾
        if (EndNext)
            CurrentPrevious->next = EndNext;
        QuickSortRecur(NewHead, GetEnd(NewHead, head), HeadPrevious, head);
        QuickSortRecur(head->next, GetEnd(head->next, EndNext), head, EndNext);
    };
    node<int> *GetEnd(node<int> *head, node<int> *EndNext)
    {
        if (!head)
            return head;
        while (head->next != EndNext && head != EndNext)
            head = head->next;
        return head;
    }

public:
    stack() : count(0), top(NULL){};

    //判空
    bool isEmpty() const { return count == 0; };

    //取栈尾元素
    T getTop() const
    {
        if (isEmpty())
            throw error_code("getTop from empty LinkList");
        else
            return top->elem;
    };

    //出栈
    T pop_back()
    {
        if (isEmpty())
            throw error_code("pop_back from enpty LinkList");
        else
        {
            T elemTemp = getTop();
            count--;
            node<T> *temp;
            temp = top;
            top = top->next;
            delete temp;
            return elemTemp;
        }
    }

    //入栈
    void push_back(T NewELem)
    {
        count++;
        node<T> *next = new node<T>;
        next->elem = NewELem;
        next->next = top;
        top = next;
    };

    int size() { return count; }; //返回结点个数

    void print() //打印所有元素
    {
        node<T> *temp = top;
        for (int i = 0; i < size(); i++)
        {
            cout << temp->elem << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void reverse() //反转函数外部接口
    {
        node<T> *temp = top->next;
        top->next = NULL;
        reserve_operation(top, temp);
    };

    //排序外部接口
    void Sort()
    {
        QuickSortRecur(top, GetEnd(top, NULL));
    };
    ~stack() //删除所有结点
    {
        while (!isEmpty())
        {
            pop_back();
        }
    };
};
