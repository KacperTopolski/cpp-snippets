template<typename It, typename Func> 
vector<It> lIncSub(It beg, It end, Func f)
{
    if (beg == end)
        return {};
    
    vector<It> dp, ret;
    map<It, It> before;
    
    auto g = [&f](It x, It y){return f(*x, *y); };
    
    for (; beg != end; ++beg)
    {
        auto pos = lower_bound(dp.begin(), dp.end(), beg, g);
        if (pos != dp.begin())
            before[beg] = *prev(pos, 1);
        if (pos == dp.end())
            dp.push_back(beg);
        else
            *pos = beg;
    }
    
    It last = dp.back();
    ret.push_back(last);
    
    while (before.count(last))
    {
        last = before[last];
        ret.push_back(last);
    }
    
    reverse(ret.begin(), ret.end());
    
    return ret;
}

template<typename It, typename Func> 
int lIncSubSize(It beg, It end, Func f)
{
    if (beg == end)
        return 0;
    
    vector<It> dp;
    
    auto g = [&f](It x, It y){return f(*x, *y); };
    
    for (; beg != end; ++beg)
    {
        auto pos = lower_bound(dp.begin(), dp.end(), beg, g);
        if (pos == dp.end())
            dp.push_back(beg);
        else
            *pos = beg;
    }
    
    return dp.size();
}

//vi test = {5, 9, 2, 7, 7, 13, 1};
//auto x = lis(all(test), less_equal<int>());
//for (auto t : x) cout << *t << ' '; //2 7 7 13
