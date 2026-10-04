#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int u;
    int v;
    int weight;
};

class UnionFind
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    void unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
            return;

        if (rank[rootA] < rank[rootB])
            parent[rootA] = rootB;
        else if (rank[rootA] > rank[rootB])
            parent[rootB] = rootA;
        else
        {
            parent[rootB] = rootA;
            rank[rootA]++;
        }
    }
};

int main()
{
    vector<Edge> edges =
    {
        {1, 2, 1},
        {3, 4, 1},
        {0, 1, 2},
        {2, 3, 2},
        {0, 2, 3},
        {1, 3, 4}
    };

    sort(edges.begin(), edges.end(),
         [](Edge a, Edge b)
         {
             return a.weight < b.weight;
         });

    UnionFind uf(5);

    int totalWeight = 0;
    int edgesSelected = 0;

    cout << "Kruskal's Minimum Spanning Tree\n\n";
    cout << "Selected Edges:\n";

    for (Edge e : edges)
    {
        if (uf.find(e.u) != uf.find(e.v))
        {
            uf.unite(e.u, e.v);

            cout << e.u << " -- " << e.v
                 << "  Weight = " << e.weight << endl;

            totalWeight += e.weight;
            edgesSelected++;

            if (edgesSelected == 4)
                break;
        }
    }

    cout << "\nTotal MST Weight = "
         << totalWeight << endl;

    return 0;
}