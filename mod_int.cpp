template<typename T> pair<T, T> extEuclidean(T a, T b)
{
    pair<T, T> s = {1, 0};
    pair<T, T> r = {a, b};

    while (r.second)
    {
        T q = r.first / r.second;
        r = {r.second, r.first - q * r.second};
        s = {s.second, s.first - q * s.second};
    }

    return {s.first, b ? (r.first - s.first * a) / b : 0};
}

template<typename T, T modulo> class modBase
{
    T val;

public:
    modBase() : val(0) {}
    modBase(T v)
    {
        if (0 <= v && v < modulo)
            val = v;
        else
            val = myMod(v, modulo);
    }

    using baseType = T;

    static T modValue() {return modulo; }
    T value() const {return val; }

    // modBase inverse() const {/*assert(gcd(modulo, val) == 1);*/ return extEuclidean(modulo, val).second; }
    modBase inverse() const {return myPow(*this, modulo - 2); }

    modBase operator-() const {modBase ret; if (val) ret.val = modulo - val; return ret; }
    modBase operator+() const {return *this; }

    modBase& operator+=(modBase const& x) {val += x.val; if (val >= modulo) val -= modulo; return *this; }
    modBase& operator-=(modBase const& x) {val -= x.val; if (val < 0) val += modulo; return *this; }
    modBase& operator*=(modBase const& x) {val = myMod(val * x.val, modulo); return *this; }
    modBase& operator/=(modBase const& x) {return (*this) *= x.inverse(); }

    friend modBase operator+(const modBase& a, const modBase& b) {modBase ret(a); return ret += b; }
    friend modBase operator-(const modBase& a, const modBase& b) {modBase ret(a); return ret -= b; }
    friend modBase operator*(const modBase& a, const modBase& b) {modBase ret(a); return ret *= b; }
    friend modBase operator/(const modBase& a, const modBase& b) {modBase ret(a); return ret /= b; }

    modBase& operator++() {return (*this) += 1; }
    modBase operator++(int) {modBase tmp(*this); operator++(); return tmp; }
    modBase& operator--() {return (*this) -= 1; }
    modBase operator--(int) {modBase tmp(*this); operator--(); return tmp; }

    template<typename X> static modBase factorial(X v) {modBase ret(1); for (modBase i(1); --v >= 0 ; ++i) ret *= i; return ret; }

    friend ostream& operator<<(ostream &os, const modBase& m) {return os << m.val; }
    friend bool operator<(const modBase& a, const modBase& b) {return a.val < b.val; }
    friend bool operator==(const modBase& a, const modBase& b) {return a.val == b.val; }
};

template<ll M> using modInteger = modBase<ll, M>;
using mod1e9p7 = modInteger<ll(1e9 + 7)>;
using mod1e9p9 = modInteger<ll(1e9 + 9)>;
using mod998s = modInteger<998244353LL>;
using mods = pair<mod1e9p7, mod1e9p9>;

// const int MX = int(1e6) + 6;
// 
// mod... fact[MX], invFact[MX];
// 
// fact[0] = 1;
// for (int i = 1; i < MX; ++i)
    // fact[i] = i * fact[i - 1];
// invFact[MX-1] = fact[MX-1].inverse();
// for (int i = MX-2; i >= 0; --i)
    // invFact[i] = (i+1) * invFact[i+1];