#include <iostream>
using namespace std;
class Fibonacci
{
private:
    long *result;
    int n;
    void count(int max, int i = 2)
    {
        if (max < i)
            return;
        result[i] = result[i - 1] + result[i - 2];
        count(n,++i);
    }

public:
    Fibonacci(int newN) : result(new long[newN + 1]()), n(newN)
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

