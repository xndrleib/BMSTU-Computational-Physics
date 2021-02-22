#include <iostream>
#include <math.h>
using namespace std;

class NDSolve{
private:
    double *a, *b, *x, *D;
    double left_b, right_b, cond1, cond2, A, B, C, p, q, h;
    int size;
public:
    NDSolve(double in1, double in2, double l, double r, double p1, double q1){
        size = 10;
        a = new double[size+1];
        b = new double[size+1];
        x = new double[size+1];
        D = new double[size];
        left_b = l;
        right_b = r;
        cond1 = in1;
        cond2 = in2;
        h = (right_b - left_b)/(size-1);
        p = p1;
        q = q1;
    }
    void CreateMatrix();
    void Reverse_stroke();
    void Forward_stroke();
    double Function(double t);
};

int main() {
    NDSolve object(2, exp(1) + exp(-2), 0, 1, 1, -2);
    object.CreateMatrix();
    object.Forward_stroke();
    object.Reverse_stroke();
    return 0;
}

double NDSolve::Function(double t){
    return 0;
}
void NDSolve::CreateMatrix(){
    B =  (0.5*p*h + 1);
    C = (-2 + q*h*h);
    A =  (-0.5*p*h + 1);
    for(int i = 0; i < size;i++){
        D[i] = h*h*Function(left_b + h*i);
    }
}
void NDSolve::Forward_stroke() {
    a[1] = 0;
    b[1] = cond1;
    for (int i = 1; i < size - 1; i++) {
        a[i + 1] = -1 * B / (C + A * a[i]);
        b[i + 1] = (D[i] - A * b[i]) / (C + A * a[i]);
    }
}
void NDSolve::Reverse_stroke() {
    x[size-1] = cond2;
    cout << "{{" << (size-1)*h << ", " << x[size-1] << "}";
    for (int i = size-1; i > 0; i--) {
        x[i - 1] = a[i] * x[i] + b[i];
        cout << ", {" << (i - 1)*h << ", " << x[i-1] << "}";
    }
}


