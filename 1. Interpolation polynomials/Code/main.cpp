#include <iostream>
#include <math.h>
using namespace std;

class Lagrange{
private:
    double* data_x;
    double* data_y;
    unsigned size;
    double left_bound, right_bound;
public:
    Lagrange(double* d1, double* d2, unsigned s, double l, double r){
        size = s;
        data_x = new double[size];
        data_y = new double[size];
        left_bound = l;
        right_bound = r;
        for(unsigned i = 0; i < s; i++)
            data_x[i]=d1[i];
        for(unsigned i = 0; i < s; i++)
            data_y[i]= d2[i];
    }
    double Interpolate(double value);
    void CreateIntArray();
};

void Lagrange::CreateIntArray(){
    cout << "Lagrange interpolation" << endl;
    cout << "{";
    int d = 150;
    double x, y;
    for(int i = 0; i < d + 1;i++){
        x = left_bound + ((right_bound - left_bound) / d)*i;
        y = Interpolate(x);
        cout << "{" << x << ", " << y << "},";
    }
    cout << endl;
    delete data_x;
    delete data_y;
}

double Lagrange::Interpolate(double x)
{
    double y = 0;
    for (int i=0; i<size; i++)
    {
        double t = data_y[i];
        for (int j = 0;j < size;j++)
        {
            if (j!=i)
                t = t * (x - data_x[j]) / double(data_x[i] - data_x[j]);
        }
        y += t;
    }
    return y;
}

class Newton{
private:
    double* data_x;
    double** data_y;
    unsigned size;
    double left_bound, right_bound;
public:
    Newton(double* d1, double* d2, unsigned s, double l, double r){
        size = s;
        data_x = new double[size];
        data_y = new double*[size];
        left_bound = l;
        right_bound = r;
        for(unsigned i = 0; i < s; i++)
            data_x[i] = d1[i];
        for(unsigned i = 0; i < s; i++){
            data_y[i]= new double[size];
            data_y[i][0] = d2[i];
        }
        for (int i = 1; i < size; i++) {
            for (int j = 0; j < size - i; j++)
                data_y[j][i] = data_y[j + 1][i - 1] - data_y[j][i - 1];
        }
        for (int i = 0; i < size; i++) {
            cout << data_x[i] << "\t";
            for (int j = 0; j < size - i; j++)
                cout << data_y[i][j] << "\t";
            cout << endl;
        }
    }
    double DeltaCalc(float u, int n);
    int Factorial(int n);
    double Interpolate(double x);
    void CreateIntArray();
};

double Newton::Interpolate(double x){
    double y = data_y[0][0];
    double u = (x - data_x[0]) / (double)(data_x[1] - data_x[0]);
    for (int i = 1; i < size; i++){y += (DeltaCalc(u, i) * data_y[0][i]) / (double)Factorial(i);}
    return y;
}

void Newton::CreateIntArray(){
    int d = 150;
    double x, y;
    for(int i = 0; i < d + 1;i++){
        x = left_bound + ((right_bound - left_bound) / (double)d)*i;
        y = Interpolate(x);
        cout << "{" << x << ", " << y << "},";
    }
    delete data_x;
    delete data_y;
}

double Newton::DeltaCalc(float u, int n)
{
    float t = u;
    for (int i = 0; i < n - 1; i++){t *= (u - i + 1);}
    return t;
}

int Newton::Factorial(int n){
    int factorial = 1;
    for (int i = 2; i <= n; i++)
        factorial *= i;
    return factorial;
}

double Runge_Function(double t){return 1.0 / (1.0 + 25.0 * pow(t, 2));}

int main() {
    int n = 5;
    double left_bound = -1, right_bound = 1, dat_x[n], dat_y[n];
    for (int i = 0; i < n; i++){
        dat_x[i] = left_bound + (double)i * (double)(right_bound - left_bound) / (double)(n - 1);
        dat_y[i] = Runge_Function(dat_x[i]);
    };
    Lagrange interp(dat_x, dat_y, n, left_bound, right_bound);
    interp.CreateIntArray();
    Newton interp2(dat_x, dat_y, n, left_bound, right_bound);
    interp2.CreateIntArray();

    return 0;
}
