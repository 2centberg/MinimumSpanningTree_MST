#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct edges
{
	int weight;
	int vertices1;
	int vertices2;
};
const int &&INF = 32767;
void Init(vector<edges> &arr, int &Gsize);
void Kruskal(vector<edges> &arr, const int &Gsize);
bool valid(vector<vector<int>> &cyc, const edges &x, const int &Gsize);
bool operator<(edges e1, edges e2)
{
	return e1.weight < e2.weight;
};
int main(int argc, char **argv)
{
	cout << "\tKruskal Algorithm\n\n";
	vector<edges> arr;
	int Gsize;
	Init(arr, Gsize);
	Kruskal(arr, Gsize);
	return 0;
};
void Init(vector<edges> &arr, int &Gsize)
{
	fstream INPUT("input.txt", ios::in);
	INPUT >> Gsize;
	string line;
	for (int i = 0; i < Gsize; i++)
	{
		for (int j = 0; j < Gsize; j++)
		{
			INPUT >> line;
			if (j <= i)
				continue;
			if (line != "INF")
				arr.push_back({stoi(line), i, j});
		}
	}
	INPUT.close();
};
void Kruskal(vector<edges> &arr, const int &Gsize)
{
	sort(arr.begin(), arr.end());
	int count = 0, tree_weight = 0;
	vector<vector<int>> cyc(Gsize);
	for (int i = 0; i < arr.size(); i++)
	{
		if (valid(cyc, arr[i], Gsize))
		{
			printf("(%d,%d) : %d\n", arr[i].vertices1 + 1, arr[i].vertices2 + 1, arr[i].weight);
			tree_weight = tree_weight + arr[i].weight;
			cyc[arr[i].vertices1].push_back(arr[i].vertices2);
			cyc[arr[i].vertices2].push_back(arr[i].vertices1);
			count++;
			if (count == Gsize - 1)
				break;
		}
	}
	cout << "Trong luong cua cay : " << tree_weight;
};
bool valid(vector<vector<int>> &cyc, const edges &x, const int &Gsize)
{
	queue<int> q;
	vector<bool> visited(Gsize, false);
	for (int i = 0; i < Gsize; i++)
		visited[i] = 0;
	q.push(x.vertices1);
	int top;
	while (!q.empty())
	{
		top = q.front();
		q.pop();
		for (int i = 0; i < cyc[top].size(); i++)
		{
			if (cyc[top][i] == x.vertices2)
				return 0;
			if (!visited[cyc[top][i]])
			{
				visited[cyc[top][i]] = 1;
				q.push(cyc[top][i]);
			}
		}
	}
	return 1;
};