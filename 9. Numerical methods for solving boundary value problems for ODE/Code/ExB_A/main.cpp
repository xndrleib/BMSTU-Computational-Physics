#include <iostream>
using namespace std;

int N = 100;
double c_0 = 0, c_n = 0, l_b = -1, r_b = 1;
double h = (r_b - l_b) / N;
double f(double t);
int main() {
    double* A = new double[N+1];
    double* C = new double[N+1];
    double* B = new double[N+1];
    double* F = new double[N+1];
    double* x = new double[N+1];
    x[0] = l_b;
    x[N] = r_b;
    double* c = new double[N+1];
    c[0] = c_0;
    c[N] = c_n;
    double* d = new double[N+1];
    double* b = new double[N+1];
    double* a = new double[N+1];
    double* alpha = new double[N+1];
    alpha[1] = 0;
    double* beta = new double[N+1];
    beta[1] = c_0;

    for(unsigned i=1; i < N; i++){
        x[i] = x[i-1] + h;
    }

    for(unsigned i=1; i < N; i++){
        A[i] = 1;
        C[i] = 4;
        B[i] = 1;
        F[i] = 6 * (f(x[i-1]) - 2 * f(x[i]) + f(x[i+1])) / (h * h);
    }
    for(unsigned i=1; i < N + 1; i++){
        alpha[i + 1] = -B[i] / (A[i] * alpha[i] + C[i]);
        beta[i + 1] = (F[i] - A[i] * beta[i]) / (A[i] * alpha[i] + C[i]);
    }
    for(unsigned i = N - 1; i > 0; i--){
        c[i] = alpha[i+1] * c[i+1] + beta[i+1];
    }
    for(unsigned i = N - 1; i > 0; i--) {
        d[i] = (c[i] - c[i - 1]) / h;
        b[i] = h * c[i] / 2 - h * h * d[i] / 6 + (f(x[i]) - f(x[i - 1])) / h;
        a[i] = f(x[i]);
        cout << "{" << x[i] << ", " << a[i] << ", " << b[i] << ", " << c[i] << ", " << d[i] << "}," << endl;
    }
    return 0;
}
double f(double t){
    return  1.0 / (1.0 + 25.0 * t * t);
}
