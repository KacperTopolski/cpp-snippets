template<typename T> inline constexpr bool is2Pow(T val) {return (val & (val - 1)) == 0; }
template<typename T> inline constexpr T min2Pow(T val) {T ret = 1; while (ret < val) ret <<= 1; return ret; }
template<typename T> inline constexpr T max2Div(T val) {return val - (val & (val - 1)); }
template<typename T> inline constexpr int v2(T val) {if (!val) return -1; int ret = 0; while (!(val & 1)) {++ret; val >>= 1; } return ret; }
template<> inline constexpr int v2<int>(int val) {return __builtin_ffs(val) - 1; }
inline constexpr int popCount(int x) {return __builtin_popcount(uns(x)); }
inline constexpr int popCount(ll x) {return __builtin_popcountll(ull(x)); }