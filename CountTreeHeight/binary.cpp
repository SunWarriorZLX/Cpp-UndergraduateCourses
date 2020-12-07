#include "binary.h"

binary::binary() {
    root = NULL;
}

void binary::buildTree() {
    Node<char> *NewTree = new Node<char>;
    queue<char> str;
    cout << "Please input a tree:" << endl;
    char temp;
    for (cin >> temp; temp != '|'; cin >> temp)
        str.push(temp);
    build(NewTree, str);
    root = NewTree;
}

void binary::inorderPrint(Node<char> *T) {
    if (T == NULL)
        return;
    cout << " " << T->elem << " ";
    inorderPrint(T->left);
    inorderPrint(T->right);
    return;
}

void binary::inorderPrint() {
    if (root == NULL) {
        cout << " empty tree " << endl;
        return;
    }
    cout << " inorderPrint: " << endl;
    inorderPrint(root);
    return;
}

void binary::build(Node<char> *&T, queue<char> &str) {
    if (str.empty()) {
        delete T;
        T = NULL;
        return;
    } else if (str.front() == '.') {
        str.pop();
        delete T;
        T = NULL;
        return;
    } else {
        T->elem = str.front();
        cout << T->elem << " ";
        str.pop();
        Node<char> *NewLeft = new Node<char>;
        Node<char> *NewRight = new Node<char>;
        T->left = NewLeft;
        T->right = NewRight;
        build(T->left, str);
        build(T->right, str);
    }
    return;
}

void binary::GetHeight_RecursiveTraversal(Node<char> *T, int &MaxHeight, int height) const {
    if (T == NULL) {
        if (height > MaxHeight)
            MaxHeight = height;
        return;
    }
    GetHeight_RecursiveTraversal(T->left, MaxHeight, height + 1);
    GetHeight_RecursiveTraversal(T->right, MaxHeight, height + 1);
}

int binary::GetHeight_RecursiveTraversal() const {
    int MaxHeight;
    GetHeight_RecursiveTraversal(root, MaxHeight);
    return MaxHeight;
}

void binary::GetHeight_LevelTraversal(Node<char> *T, int &MaxHeight) const {
    queue<Node<char> *> Level1;
    queue<Node<char> *> Level2;
    MaxHeight = 0;
    if (T == NULL)
        return;
    Level2.push(T);
    while (!(Level1.empty() && Level2.empty())) {
        while (!Level1.empty()) {
            T = Level1.front();
            Level1.pop();
            if (T->right != NULL)
                Level2.push(T->right);
            if (T->left != NULL)
                Level2.push(T->left);
        }
        if (!Level2.empty())
            MaxHeight++;
        while (!Level2.empty()) {
            T = Level2.front();
            Level2.pop();
            if (T->right != NULL)
                Level1.push(T->right);
            if (T->left != NULL)
                Level1.push(T->left);
        }
        if (!Level1.empty())
            MaxHeight++;
    }
}

int binary::GetHeight_LevelTraversal() const {
    int MaxHeight = 0;
    GetHeight_LevelTraversal(root, MaxHeight);
    return MaxHeight;
}

int binary::GetHeight_RecursiveTraversal_Forest() const {
    int max = 0;
    GetHeight_RecursiveTraversal_Forest(root, max);
    return max;
}

void binary::GetHeight_RecursiveTraversal_Forest(Node<char> *T, int &MaxHeight, int height) const {
    if (T == NULL) {
        if (height > MaxHeight)
            MaxHeight = height;
        return;
    }
    GetHeight_RecursiveTraversal_Forest(T->left, MaxHeight, height + 1);
    GetHeight_RecursiveTraversal_Forest(T->right, MaxHeight, height);
}