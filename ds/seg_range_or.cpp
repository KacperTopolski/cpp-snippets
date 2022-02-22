struct seg
{
    int n;
    vb v;
    
    seg(int nn = 262144) : n(nn), v(2*nn) { }
    
    bool at(int x)
    {
        if (x < 0 || x >= n)
            return false;
        
        bool on = false;
        
        x += n;
        while (x)
        {
            on |= v[x];
            x /= 2;
        }
        return on;
    }
    
    void range_on_int(int l, int r, int node, int nl, int nr)
    {
        if (l == nl && r == nr)
        {
            v[node] = true;
        }
        else
        {
            int mid = (nl+nr) / 2;
            
            if (r <= mid)
                seg_add_int(l,r,node*2,nl,mid);
            else if (l > mid)
                seg_add_int(l,r,node*2+1,mid+1,nr);
            else
            {
                seg_add_int(l,mid,node*2, nl,mid);
                seg_add_int(mid+1,r,node*2+1, mid+1,nr);
            }
        }
    }
    void range_on(int l, int r)
    {
        range_on_int(l,r,1,0,n-1);
    }
    
};