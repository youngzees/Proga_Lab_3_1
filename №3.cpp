#include <iostream>
#include <numeric>
using namespace std;

long long gcd(long long a, long long b) { return b ? gcd(b, a % b) : a; }

// Числа Эйлера 2-го рода
const long long E[11][11] = {
    {1},
    {1},
    {1, 1},
    {1, 4, 1},
    {1, 11, 11, 1},
    {1, 26, 66, 26, 1},
    {1, 57, 302, 302, 57, 1},
    {1, 120, 1191, 2416, 1191, 120, 1},
    {1, 247, 4293, 15619, 15619, 4293, 247, 1},
    {1, 502, 14608, 88234, 156190, 88234, 14608, 502, 1},
    {1, 1013, 47840, 455192, 1310354, 1310354, 455192, 47840, 1013, 1}
};

int main() {
    int a, b;
    cin >> a >> b;
    
    if (b == 1) {
        cout << "infinity" << endl;
        return 0;
    }
    
    // Вычисляем A_a(b) = sum_{k=0}^{a-1} E[a][k] * b^(a-1-k)
    long long A = 0, powB = 1;
    for (int k = a - 1; k >= 0; k--) {
        A += E[a][k] * powB;
        powB *= b;
    }
    
    long long num = A * b;
    long long den = 1;
    for (int i = 0; i < a + 1; i++) den *= (b - 1);
    
    long long g = gcd(num, den);
    cout << num / g << "/" << den / g << endl;
    
    return 0;
}