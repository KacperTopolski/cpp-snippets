struct seg
{
    int n;
    vector<mod998s> v;
    
    void reset(int m)
    {
        n = 1;
        while (n < m)
            n *= 2;
        v.resize(2 * n);
        fill(all(v), 0);
    }
    seg(int m = 1) {reset(m); }
    
    void set_at(int p, mod998s x)
    {
        p += n;
        v[p] = x;
        p /= 2;
        
        while (p)
        {
            v[p] = v[2*p] + v[2*p+1];
            p /= 2;
        }
    }
    
    mod998s seg_sum_int(int l, int r, int node, int nl, int nr)
    {
        if (l == nl && r == nr)
            return v[node];
            
        int mid = (nl+nr) / 2;
            
        if (r <= mid)
            return seg_sum_int(l,r,node*2,nl,mid);
        else if (l > mid)
            return seg_sum_int(l,r,node*2+1,mid+1,nr);
            
        return seg_sum_int(l,mid,node*2, nl,mid) + seg_sum_int(mid+1,r,node*2+1, mid+1,nr);
    }
    mod998s seg_sum(int l, int r)
    {
        return seg_sum_int(l,r,1,0,n-1);
    }
};