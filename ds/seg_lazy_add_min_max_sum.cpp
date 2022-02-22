template<typename T> struct lazySegTree
{
    int sz = 1;
    vector<T> lazy, rmin, rmax, rsum;
    
    lazySegTree(int s)
    {
        while (sz < s) sz *= 2;
        lazy.resize(sz*2);
        rmin.resize(sz*2);
        rmax.resize(sz*2);
        rsum.resize(sz*2);
    }
    
    void push(int n)
    {
        T val = lazy[n];
        lazy[n] = 0;
        
        if (n >= sz) return;
            
        for (int i : {2*n, 2*n+1})
        {
            rmin[i] += val;
            rmax[i] += val;
            lazy[i] += val;
            rsum[i] += val * (sz >> bit_width(unsigned(n)));
        }
    }
    
    void range_add_int(int l, int r, T x, int node, int nl, int nr)
    {
        if (l == nl && r == nr)
        {
            rmin[node] += x;
            rmax[node] += x;
            lazy[node] += x;
            rsum[node] += x * (nr - nl + 1);
            return;
        }
        
        if (lazy[node]) push(node);
        int mid = (nl+nr)/2;
            
        if (r <= mid)
            range_add_int(l,r,x,node*2,nl,mid);
        else if (l > mid)
            range_add_int(l,r,x,node*2+1,mid+1,nr);
        else
        {
            range_add_int(l,mid,x,node*2,nl,mid);
            range_add_int(mid+1,r,x,node*2+1,mid+1,nr);
        }
            
        rmin[node] = min(rmin[node*2], rmin[node*2+1]);
        rmax[node] = max(rmax[node*2], rmax[node*2+1]);
        rsum[node] = rsum[node*2] + rsum[node*2+1];
    }
    void range_add(int l, int r, T x) {range_add_int(l,r,x,1,0,sz-1); }
    
    T query_min_int(int l, int r, int node, int nl, int nr)
    {
        if (l == nl && r == nr)
            return rmin[node];
        
        if (lazy[node]) push(node);
        int mid = (nl+nr)/2;
        
        if (r <= mid)
            return query_min_int(l,r,node*2,nl,mid);
        else if (l > mid)
            return query_min_int(l,r,node*2+1,mid+1,nr);
        else
            return min(query_min_int(l,mid,node*2,nl,mid), query_min_int(mid+1,r,node*2+1,mid+1,nr));
    }
    T query_min(int l, int r) {return query_min_int(l,r,1,0,sz-1); }
    
    T query_max_int(int l, int r, int node, int nl, int nr)
    {
        if (l == nl && r == nr)
            return rmax[node];
        
        if (lazy[node]) push(node);
        int mid = (nl+nr)/2;
        
        if (r <= mid)
            return query_max_int(l,r,node*2,nl,mid);
        else if (l > mid)
            return query_max_int(l,r,node*2+1,mid+1,nr);
        else
            return max(query_max_int(l,mid,node*2,nl,mid), query_max_int(mid+1,r,node*2+1,mid+1,nr));
    }
    T query_max(int l, int r) {return query_max_int(l,r,1,0,sz-1); }
    
    T query_sum_int(int l, int r, int node, int nl, int nr)
    {
        if (l == nl && r == nr)
            return rsum[node];
        
        if (lazy[node]) push(node);
        int mid = (nl+nr)/2;
        
        if (r <= mid)
            return query_sum_int(l,r,node*2,nl,mid);
        else if (l > mid)
            return query_sum_int(l,r,node*2+1,mid+1,nr);
        else
            return query_sum_int(l,mid,node*2,nl,mid) + query_sum_int(mid+1,r,node*2+1,mid+1,nr);
    }
    T query_sum(int l, int r) {return query_sum_int(l,r,1,0,sz-1); }
};