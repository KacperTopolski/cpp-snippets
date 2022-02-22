struct trie
{
    int l = inf, r = -inf;
    int bit;
    //bool on;
    int ans = inf;
    int toPush = 0;
    
    int child[2] = {0, 0};
    
    trie(int b/*, bool o*/) : bit(b)/*, on(o)*/ { }
};
 
vector<trie> v;
 
void push(int x, int tr = 1)
{
    mini(v[tr].l, x);
    maxi(v[tr].r, x);
    
    if (v[tr].bit)
    {
        int lowbit = v[tr].bit - 1;
        bool on = (x & (1 << lowbit));
 
        if (!v[tr].child[on])
        {
            v[tr].child[on] = v.size();
            v.emplace_back(lowbit/*, on*/);
        }
        
        push(x, v[tr].child[on]);
    }
}
 
void print(int tr = 1)
{
    cout << dbg(tr) << dbg(v[tr].bit) << dbg(v[tr].toPush) << dbg(v[tr].ans) << dbg(v[tr].l) << dbg(v[tr].r) << dbg(v[tr].child[0]) << dbg(v[tr].child[1]) << '\n';
    for (int i : v[tr].child)
        if (i)
            print(i);
}
 
void calcAns(int tr = 1)
{
    for (int i : v[tr].child)
        if (i)
        {
            calcAns(i);
            mini(v[tr].ans, v[i].ans);
        }
            
    if (v[tr].l != v[tr].r)
        mini(v[tr].ans, v[tr].r - v[tr].l);
        
    if (v[tr].child[0] && v[tr].child[1])
        mini(v[tr].ans, v[v[tr].child[1]].l - v[v[tr].child[0]].r);
}
 
void xr(int val, int tr = 1)
{
    int mask = (1 << (v[tr].bit +1)) - 1;
    
    if (val & mask)
    {
        for (int i : v[tr].child)
            if (i)
                xr(val ^ v[tr].toPush, i);
                
        v[tr].toPush = 0;
                    
        if ((val << 1) & (1 << v[tr].bit))
            swap(v[tr].child[0], v[tr].child[1]);
            
        if (v[tr].bit)
        {
            v[tr].l = inf;
            v[tr].r = -inf;
        }
        else
        {
            v[tr].l ^= val;
            v[tr].r ^= val;
        }
            
        v[tr].ans = inf;
        
        for (int i : v[tr].child)
            if (i)
            {
                mini(v[tr].l, v[i].l);
                maxi(v[tr].r, v[i].r);
                mini(v[tr].ans, v[i].ans);
            }
            
        if (v[tr].l != v[tr].r)
            mini(v[tr].ans, v[tr].r - v[tr].l);
            
        if (v[tr].child[0] && v[tr].child[1])
            mini(v[tr].ans, v[ v[tr].child[1] ].l - v[ v[tr].child[0] ].r);
            
    }
    else
    {
        v[tr].toPush ^= val;
        v[tr].l ^= val;
        v[tr].r ^= val;
    }
}