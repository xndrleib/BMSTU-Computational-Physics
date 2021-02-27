#include <iostream>
#include <cmath>
#include <fstream>
#include <random>

using std::cout; using std::endl; using std::ofstream; using std::ios;

const double tga = 0.3, h1 = 10, h2 = 5, r1 = 5, r2 = 2, degtorad = 2 * M_PI / 360;
const double N = 10;

void step(double& h, double& r, double& phi, double& theta, double& psi);
void step2(double& h, double& r, double& phi, double& theta, double& psi);

int main() {

    std::mt19937 gen{std::random_device()()};
    std::uniform_real_distribution <double> dist(0.0, 1.0);


    double h; // высота
    double phi; // аксиальный угол
    double theta; // азимутальный угол
    double psi;
    // double theta_last = 0;
    // double h_last = 0;
    double r, R; // радиусы

    // розыгрыш точки рождения и направления
    // for (int i = 0; i < N; i++) {
    h = (h1) * dist(gen);
    phi = 2 * M_PI * dist(gen);
    psi = M_PI * dist(gen);


    ofstream out;
    out.open("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\Курсовая работа\\Визуализация\\data_1.txt");
    out.setf(ios::fixed);
        do {

            out << (r1/tga - h) * tga << "\t" << h << "\t" << phi << endl;
            cout << (r1/tga - h) * tga << "\t" << h << "\t" << phi << endl;
            if (h < h1){
                r = (r1/tga - h) * tga;
                theta = atan(tga) * dist(gen);
                while(h < h1){
                    cout << "con " << h << ", " << theta  << "," << psi << endl;
                    // h_last = h;
                    // theta_last = theta;
                    step(h, r, phi, theta, psi);
                    out << r << "\t" << h << "\t" << phi << endl;
                }
            }
            else if (h < h1 + h2){
                r = r2;
                theta = M_PI/2 * dist(gen);
                while(h < h1 + h2){
                    cout << "cyl " << h << ", " << theta  << "," << psi << endl;
                    // h_last = h;
                    // theta_last = theta;
                    step2(h, r, phi, theta, psi);
                    out << r << "\t" << h << "\t" << phi << endl;
                }
            }
            else{
                return 0;
            }
        } while (h < h1 + h2);

    return 0;
}
void step(double& h, double& r, double& phi, double& theta, double& psi) {
    double eta = M_PI/2 - psi, h3 = h1 - h;
    double l = r*sin(M_PI -2*eta)/sin(eta);
    double beta = acos(cos(M_PI/2 - atan(tga))*cos(M_PI/2 - psi));
    double theta2 = M_PI - theta - beta;

    phi += 2 * psi - 2 * M_PI * ((phi + 2 * psi) >= 2 * M_PI);

    double L = l * sin(theta) / sin(theta2), H = r1/tga - h;
    double hr = H * r;
    h += ((hr*r) + sqrt(H*H*H*H*L*L - H*H*hr*hr + hr*hr*L*L))/(H*H + r*r);
    r = (r1/tga - h) * tga;
    theta = M_PI/2 - theta2;

    if (h > h1) {
        double nu = acos(h / (l * sin(beta) / sin(theta2)));
        double dh = (h - h3) * cos(atan(tga)) * sin(M_PI - theta2) / sin(nu) - (h - h3);
        h += dh;
        theta = M_PI/2 - nu;
    }
}

void step2(double& h, double& r, double& phi, double& theta, double& psi) {
    double l = 2 * r * cos(M_PI / 2 - psi + M_PI/2 * (psi > M_PI/2));
    phi += 2 * psi - 2 * M_PI * ((phi + 2 * psi) >= 2 * M_PI);
    h += l * tan(theta);
}