template<typename A, typename B> pair<A, B> operator+(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi + y.fi, x.se + y.se}; }
template<typename A, typename B> pair<A, B> operator-(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi - y.fi, x.se - y.se}; }
template<typename A, typename B> pair<A, B> operator*(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi * y.fi, x.se * y.se}; }
template<typename A, typename B> pair<A, B> operator/(const pair<A, B>& x, const pair<A, B>& y) {return {x.fi / y.fi, x.se / y.se}; }

template<typename A, typename B> pair<A, B> operator+(const pair<A, B>& x) {return x; }
template<typename A, typename B> pair<A, B> operator-(const pair<A, B>& x) {return {-x.fi, -x.se}; }

template<typename A, typename B, typename C> pair<A, B> operator*(const C& y, const pair<A, B>& x) {return {x.fi * y, x.se * y}; }
template<typename A, typename B, typename C> pair<A, B> operator*(const pair<A, B>& x, const C& y) {return {x.fi * y, x.se * y}; }
template<typename A, typename B, typename C> pair<A, B> operator/(const pair<A, B>& x, const C& y) {return {x.fi / y, x.se / y}; }