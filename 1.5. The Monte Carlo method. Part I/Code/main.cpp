#include <iostream>
using namespace std;
#include <random>
#include <cmath>

const double PI = 3.141592653589793238463;
double a1 = 0, b1 = 1, c1 = exp(1), c11 = exp(1) - 2.5, c111 = 0.5 * (exp(1)+1); // границы интегрирования для f1
double Integral1 = exp(1) - 1;  // точное значение интеграла для f1
double a2 = 0, b2 = PI/2, c2 = 1, c22 = 1 - PI/2 + pow(PI,3) / 48, c222 = PI / 4; // границы интегрирования для f2
double Integral2 = 1;  // точное значение интеграла для f2
double a3 = 0, b3 = sqrt(3), c3 = sqrt(3) * atan(sqrt(3)), c33 = 7.985, c333 = PI / (2 * sqrt(3)); // границы интегрирования для f3
double Integral3 = (4 * PI - 3 * sqrt(3)) * 1 / 6;  // точное значение интеграла для f3
int N = 100;

// Функции f1
double f1(double x); // интегрируемая функция
double fg1(double x); // функция для выделения главной части
double fs1(double x); // симметризованная функция

double f2(double x);
double fg2(double x);
double fs2(double x);

double f3(double x);
double fg3(double x);
double fs3(double x);

