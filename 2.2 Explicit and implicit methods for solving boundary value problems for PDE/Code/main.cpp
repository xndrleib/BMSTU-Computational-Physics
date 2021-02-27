#include <iostream>
#include <cmath>
#include <fstream>

using std:: cout; using std:: endl; using std::ofstream; using std::ios;

double k = 0.3, theta = 1;
double a = 0, b = 2 * M_PI, T = 2;
int Nx = 120, Ny = 200;
double h = (b - a) / Nx, tau = T / Ny;

double D(double x); // коэффициент диффузии
double Ad(double x); // коэффициент диффузии, умноженный на tau / h^2
double u0(double x); // начальное условие
double alpha1(double x, double t); // ГУ-1
double beta1(double t); // ГУ-1
double mu1(double t); // ГУ-1
double alpha2(double x, double t);  // ГУ-2
double beta2(double t); // ГУ-2
double mu2(double t); // ГУ-2
double fun(double x, double t);

int main() {
    cout << k * k * tau / (h * h);

    double A, C, B;
    double F;
    auto **xi = new double* [Nx+1];
    auto **eta = new double* [Nx+1];
    auto **u = new double* [Nx+1];

    for(int i = 0; i < Nx + 1; i++) {
        xi[i] = new double [Ny+1];
        eta[i] = new double [Ny+1];
        u[i] = new double [Ny+1];
    }

    // Начальные условия и коэффициенты прямой прогонки
    for (int j = 0; j < Ny; j++) {
        xi[1][j+1] = alpha1(a,(j+1) * tau) / (alpha1(a,(j+1) * tau) - h * beta1((j+1) * tau));
        eta[1][j+1] = h * mu1((j+1) * tau) / (h * beta1((j+1) * tau) - alpha1(a,(j+1) * tau));
    }

    for (int i = 0; i < Nx + 1; i++) {
        u[i][0] = u0(i * h + a);
    }

    for (int j = 0; j < Ny; j++) {
        for (int i = 1; i < Nx; i++) {
            A = theta * Ad((i - 0.5) * h + a);
            C = 1 + theta * (Ad((i + 0.5) * h + a) + Ad((i - 0.5) * h + a));
            B = theta * Ad((i + 0.5) * h + a);
            F = (1 - theta) * Ad((i-0.5) * h + a) * u[i-1][j] +
                    (1 - (1 - theta) * (Ad((i+0.5) * h + a) + Ad((i-0.5) * h + a))) * u[i][j] +
                    (1 - theta) * Ad((i+0.5) * h + a) * u[i+1][j] + fun(i * h + a, j * tau) * tau;
            xi[i+1][j+1] = B / (C - A * xi[i][j+1]);
            eta[i+1][j+1] = (A * eta[i][j+1] + F) / (C - xi[i][j+1] * A);
            }

        u[Nx][j+1] = (eta[Nx][j+1] * alpha2(Nx * h + a, j+1) + h * mu2((j+1) * tau)) /
                   ((1 - xi[Nx][j+1]) * alpha2(Nx * h + a, (j + 1) * tau) + h * beta2((j+1) * tau));

        for (int i = Nx - 1; i >= 0; i--) {
                u[i][j+1] = xi[i+1][j+1] * u[i+1][j+1] + eta[i+1][j+1];
        }
    }

    ofstream out;
    out.open("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW2\\Визуализация\\data_implicit.txt");
    out.setf(ios::fixed);
    for (int j = 0; j < Ny+1; j++) {
        if (j == 0) out << "{";
        for (int i = 0; i < Nx+1; i++) {
            out << "{" << a + i * h << "," << j * tau << "," << u[i][j] << "}";
            if (i < Nx || j < Ny) out << "," << endl;
        }
        if (j == Ny) out << "}";
    }
    return 0;
}
double D(double x) {
    return k * k;
}
double Ad(double x) {
    return D(x) * tau / (h * h);
}
double u0(double x) {
    return sin(x / 2) + x / 2;
}
double alpha1(double x, double t) {
    return 0;
}
double beta1(double t) {
    return 1;
}
double mu1(double t) {
    return 0;
}
double alpha2(double x, double t) {
    return 1;
}
double beta2(double t) {
    return 0;
}
double mu2(double t) {
    return 0;
}
double fun(double x, double t) {
    return cos(x);
}