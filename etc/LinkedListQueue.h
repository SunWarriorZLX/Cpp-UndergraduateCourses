/* 使用链表定义一个简单的队列 */
#include <iostream>
#include "error_code.h"
#include <cstdlib>
#define defT template <typename T>
using std::cout;
using std::endl;
defT struct node
{
    T elem;
    node<T> *next;
};

defT class Queue
{
private:
    int count;
    node<T> *front; //链表表首
    node<T> *rear;  //链表表尾

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
            front->next = NewHead; //保证top指针永远指向栈尾
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
    /* 链表表首指向的下一个node<T>表示为队首 */
    Queue()
    {
        count = 0;
        front = new node<T>;
        front->next = NULL;
        rear = front;
    };
    T append(T NewElem);                            //入队操作
    T getFront();                                   //获取队首元素
    void deleteFront();                             //出队操作
    bool IsEmpty() { return front->next == NULL; }; //判空
    int size() { return count; };
    void print()
    {
        node<T> *temp = front->next;
        for (; temp;)
        {
            cout << temp->elem << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    void Sort()
    {
        QuickSortRecur(front->next, GetEnd(front->next, NULL));
    };
    ~Queue() //依次释放队列所有元素
    {
        while (!IsEmpty())
            deleteFront();
    };
};

defT T Queue<T>::getFront()
{

    if (IsEmpty())
        throw error_code("getFront from an empty Queue");

    else
        return front->next->elem;
}

defT T Queue<T>::append(T NewElem)
{
    count++;
    node<T> *temp = new node<T>;
    temp->elem = NewElem;
    temp->next = NULL;
    rear->next = temp;
    rear = temp;
    return NewElem;
}

defT void Queue<T>::deleteFront()
{
    if (IsEmpty())
        throw error_code("deleteFront from an empty queue");
    else
    {
        count--;
        node<T> *temp = front->next;
        front->next = front->next->next;
        delete temp;
    }
}