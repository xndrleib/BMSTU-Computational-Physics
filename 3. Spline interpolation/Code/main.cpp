#include <iostream>
#include <math.h>
using namespace std;



class Spline3{
private:
    double* data_x;
    double* data_y;
    double* data_m;
    double* data_m2;
    unsigned size;
    double h;
    double left_bound, right_bound;
public:
    Spline3(double* d1, double* d2, unsigned s, double l, double r){
        size = s;
        data_x = new double[size];
        data_y = new double[size];
        data_m = new double[size];
        data_m2 = new double[size];
        left_bound = l;
        right_bound = r;
        
        double h = (right_bound - left_bound)/(double)((size) - 1);
        for(unsigned i = 0; i < s; i++)
            data_x[i]=d1[i];
        for(unsigned i = 0; i < s; i++)
            data_y[i]= d2[i];
        data_m[0] = (-3*data_y[0] + 4*data_y[1] - data_y[2])/(2*h);
        data_m[size - 1] = (3*data_y[size - 1] - 4*data_y[size - 2] + data_y[size - 3])/(2*h);
        for (int i = 0;i <= size - 1;i++)
            data_m2[i] = Diff_Runge(left_bound  + h * i);
        for (int i = 1;i <= size - 2;i++)
            data_m[i] = (data_y[i + 1] - data_y[i - 1]) / (2 * h);
}
    double VariantA(double x, int index);
    double VariantB(double x, int index);
    void Spline();
    double Diff_Runge(double t);
};


double Spline3::Diff_Runge(double t){return -(50.0 * t )/ pow((1.0 + 25.0 * pow(t, 2)), 2);}


double Spline3::VariantA(double x, int index){
    double h = (right_bound - left_bound)/(double)((size) - 1);
    double s1, s2, s3, s4;
    double xi = data_x[index];
    double xii = data_x[index + 1];
    s1 = (pow((xii - x), 2) * (2 * (x - xi) + h)) * data_y[index] / (double)pow(h, 3);
    s2 = (pow((x - xi), 2) * (2 * (xii - x) + h)) * data_y[index + 1] / (double)pow(h, 3);
    s3 = pow((xii - x), 2) * (x - xi) * data_m[index] / (double)pow(h, 2);
    s4 = pow((x - xi), 2) * (x - xii) * data_m[index + 1] / (double)pow(h, 2);
    return s1 + s2 + s3 + s4;
}


double Spline3::VariantB(double x, int index){
    double h = (right_bound - left_bound)/(double)((size) - 1);
    double s1, s2, s3, s4;
    double xi = data_x[index];
    double xii = data_x[index + 1];
    s1 = (pow((xii - x), 2) * (2 * (x - xi) + h)) * data_y[index] / (double)pow(h, 3);
    s2 = (pow((x - xi), 2) * (2 * (xii - x) + h)) * data_y[index + 1] / (double)pow(h, 3);
    s3 = pow((xii - x), 2) * (x - xi) * data_m2[index] / (double)pow(h, 2);
    s4 = pow((x - xi), 2) * (x - xii) * data_m2[index + 1] / (double)pow(h, 2);
    return s1 + s2 + s3 + s4;
}

void Spline3::Spline(){
    cout << "Qubic Spline: "  << endl;
    double h = (right_bound - left_bound)/(double)((size) - 1);
    cout << "Varriant A: "  << endl;
    for(int i = 0; i <= size - 2; i++){
        for(int j = 0; j <= 15; j++){
            cout << VariantA(left_bound + h * i + h / 15.0 * j, i) << ", ";
        }
    }
    cout << endl;
    cout << "Variant B: "  << endl;
    for(int i = 0; i <= size - 2; i++){
        for(int j = 0; j <= 15; j++){
            cout << VariantB(left_bound + h * i + h / 15.0 * j, i) << ", ";
        }
    }

    delete data_x;
    delete data_y;
    delete data_m;
    delete data_m2;

}


double Runge_Function(double t){return 1.0 / (1.0 + 25.0 * pow(t, 2));}

int main() {
    int n = 5;
    double left_bound = -1, right_bound = 1, dat_x[n], dat_y[n];
    for (int i = 0; i < n + 1; i++){
        dat_x[i] = left_bound + (double)i * (double)(right_bound - left_bound) / (double)(n);
        dat_y[i] = Runge_Function(dat_x[i]);
    };
    Spline3 spline(dat_x, dat_y, n + 1, left_bound, right_bound);
    spline.Spline();


    return 0;
}
