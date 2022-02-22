uniform_int_distribution<ll> dist(ll(0.1e9), ll(0.9e9))   //dist(rng);

template<typename A, typename B> pair<A, B> operator+(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi + y.fi, x.se + y.se}; }
template<typename A, typename B> pair<A, B> operator-(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi - y.fi, x.se - y.se}; }
template<typename A, typename B> pair<A, B> operator*(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi * y.fi, x.se * y.se}; }
template<typename A, typename B> pair<A, B> operator/(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi / y.fi, x.se / y.se}; }
 
template<typename A, typename B> pair<A, B> operator+(const pair<A, B>& x) {return x; }
template<typename A, typename B> pair<A, B> operator-(const pair<A, B>& x) {return {-x.fi, -x.se}; }
 
template<typename A, typename B, typename C> pair<A, B> operator*(const C& y, const pair<A, B>& x) {return {x.fi * y, x.se * y}; }
template<typename A, typename B, typename C> pair<A, B> operator*(const pair<A, B>& x, const C& y) {return {x.fi * y, x.se * y}; }
template<typename A, typename B, typename C> pair<A, B> operator/(const pair<A, B>& x, const C& y) {return {x.fi / y, x.se / y}; }
 
template<typename C = string, typename T = mods> struct rollingHash
{
    int l, r;
    T currHash;
    
    const C& obj;
    const vector<T>& base;
    const T& invBase;
    
    T hash() {return currHash; }
    
    void rollLeftSide(int v)
    {
        while (l < v)
        {
            currHash = currHash - obj[l] * base[0];
            currHash = currHash * invBase;
            ++l;
        }
        
        while (l > v)
        {
            --l;
            currHash = currHash * base[1];
            currHash = currHash + obj[l] * base[0];
        }
    }
    
    void rollRightSide(int v)
    {
        while (r < v)
        {
            ++r;
            currHash = currHash + obj[r] * base[r - l];
        }
        
        while (r > v)
        {
            currHash = currHash - obj[r] * base[r - l];
            --r;
        }
    }
    
    void set(int vl, int vr) //O(vr - vl)
    {
        currHash = T();
        l = vr + 1;
        r = vr;
        rollLeftSide(vl);
    }
    
    rollingHash(const C& o, const vector<T>& b, const T& iB) 
        : obj(o), base(b), invBase(iB), l(0), r(-1), currHash(T()) {}
        
    rollingHash(const C& o, const vector<T>& b, const T& iB, int vl, int vr) 
        : obj(o), base(b), invBase(iB) {set(vl, vr); }
};
 
size_t hash_combine(size_t lhs, size_t rhs) 
{
    lhs ^= rhs + 0x9e3779b9 + (lhs << 6) + (lhs >> 2);
    return lhs;
}
 
/*template<>
struct std::hash<array<ll, 4>> {
    std::size_t operator()(const array<ll, 4>& a) const {
        return hash_combine(hash_combine(a[0], a[1]), hash_combine(a[2], a[3]));
    }
};*/