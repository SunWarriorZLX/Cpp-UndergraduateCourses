#define defT template <typename T>
#include <iostream>
#include <cstdlib>
using namespace std;
defT struct DuLNode
{
    T elem;
    DuLNode<T> *prior, *next;
};

defT class InitList
{
private:
    DuLNode<T> *head;
    DuLNode<T> *rear;
    int count;

public:
    InitList() : count(0)
    {
        head = new DuLNode<T>;
        rear = head;
    };
    ~InitList(){};
    void push_back(T NewELem)
    {
        DuLNode<T> *NewNode = new DuLNode<T>;
        NewNode->elem = NewELem;
        rear->next = NewNode;
        NewNode->prior = rear;
        NewNode->next = head->next;
        rear = NewNode;
        head->next->prior = rear;
        count++;
    }
    void print()
    {
        DuLNode<T> *temp = head;
        for (int i = 0; i <= count; i++)
        {
            cout << temp << " " << temp->elem << " ";
            temp = temp->next;
        }
    }
    void reserve()
    {
        DuLNode<T> *temp1 = head->next, *temp2;
        for (int i = 0; i <= count; i++)
        {
            temp2 = temp1->next;
            temp1->next = temp1->prior;
            temp1->prior = temp2;
            temp1 = temp1->prior;
        }
        head->next = rear;
    }
};
