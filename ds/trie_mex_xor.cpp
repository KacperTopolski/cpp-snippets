struct trie
{
    int count = 0;
    int toPush = 0;
    int child[2] = {0, 0};
};
 
vector<trie> v;
 
void push(int x, int t = 1, int bit = 20)
{
    ++v[t].count;
    
    if (!bit)
        return;
        
    int lowbit = bit - 1;
    bool on = (x & (1 << lowbit));
    
    if (!v[t].child[on])
        v[t].child[on] = v.size();
    v.emplace_back();
    
    push(x, v[t].child[on], bit - 1);
}
 
int mex(int t = 1, int bit = 20)
{
    if ((v[t].toPush << 1) & (1 << bit))
        swap(v[t].child[0], v[t].child[1]);
        
    for (int i : v[t].child)
        if (i)
            v[i].toPush ^= v[t].toPush;
        
    v[t].toPush = 0;
    
    int c0 = v[t].child[0];
    int c1 = v[t].child[1];
    
    if (!c0)
        return 0;
    
    if (v[c0].count < (1 << (bit - 1)))
        return mex(c0, bit - 1);
        
    if (!c1)
        return 1 << (bit-1);
        
    return (1 << (bit-1)) + mex(c1, bit - 1);
}