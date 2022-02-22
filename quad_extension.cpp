template<typename T, T D> 
class quadratic_extension
{
    T re, im;

public:
    quadratic_extension(T a = T(), T b = T()) : re(a), im(b) { }

    T norm() const {
        return re * re - im * im * D;
    }

    quadratic_extension inverse() const {
        return {re / norm(), -im / norm()};
    }

    quadratic_extension conjugate() const {
        return {re, -im};
    }

    friend quadratic_extension operator+(const quadratic_extension &a, const quadratic_extension &b) {
        return {a.re + b.re, a.im + b.im};
    }
    friend quadratic_extension operator-(const quadratic_extension &a, const quadratic_extension &b) {
        return {a.re - b.re, a.im - b.im};
    }
    friend quadratic_extension operator*(const quadratic_extension &a, const quadratic_extension &b) {
        return {a.re * b.re + a.im * b.im * D, a.re * b.im + a.im * b.re};
    }
    friend quadratic_extension operator/(const quadratic_extension &a, const quadratic_extension &b) {
        return a * b.inverse();
    }

    quadratic_extension operator+() const {
        return *this;
    }
    quadratic_extension operator-() const {
        return {-re, -im};
    }

    quadratic_extension& operator+=(const quadratic_extension &a) {
        return *this = *this + a;
    }
    quadratic_extension& operator-=(const quadratic_extension &a) {
        return *this = *this - a;
    }
    quadratic_extension& operator*=(const quadratic_extension &a) {
        return *this = *this * a;
    }
    quadratic_extension& operator/=(const quadratic_extension &a) {
        return *this = *this / a;
    }

    friend ostream& operator<<(ostream& os, const quadratic_extension &a) {
        return os << '(' << a.re << ", " << a.im << ')';
    }
    friend istream& operator>>(istream& is, quadratic_extension &a) {
        return is >> a.re >> a.im;
    }
};

template<typename T> 
using my_complex = quadratic_extension<T, T(-1)>;
using cmpl = my_complex<int>;
using cmpll = my_complex<ll>;