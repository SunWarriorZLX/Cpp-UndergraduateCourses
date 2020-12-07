/* 定义一个简单的stack，实现基本的栈逻辑结构 */
#define DEFAULT_CAPACITY 20 /* 默认初始容量 */
#include <iostream>
#define defT template <typename T>
#include "error_code.h"
defT class stack
{
private:
    T *elem;
    int _size;     /* 栈已使用的容量 _size-1 即为栈顶下标 */
    int _capacity; /* 栈的实际容量，容量不足将自动扩容 */
    void copy();   /* 复制函数，用于栈的扩容 */

public:
    stack(int size = 0) : _size(size), _capacity(size + DEFAULT_CAPACITY), elem(new T[size + DEFAULT_CAPACITY]){};
    /* T &operator[](int i); */

    /* 判空 */
    bool isEmpty() { return _size == 0; }

    /* 判满 */
    bool isFull() { return _size == _capacity; }
    T getTop();                /* 取栈顶元素 */
    void push_back(T newElem); /* 将元素插入栈尾 */
    T pop_back();              /* 删除栈尾的元素，并返回栈尾元素的值 */

    /* 获取栈已使用的容量 */
    int size() { return _size; }
    void reverse(); /* 将栈的元素反转 */
    void printElem() const;
    ~stack() { delete[] elem; };
};

/*
 defT T &stack<T>::operator[](int i)
{
    if (i >= _size || i < 0 || i >= _capacity)
        throw error_code("Illegal access");
    else
        return elem[i];
}
*/

defT T stack<T>::getTop()
{
    if (isEmpty())
        throw error_code("getting top from an empty stack"); /* 防止数组越界，抛出异常 */
    else
        return elem[_size - 1];
}

/* 扩容的基本思路为，初始化一个容量更大的数组，并用原来数组的值为其一一赋值 */
defT void stack<T>::copy()
{
    _capacity = _capacity + DEFAULT_CAPACITY;
    T *temp = elem;
    elem = new T[_capacity];
    for (int i = 0; i < _size; i++)
        elem[i] = temp[i];
    delete[] temp; /* 此处的temp为旧的栈数组指针 */
}

defT void stack<T>::push_back(T newElem)
{
    if (_size >= _capacity) /* 容量不足 */
    {
        copy();
        elem[_size] = newElem;
        _size++;
    }
    else
    {
        elem[_size] = newElem;
        _size++;
    }
}

defT T stack<T>::pop_back()
{
    if (isEmpty())
        throw error_code("pop_back empty stack");
    else
        _size--;
    return elem[_size];
}

defT void stack<T>::reverse()
{
    if (isEmpty())
        throw error_code("reverse empty stack");
    T temp;
    for (int i = 0, j = _size - 1; i < j; i++, j--)
    {
        temp = elem[i];
        elem[i] = elem[j];
        elem[j] = temp;
    }
}
defT void stack<T>::printElem() const
{
    for (int i = 0; i < _size; i++)
        std::cout << elem[i];
    std::cout << std::endl;
}