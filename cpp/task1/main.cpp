#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x) {
    return 2*log(x) - 0.5*x + 1;
}

// Производная функции для метода Ньютона
double df(double x) {
    return (2 / x - 0.5);
}

// Функция для метода простых итераций
double phi(double x) {
    return x - 0.5 * (2 * log(x) - 0.5 * x + 1);
}

// Метод половинного деления
void bisection(double a, double b, double precision) {
    cout << "Метод половинного деления:\n";
    cout << "N\tan\t\t\tbn\t\t\tbn - an\n";
    cout << "————————————————————————————————————\n";

    int n = 0;
    double c;
    while (fabs(b - a) > precision) {
        n++;
        c = (a + b) / 2;
        cout << n << "\t" << fixed << setprecision(6) << a << "\t" << b << "\t" << fabs(b - a) << endl;

        if (f(c) == 0.0) {
            break;
        } else if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    cout << "Найденный корень: " << ((a + b) / 2) << endl;
    cout << "Значение в корне: " << f(((a + b) / 2)) << endl;
    cout << "Количество итераций: " << n << "\n\n";
}

// Метод Ньютона
void newton(double x0, double precision) {
    cout << "Метод Ньютона:\n";
    cout << "N\tXn\t\t\tXn+1\t\tXn+1 - Xn\n";
    cout << "————————————————————————————————————\n";

    int n = 0;
    double x = x0;
    double x_prev;
    double delta;

    do {
        n++;
        x_prev = x;
        x = x_prev - f(x_prev) / df(x_prev);
        delta = fabs(x - x_prev);
        cout << n << "\t" << fixed << setprecision(6) << x_prev << "\t" << x << "\t" << delta << endl;
    } while (fabs(f(x)) > precision);

    cout << "Найденный корень: " << x << endl;
    cout << "Значение в корне: " << f(x) << endl;
    cout << "Количество итераций: " << n << "\n\n";
}

// Метод простых итераций
void simple_iteration(double x0, double precision) {
    cout << "Метод простых итераций:\n";
    cout << "N\tXn\t\t\tXn+1\t\tXn+1 - Xn\n";
    cout << "————————————————————————————————————\n";

    int n = 0;
    double x = x0;
    double x_prev;
    double delta;

    do {
        n++;
        x_prev = x;
        x = phi(x_prev);
        delta = fabs(x - x_prev);
        cout << n << "\t" << fixed << setprecision(6) << x_prev << "\t" << x << "\t" << delta << endl;
    } while (fabs(f(x)) > precision);

    cout << "Найденный корень: " << x << endl;
    cout << "Значение в корне: " << f(x) << endl;
    cout << "Количество итераций: " << n << "\n";
}

int main() {
    double precision = 0.0001; // требуемая точность
    double a = 0.0, b = 1.0;  // графически определили интервал
    // Начальное приближение для Ньютона и простых итераций (середина интервала)
    double x0 = (a+b)/2;

    cout << "Решение уравнения 2𝑙𝑛𝑥 − 0.5𝑥 + 1 = 0 с точностью " << precision << endl;
    bisection(a, b, precision);
    newton(x0, precision);
    simple_iteration(x0, precision);

    return 0;
}