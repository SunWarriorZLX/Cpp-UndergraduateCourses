/*
#include <iostream>
#include <cmath>
#include "binary.h"

using namespace std;

int LevelTraversal(vector<char> &T) {
    int height = 0;
    int j = 0;
    for (j += pow(2, height - 1);; j += pow(2, height - 1)) {
        if (j >= T.size())
            return height;
        for (int i = j - 1; i < j + pow(2, height); i++) {
            if (T[i] != '.') {
                height++;
                break;
            }
        }
    }
}

void RecursiveTraversal(vector<char> &T, int &MaxHeight, int i, int height = 0) {
    if (i >= T.size() || T[i] == 0) {
        if (height > MaxHeight)
            MaxHeight = height;
        return;
    }
    RecursiveTraversal(T, MaxHeight, 2 * i + 1, height + 1);//left
    RecursiveTraversal(T, MaxHeight, 2 * i + 2, height + 1);//right
}

int main() {
*/
/*    string string1;
    cout << "Please input a tree:" << endl;
    cin >> string1;
    vector<char> T(string1.begin(), string1.end());
    cout << "LevelTraversal Height: " << LevelTraversal(T) << endl;
    int max = 0;
    RecursiveTraversal(T, max, 0);
    cout << "RecursiveTraversal Height: " << max << endl;*//*

   binary tree;
    tree.buildTree();
    tree.inorderPrint();
    cout << "GetHeight_RecursiveTraversal Height: " << tree.GetHeight_RecursiveTraversal() << endl;
    cout << "GetHeight_LevelTraversal Height: " << tree.GetHeight_LevelTraversal() << endl;
    return 0;
}
 */
#include <iostream>

#include "binary.h"

using namespace std;

int main() {
    binary T;
    T.buildTree();
    cout << "The Height of the forest is: " << T.GetHeight_RecursiveTraversal_Forest();
    return 0;
}