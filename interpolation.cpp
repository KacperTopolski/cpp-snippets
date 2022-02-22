//template<typename F> F interpolate(F x, const vector<pair<F, F>>& P) //O(n^2) TODO

template<typename F> void fillFactInv(vector<F>& fInv, int n)
{
    fInv.resize(n + 1);
    
    F nFact(1);
    for (int i = 2; i <= n; ++i)
        nFact *= i;
    
    fInv[n] = 1 / nFact;
    
    for (int i = n - 1; i >= 0; --i)
        fInv[i] = fInv[i + 1] * (i + 1);
}

template<typename F> F interpolateFast(F x, const vector<F>& P, const vector<F>& fInv) //O(n)
{
    int n = P.size();
    assert(n);
    assert(fInv.size() >= n);
    assert(F(n) < x);
        
    F ans(0), num(1);

    for (int i = 0; i < n; ++i)
        num *= x - i;
    
    for (int i = 0; i < n; ++i)
        ans += P[i] * num / (x - i) * fInv[i] * fInv[n-i-1] * ((M - i)&1 ? 1 : -1);
    
    return ans;
}