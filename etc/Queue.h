/* 使用数组实现一个简答的链表 */
#include <cstdlib>
#include "error_code.h"
#define defT template <typename T>
const int default_capacity = 5;
defT class Queue
{
private:
    int count;               //总的元素个数
    int front;               //队首下标
    int rear;                //队尾下标加一
    int capacity;            //数组的实际容量
    T *elem;                 //数组指针
    void CapacityExpansion() //复制数组的所有元素到另一个数组，用于链表扩容
    {
        if (IsEmpty())
            throw error_code("CapacityExpansion empty queue");
        capacity = capacity + default_capacity;
        T *NewContainer = new T[capacity];
        for (int i = 0; i < rear; i++)
            NewContainer[i] = elem[i];
        delete[] elem;
        elem = NewContainer;
    };
    void shift() //将数组所有元素向数组首部移动
    {
        int i;
        for (i = 0; i < count; i++)
        {
            elem[i] = elem[front + i];
        }
        front = 0;
        rear = i;
    };

public:
    Queue() : count(0), front(0), rear(0), capacity(default_capacity), elem(new T[default_capacity]){};
    bool IsEmpty() const { return count == 0; };
    bool IsFull() const { return count == capacity; };
    T append(T NewElem)
    {
        if (IsFull()) //容量不足时扩容
            CapacityExpansion();
        if (rear == capacity && front > 0)
            shift();
        elem[rear] = NewElem;
        rear++;
        count++;
    }
    T getFront() const //取队头元素
    {
        if (IsEmpty())
            throw error_code("getFront from an empty queue");
        else
            return elem[front];
    };
    void deleteFront() //删除队头
    {
        if (IsEmpty())
            throw error_code("deleteFront from an empty queue");
        else
        {
            front++;
            count--;
        }
    };
    ~Queue(){};
};