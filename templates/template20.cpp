#include <bits/stdc++.h>
using namespace std;

#define fastIO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(...) "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define fi first
#define se second
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define mt make_tuple
#define rev views::reverse

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

template<typename A, typename B> A& maxi(A& a, B b) {return a = max(a, A(b)); }
template<typename A, typename B> A& mini(A& a, B b) {return a = min(a, A(b)); }

template<ranges::range R> requires (!is_convertible_v<R, const char*>) ostream& operator<<(ostream &os, const R &v) {for (const auto& x : v) os << x << ' '; return os << '\n'; }
template<ranges::range R> istream& operator>>(istream &is, R &v) {for (auto& x : v) is >> x; return is; }
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) {return os << '(' << p.first << ", " << p.second << ')'; }
template<typename A, typename B> istream& operator>>(istream &is, pair<A, B> &p) {return is >> p.first >> p.second; }

template<typename T, typename V> T myPow(T base, V exp) {T ans(1); while (exp > 0) {if (exp & 1) ans *= base; base *= base; exp >>= 1; } return ans; }
template<typename T, typename V> T myPowMod(T base, T mod, V exp) {T ans(1); while (exp > 0) {if (exp & 1) ans = (ans * base) % mod; base = (base * base) % mod; exp >>= 1; } return ans; }
template<typename T> T myMod(T val, T mod) {val %= mod; if (val < 0) val += mod; return val; }
mt19937_64 mt_rng(chrono::high_resolution_clock::now().time_since_epoch().count());

int32_t main()
{
    fastIO;
    
    int _tc; 
    cin >> _tc; 
    for (int _ti = 1; _ti <= _tc; ++_ti) 
    { 
        // cout << "Case #" << _ti << ": ";
        
        
    }

    return 0;
}
