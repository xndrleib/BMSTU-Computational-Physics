#include <iostream>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::ofstream;

double a = 0, b = 1, y_zero = 1;
int N = 25;
double h = (b-a) / N;
double lambda[] = {1., 10. ,100.};
int k = 2;
void Euler_Method(double* x, double* y);
void Implicit_Method4(double* x, double* y);
void Implicit_Euler_Method(double* x, double* y);

int main(){
    cout.setf(std::ios::fixed);
    double *y = new double[N+1];
    double *x = new double[N+1];
    y[0] = y_zero;
    x[N] = b;
    for(int i=0; i<=N; i++){
        x[i] = a + i * h;
    }
    Euler_Method(x, y);
    Implicit_Method4(x, y);
    Implicit_Euler_Method(x, y);
    return 0;
}
void Euler_Method(double* x, double* y){
    ofstream fout("Euler_Method_N100_L1");
    fout << "{";
    cout << "{";
    for(int i=0; i<=N; i++){
        y[i+1] = (1 - h * lambda[k]) * y[i];
        cout << "{" << x[i] << "," << y[i] << "},"  << endl;
        fout << "{" << x[i] << "," << y[i] << "}";
    }
    cout << "}" << endl;
    fout << "}";
    fout.close();
}
void Implicit_Euler_Method(double* x, double* y){
    ofstream fout("Implicit_Euler_Method_N100_L1");
    fout << "{";
    cout << "{";
    for(int i=0; i<=N; i++){
        y[i+1] = y[i] / (1 + h * lambda[k]);
        cout << "{" << x[i] << "," << y[i] << "},"  << endl;
        fout << "{" << x[i] << "," << y[i] << "}";
    }
    cout << "}" << endl;
    fout << "}";
    fout.close();
}
void Implicit_Method4(double* x, double* y){
    ofstream fout("Implicit_Method4_N100_L1");
    fout << "{";
    cout << "{";
    for(int i=0; i<=N; i++){
        y[i+4] = (48. / 25 * y[i+3] - 36. /25 * y[i+2] + 16. /25 * y[i+1] - 3. / 25 * y[i]) / (1 + 12. / 25 * h * lambda[k]);
        cout << "{" << x[i] << "," << y[i] << "},"  << endl;
        fout << "{" << x[i] << "," << y[i] << "}";
    }
    cout << "}" << endl;
    fout << "}";
    fout.close();
}