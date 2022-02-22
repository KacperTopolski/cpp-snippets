// Problem: E. Distinctive Roots in a Tree
// Contest: Codeforces - Codeforces Round #695 (Div. 2)
// URL: https://codeforces.com/problemset/problem/1467/E
// Memory Limit: 256 MB
// Time Limit: 3000 ms

#include <bits/stdc++.h>
using namespace std;

#define fastIO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(...) "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define fi first
#define se second
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

#define readRepeatInt int _t; cin >> _t; while (_t--)
#define repeat(i, x) for (int i = 0; i < (x); ++i)
#define repeatRev(i, x) for (int i = (x) - 1; i >= 0; --i)

using ll =  long long;                  using vb = vector<bool>;
// using i128 = __int128;               using vi128 = vector<i128>;
using ull = unsigned long long;         using vull = vector<ull>;
using vll = vector<ll>;                 using vvll = vector<vll>;
using vi = vector<int>;                 using vvi = vector<vi>;

using pi = pair<int, int>;              using vpi = vector<pi>;
using pll = pair<ll, ll>;               using vpll = vector<pll>;

using si = set<int>;                    using sll = set<ll>;
using usi = unordered_set<int>;         using usll = unordered_set<ll>;
using di = deque<int>;                  using dll = deque<ll>;
using mi = map<int, int>;               using mll = map<ll, ll>;
using umi = unordered_map<int, int>;    using umll = unordered_map<ll, ll>;

using vsi = vector<si>;                 using vsll = vector<sll>;
using vusi = vector<usi>;               using vusll = vector<usll>;

template<typename A, typename B> inline A& maxi(A& a, B b) {return a = max(a, A(b)); }
template<typename A, typename B> inline A& mini(A& a, B b) {return a = min(a, A(b)); }

template <typename T> struct reversion_wrapper {T& iterable; };
template <typename T> reversion_wrapper<T> reverse(T&& iterable) {return {iterable}; }
template <typename T> auto begin(reversion_wrapper<T> w) {return rbegin(w.iterable); }
template <typename T> auto end(reversion_wrapper<T> w) {return rend(w.iterable); }

template<typename Iter> inline ostream& streamByIterators(ostream &os, Iter beg, Iter end) {os << '{'; if (beg != end) {os << *beg; while (++beg != end) os << ", " << *beg; }; return os << '}'; }
template<typename T> inline ostream& operator<<(ostream &os, const vector<T> &v) {return streamByIterators(os, v.begin(), v.end()); }
template<typename T> inline ostream& operator<<(ostream &os, const deque<T> &d) {return streamByIterators(os, d.begin(), d.end()); }
template<typename T> inline ostream& operator<<(ostream &os, const set<T> &s) {return streamByIterators(os, s.begin(), s.end()); }
template<typename T, typename V> inline ostream& operator<<(ostream &os, const map<T, V> &m) {return streamByIterators(os, m.begin(), m.end()); }
template<typename T> inline ostream& operator<<(ostream &os, const unordered_set<T> &s) {return streamByIterators(os, s.begin(), s.end()); }
template<typename T, typename V> inline ostream& operator<<(ostream &os, const unordered_map<T, V> &m) {return streamByIterators(os, m.begin(), m.end()); }
template<typename T, size_t size> inline ostream& operator<<(ostream &os, const array<T, size> &a) {return streamByIterators(os, a.begin(), a.end()); }
template<typename A, typename B> inline ostream& operator<<(ostream &os, const pair<A, B> &p) {return os << '(' << p.first << ", " << p.second << ')'; }
 
template<typename T> inline istream& operator>>(istream &is, vector<T> &v) {for (T& t : v) is >> t; return is; }
template<typename T> inline istream& operator>>(istream &is, deque<T> &d) {for (T& t : d) is >> t; return is;}
template<typename T, size_t size> inline istream& operator>>(istream &is, array<T, size> &a) {for (T& t : a) is >> t; return is; }
template<typename A, typename B> inline istream& operator>>(istream &is, pair<A, B> &p) {return is >> p.first >> p.second; }

template<typename T, typename V> T constexpr myPow(T base, V exp) {T ans(1); while (exp > 0) {if (exp & 1) ans *= base; base *= base; exp >>= 1; } return ans; }
template<typename T, typename V> T constexpr myPowMod(T base, T mod, V exp) {T ans(1); while (exp > 0) {if (exp & 1) ans = (ans * base) % mod; base = (base * base) % mod; exp >>= 1; } return ans; }
template<typename T> inline constexpr T myMod(T val, T mod) {val %= mod; if (val < 0) val += mod; return val; }
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int n, dfsTime = 0;
vi preOrder, postOrder, height;
vusi G;
vvi byHeight, binaryLift;
vb killSubTree;
vi killUpperTreeExceptPost;
vsi leavesPostOrder;

const int binLiftSize = 20;

void dfsInit(int u, int h)
{
    preOrder[u] = dfsTime++;
    height[u] = h;
    byHeight[h].push_back(u);
    
    for (int i = 1; i < binLiftSize; ++i)
    {
        if (binaryLift[u][i-1] != -1)
            binaryLift[u][i] = binaryLift[ binaryLift[u][i-1] ][i-1];
    }
    
    for (int e : G[u])
    {
        G[e].erase(u);
        binaryLift[e][0] = u;
        dfsInit(e, h + 1);
    }
    
    for (int e : G[u])
        leavesPostOrder[u].insert(postOrder[e]);
    
    postOrder[u] = dfsTime++;
}

