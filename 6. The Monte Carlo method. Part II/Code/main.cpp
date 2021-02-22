#include <iostream>
using namespace std;
#include <random>
#include <cmath>

double N = 1e5;
double fun1(double dis, double m);

int main(){
    mt19937 gen{random_device()()};
    uniform_real_distribution <double> dist(0.0, 1.0);
    double r1, mu2, r2, dis1, dis2, l;
    double sum11 = 0, sum12 = 0, sum21 = 0, sum22 = 0;
    double Integral1(2.133), Integral2(4.000);

    for (int i = 0; i < N-1; i++) {
        r1 = pow(dist(gen), 1. / 3);
        mu2 = 2 * dist(gen) - 1;
        r2 = pow(dist(gen), 1. / 3);
        dis1 = sqrt(r1*r1 + r2*r2 - 2*r1*r2*mu2);
        l = r1*mu2 + sqrt(1 - r1*r1*(1 - mu2*mu2));
        dis2 = l*dist(gen);
        sum11 += fun1(dis1, 1.);
        sum12 += fun1(dis2, 1.) * dis2*dis2 * l;
        sum21 += fun1(dis1, 2.);
        sum22 += fun1(dis2, 2.) * dis2*dis2 * l;
    }

    cout << "Number of steps: " << N << endl;

    double Integral11 = 16 * sum11 / (9*N);
    double AbsError11 = abs(Integral11 - Integral1);
    double Disp11 = N / 9 * pow(AbsError11, 2);

    cout << "m = 1\n" << "I1 = " << Integral11 << endl;
    cout << "AbsError = " << AbsError11 << endl;
    cout << "Dispersion = " << Disp11 << "\n\n";

    double Integral12 = 16 * sum12 / (3*N);
    double AbsError12 = abs(Integral12 - Integral1);
    double Disp12 = N / 9 * pow(AbsError12, 2);

    cout << "I2 = " << Integral12 << endl;
    cout << "AbsError = " << AbsError12 << endl;
    cout << "Dispersion = " << Disp12 << "\n\n";

    double Integral21 = 16 * sum21 / (9*N);
    double AbsError21 = abs(Integral21 - Integral2);
    double Disp21 = N / 9 * pow(AbsError21, 2);

    cout << "m = 2\n" << "I1 = " << Integral21 << endl;
    cout << "AbsError = " << AbsError21 << endl;
    cout << "Dispersion = " << Disp21 << "\n\n";

    double Integral22 = 16 * sum22 / (3*N);
    double AbsError22 = abs(Integral22 - Integral2);
    double Disp22 = N / 9 * pow(AbsError22, 2);

    cout << "I2 = " << Integral22 << endl;
    cout << "AbsError = " << AbsError22 << endl;
    cout << "Dispersion = " << Disp22 << "\n\n";
    return 0;
}
double fun1(double dis, double m){
    return 1 / pow(dis, m);
}