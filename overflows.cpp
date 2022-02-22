template<typename A, typename B, typename C> inline bool addOverflow(A& a, B b, C c) {return __builtin_add_overflow(b, c, &a); }
template<typename A, typename B> inline bool addOverflow(A& a, B b) {return __builtin_add_overflow(a, b, &a); }
template<typename A, typename B, typename C> inline bool mulOverflow(A& a, B b, C c) {return __builtin_mul_overflow(b, c, &a); }
template<typename A, typename B> inline bool mulOverflow(A& a, B b) {return __builtin_mul_overflow(a, b, &a); }
