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

template<typename T> class dynModBase
{
    T val, modulo;

public:
    dynModBase() = delete;
    dynModBase(T v, T modul)
    {
        modulo = modul;
        if (0 <= v && v < modulo)
            val = v;
        else
            val = myMod(v, modulo);
    }

    using baseType = T;

    T modValue() const {return modulo; }
    T value() const {return val; }
    
    dynModBase changeMod(T newMod) const {assert(modulo % newMod == 0); return dynModBase(val, newMod); }

    // dynModBase inverse() const {assert(gcd(modulo, val) == 1); return dynModBase(extEuclidean(modulo, val).second, modulo); }
    dynModBase inverse() const {dynModBase(myPowMod(val, modulo, modulo - 2), modulo); }

    dynModBase operator-() const {return dynModBase(modulo - val, modulo); }
    dynModBase operator+() const {return *this; }

    dynModBase& operator+=(dynModBase const& x) {assert(modulo == x.modulo); val += x.val; if (val >= modulo) val -= modulo; return *this; }
    dynModBase& operator-=(dynModBase const& x) {assert(modulo == x.modulo); val -= x.val; if (val < 0) val += modulo; return *this; }
    dynModBase& operator*=(dynModBase const& x) {assert(modulo == x.modulo); val = myMod(val * x.val, modulo); return *this; }
    dynModBase& operator/=(dynModBase const& x) {assert(modulo == x.modulo); return (*this) *= x.inverse(); }

    friend dynModBase operator+(const dynModBase& a, const dynModBase& b) {dynModBase ret(a); return ret += b; }
    friend dynModBase operator-(const dynModBase& a, const dynModBase& b) {dynModBase ret(a); return ret -= b; }
    friend dynModBase operator*(const dynModBase& a, const dynModBase& b) {dynModBase ret(a); return ret *= b; }
    friend dynModBase operator/(const dynModBase& a, const dynModBase& b) {dynModBase ret(a); return ret /= b; }

    dynModBase& operator++() {return (*this) += 1; }
    dynModBase operator++(int) {dynModBase tmp(*this); operator++(); return tmp; }
    dynModBase& operator--() {return (*this) -= 1; }
    dynModBase operator--(int) {dynModBase tmp(*this); operator--(); return tmp; }

    template<typename X> static dynModBase factorial(X v, T mod) {dynModBase ret(1, mod); for (dynModBase i(1, mod); --v >= 0 ; ++i) ret *= i; return ret; }

    friend ostream& operator<<(ostream &os, const dynModBase& m) {return os << m.val; }
    friend bool operator<(const dynModBase& a, const dynModBase& b) {return a.val < b.val; }
    friend bool operator==(const dynModBase& a, const dynModBase& b) {return a.val == b.val && a.modulo == b.modulo; }
};

using dynModInteger = dynModBase<ll>;
