#include <iostream>
#include <vector>
using namespace std;
class Fibonacci
{
private:
    long *result;
    int n;
    void count(int max, int i = 2)
    {
        vector<int> temp;
    again:
        if (max >= i)
        {
            result[i] = result[i - 1] + result[i - 2];
            temp.push_back(max);
            temp.push_back(i);
            i++;
            goto again;
        }
    next:
        if (!temp.empty())
        {
            temp.pop_back();
            temp.pop_back();
            goto next;
        }
    }

public:
    Fibonacci(int newN) : result(new long[newN+1]()), n(newN)
    {
        result[0] = 0;
        result[1] = 1;
        count(n);
    };
    void print()
    {
        for (int i = 1; i <= n; i++)
            cout << result[i] << " ";
    }
    ~Fibonacci() { delete[] result; };
};
int main()
{
    Fibonacci t(80);
    t.print();
}