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
void Init(vector<vector<int>> &arr, int &Gsize);
void Prim(vector<vector<int>> &arr, const int &Gsize);
bool valid(const vector<vector<int>> &cyc, const edges &x, const int &Gsize);
bool operator<(edges e1, edges e2)
{
	return e1.weight < e2.weight;
}
int main(int argc, char **argv)
{
	cout << "\tPrim Algorithm\n\n";
	vector<vector<int>> weights;
	int Gsize = 0;
	Init(weights, Gsize);
	Prim(weights, Gsize);
	return 0;
}
void Init(vector<vector<int>> &weights, int &Gsize)
{
	fstream INPUT("input.txt", ios::in);
	INPUT >> Gsize;
	string line;
	vector<int> x(Gsize);
	for (int i = 0; i < Gsize; i++)
	{
		for (int j = 0; j < Gsize; j++)
		{
			INPUT >> line;
			if (line != "INF")
				x[j] = stoi(line);
			else
				x[j] = INF;
		}
		weights.push_back(x);
	}
	INPUT.close();
};
void Prim(vector<vector<int>> &arr, const int &Gsize)
{
	int tree_weight = 0;
	vector<int> X, Y(1,0);
	for (int i = 1; i <= Gsize-1; i++)
		X.push_back(i);
	vector<edges> ans;
	vector<edges> temp;
	vector<vector<int>> cyc(Gsize);
	while (X.size() != 0)
	{
		temp.clear();
		for (int &i : X)
		{
			for (int &j : Y)
			{
				if (arr[i][j] != INF)
					temp.push_back({arr[i][j], i, j});
			}
		}
		sort(temp.begin(), temp.end());
		for (edges &e : temp)
		{
			if (valid(cyc, e, Gsize))
			{
				ans.push_back(e);
				cyc[e.vertices1].push_back(e.vertices2);
				cyc[e.vertices2].push_back(e.vertices1);
				for (int i = 0; i < X.size(); i++)
				{
					if (X[i] == e.vertices1)
					{
						swap(X[i], X.back());
						Y.push_back(X.back());
						X.pop_back();
					}
				}
				tree_weight = tree_weight + e.weight;
				break;
			}
		}
	}
	for (edges &e : ans)
	{
		printf("(%d,%d) %d\n", e.vertices1 + 1, e.vertices2 + 1, e.weight);
	}
	cout << "Trong luong cua cay : " << tree_weight;
}
bool valid(const vector<vector<int>> &cyc, const edges &x, const int &Gsize)
{
	queue<int> q;
	vector<bool> visited(Gsize);
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
}