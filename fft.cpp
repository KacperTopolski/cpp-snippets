template<typename T> class myComplex
{
public:
    T re, im;

    const static myComplex PI;
    const static myComplex I;

    using baseType = T;

    myComplex(T r = 0, T i = 0) : re(r), im(i) {}

    T absSq() const {return re * re + im * im; }
    myComplex conjugate() const {return myComplex(re, -im); }
    myComplex inverse() const {return myComplex(re / absSq(), -im / absSq()); }

    myComplex operator-() const {return myComplex(-re, -im); }
    myComplex operator+() const {return *this; }

    myComplex& operator+=(myComplex const& z) {re += z.re; im += z.im; return *this; }
    myComplex& operator-=(myComplex const& z) {re -= z.re; im -= z.im; return *this; }
    myComplex& operator*=(myComplex const& z) {myComplex ret(re * z.re - im * z.im, re * z.im + im * z.re); return (*this) = ret; }
    myComplex& operator/=(myComplex const& z) {return (*this) *= z.inverse(); }

    friend myComplex operator+(const myComplex& a, const myComplex& b) {myComplex ret(a); return ret += b; }
    friend myComplex operator-(const myComplex& a, const myComplex& b) {myComplex ret(a); return ret -= b; }
    friend myComplex operator*(const myComplex& a, const myComplex& b) {myComplex ret(a); return ret *= b; }
    friend myComplex operator/(const myComplex& a, const myComplex& b) {myComplex ret(a); return ret /= b; }

    static myComplex exp(const myComplex& z) {T realR = ::exp(z.re); return myComplex(realR * cos(z.im), realR * sin(z.im)); }

    friend ostream& operator<<(ostream &os, const myComplex& z) {return os << z.re << '+' << z.im << 'i'; }
    friend bool operator<(const myComplex& a, const myComplex& b) {return (a.re == b.re ? a.im < b.im : a.re < b.re); }
    friend bool operator==(const myComplex& a, const myComplex& b) {return a.re == b.re && a.im == b.im; }
};
template<typename T> const myComplex<T> myComplex<T>::PI(acos(T(-1)));
template<typename T> const myComplex<T> myComplex<T>::I(0, 1);

using cd = myComplex<double>;           using vcd = vector<cd>;
using cf = myComplex<double>;           using vcf = vector<cf>;

template<typename It> void innerFft(It beg, It end, bool inverse = false)
{
    int size = int(end - beg);
    assert(is2Pow(size));

    using comp = decltype (+*beg);

    for (int i = 1, j = 0; i < size; i++)
    {
        int b = size / 2;
        for (; j & b; b /= 2)
            j ^= b;
        j ^= b;

        if (i < j)
            swap(beg[i], beg[j]);
    }

    for (int ln = 2; ln <= size; ln *= 2)
    {
        comp omega = comp::exp((inverse ? -1 : 1) * 2 * comp::PI / ln * comp::I);
        for (int i = 0; i < size; i += ln)
        {
            comp omegaCurr(1, 0);
            for (int j = 0; j < ln / 2; j++)
            {
                comp f = beg[i + j];
                comp s = beg[i + j + ln / 2] * omegaCurr;
                beg[i + j] = f + s;
                beg[i + j + ln / 2] = f - s;
                omegaCurr *= omega;
            }
        }
    }
}

template<typename It> inline void fft(It beg, It end) {innerFft(beg, end, false); }

template<typename It> inline void ifft(It beg, It end)
{
    innerFft(beg, end, true);
    using comp = decltype (+*beg);
    using base = typename comp::baseType;
    comp m = comp(base(end - beg)).inverse();
    for (; beg != end; ++beg)
        *beg *= m;
}

template<typename T, typename V = double> vector<T> mult(const vector<T>& a, const vector<T>& b)
{
    int n = 1;
    while (n <= int(a.size() + b.size()))
        n *= 2;

    vector<myComplex<V>> a_fft(n), b_fft(n);

    for (int i = 0; i < int(a.size()); ++i)
        a_fft[i] = cd(a[i], 0);
    for (int i = 0; i < int(b.size()); ++i)
        b_fft[i] = cd(b[i], 0);

    fft(a_fft.begin(), a_fft.end());
    fft(b_fft.begin(), b_fft.end());

    for (int i = 0; i < n; ++i)
        a_fft[i] *= b_fft[i];

    ifft(a_fft.begin(), a_fft.end());

    vector<T> ret(n);
    for (int i = 0; i < n; ++i)
        ret[i] = T(round(a_fft[i].re));

    return ret;
}

template<typename T, typename V = double> vector<T> sq(const vector<T>& a)
{
    int n = 1;
    while (n <= int(a.size()) * 2)
        n *= 2;

    vector<myComplex<V>> a_fft(n);

    for (int i = 0; i < int(a.size()); ++i)
        a_fft[i] = cd(a[i], 0);

    fft(a_fft.begin(), a_fft.end());

    for (int i = 0; i < n; ++i)
        a_fft[i] *= a_fft[i];

    ifft(a_fft.begin(), a_fft.end());

    vector<T> ret(n);
    for (int i = 0; i < n; ++i)
        ret[i] = T(round(a_fft[i].re));

    return ret;
}

template<typename T = double> vector<myComplex<T>>& multInPlace(vector<myComplex<T>>& a, vector<myComplex<T>>& b)
{
    int n = 1;
    while (n <= int(a.size() + b.size()))
        n *= 2;

    a.resize(n);
    b.resize(n);

    fft(a.begin(), a.end());
    fft(b.begin(), b.end());

    for (int i = 0; i < n; ++i)
        a[i] *= b[i];

    ifft(a.begin(), a.end());

    return a;
}

template<typename T = double> vector<myComplex<T>>& sqInPlace(vector<myComplex<T>>& a)
{
    int n = 1;
    while (n <= int(a.size()) * 2)
        n *= 2;

    a.resize(n);

    fft(a.begin(), a.end());

    for (int i = 0; i < n; ++i)
        a[i] *= a[i];

    ifft(a.begin(), a.end());

    return a;
}
