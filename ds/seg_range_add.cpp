struct seg
{
    int n;
    vector<mod998s> v;
    
    seg(int nn) : n(nn), v(2*nn) { }
    
    mod998s at(int x)
    {
        mod998s ret;
        
        x += n;
        while (x)
        {
            ret += v[x];
            x /= 2;
        }
        return ret;
    }
    
    void seg_add_int(int l, int r, int node, int nl, int nr, mod998s x)
    {
        if (l == nl && r == nr)
        {
            v[node] += x;
        }
        else
        {
            int mid = (nl+nr) / 2;
            
            if (r <= mid)
                seg_add_int(l,r,node*2,nl,mid,x);
            else if (l > mid)
                seg_add_int(l,r,node*2+1,mid+1,nr,x);
            else
            {
                seg_add_int(l,mid,node*2, nl,mid,x);
                seg_add_int(mid+1,r,node*2+1, mid+1,nr,x);
            }
        }
    }
    void seg_add(int l, int r, mod998s x)
    {
        seg_add_int(l,r,1,0,n-1,x);
    }
    
};