#include <iostream>
#define INF (~0U >> 2)
#define MAX_EDGE 100
#define N 7
using namespace std;

struct Edge
{
	int u, v, weight;
};
struct Node
{
	int vertex, weight;
	Node* next;

	Node(int v, int w, Node* n) : vertex(v), weight(w), next(n) {}
};

Edge edges[MAX_EDGE];

void insertion_sort(Edge data[], int edge_count)
{
	for (int i = 1; i < edge_count; i++)
	{
		Edge key = data[i];
		int idx = i - 1;

		while ((idx >= 0) && (data[idx].weight > key.weight))
		{
			data[idx + 1] = data[idx];
			idx--;
		}
		data[idx + 1] = key;
	}
}

bool hasCycle(int u, int parent, Node* list[], int visited[])
{
	visited[u] = 1;
	Node* current = list[u];
	while (current)
	{
		int v = current->vertex;
		if (!visited[v])
		{
			if(hasCycle(v, u, list, visited)) return true;
		}
		else if (v != parent) return true;
		current = current->next;
	}
	return false;
}

void mst_kruskal(int graph[][N])
{
	int edge_count = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			if (graph[i][j] == INF || graph[i][j] <= 0) continue;
			edges[edge_count] = { i, j, graph[i][j] };
			edge_count++;
		}
	}

	insertion_sort(edges, edge_count);

	Node* mst_list[N] = { 0 };

	for (int i = 0; i < edge_count; i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		int weight = edges[i].weight;

		Node* node1 = new Node(v, weight, mst_list[u]);
		Node* node2 = new Node(u, weight, mst_list[v]);
		mst_list[u] = node1;
		mst_list[v] = node2;

		int visited[N] = { 0 };
		bool isCycle = false;

		for (int j = 0; j < N; j++)
		{
			if (!visited[j] && hasCycle(j, -1, mst_list, visited))
			{
				isCycle = true;
				break;
			}
		}

		if (isCycle)
		{
			mst_list[u] = node1->next;
			mst_list[v] = node2->next;
			delete node1;
			delete node2;
		}
		else
			cout << u << " " << v << " " << weight << endl;
	}
}

int main()
{
	int graph[N][N] = {
	{ 0, 29, INF, INF, INF, 10, 7 },
	{ 29, 0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, 13 },
	{ INF, 29, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ 7, 15, 13, 18, 25, INF, 0 },
	};

	mst_kruskal(graph);
}