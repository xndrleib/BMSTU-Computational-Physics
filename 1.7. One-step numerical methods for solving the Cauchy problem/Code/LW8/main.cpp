#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;

double a = 0, b = 1, y_zero = -1;
int N = 1000;
double h = (b-a) / N;
double fun(double x, double y);
double fun_ex(double x);
void Euler_Method(double* x, double* y, double* delta, int i);
void Modified_Euler_Method(double* x, double* y, double* delta, int i);
void Improved_Euler_Method(double* x, double* y, double* delta, int i);
void RungeKutta(double* x, double* y, double* delta, int i);

int main() {
    double *y = new double[N+1];
    double *x = new double[N+1];
    double *delta = new double[N+1];
    y[0] = y_zero;
    x[N] = b;
    int i;
    for(i=0; i<=N; i++){
        x[i] = a + i*h;
    }

    cout << "EM" << endl;
    Euler_Method(x, y, delta, i);

    cout << endl << "MEM" << endl;
    Modified_Euler_Method(x, y, delta, i);

    cout << endl << "IEM" << endl;
    Improved_Euler_Method(x, y, delta, i);

    cout << endl << "R-K" << endl;
    RungeKutta(x, y, delta, i);
    return 0;
}
void Euler_Method(double* x, double* y, double* delta, int i){
    ofstream fout("Euler_Method");
    for(i=0; i<=N; i++){
        y[i+1] = y[i] + h*fun(x[i],y[i]);
        delta[i] = fun_ex(x[i]) - y[i];
        cout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
        fout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
    }
    fout.close();
}
void Modified_Euler_Method(double* x, double* y, double* delta, int i){
    ofstream fout("Modified_Euler_Method");
    for(i=0; i<=N; i++){
        y[i+1] = y[i] + h*(fun(x[i],y[i]) + fun(x[i+1],y[i] + h*fun(x[i],y[i]))) / 2;
        delta[i] = fun_ex(x[i]) - y[i];
        cout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
        fout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
    }
    fout.close();
}
void Improved_Euler_Method(double* x, double* y, double* delta, int i){
    ofstream fout("Improved_Euler_Method");
    for(i=0; i<=N; i++){
        y[i+1] = y[i] + h*fun(x[i] + h / 2, y[i] + h * fun(x[i], y[i]) / 2);
        delta[i] = fun_ex(x[i]) - y[i];
        cout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
        fout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
    }
    fout.close();
}
void RungeKutta(double* x, double* y, double* delta, int i){
    ofstream fout("RungeKutta");
    double *k0 = new double[N+1];
    double *k1 = new double[N+1];
    double *k2 = new double[N+1];
    double *k3 = new double[N+1];
    for(i=0; i<=N; i++){
        k0[i] = fun(x[i], y[i]);
        k1[i] = fun(x[i] + h / 2, y[i] + h * k0[i] / 2);
        k2[i] = fun(x[i] + h / 2, y[i] + h * k1[i] / 2);
        k3[i] = fun(x[i] + h, y[i] + h * k2[i]);
        y[i+1] = y[i] + h * (k0[i] + 2 * k1[i] + 2 * k2[i] + k3[i]) / 6;
        delta[i] = fun_ex(x[i]) - y[i];
        cout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
        fout << i << "\t" << x[i] << "\t" << y[i] << "\t" << delta[i] << endl;
    }
    fout.close();
}
double fun(double x, double y){
    return (2-y) * tan(x);
}
double fun_ex(double x) {
    return -3 * cos(x) + 2;
}