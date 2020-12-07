
#ifndef COUNTTREEHEIGHT_BINARY_H
#define COUNTTREEHEIGHT_BINARY_H

#include <iostream>
#include <queue>
#include "Node.h"

using namespace std;

class binary {
private:
    Node<char> *root;

    void build(Node<char> *&T, queue<char> &str);

    void inorderPrint(Node<char> *T);

    void GetHeight_RecursiveTraversal(Node<char> *T, int &MaxHeight, int height = 0) const;

    void GetHeight_LevelTraversal(Node<char> *T, int &MaxHeight) const;

    void GetHeight_RecursiveTraversal_Forest(Node<char> *T, int &MaxHeight, int height = 0) const;

public:
    binary();

    void buildTree();

    void inorderPrint();

    int GetHeight_RecursiveTraversal() const;

    int GetHeight_LevelTraversal() const;

    int GetHeight_RecursiveTraversal_Forest() const;
};


#endif
