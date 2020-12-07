#include <string>
#include <vector>
#include <iostream>
using namespace std;
int main()
{
    string a="/*dsfdsfds*/*/";
    cout<<a.find_first_of("*/",3);
    getline(cin,a,'#');
    cout<<a;
}
