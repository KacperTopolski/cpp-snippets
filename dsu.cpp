struct DSU
{
    vi v;
    vi sz;
    
    DSU(int k)
    {
        v.resize(k);
        iota(all(v), 0);
        sz = vi(k, 1);
    }
    
    int find(int x)
    {
        if (v[x] == x)
            return x;
        return v[x] = find(v[x]);
    }
    
    bool merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        
        if (x == y) return false;
        
        if (sz[y] > sz[x]) swap(x, y);
        
        sz[x] += sz[y];
        v[y] = x;
        
        return true;
    }

    int size(int i)
    {
        return sz[find(i)];
    }
};