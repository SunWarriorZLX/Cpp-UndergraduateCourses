//
// Created by 张力炫 on 2020/6/1.
//

#include "Huffman_Code.h"

//比较两个霍夫曼节点的大小
bool compare(const HuffNode *a, const HuffNode *b) {
    return (*a).weight > (*b).weight;
}

//创建霍夫曼树
void BuildHffTree(vector<HuffNode *> &source) {
    sort(source.begin(), source.end(), compare);
    buildHffTree(source);
}

//入口参数source已经完成第一次排序
void buildHffTree(vector<HuffNode *> &source) {
    HuffNode *NewNode = new HuffNode;
    NewNode->weight = source[source.size() - 1]->weight + source[source.size() - 2]->weight;
    NewNode->left = source[source.size() - 2];
    NewNode->right = source[source.size() - 1];
    NewNode->s = 0xFFFFFFFF;//非信源符号的节点s值都为 0xFFFFFFFF
    NewNode->code = "";
    source.pop_back();
    source.pop_back();
    if (source.size() == 0) {
        source.push_back(NewNode);
        return;
    }
    for (int i = 0; i < source.size(); i++) {
        if (NewNode->weight >= source[i]->weight) {
            source.insert(source.begin() + i, NewNode);
            break;
        }
        if (i == source.size() - 1)
            source.push_back(NewNode);
    }
    buildHffTree(source);
    return;
}

//从根节点到叶子节点，对所有信源符号进行编码；概率大的为0，小的为1
void GetCodeTable(map<unsigned char, string> &CodeTable, map<string, unsigned char> &InCodeTable, HuffNode *source) {
    if (source->s != 0xFFFFFFFF)//叶子节点
    {
        CodeTable[source->s] = source->code;
        InCodeTable[source->code] = source->s;
        return;
    }
    //先序遍历
    source->left->code = source->code + "0";
    GetCodeTable(CodeTable, InCodeTable, source->left);
    source->right->code = source->code + "1";
    GetCodeTable(CodeTable, InCodeTable, source->right);
}

//打印编码表
void print(map<unsigned char, string> CodeTable) {
    map<unsigned char, string>::iterator p;
    cout << "信源符号" << setw(10) << "编码" << endl;
    for (p = CodeTable.begin(); p != CodeTable.end(); p++) {
        cout << hex << (int) p->first << setw(16) << p->second << endl;
    }
}

//计算平均码长
double GetAverageCodeLength(map<unsigned char, string> CodeTable, double *M/*概率矩阵*/) {
    double L = 0;
//    double count = 512 * 512 * 3;
    map<unsigned char, string>::iterator p;
    for (p = CodeTable.begin(); p != CodeTable.end(); p++) {
        L = L + M[p->first] * p->second.size();
    }
    cout << "平均编码长度：" << L << "比特/信源符号" << endl;
    return L;
}

//计算编码效率
double GetCodingEfficiency(map<unsigned char, string> CodeTable, double *M/*概率矩阵*/) {
    double Hs = 0;
//    double count = 512 * 512 * 3;
    double efficiency;
    map<unsigned char, string>::iterator p;
    for (p = CodeTable.begin(); p != CodeTable.end(); p++) {
        if (M[p->first] == 0)
            continue;
        Hs += log(M[p->first]) * (M[p->first]) / log(2);
    }
/*    Hs = Hs / log(2);*/
    Hs = -Hs;
    cout << Hs << " <= L <= " << Hs + 1 << endl;
    efficiency = GetAverageCodeLength(CodeTable, M);
    cout << "编码效率：" << Hs / efficiency << endl;
    return Hs / efficiency;

}

//打印 信源符号与其对应的配重
void print(vector<HuffNode *> source) {
    for (int i = 0; i < source.size(); i++) {
        cout << hex << source[i]->s << " " << source[i]->weight << endl;
    }
}

//判断是否唯一可译
bool IsUnique(map<unsigned char, string> &CodeTable) {
    map<unsigned char, string>::iterator p, q;
    for (p = CodeTable.begin(); p != CodeTable.end(); p++)
        for (q = p; q != CodeTable.end(); q++)
            if (p->second == q->second && p != q)
                return false;
    return true;
}