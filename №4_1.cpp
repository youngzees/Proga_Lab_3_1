#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<long long> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Префиксные суммы
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    
    int pos = 0;           // текущая позиция в массиве
    int last_opponent = 0; // сколько чисел стёр противник на прошлом ходу (0 — нет ограничения)
    long long score_pavel = 0, score_vika = 0;
    bool pavel_turn = true;
    
    while (pos < n) {
        int remaining = n - pos;
        int max_k = min(m, remaining);
        
        int best_k = -1;
        long long best_sum = -1e18; // очень маленькое число
        
        for (int k = 1; k <= max_k; k++) {
            // нельзя брать столько же, сколько противник на прошлом ходу
            if (k == last_opponent) continue;
            
            long long sum = prefix[pos + k] - prefix[pos];
            
            if (sum > best_sum || (sum == best_sum && k < best_k)) {
                best_sum = sum;
                best_k = k;
            }
        }
        
        // Если нет подходящего k (такое возможно только если m=1 и last_opponent=1, но m>=2, так что не случится)
        if (best_k == -1) {
            // на всякий случай — берём k=1, если вдруг
            best_k = 1;
            best_sum = prefix[pos + 1] - prefix[pos];
        }
        
        // Добавляем сумму к счёту текущего игрока
        if (pavel_turn) {
            score_pavel += best_sum;
        } else {
            score_vika += best_sum;
        }
        
        // Обновляем позицию
        pos += best_k;
        
        // Для следующего хода: противник стёр best_k чисел
        last_opponent = best_k;
        
        // Меняем игрока
        pavel_turn = !pavel_turn;
    }
    
    // Определяем победителя
    if (score_pavel > score_vika) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
    
    return 0;
}