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
    vector<int> rankValue;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        rankValue.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    bool unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
            return false;

        if (rankValue[rootA] < rankValue[rootB])
            parent[rootA] = rootB;
        else if (rankValue[rootA] > rankValue[rootB])
            parent[rootB] = rootA;
        else
        {
            parent[rootB] = rootA;
            rankValue[rootA]++;
        }

        return true;
    }
};

bool compareEdges(const Edge& a, const Edge& b)
{
    return a.weight < b.weight;
}

int main()
{
    vector<Edge> edges =
    {
        {0, 1, 2},
        {0, 2, 3},
        {1, 2, 1},
        {1, 3, 4},
        {2, 3, 2},
        {2, 4, 5},
        {3, 4, 1}
    };

    int numberOfNodes = 5;

    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind uf(numberOfNodes);

    int totalWeight = 0;

    cout << "Kruskal's Minimum Spanning Tree\n\n";

    cout << "Selected Edges:\n";

    for (const Edge& edge : edges)
    {
        if (uf.unite(edge.u, edge.v))
        {
            cout << edge.u << " -- "
                 << edge.v
                 << "  Weight = "
                 << edge.weight << endl;

            totalWeight += edge.weight;
        }
    }

    cout << "\nTotal MST Weight = "
         << totalWeight << endl;

    return 0;
}