#include<iostream>
#include<queue>
using namespace std;

struct AdjNode
{
	char data;
	int index;
	int num;
	AdjNode* next;
};

struct AdjList
{
	AdjNode node;
	bool isvisted;
};

class UDG
{
public:
	UDG();
	~UDG();
	bool bfs();
	bool dfs();
protected:
	int bfs(int i);
	int dfs(int i);
private:
	struct AdjList* list;
	int V_num;
};

UDG::UDG()
{
	cout << "请输入所有顶点数:";
	cin >> V_num;
	list = new AdjList[V_num];
	cout << "请依次输入每个顶点的名称:" << endl;
	for (int i = 0; i < V_num; i++)
	{
		cin >> list[i].node.data;
		list[i].node.index = i + 1;
		list[i].node.next = NULL;
	}
	for (int i = 0; i < V_num; i++)
	{
		int size;
		cout << "请输入第" << i + 1 << "个顶点的邻接点数量:";
		cin >> size;
		for (int j = 1; j <= size; j++)
		{
			int index, E_num;
			cout << "请依次输入第"<<j<<"个邻接点的编号,到达该邻接点的边数:";
			cin >> index >> E_num;
			AdjNode* p = new AdjNode;
			p->index = index;
			p->num = E_num;
			p->next = list[i].node.next;
			list[i].node.next = p;
		}
	}
}

UDG::~UDG()
{
	for (int i = 0; i < V_num; i++)
	{
		while (list[i].node.next!=NULL)
		{
			AdjNode* p = new AdjNode;
			p = list[i].node.next;
			list[i].node.next = p->next;
			delete p;
		}
	}
	delete[]list;
}

bool UDG::bfs()
{
	for (int i = 0; i < V_num; i++)
		list[i].isvisted = false;
	int length = 0;
	int count = 0;
	for (int i = 0; i < V_num; i++)
	{
		if (!list[i].isvisted)
		{
			length += bfs(i + 1);
			count++;
		}
	}
	bool a = true;
	if (count != 1)
	{
		cout << "该图不连通" << endl;
		a = false;
	}
	if (length != V_num - 1)
	{
		cout << "该图不满足|V|=|E|+1" << endl;
		a = false;
	}
	return a;
}
int UDG::bfs(int i)
{
	queue<int> Queue;
	Queue.push(i);
	int length = 0;
	while (!Queue.empty())
	{
		int index = Queue.front();
		cout << list[index-1].node.data << " ";
		Queue.pop();
		list[index - 1].isvisted = true;
		AdjNode* p = list[index - 1].node.next;
		while (p != NULL)
		{
			if (!list[p->index - 1].isvisted)
			{
				Queue.push(p->index);
				length += p->num;
			}
			p = p->next;
		}
	}
	cout << endl;
	return length;
}

bool UDG::dfs()
{
	for (int i = 0; i < V_num; i++)
		list[i].isvisted = false;
	int length = 0;
	int count = 0;
	for (int i = 0; i < V_num; i++)
	{
		if (!list[i].isvisted)
		{
			length += dfs(i);
			count++;
		}
	}
	cout << endl;
	bool a = true;
	if (count != 1)
	{
		cout << "该图不连通" << endl;
		a = false;
	}
	if (length != V_num - 1)
	{
		cout << "该图不满足|V|=|E|+1" << endl;
		a = false;
	}
	return a;
}

int UDG::dfs(int i)
{
	int length = 0;
	list[i].isvisted = true;
	cout << list[i].node.data << " ";
	AdjNode* p = new AdjNode;
	p = list[i].node.next;
	while (p != NULL)
	{
		if (!list[p->index - 1].isvisted)
		{
			length += p->num;
			length+=dfs(p->index - 1);
		}
		p = p->next;
	}
	return length;
}
int main()
{
	UDG graph;
	cout << "通过广度优先搜索算法判断：" << endl;
	if (graph.bfs()) cout << "该图是树" << endl;
	else cout << "该图不是树" << endl;
	cout << endl << endl << endl;
	cout << "通过深度优先搜索算法判断:" << endl;
	if (graph.dfs()) cout << "该图是树" << endl;
	else cout << "该图不是树" << endl;
	return 0;
}

