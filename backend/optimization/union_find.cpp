#include <iostream>
#include <vector>

using namespace std;

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
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    bool unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
        {
            return false;
        }

        if (rankValue[rootA] < rankValue[rootB])
        {
            parent[rootA] = rootB;
        }
        else if (rankValue[rootA] > rankValue[rootB])
        {
            parent[rootB] = rootA;
        }
        else
        {
            parent[rootB] = rootA;
            rankValue[rootA]++;
        }

        return true;
    }
};

int main()
{
    UnionFind uf(6);

    cout << "Union-Find Test\n\n";

    cout << "Joining 0 and 1\n";
    uf.unite(0, 1);

    cout << "Joining 1 and 2\n";
    uf.unite(1, 2);

    cout << "Joining 3 and 4\n";
    uf.unite(3, 4);

    cout << "\nChecking connections:\n";

    if (uf.find(0) == uf.find(2))
        cout << "0 and 2 are connected\n";
    else
        cout << "0 and 2 are not connected\n";

    if (uf.find(0) == uf.find(4))
        cout << "0 and 4 are connected\n";
    else
        cout << "0 and 4 are not connected\n";

    return 0;
}