int main()
{
    setlocale(LC_ALL, "Rus");
    mt19937 gen{random_device()()};
    uniform_real_distribution <double> dist(0.0, 1.0);

    // Метод среднего и площадей для f1
    double x, y;
    double sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a1 + (b1 - a1)*dist(gen); // gamma_i
        y = c1 * dist(gen); // gamma_i+1
        if (y < f1(x)) {
            n += 1;
        }
        sum += f1(x);
    }

    double IntegralM1 = (b1 - a1) * sum / N;
    double AbsErrorM1 = abs(IntegralM1 - Integral1);
    double DispM1 = N / 9 * pow(AbsErrorM1, 2);

    cout << "Method of the average for I1: " << IntegralM1 << endl;
    cout << "AbsError = " << AbsErrorM1 << endl;
    cout << "Dispersion = " << DispM1 << "\n\n";

    double IntegralS1 = c1 * (b1 - a1) * n / N;
    double AbsErrorS1 = abs(IntegralS1 - Integral1);
    double DispS1 = N / 9 * pow(AbsErrorS1, 2);

    cout << "Square method for I1: " << IntegralS1 << endl;
    cout << "AbsError = " << AbsErrorS1 << endl;
    cout << "Dispersion = " << DispS1 << "\n\n";

    // Метод среднего и площадей для fg1
    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a1 + (b1 - a1)*dist(gen); // gamma_i
        y = c11 * dist(gen); // gamma_i+1
        if (y < f1(x) - fg1(x)) {
            n += 1;
        }
        sum += f1(x) - fg1(x);
    }
    double IntegralMG1 = (b1 - a1) * sum / N + 1.66;
    double AbsErrorMG1 = abs(IntegralMG1 - Integral1);
    double DispMG1 = N / 9 * pow(AbsErrorMG1, 2);

    cout << "Main part selection + MA for I1: " << IntegralMG1 << endl;
    cout << "AbsError = " << AbsErrorMG1 << endl;
    cout << "Dispersion = " << DispMG1 << "\n\n";

    double IntegralSG1 = c11 * (b1 - a1) * n / N + 1.66;
    double AbsErrorSG1 = abs(IntegralSG1 - Integral1);
    double DispSG1 = N / 9 * pow(AbsErrorSG1, 2);

    cout << "Main part selection + SM for I1: " << IntegralSG1 << endl;
    cout << "AbsError = " << AbsErrorSG1 << endl;
    cout << "Dispersion = " << DispSG1 << "\n\n";

    //Метод симметризации для fs1
    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a1 + (b1 - a1)*dist(gen);
        y = c111 * dist(gen);
        if (y < fs1(x)) {
            n += 1;
        }
        sum += fs1(x);
    }
    double IntegralMS1 = (b1 - a1) * sum / N;
    double AbsErrorMS1 = abs(IntegralMS1 - Integral1);
    double DispMS1 = N / 9 * pow(AbsErrorMS1, 2);

    cout << "Method of the average + symmetrization for I1: " << IntegralMS1 << endl;
    cout << "AbsError = " << AbsErrorMS1 << endl;
    cout << "Dispersion = " << DispMS1 << "\n\n";

    double IntegralSS1 = c111 * (b1 - a1) * n / N;
    double AbsErrorSS1 = abs(IntegralSS1 - Integral1);
    double DispSS1 = N / 9 * pow(AbsErrorSS1, 2);

    cout << "Square method + symmetrization for I1: " << IntegralSS1 << endl;
    cout << "AbsError = " << AbsErrorSS1 << endl;
    cout << "Dispersion = " << DispSS1 << "\n\n";

    // Метод среднего и площадей для f2

    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a2 + (b2 - a2)*dist(gen);
        y = c2 * dist(gen);
        if (y < f2(x)) {
            n += 1;
        }
        sum += f2(x);
    }

    double IntegralM2 = (b2 - a2) * sum / N;
    double AbsErrorM2 = abs(IntegralM2 - Integral2);
    double DispM2 = N / 9 * pow(AbsErrorM2, 2);

    cout << "Method of the average for I2: " << IntegralM1 << endl;
    cout << "AbsError = " << AbsErrorM2 << endl;
    cout << "Dispersion = " << DispM2 << "\n\n";

    double IntegralS2 = c2 * (b2 - a2) * n / N;
    double AbsErrorS2 = abs(IntegralS2 - Integral2);
    double DispS2 = N / 9 * pow(AbsErrorS2, 2);

    cout << "Square method for I2: " << IntegralS2 << endl;
    cout << "AbsError = " << AbsErrorS2 << endl;
    cout << "Dispersion = " << DispS2 << "\n\n";

    // Метод среднего и площадей для fg3
    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a2 + (b3 - a2)*dist(gen);
        y = c22 * dist(gen);
        if (y < f2(x) - fg2(x)) {
            n += 1;
        }
        sum += f2(x) - fg2(x);
    }
    double IntegralMG2 = (b2 - a2) * sum / N + 0.98003;
    double AbsErrorMG2 = abs(IntegralMG2 - Integral2);
    double DispMG2 = N / 9 * pow(AbsErrorMG2, 2);

    cout << "Main part selection + MA for I2: " << IntegralMG2 << endl;
    cout << "AbsError = " << AbsErrorMG2 << endl;
    cout << "Dispersion = " << DispMG2 << "\n\n";

    double IntegralSG2 = c22 * (b2 - a2) * n / N + 0.98003;
    double AbsErrorSG2 = abs(IntegralSG2 - Integral2);
    double DispSG2 = N / 9 * pow(AbsErrorSG2, 2);

    cout << "Main part selection + SM for I2: " << IntegralSG2 << endl;
    cout << "AbsError = " << AbsErrorSG2 << endl;
    cout << "Dispersion = " << DispSG2 << "\n\n";

    //Метод симметризации для fs2
    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a2 + (b2 - a2)*dist(gen);
        y = c222 * dist(gen);
        if (y < fs2(x)) {
            n += 1;
        }
        sum += fs2(x);
    }
    double IntegralMS2 = (b2 - a2) * sum / N;
    double AbsErrorMS2 = abs(IntegralMS2 - Integral2);
    double DispMS2 = N / 9 * pow(AbsErrorMS2, 2);

    cout << "Method of the average + symmetrization for I2: " << IntegralMS2 << endl;
    cout << "AbsError = " << AbsErrorMS2 << endl;
    cout << "Dispersion = " << DispMS2 << "\n\n";

    double IntegralSS2 = c222 * (b2 - a2) * n / N;
    double AbsErrorSS2 = abs(IntegralSS2 - Integral2);
    double DispSS2 = N / 9 * pow(AbsErrorSS2, 2);

    cout << "Square method + symmetrization for I2: " << IntegralSS2 << endl;
    cout << "AbsError = " << AbsErrorSS2 << endl;
    cout << "Dispersion = " << DispSS2 << "\n\n";

    // Метод среднего и площадей для f3

    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a3 + (b3 - a3)*dist(gen);
        y = c3 * dist(gen);
        if (y < f3(x)) {
            n += 1;
        }
        sum += f3(x);
    }

    double IntegralM3 = (b3 - a3) * sum / N;
    double AbsErrorM3 = abs(IntegralM3 - Integral3);
    double DispM3 = N / 9 * pow(AbsErrorM3, 2);

    cout << "Method of the average for I3: " << IntegralM3 << endl;
    cout << "AbsError = " << AbsErrorM3 << endl;
    cout << "Dispersion = " << DispM3 << "\n\n";

    double IntegralS3 = c3 * (b3 - a3) * n / N;
    double AbsErrorS3 = abs(IntegralS3 - Integral3);
    double DispS3 = N / 9 * pow(AbsErrorS3, 2);

    cout << "Square method for I3: " << IntegralS3 << endl;
    cout << "AbsError = " << AbsErrorS3 << endl;
    cout << "Dispersion = " << DispS3 << "\n\n";

    // Метод среднего и площадей для fg3
    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a3 + (b3 - a3)*dist(gen);
        y = c33 * dist(gen);
        if (y < f3(x) - fg3(x)) {
            n += 1;
        }
        sum += f3(x) - fg3(x);
    }
    double IntegralMG3 = (b3 - a3) * sum / N - 0.19795;
    double AbsErrorMG3 = abs(IntegralMG3 - Integral3);
    double DispMG3 = N / 9 * pow(AbsErrorMG3, 2);

    cout << "Main part selection + MA for I3: " << IntegralMG3 << endl;
    cout << "AbsError = " << AbsErrorMG3 << endl;
    cout << "Dispersion = " << DispMG3 << "\n\n";

    double IntegralSG3 = c33 * (b3 - a3) * n / N - 0.19795;
    double AbsErrorSG3 = abs(IntegralSG3 - Integral3);
    double DispSG3 = N / 9 * pow(AbsErrorSG3, 2);

    cout << "Main part selection + SM for I3: " << IntegralSG3 << endl;
    cout << "AbsError = " << AbsErrorSG3 << endl;
    cout << "Dispersion = " << DispSG3 << "\n\n";

    //Метод симметризации для fs3
    sum = 0, n = 0;
    for (int i = 0; i < N; i++) {
        x = a3 + (b3 - a3)*dist(gen);
        y = c333 * dist(gen);
        if (y < fs3(x)) {
            n += 1;
        }
        sum += fs3(x);
    }
    double IntegralMS3 = (b3 - a3) * sum / N;
    double AbsErrorMS3 = abs(IntegralMS3 - Integral3);
    double DispMS3 = N / 9 * pow(AbsErrorMS3, 2);

    cout << "Method of the average + symmetrization for I3: " << IntegralMS3 << endl;
    cout << "AbsError = " << AbsErrorMS3 << endl;
    cout << "Dispersion = " << DispMS3 << "\n\n";

    double IntegralSS3 = c333 * (b3 - a3) * n / N;
    double AbsErrorSS3 = abs(IntegralSS3 - Integral3);
    double DispSS3 = N / 9 * pow(AbsErrorSS3, 2);

    cout << "Square method + symmetrization for I3: " << IntegralSS3 << endl;
    cout << "AbsError = " << AbsErrorSS3 << endl;
    cout << "Dispersion = " << DispSS3 << "\n\n";
    return 0;
}

double f1(double x)
{
    return exp(x);
}

double fg1(double x)
{
    return 1 + x + x*x/2;
}

double fs1(double x)
{
    return 0.5*(exp(x) + exp(b1 - x));
}

double f2(double x)
{
    return sin(x);
}

double fg2(double x)
{
    return x - pow(x,3) / 6;
}

double fs2(double x)
{
    return 0.5 * (sin(x) + sin(b2 - x));
}

double f3(double x)
{
    return x * atan(x);
}

double fg3(double x)
{
    return pow(x,2) - pow(x,4) / 3 + pow(x,6) / 5 - pow(x,8) / 7;
}

double fs3(double x)
{
    return 0.5 * (x * atan(x) + (b3 - x) * atan(b3 - x));
}
