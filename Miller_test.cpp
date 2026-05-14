#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;

long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

bool is_prime_simple(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

bool miller_rabin(long long n, int k, int& rejected) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    
    random_device rd;
    mt19937 rng(rd());
    
    for (int i = 0; i < k; i++) {
        uniform_int_distribution<long long> dist(2, n - 2);
        long long a = dist(rng);
        long long x = mod_pow(a, d, n);
        
        if (x == 1 || x == n - 1) continue;
        
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        
        if (composite) {
            rejected++;
            return false;
        }
    }
    return true;
}

long long generate_candidate(int bits, mt19937& rng) {
    long long min_val = 1LL << (bits - 1);
    long long max_val = (1LL << bits) - 1;
    uniform_int_distribution<long long> dist(min_val, max_val);
    long long n;
    do {
        n = dist(rng);
    } while (n % 2 == 0);
    return n;
}

int main() {
    int bits;
    cin >> bits;
    
    random_device rd;
    mt19937 rng(rd());
    
    vector<long long> nums(10);
    vector<int> rejects(10);
    
    for (int cand = 0; cand < 10; cand++) {
        int rejected = 0;
        bool prime = false;
        long long n = 0;
        
        while (!prime) {
            n = generate_candidate(bits, rng);
            
            if (!is_prime_simple(n)) {
                rejected++;
                continue;
            }
            
            if (miller_rabin(n, 20, rejected)) {
                int temp = 0;
                if (miller_rabin(n, 2, temp)) {
                    prime = true;
                } else {
                    rejected++;
                }
            }
        }
        nums[cand] = n;
        rejects[cand] = rejected;
    }
    
    cout << "\nТаблица 2\n";
    cout << "Результаты выполнения тестов\n\n";
    
    for (int i = 0; i < 10; i++) {
        cout << i + 1 << " | " << nums[i] << " | true | " << rejects[i] << "\n";
    }
    
    return 0;
}