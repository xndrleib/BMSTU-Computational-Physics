#include <iostream>
#include <math.h>
using namespace std;

class Integrate{
private:
    int n;
    double h;
    double left_bound, right_bound;
public:
    Integrate(unsigned s, double l, double r){
        n = s;
        left_bound = l;
        right_bound = r;

        double h = (right_bound - left_bound)/(double)((n) - 1);
    }
    double Rectangle();
    double Trapeze();
    double Simpson(double n2);
    double Richardson();
    double Function(double t);
};


double Integrate::Rectangle(){
    double data_x[n + 1];
    double I = 0;

    for (int i = 0; i < n + 1; i++){
        data_x[i] = left_bound + i * (right_bound - left_bound) / (double)(n);
    };
    double h = (data_x[1] - data_x[0]) * 1.0;
    for (int i = 0; i < n; i++){
        I += (data_x[i+1] - data_x[i]) * Function(data_x[i] + 0.5 * h);
    };
    return I;
}

double Integrate::Trapeze(){
    double data_x[n + 1];
    double I = 0;
    for (int i = 0; i < n + 1; i++){
        data_x[i] = left_bound + i * (right_bound - left_bound) / (double)(n);
    };
    for (int i = 0; i < n; i++){
        I += (data_x[i+1] - data_x[i]) * 0.5 * (Function(data_x[i+1]) + Function(data_x[i]));
    };
    return I;
}

double Integrate::Simpson(double n2){
    int n1 = n2 * 2;
    double data_x[n1 + 1];
    double I = 0;
    for (int i = 0; i < n1 + 1; i++){
        data_x[i] = left_bound + i * (right_bound - left_bound) / (double)(n1);
    };

    double h = (data_x[1] - data_x[0]) * 1.0;
    for (int i = 0; i < n1 / 2; i++){
        I += Function(data_x[2*i]) + 4 * Function(data_x[2*i + 1]) + Function(data_x[2*i + 2]);
    };
    return I * h / 3.0;
}

double Integrate::Function(double t){
    return atan(t)*t;
}

double Integrate::Richardson(){
    double r1 = Simpson(10);
    double r2 = Simpson(20);
    double r3 = Simpson(40);
    int p = log2((r3 - r2) / (r2 - r1));
    double I = ((2 ^ p)*r1 - r2) / ((2 ^ p) - 1);
    return I;
}


int main() {
    Integrate tmp(10, 0, pow(3, 0.5));
    cout << "Rectangle: " << tmp.Rectangle() << endl;
    cout << "Trapeze: " << tmp.Trapeze() << endl;
    cout << "Simpson: " << tmp.Simpson(10) << endl;
    cout << "Richardson: " << tmp.Richardson() << endl;


    double true_mean = 1.2283696986087567;
    cout << "Rectangle error: " << (true_mean - tmp.Rectangle()) / true_mean << endl;
    cout << "Trapeze error: " << abs((true_mean - tmp.Trapeze()) / true_mean)<< endl;
    cout << "Simpson error: " << (true_mean - tmp.Simpson(10)) / true_mean << endl;
    cout << "Richardson error: " << (true_mean - tmp.Richardson()) / true_mean << endl;
}
