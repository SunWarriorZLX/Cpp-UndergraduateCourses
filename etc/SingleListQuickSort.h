#include <cstdlib>
#include <iostream>
using std::cout;
template <typename T>
struct node
{
    T elem;
    node<T> *next;
};
template <typename T>
node<T> push(T NewElem, node<T> *old)
{
    struct node<T> *newnode=new node<T>;
    newnode->elem = NewElem;
    newnode->next=old;
    return *newnode;
}

class QuickSort
{
private:
    void QuickSortRecur(node<int> *head, node<int> *end, node<int> *HeadPrevious = NULL, node<int> *EndNext = NULL)
    {
        if (head == end)
            return;
        node<int> *current = head->next;
        node<int> *NewHead = head;
        node<int> *CurrentPrevious = head;
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
        if (EndNext)
            CurrentPrevious->next = EndNext;
        QuickSortRecur(NewHead, GetEnd(NewHead, head), HeadPrevious, head);
        QuickSortRecur(head->next, GetEnd(head->next, EndNext), head, EndNext);
    };
    node<int> *GetEnd(node<int> *head, node<int> *EndNext)
    {
        while (head->next != EndNext)
            head = head->next;
        return head;
    }

public:
    //公共接口
    void Sort(node<int> nums)
    {
        QuickSortRecur(&nums, GetEnd(&nums, NULL));
    };
};
