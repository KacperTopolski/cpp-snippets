template<typename F>
class matrix 
{
    int n, m;
    vector<vector<F>> ent;
    
public:
// -- Misc. 1
    int get_row_count()    const {return n; }
    int get_col_count()    const {return m; }
    int get_n()            const {return n; }
    int get_m()            const {return m; }
    
    auto begin()                 {return ent.begin(); }
    auto end()                   {return ent.end(); }
    auto rbegin()                {return ent.rbegin(); }
    auto rend()                  {return ent.rend(); }
    auto begin()           const {return ent.begin(); }
    auto end()             const {return ent.end(); }
    auto rbegin()          const {return ent.rbegin(); }
    auto rend()            const {return ent.rend(); }
    auto cbegin()          const {return ent.begin(); }
    auto cend()            const {return ent.end(); }
    auto crbegin()         const {return ent.rbegin(); }
    auto crend()           const {return ent.rend(); }
    
    vector<F>& operator[](int i) {return ent[i]; }
    const vector<F>& operator[](int i) const {return ent[i]; }
    
    friend bool add_able(const matrix &A, const matrix &B) {return A.n == B.n && A.m == B.m; }
    friend bool mul_able(const matrix &A, const matrix &B) {return A.m == B.n; }
    bool is_square() {return n == m; }
    
// -- Constructors & etc
    matrix(int _n = 1, int _m = 1, F f = 0) : n(_n), m(_m), ent(n, vector<F>(m, f)) { }
    matrix(const matrix &A) : n(A.n), m(A.m), ent(A.ent) {}
    matrix(matrix &&A) : n(A.n), m(A.m), ent(move(A.ent)) {}
    ~matrix() { }
    
    matrix& operator=(const matrix& M) {
        n = M.n;
        m = M.n;
        ent = M.ent;
        return *this;
    }
    
    matrix& operator=(matrix&& M) {
        n = M.n;
        m = M.n;
        ent = move(M.ent);
        return *this;
    }
    
    template<typename functor> 
    static matrix from_functor(int n, int m, functor f) {
        matrix A(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                A[i][j] = f(i, j);
        return A;
    }
    
    template<typename G> 
    static matrix convert(int n, int m, const G &A) {
        return from_functor(n, m, [&A](int i, int j){return A[i][j]; }); 
    }
    
    template<typename G> 
    static matrix convert(const G &A) {
        return from_functor(A.get_row_count(), A.get_col_count(), [&A](int i, int j){return A[i][j]; }); 
    }
    
    static matrix identity(int n) {
        return from_functor(n, n, [](int i, int j){return i == j; });
    }
    
// -- Oper.
    
    friend ostream& operator<<(ostream& os, const matrix &A) {
        for (int i = 0; i < A.n; ++i)
            for (int j = 0; j < A.m; ++j)
                os << A[i][j] << " \n"[j+1 == A.m];
        return os;
    }
    
    friend istream& operator>>(istream& is, matrix &A) {
        for (int i = 0; i < A.n; ++i)
            for (int j = 0; j < A.m; ++j)
                is >> A[i][j];
        return is;
    }
    
    friend bool operator==(const matrix &A, const matrix &B)
    {
        if (!add_able(A, B))
            return false;
            
        for (int i = 0; i < A.get_row_count(); ++i)
            if (A[i] != B[i])
                return false;
                
        return true;
    }
    
    friend bool operator<(const matrix &A, const matrix &B)
    {
        assert(add_able(A, B));
        
        for (int i = 0; i < A.get_row_count(); ++i)
            for (int j = 0; j < A.get_col_count(); ++j)
            {
                if (A[i][j] == B[i][j])
                    continue;
                else
                    return A[i][j] < B[i][j];
            }
            
        return false;
    }
    
// -- Misc. 2

    void clear()
    {
        ent.clear();
        n = m = 0;
    }
    
    void fill(F f = 0)
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ent[i][j] = f;
    }
    
    matrix& change_row_count(int k, F f = 0) {
        if (k <= n)
            ent.resize(k);
        else
            ent.resize(k, vector<F>(m, f));
        n = k;
            
        return *this;
    }
    
    matrix& change_col_count(int k, F f = 0) {
        for (vector<F>& v : ent)
            v.resize(k, f);
        m = k;
            
        return *this;
    }
    
    matrix& resize(int kn, int km, F f = 0) {
        change_row_count(kn, f);
        change_col_count(km, f);
    }
    
    matrix& add_row(vector<F> &&v) {
        assert((int)v.size() == m);
        ++n;
        ent.push_back(v);
        return *this;
    }
    
    matrix& add_row(const vector<F> &v) {
        vector<F> w(v);
        return add_row(move(w));
    }
    
    matrix& add_col(const vector<F> &v) {
        assert(v.size() == n);
        ++m;
        for (int i = 0; i < n; ++i)
            ent[i].push_back(v[i]);
            
        return *this;
    }
    
// -- Echelon Form
    template<bool det_only> 
    F det_echelon();
    
    matrix& make_echelon() {
        det_echelon<false>();
        return *this;
    }
    
    matrix get_echelon() {
        matrix A(*this);
        return A.make_echelon();
    }
    
    friend matrix get_echelon(const matrix &A) {
        return A.get_echelon();
    }
    
    friend matrix get_echelon(matrix &&A) {
        return A.make_echelon();
    }
    
// -- Inverse
    bool try_to_invert();
    
