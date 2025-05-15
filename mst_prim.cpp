#include <iostream>
#define INF (~0U >> 2)
using namespace std;

void mst_prim(int weight[][7], int n)
{
	int* selected = new int[n] {0};
	int edge_count = 0;

	selected[0] = 1;

	while (edge_count < n-1)
	{
		int min = INF;
		int u = 0, v = 0;

		for (int i = 0; i < n; i++)
		{
			if (selected[i] == 1)
			{
				for (int j = 0; j < n; j++)
				{
					if ((selected[j] == 0) && weight[i][j] > 0 && weight[i][j] != INF)
					{
						if (min > weight[i][j])
						{
							min = weight[i][j];
							u = i;
							v = j;
						}
					}
				}
			}
		}

		selected[v] = 1;
		cout << u << " " << v << " " << weight[u][v] << endl;
		edge_count += 1;
	}
	delete [] selected;
}

int main()
{
	int graph[7][7] = {
	{ 0, 29, INF, INF, INF, 10, 7 },
	{ 29, 0, 16, INF, INF, INF, 15 },
	{ INF, 16, 0, 12, INF, INF, 13 },
	{ INF, 29, 12, 0, 22, INF, 18 },
	{ INF, INF, INF, 22, 0, 27, 25 },
	{ 10, INF, INF, INF, 27, 0, INF },
	{ 7, 15, 13, 18, 25, INF, 0 },
	};

	mst_prim(graph, 7);
}