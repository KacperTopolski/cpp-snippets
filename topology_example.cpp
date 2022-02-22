#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

string i_to_s(int v, int n)
{
    string ret(n, '0');
    for (int i = 0; i < n; ++i)
        if (v & (1 << i))
            ret[i] = '1';
            
    return ret;
}

struct Topology
{
    int n;
    vector<bool> U;
    
    Topology(int _n) : n(_n), U(1 << _n)
    {
        U.front() = U.back() = 1;
    }
    
    int full() const
    {
        return (1 << n) - 1;
    }
    
    bool verify() const
    {
        if ((int)U.size() != (1 << n) || !U[0] || !U[full()])
            return false;
            
        for (int i = 0; i <= full(); ++i)
        {
            if (!U[i])
                continue;
                
            for (int j = 0; j <= full(); ++j)
            {
                if (!U[j])
                    continue;
                    
                if (!U[i|j] || !U[i&j])
                    return false;
            }
        }
        
        return true;
    }
    
    Topology induce(int R) const
    {
        int m = popcount(unsigned(R));
        Topology ind(m);
        
        for (int i = 0; i <= full(); ++i)
        {
            if (!U[i])
                continue;
                
            int ind_set = 0;
            
            for (int j = 0, k = 0; j < n; ++j)
            {
                if ((1 << j) & R)
                {
                    if ((1 << j) & i)
                        ind_set |= 1 << k;
                        
                    ++k;
                }
            }
            
            ind.U[ind_set] = 1;
        }
        
        return ind;
    }
    
    bool is_f_continuous(const vector<int> &f) const
    {
        vector<int> singleton_pre(n);
        
        for (int i = 0; i < n; ++i)
            singleton_pre[f[i]] |= 1 << i;
            
        for (int i = 0; i <= full(); ++i)
        {
            if (!U[i])
                continue;
                
            int pre = 0;
            
            for (int j = 0; j < n; ++j)
                if (i & (1 << j))
                    pre |= singleton_pre[j];
                    
            if (!U[pre])
                return false;
        }
        
        return true;
    }
    
    bool has_fpp() const
    {
        vector<int> f(n);
        auto iter = [&](auto l, int i)
        {
            if (i == n)
                return !is_f_continuous(f);
            
            for (int j = 0; j < n; ++j)
            {
                if (i == j)
                    continue;
                    
                f[i] = j;
                
                if (!l(l, i+1))
                    return false;
            }
            
            return true;
        };
        
        return iter(iter, 0);
    }
    
    friend ostream& operator<<(ostream& os, const Topology& top)
    {
        if (!top.verify())
            os << "[non] ";
        else if (top.has_fpp())
            os << "[FPP] ";
        else
            os << "[   ] ";
        
        os << "topo on " << top.n << " points : {";
        
        for (int i = 0; i <= top.full(); ++i)
        {
            if (!top.U[i])
                continue;
                
            os << i_to_s(i, top.n) << ',';
        }
        
        return os << '}';
    }
};

void iterate_over_topo(int n, auto f)
{
    Topology top(n);
    
    auto iter = [&](auto l, int i)
    {
        if (i == top.full())
        {
            f(top);
            return;
        }
        
        top.U[i] = 0;
        l(l, i + 1);
            
        top.U[i] = 1;
        l(l, i + 1);
    };
    
    iter(iter, 1);
}

int main()
{
    iterate_over_topo(3, [](Topology &top)
    {
        if (!top.verify())
            return;
            
        if (top.has_fpp())
            return;
            
        for (int A = 1; A < (1 << top.n) - 1; ++A)
        {
            Topology A_top = top.induce(A);
            if (!A_top.has_fpp())
                continue;
            
            for (int B = 1; B < A; ++B)
            {
                if ((A&B) == 0 || (A|B) != top.full())
                    continue;
                    
                Topology B_top = top.induce(B);
                if (!B_top.has_fpp())
                    continue;
                    
                Topology AB_top = top.induce(A&B);
                if (!AB_top.has_fpp())
                    continue;
                    
                cout << string(top.n+1, ' ') << top << endl;
                cout << i_to_s(A, top.n) << ' ' << A_top << endl;
                cout << i_to_s(B, top.n) << ' ' << B_top << endl;
                cout << i_to_s(A&B, top.n) << ' ' << AB_top << endl << endl;
            }
        }
    });

    return 0;
}
