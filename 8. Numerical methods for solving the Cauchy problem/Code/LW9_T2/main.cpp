#include <iostream>
#include <cmath>
using namespace std;

int fact(int n);

class Integrate{
private:
    int i_val, k_val, scenario;
    double left_bound, right_bound;
public:
    Integrate(int p1, int p2, int t, double l, double r){
        k_val = p1;
        i_val = p2;
        scenario = t;
        left_bound = l;
        right_bound = r;
    }
    double Simpson(double n2);
    double Richardson();
    double Function(double t);
    double Function1(double t);
    double Function2(double t);
};
int main() {
    for(int k = 0; k <= 7; k++){
        for(auto i = 0; i <= k; i++) {
            Integrate tmp(k, i, 1, 0.0, 1);
            cout << "{" <<  k << ", " << i << ", " << (pow(-1, i)/(1.0*fact(i)*fact(k - i))) * tmp.Richardson() << "}, ";
        }
        cout << endl;
    }
    for(int k = 0; k <= 7; k++){
        for(auto i = 0; i <= k; i++) {
            Integrate tmp(k, i, 2, 0.0, 1);
            cout << "{" <<  k << ", " << i << ", " << (pow(-1, i)/(1.0*fact(i)*fact(k - i))) * tmp.Richardson() << "}, ";
        }
        cout << endl;
    }
    for(int k = 0; k <= 7; k++){
        Integrate tmp(k, 1, 3, 0.0, 1.0);
        cout << "{" <<  k  << ", " << (1/(fact(k)*1.0)) * tmp.Richardson() << "}, " << endl;
    }
    for(int k = 0; k <= 7; k++){
        Integrate tmp(k, 1, 4, 0.0, 1.0);
        cout << "{" <<  k  << ", " << (1/(fact(k)*1.0)) * tmp.Richardson() << "}, " << endl;
    }
    return 0;
}
int fact(int n) {
    if ((n==0)||(n==1)){return 1;}
    else {return n*fact(n-1);}
}
double Integrate::Function(double x){
    return Function1(x) * ((scenario == 1) or (scenario == 2)) + Function2(x) * ((scenario == 3) or (scenario == 4));
}
double Integrate::Function1(double x){
    double answ = 1;
    if ((x + i_val - 1 * (scenario == 2)) == 0.0)
        return 1;
    else
        for(int t = 0; t <= k_val; t++){answ *= (x + t - 1 * (scenario == 2));};
    return answ/(x + i_val - 1 * (scenario == 2));
}
double Integrate::Function2(double x){
    double answ = 1;
    for(int t = 0; t <= k_val - 1; t++){answ *= (x + t - 1 * (scenario == 4));};
    return answ;
}
double Integrate::Simpson(double n2){
    int n1 = n2 * 2;
    double data_x[n1 + 1], I = 0;
    for (int i = 0; i < n1 + 1; i++){
        data_x[i] = left_bound + i * (right_bound - left_bound) / (double)(n1);
    };
    double h = (data_x[1] - data_x[0]) * 1.0;
    for (int i = 0; i < n1 / 2; i++){
        I += Function(data_x[2*i]) + 4 * Function(data_x[2*i + 1]) + Function(data_x[2*i + 2]);
    };
    return I * h / 3.0;
}
double Integrate::Richardson(){
    double r1 = Simpson(1000);
    double r2 = Simpson(1500);
    double r3 = Simpson(2000);
    int p = log2((r3 - r2) / (r2 - r1));
    return 1.0*((2 ^ p)*r1 - r2) / ((2 ^ p) - 1);
}
