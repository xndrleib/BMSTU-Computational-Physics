#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::endl;

double a = 0, b = 1, u_zero = -1;
int N = 50;
int NR = 3;
double eps = 1E-1;
double h = (b-a) / N;
double fun(double x, double u);
void pred_cor(double* x, double* u, int i);
int main() {
    double *u = new double[N+1];
    double *x = new double[N+1];
    u[0] = u_zero;
    x[N] = b;
    double *k0 = new double[NR];
    double *k1 = new double[NR];
    double *k2 = new double[NR];
    double *k3 = new double[NR];
    int i;
    for(i=0; i<=N; i++){
        x[i] = a + i*h;
    }
    // Runge_Kutta
    cout << "Runge_Kutta" << endl;
    for(i=0; i <= NR; i++){

        k0[i] = fun(x[i], u[i]);
        k1[i] = fun(x[i] + h / 2, u[i] + h * k0[i] / 2);
        k2[i] = fun(x[i] + h / 2, u[i] + h * k1[i] / 2);
        k3[i] = fun(x[i] + h, u[i] + h * k2[i]);
        u[i+1] = u[i] + h * (k0[i] + 2 * k1[i] + 2 * k2[i] + k3[i]) / 6;
        cout << "{" << i << ", " << x[i] << ", " << u[i] << "}," << endl;
    }
    pred_cor(x, u, i);
    return 0;
}
void pred_cor(double* x, double* u, int i){
    double u_cor;
    for(i = NR; i<=N; i++){
        u[i+1] = u[i] + h*(55*fun(x[i],u[i]) - 59*fun(x[i-1],u[i-1]) + 37*fun(x[i-2],u[i-2]) - 9*fun(x[i-3],u[i-3])) / 24;
        do{
            u_cor = u[i+1];
            u[i+1] = u[i] + h * (9*fun(x[i+1], u_cor) + 19 * fun(x[i], u[i]) - 5*fun(x[i-1],u[i-1]) + fun(x[i-2],u[i-2])) / 24;
        } while(eps <= abs(u[i+1]-u_cor));
        cout << "{" << i << ", " << x[i] << ", " << u[i] << "}," << endl;
    }
}
double fun(double x, double u){
    return (2-u) * tan(x);
}