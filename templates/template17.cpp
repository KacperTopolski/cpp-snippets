#include <bits/stdc++.h>
using namespace std;

#define fastIO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(...) "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define fi first
#define se second
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define mt make_tuple

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
// uniform_int_distribution<int> dist(1, MX);

int32_t main()
{
    fastIO;
    
    readRepeatInt
    {
        
    }

    return 0;
}
