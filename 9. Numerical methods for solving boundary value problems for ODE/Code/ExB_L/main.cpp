#include <iostream>
using namespace std;

class Spline{
private:
    double *a, *b, *m, *D;
    double left_b, right_b, A{}, B{}, C{}, h;
    int size;
public:
    explicit Spline(int N){
        size = N;
        a = new double[size+1];
        b = new double[size+1];
        m = new double[size+1];
        D = new double[size];
        left_b = -1;
        right_b = 1;
        h = (right_b - left_b)/(size-1);
    }
    void CreateMatrix();
    void Reverse_stroke();
    void Forward_stroke();
    double Values(double x, int index);
    void Spline1();
    static double R(double t);
};
double Spline::R(double t){
    return  1.0 / (1.0 + 25.0 * t * t);
}
void Spline::CreateMatrix(){
    B =  1.0;
    C = 4.0;
    A =  1.0;
    D[0] = (-11*R(left_b) + 18*R(left_b + h) - 9*R(left_b + 2*h) + 2*R(left_b + 3*h))/h/6.0;
    for(int i = 1; i < size-1;i++){
        D[i] = 3*(R(left_b + h*(i+1))  - R(left_b + h*(i-1)))/h;
    }
    D[size-1] = (11*R(right_b) - 18*R(right_b - h) + 9*R(right_b - 2*h) - 2*R(right_b - 3*h))/h/6.0;
}
void Spline::Forward_stroke(){
    a[1] = 0;
    b[1] = R(-1);
    for (int i = 1; i < size - 1; i++) {
        a[i + 1] = -1 * B / (C + A * a[i]);
        b[i + 1] = (D[i] - A * b[i]) / (C + A * a[i]);
    }
}
void Spline::Reverse_stroke(){
    m[size-1] = R(1);
    for (int i = size-1; i > 0; i--) {
        m[i - 1] = a[i] * m[i] + b[i];
    }
}
double Spline::Values(double x, int index){
    double data_x[size+1];
    double data_y[size + 1];

    for (int i = 0; i <= size; i++){
        data_x[i] = left_b + h*i;
        data_y[i] = R(left_b + h*i);
    }
    double s1, s2, s3, s4;
    double xi = data_x[index];
    double xii = data_x[index + 1];
    s1 = (pow((xii - x), 2) * (2 * (x - xi) + h)) * data_y[index] / (h*h*h);
    s2 = (pow((x - xi), 2) * (2 * (xii - x) + h)) * data_y[index + 1] /  (h*h*h);
    s3 = pow((xii - x), 2) * (x - xi) * m[index] /  (h*h);
    s4 = pow((x - xi), 2) * (x - xii) * m[index + 1] /  (h*h);
    return s1 + s2 + s3 + s4;
}
void Spline::Spline1(){
    int M = 25;
    for(int i = 0; i <= size-2; i++){
        for(int j = 0; j <= M; j++){
            cout << "{" << left_b + i*h + j*h/M << ", " << Values(left_b + h * i + h / M * j, i) << "}, ";
        }
    }
}
int main(){
    Spline object(5);
    object.CreateMatrix();
    object.Forward_stroke();
    object.Reverse_stroke();
    object.Spline1();
    return 0;
}
