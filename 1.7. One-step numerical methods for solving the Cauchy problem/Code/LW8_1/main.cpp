#include <iostream>
#include <cmath>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;

double N = 1000;
double lambda = 1, omega_zero = 1. / 2, upsilon_zero = 1, x_zero = 0;
double T = 3 / lambda;
double tau = T / N;
double theta = sqrt(pow(lambda, 2) - pow(omega_zero, 2));

void Euler_Method(double* x, double* v, double* t, double* delta, int i);
void Euler_Kromer(double* x, double* v, double* t, double* delta, int i);
double fun_ex(double t);
double fun(double x, double v);
int main() {
    double *x = new double[N+1];
    double *v = new double[N+1];
    double *t = new double[N+1];
    double *delta = new double[N+1];
    x[0] = x_zero;
    v[0] = upsilon_zero;
    int i;
    for(i=0; i<=N; i++){
        t[i] = i * tau;
    }
    cout << "EM" << endl;
    Euler_Method(x, v, t, delta, i);

    cout << endl << "E-K" << endl;
    Euler_Kromer(x, v, t, delta, i);
    return 0;
}
void Euler_Method(double* x, double* v, double* t, double* delta, int i){
    ofstream fout("Euler_Method");
    for(i=0; i<=N; i++){
        v[i + 1] = v[i] + tau * fun(x[i], v[i]);
        x[i + 1] = x[i] + tau * v[i];
        delta[i] = fun_ex(t[i]) - x[i];
        cout << i << "\t" << t[i] << "\t" << v[i] << "\t" << x[i] << "\t" << delta[i] << "\t" << fun_ex(t[i]) << endl;
        fout << i << "\t" << t[i] << "\t" << v[i] << "\t" << x[i] << "\t" << delta[i] << endl;
    }
    fout.close();
}
void Euler_Kromer(double* x, double* v, double* t, double* delta, int i){
    ofstream fout("Euler_Kromer");
    for(i=0; i<=N; i++){
        v[i + 1] = v[i] + tau * fun(x[i], v[i]);
        x[i + 1] = x[i] + tau * v[i + 1];
        delta[i] = fun_ex(t[i]) - x[i];
        cout << i << "\t" << t[i] << "\t" << v[i] << "\t" << x[i] << "\t" << delta[i] << "\t" << fun_ex(t[i]) << endl;
        fout << i << "\t" << t[i] << "\t" << v[i] << "\t" << x[i] << "\t" << delta[i] << endl;
    }
    fout.close();
}
double fun(double x, double v){
    return -2 * lambda * v - pow(omega_zero, 2) * x ;
}
double fun_ex(double t){
    return upsilon_zero * exp(- t * lambda ) * sinh(t * theta) / theta;
}