    matrix& invert() {
        assert(try_to_invert());
        return *this;
    }
    
    matrix inverse() const {
        matrix A(*this);
        return A.invert();
    }
    
    friend matrix inverse(const matrix &A) {
        return A.inverse();
    }
    
    friend matrix inverse(matrix &&A) {
        return A.invert();
    }
    
// -- Determinant
    F det_destroy() {
        assert(is_square());
        return det_echelon<true>();
    }
    
    F det() const {
        matrix A(*this);
        return A.det_destroy();
    }
    
    friend F det(const matrix &A) {
        return A.det();
    }
    
    friend F det(matrix &&A) {
        return A.det_destroy();
    }
    
// --  Alg oper. 1
    friend matrix operator+(const matrix &A) {return A; }
    friend matrix operator-(const matrix &A) {
        return from_functor(A.n, A.m, [&A](int i, int j){return -A[i][j]; });
    }
    
    friend matrix operator+(const matrix &A, const matrix &B) {
        assert(add_able(A, B));
        return from_functor(A.n, A.m, [&A, &B](int i, int j){return A[i][j] + B[i][j]; });
    }
    
    friend matrix operator-(const matrix &A, const matrix &B) {
        assert(add_able(A, B));
        return from_functor(A.n, A.m, [&A, &B](int i, int j){return A[i][j] - B[i][j]; });
    }
    
    friend matrix operator*(const matrix &A, const matrix &B) {
        assert(mul_able(A, B));
        return from_functor(A.n, B.m, [&A, &B](int i, int j){
            F res = 0;
            for (int k = 0; k < A.m; ++k)
                res += A[i][k] * B[k][j];
            return res;
        });
    }
    
    friend matrix operator/(const matrix &A, const matrix &B) {
        return A * B.inverse();
    }
    
// --  Alg oper. 1
    matrix& operator+=(const matrix &A) {
        assert(add_able(*this, A));
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ent[i][j] += A[i][j];
        
        return *this; 
    }
    
    matrix& operator-=(const matrix &A) {
        assert(add_able(*this, A));
        
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                ent[i][j] -= A[i][j];
        
        return *this; 
    }
    
    matrix& operator*=(const matrix &A) {
        assert(mul_able(*this, A));
        return *this = *this * A;
    }
    
    matrix& operator/=(const matrix &A) {
        assert(mul_able(*this, A));
        return *this = *this / A;
    }
};

template<typename F> template<bool det_only> 
F matrix<F>::det_echelon() {
    if constexpr (det_only)
        if (n != m)
            return 0;
    
    F d = (n == m ? 1 : 0);
    
    int row = 0;
    for (int col = 0; col < m; ++col) {
        int non_zero = -1;
        
        for (int i = row; i < n; ++i) {
            if (ent[i][col] != 0) {
                non_zero = i;
                break;
            }
        }
        
        if (non_zero == -1) {
            if constexpr (det_only)
                return 0;
            
            d = 0;
            continue;
        }
        
        if (non_zero != row) {
            d = -d;
            swap(ent[non_zero], ent[row]);
        }
        
        if (ent[row][col] != 1) {
            d *= ent[row][col];
            F inverse = 1 / ent[row][col];
            for (F &f : ent[row])
                f *= inverse;
        }
        
        if constexpr (!det_only)
        {
            for (int i = 0; i < row; ++i)
            {
            if (ent[i][col] == 0)
                continue;
                
            F mul = ent[i][col];
            
            for (int j = 0; j < m; ++j)
                ent[i][j] -= mul * ent[row][j];
            }
        }
        
        {
            for (int i = row + 1; i < n; ++i)
            {
                if (ent[i][col] == 0)
                    continue;
                    
                F mul = ent[i][col];
                
                for (int j = 0; j < m; ++j)
                    ent[i][j] -= mul * ent[row][j];
            }
        }
        
        ++row;
    }
    
    return d;
}

template<typename F> 
bool matrix<F>::try_to_invert() {
    assert(is_square());
    m = 2 * n;
    for (int i = 0; i < n; ++i) {
        ent[i].resize(2 * n);
        ent[i][n + i] = 1;
     }
        
    make_echelon();
        
    if (ent[n-1][n-1] != 1) {
        clear();
        return false;
    }
        
    m = n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            ent[i][j] = ent[i][n + j];
        ent[i].resize(n);
    }
        
    return true;
}

template<typename F> 
class linear_eq_solver
{
    linear_eq_solver(const linear_eq_solver &L) = delete;
    linear_eq_solver& operator=(const linear_eq_solver &L) = delete;
    
    int var_c;
    matrix<F> M;
    
public:
    linear_eq_solver(int n) : var_c(n), M(0, n+1) { }
    const matrix<F>& get_eqs() {return M; }
    
    void add_eq(vector<F> &&v, F out) {
        v.push_back(out);
        M.add_row(v);
    }
    
    void add_eq(const vector<F> &v, F out) {
        vector<F> w(v);
        add_eq(move(w), out);
    }
    
    optional<vector<F>> solve() {
        M.make_echelon();
            
        vector<F> sol(var_c);
        int col = 0;
        
        for (vector<F> &row : M)
        {
            while (row[col] == 0 && col <= var_c)
                ++col;
                
            if (col > var_c)  return sol;
            if (col == var_c) return {};
                
            sol[col] = row[var_c];
            ++col;
        }
            
        return sol;
    }
};