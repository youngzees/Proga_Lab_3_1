#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double x_start, x_end, dx;
    
    cout << "X начальное: ";
    cin >> x_start;
    cout << "X конечное: ";
    cin >> x_end;
    cout << "шаг dx: ";
    cin >> dx;

    cout << "\n" << "    X  |   Y  \n";
    
    // Табулирование
    for (double x = x_start; x <= x_end; x += dx) {
        double y = -sin(M_PI * x / 4.0);
        cout << setw(6) << x << " | " << y << endl;
    }
    
    cout << "\n";
    return 0;
}