int getAncestor(int u, int h)
{
    while (height[u] != h)
    {
        for (int i : reverse(binaryLift[u]))
        {
            if (i != -1 && height[i] >= h)
            {
                u = i;
                break;
            }
        }
    }
        
    return u;
}

int lca(int u, int v)
{
    if (height[u] < height[v])
        swap(u, v);
    if (height[u] > height[v])
        u = getAncestor(u, height[v]);
        
    while (u != v)
    {
        // cout << dbg(u) << dbg(v) << endl;
        
        for (int j = binLiftSize - 2; j >= 0; --j)
        {
            if (binaryLift[u][j] != binaryLift[v][j])
            {
                u = binaryLift[u][j];
                v = binaryLift[v][j];
                break;
            }
            if (j == 0)
                return binaryLift[u][0];
        }
    }
        
    return u;
}

int32_t main()
{
    fastIO;
    
    cin >> n;
    
    map<int, vi> byCol;
    repeat(i, n)
    {
        int col;
        cin >> col; //col = 1;
        byCol[col].push_back(i);
    }
    
    preOrder = vi(n);
    postOrder = vi(n);
    height = vi(n);
    
    G = vusi(n);
    
    binaryLift = vvi(n, vi(binLiftSize, -1));
    byHeight = vvi(n);
    
    killSubTree = vb(n);
    killUpperTreeExceptPost = vi(n, -1);
    
    leavesPostOrder = vsi(n);
    
    repeat(_, n - 1)
    {
        int u, v;
        cin >> u >> v;
        --u; --v;
        // u = _;
        // v = _ + 1;        
        
        G[u].insert(v);
        G[v].insert(u);
    }
    
    dfsInit(0, 0);
    
    // repeat(i, n)
        // cout << dbg(i) << dbg(binaryLift[i]) << endl;
//     
    // cout << lca(9, 18) << endl;
    
    for (auto& [col, e] : byCol)
    {
        if (e.size() <= 1)
            continue;
            
        int currLCA = e[0];
        for (int i : e)
            currLCA = lca(currLCA, i);
            
        bool LCA_in_E = false;
        for (int i : e)
            if (i == currLCA)
                LCA_in_E = true;
                
        if (!LCA_in_E)
        {
            vpi orders;
            orders.reserve(e.size());
            
            for (int i : e)
            {
                orders.emplace_back(preOrder[i], postOrder[i]);
                killSubTree[i] = true;
            }
            sort(all(orders));
            
            for (int i = 1; i < (int)orders.size(); ++i)
            {
                if (orders[i].fi < orders[i-1].se)
                {
                    cout << 0;
                    return 0;
                }
            }
        }
        else
        {
            vpi orders;
            orders.reserve(e.size());
            
            usi LCAsLeavesPostOrders;
            
            // killUpperTree[currLCA] = true;
            for (int i : e)
            {
                if (i == currLCA) continue;
                
                LCAsLeavesPostOrders.insert(*leavesPostOrder[currLCA].lower_bound(preOrder[i]));
                
                orders.emplace_back(preOrder[i], postOrder[i]);
                killSubTree[i] = true;
            }
            
            if (LCAsLeavesPostOrders.size() > 1)
            {
                cout << 0;
                return 0;
            }
            if (killUpperTreeExceptPost[currLCA] != -1 && killUpperTreeExceptPost[currLCA] != *LCAsLeavesPostOrders.begin())
            {
                cout << 0;
                return 0;
            }
            killUpperTreeExceptPost[currLCA] = *LCAsLeavesPostOrders.begin();
            
            sort(all(orders));
            
            for (int i = 1; i < (int)orders.size(); ++i)
            {
                if (orders[i].fi < orders[i-1].se)
                {
                    cout << 0;
                    return 0;
                }
            }
        }
    } //byCol END
    
    for (vi& e : reverse(byHeight))
    {
        for (int u : e)
        {
            for (int v : G[u])
                if (killUpperTreeExceptPost[v] != -1)
                {
                    if (killUpperTreeExceptPost[u] != -1 && killUpperTreeExceptPost[u] != postOrder[v])
                    {
                        cout << 0;
                        return 0;
                    }
                    killUpperTreeExceptPost[u] = postOrder[v];
                }
                
            if (killUpperTreeExceptPost[u] == -1) continue;
            
            for (int v : G[u])
                if (postOrder[v] != killUpperTreeExceptPost[u])
                    killSubTree[v] = true;
        }
    }
    
    for (vi& e : byHeight)
    {
        for (int u : e)
        {
            if (!killSubTree[u]) continue;
            
            for (int v : G[u])
                killSubTree[v] = true;
        }
    }
    
    int ans = 0;
    repeat(i, n)
    {
        if (!killSubTree[i] && killUpperTreeExceptPost[i] == -1)
            ++ans;
    }
    
    cout << ans;
    
    

    return 0;
}
