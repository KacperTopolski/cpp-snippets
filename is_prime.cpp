template<int mxPre = int(1e5)> class isPrimeHelper
{
    static_assert(mxPre >= 3);
    static bitset<mxPre> precompute;
    static unordered_map<ull, bool> cache;
    static void init()
    {
        precompute.set();
        precompute[0] = false;
        precompute[1] = false;
        for (int i = 2; i < mxPre; ++i)
            if (precompute[i])
                for (int j = 2; i * j < mxPre; ++j)
                    precompute[i * j] = false;
    }
public:
    isPrimeHelper() {if(!precompute[2]) init(); }
    
    bool isPrimeWitness(ull x, ull witness)
    {
        int v2 = 0;
        ull xMinusOne = x - 1;
        
        while (!(xMinusOne & 1))
        {
            xMinusOne /= 2;
            ++v2;
        }
        
        ull powWit = myPowMod(witness, x, xMinusOne);
        
        if (powWit == 1 || powWit == x - 1) return true;
            
        while (v2--)
        {
            powWit = (powWit * powWit) % x;
            if (powWit == x - 1) return true;
        }
        
        return false;
    }
    bool isPrime(ull x)
    {
        if (x < mxPre)
            return precompute[x];
        if (cache.count(x))
            return cache[x];
            
        //https://primes.utm.edu/prove/prove2_3.html
        if (!isPrimeWitness(x, 2) || !isPrimeWitness(x,3)) return cache[x] = false;
        if (x < 1e6) return cache[x] = true;
            
        if (!isPrimeWitness(x, 5)) return cache[x] = false;
        if (x < 25e6) return cache[x] = true;
            
        if (!isPrimeWitness(x, 7)) return cache[x] = false;
        if (x < 3e9) return cache[x] = true;
            
        //if (!isPrimeWitness(x, 11)) return cache[x] = false;
        //if (x < 2e12) return cache[x] = true;
            
        //if (!isPrimeWitness(x, 13)) return cache[x] = false;
        //if (x < 3e12) return cache[x] = true;
            
        //if (!isPrimeWitness(x, 17)) return cache[x] = false;
        //if (x < 341e12) return cache[x] = true;
            
        assert(false);
        return false;
    }
    bool isPrime(ll x) {return x > 0 ? isPrime(ull(x)) : false; }
    bool operator()(ull x) {return isPrime(x); }
    bool operator()(ll x) {return x > 0 ? isPrime(ull(x)) : false; }
    
    
};
template<int mxPre> bitset<mxPre> isPrimeHelper<mxPre>::precompute;
template<int mxPre> unordered_map<ull, bool> isPrimeHelper<mxPre>::cache;

isPrimeHelper isPrime;
