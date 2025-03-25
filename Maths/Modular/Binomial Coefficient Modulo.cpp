Binomial coefficient modulo prime : 

Lucas Theorem : It provides a way to compute binomial coefficients modulo a prime number. 

Let 'p' be the prime number and let 'n' and 'm' be non-negative integers. Express 'n' and 'm' in base 'p';

	n = n_k n_k-1 n_k-2 . . . . n_0
	m = m_k m_k-1 m_k-2 . . . . m_0

where 'n_i' and 'm_i' are the digits in the base 'p' representation. Then, 

+-------------------------------------------+
|					 k						           |
|	C(n, m) mod p = MUL C(n_i, m_i) mod p	  |
|					i=0						        |
+-------------------------------------------+

CPP Code : 

// Function to compute (a^b) % p using modular exponentiation
long long power(long long a, long long b, long long p) {
    long long res = 1;
    a %= p;
    while (b > 0) {
        if (b & 1) res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}

// Function to compute modular inverse of a under mod p using Fermat's theorem
long long modInverse(long long a, long long p) {
    return power(a, p - 2, p);  // a^(p-2) % p (Fermat's Little Theorem)
}

// Function to compute C(n, r) % p using an iterative approach
long long binomialMod(long long n, long long r, long long p) {
    if (r > n) return 0;
    long long num = 1, den = 1;

    for (long long i = 0; i < r; i++) {
        num = (num * (n - i)) % p;
        den = (den * (i + 1)) % p;
    }

    return (num * modInverse(den, p)) % p;
}

// Iterative Lucas' theorem function to compute C(n, r) % p
long long lucasIterative(long long n, long long r, long long p) {
    long long result = 1;

    while (n > 0 || r > 0) {
        long long ni = n % p, ri = r % p;

        if (ri > ni) return 0;  // If any r_i > n_i, C(n, r) is 0

        result = (result * binomialMod(ni, ri, p)) % p;
		
        n /= p;
        r /= p;
    }

    return result;
}

--------------------------------------------------------------------------------------------------------------

Binomial coefficient modulo prime power

https://cp-algorithms.com/combinatorics/binomial-coefficients.html#mod-prime-pow

Formula to Compute C(n,m)mod p^e

1. Make C(n,m) free from prime divisor
2. Compute factorials ignoring p-factors using modular inverses.
3. Multiply back and adjust for missing p-powers. 

// Function to compute (a^b) % mod using modular exponentiation
ll power(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// Compute factorial modulo p^e, ignoring multiples of p
ll factModP(ll n, ll p, ll pe) {
    ll res = 1;
    while (n > 0) {
        for (ll i = 1; i <= n % p; i++)
            res = (res * i) % pe;
        n /= p;
        if (n % 2) res = (res * (p - 1)) % pe; // Wilson's theorem
    }
    return res;
}

// Compute binomial coefficient C(n, m) % p^e using p-adic methods
ll binomialPrimePower(ll n, ll m, ll p, ll e) {
    if (m > n) return 0;

    ll pe = power(p, e, 1e18);  // Compute p^e
    ll vp = 0, temp = n;

    // Compute v_p(C(n, m)) using Kummer’s theorem
    for (ll i = p; i <= n; i *= p) {
        vp += (n / i) - (m / i) - ((n - m) / i);
    }

    // If C(n, m) has at least e factors of p, result is 0
    if (vp >= e) return 0;

    // Compute C(n, m) ignoring p factors
    ll num = factModP(n, p, pe);
    ll den = (factModP(m, p, pe) * factModP(n - m, p, pe)) % pe;

    // Compute modular inverse of denominator mod p^e
    ll den_inv = power(den, pe / p * (p - 1) - 1, pe); 

    return (num * den_inv) % pe * power(p, vp, pe) % pe;
}

--------------------------------------------------------------------------------------------------------------

Binomial coefficient modulo arbitrary-number

https://cp-algorithms.com/combinatorics/binomial-coefficients.html#binomial-coefficient-modulo-an-arbitrary-number

Formula to Compute C(n,m) mod M

1) Factorize M into prime powers.
2) Use Lucas' theorem for each prime modulus.
3) Combine results using Chinese Remainder Theorem.

// Function to compute (a^b) % mod using modular exponentiation
ll power(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

// Function to compute modular inverse of a under mod p using Fermat's theorem
ll modInverse(ll a, ll p) {
    return power(a, p - 2, p);  // Only works if p is prime
}

// Function to compute C(n, r) % p using factorial mod p
ll binomialMod(ll n, ll r, ll p) {
    if (r > n) return 0;
    ll num = 1, den = 1;

    for (ll i = 0; i < r; i++) {
        num = (num * (n - i)) % p;
        den = (den * (i + 1)) % p;
    }

    return (num * modInverse(den, p)) % p;
}

// Lucas' theorem for C(n, r) % p
ll lucas(ll n, ll r, ll p) {
    ll result = 1;
    while (n > 0 || r > 0) {
        ll ni = n % p, ri = r % p;
        if (ri > ni) return 0; // If any r_i > n_i, result is 0
        result = (result * binomialMod(ni, ri, p)) % p;
        n /= p;
        r /= p;
    }
    return result;
}

// Function to factorize M into prime powers
map<ll, ll> factorize(ll M) {
    map<ll, ll> factors;
    for (ll i = 2; i * i <= M; i++) {
        while (M % i == 0) {
            factors[i]++;
            M /= i;
        }
    }
    if (M > 1) factors[M]++;
    return factors;
}

// Chinese Remainder Theorem solver using modular inverses
ll CRT(const vector<ll>& num, const vector<ll>& rem) {
    ll prod = 1, result = 0;
    int k = num.size();

    for (int i = 0; i < k; i++) prod *= num[i];

    for (int i = 0; i < k; i++) {
        ll pp = prod / num[i];
        result += rem[i] * modInverse(pp, num[i]) * pp;
        result %= prod;
    }

    return result;
}

// Function to compute C(n, r) % M for composite M
ll binomialComposite(ll n, ll r, ll M) {
    map<ll, ll> factors = factorize(M);
    vector<ll> moduli, remainders;

    for (auto [p, e] : factors) {
        ll pe = power(p, e, M);  // Compute p^e
        moduli.push_back(pe);
        remainders.push_back(lucas(n, r, p));  // Compute C(n, r) % p
    }

    return CRT(moduli, remainders);
}

