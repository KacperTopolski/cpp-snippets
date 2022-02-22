int mn(int x, int y) {return x < y ? x : y; }
int mx(int x, int y) {return x < y ? y : x; }

template<decltype(mn) F>
struct tree
{
    int n = 1;
    vi seg;
    
    tree(vi& init)
    {
        while (n < init.size()) n *= 2;
        seg.resize(2 * n);
        copy(all(init), seg.begin() + n);
        
        for (int i = n - 1; i; --i)
            seg[i] = F(seg[2*i], seg[2*i+1]);
    }
    tree(int k)
    {
        while (n < k) n *= 2;
        seg.resize(2 * n);
    }
    
    void setAt(int pos, int x)
    {
        pos += n;
        seg[pos] = x;
        pos /= 2;
        
        while (pos)
        {
            seg[pos] = F(seg[2*pos], seg[2*pos+1]);
            pos /= 2;
        }
    }
    
    int query_int(int l, int r, int node, int nl, int nr)
    {
        // cout << dbg(l) << dbg(r) << dbg(node) << dbg(nl) << dbg(nr) << endl;
        
        if (l == nl && r == nr)
            return seg[node];
            
        int mid = (nl + nr) / 2;
        
        if (r <= mid)
            return query_int(l, r, node * 2, nl, mid);
        if (l > mid)
            return query_int(l, r, node * 2 + 1, mid + 1, nr);
            
        return F(query_int(l, mid, node * 2, nl, mid), query_int(mid + 1, r, node * 2 + 1, mid + 1, nr));
    }
    
    int query(int l, int r) {return query_int(l, r, 1, 0, n - 1); }
};