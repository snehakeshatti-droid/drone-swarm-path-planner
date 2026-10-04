#include <iostream>
#include <vector>

using namespace std;

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

    bool connected(int a, int b)
    {
        return find(a) == find(b);
    }
};

int main()
{
    UnionFind uf(5);

    cout << "Union-Find Test\n\n";

    cout << "Joining 0 and 1" << endl;
    uf.unite(0, 1);

    cout << "Joining 1 and 2" << endl;
    uf.unite(1, 2);

    cout << "Joining 3 and 4" << endl;
    uf.unite(3, 4);

    cout << "\nChecking connections:\n";

    if (uf.connected(0, 2))
        cout << "0 and 2 are connected" << endl;
    else
        cout << "0 and 2 are not connected" << endl;

    if (uf.connected(0, 4))
        cout << "0 and 4 are connected" << endl;
    else
        cout << "0 and 4 are not connected" << endl;

    return 0;
}