#include <iostream>
#include <random>
#include <cmath>
#include <fstream>

using namespace std;

double PhAbsorbtion(double x);
double IncohScattering(double x);
double DiffCrossection(double a1, double mu);
double IntCrossection(double a1);

const double a = 40, b = 5; // geometric parameters of the source
const double R = 30, H = 20; // geometric parameters of the surface
const int N = 10000, M = 1000;
const double Rho = 2.69; // Value of the density (Al)
const double relatConst = 391.4*5.11*0.0001;

int main()
{
    //double r_arr1[4] = {{30, 0, 0}, {30, 0, 10}, {30, 0, 10}, {30, 0, 10}};
    //double r_arr2[4] = {{30, 0, 0}, {30, 0, 10}, {30, 0, 10}, {30, 0, 10}};
    //double r_arr3[4] = {{30, 0, 0}, {30, 0, 10}, {30, 0, 10}, {30, 0, 10}};
    //double r_arr4[4] = {{30, 0, 0}, {30, 0, 10}, {30, 0, 10}, {30, 0, 10}};

    mt19937 gen{random_device()()};
    uniform_real_distribution <double> dist(0.0, 1.0);


    double r[20][3] = {{30, 0, 0}, {30, 0, 20.0/3.0}, {30, 0, 40.0/3.0}, {30, 0, 20},
                       {20, 0, 20}, {10, 0, 20}, {0, 0, 20}, {-10, 0, 20}, {-20, 0, 20}, {-30, 0, 20},
                       {0, 30, 20}, {0, 20, 20}, {0, 10, 20}, {0, -10, 20}, {0, -20, 20}, {0, -30, 20},
                       {0, 0, 20}, {0, 0, 40.0/3.0}, {0, 0, 20.0/3.0}, {0, 0, 0}};

    fstream fs1,fs2,fs3,fs4,fs5,fs6,fs7,fs8,fs9,fs10,fs11,fs12,fs13,fs14,fs15,fs16,fs17,fs18,fs19,fs20, p;
    fs1.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_1.txt", fstream::in | fstream::out | fstream::trunc);
    fs2.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_2.txt", fstream::in | fstream::out | fstream::trunc);
    fs3.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_3.txt", fstream::in | fstream::out | fstream::trunc);
    fs4.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_4.txt", fstream::in | fstream::out | fstream::trunc);
    fs5.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_5.txt", fstream::in | fstream::out | fstream::trunc);
    fs6.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_6.txt", fstream::in | fstream::out | fstream::trunc);
    fs7.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_7.txt", fstream::in | fstream::out | fstream::trunc);
    fs8.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_8.txt", fstream::in | fstream::out | fstream::trunc);
    fs9.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_9.txt", fstream::in | fstream::out | fstream::trunc);
    fs10.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_10.txt", fstream::in | fstream::out | fstream::trunc);
    fs11.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_11.txt", fstream::in | fstream::out | fstream::trunc);
    fs12.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_12.txt", fstream::in | fstream::out | fstream::trunc);
    fs13.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_13.txt", fstream::in | fstream::out | fstream::trunc);
    fs14.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_14.txt", fstream::in | fstream::out | fstream::trunc);
    fs15.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_15.txt", fstream::in | fstream::out | fstream::trunc);
    fs16.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_16.txt", fstream::in | fstream::out | fstream::trunc);
    fs17.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_17.txt", fstream::in | fstream::out | fstream::trunc);
    fs18.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_18.txt", fstream::in | fstream::out | fstream::trunc);
    fs19.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_19.txt", fstream::in | fstream::out | fstream::trunc);
    fs20.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\alpha_20.txt", fstream::in | fstream::out | fstream::trunc);
    p.open ("C:\\Users\\akhiz\\Google Drive\\Университет\\8 Семестр\\Вычислительная физика\\HW1\\Results\\points.txt", fstream::in | fstream::out | fstream::trunc);

    double flux2[20];

    struct quantum
    {
        double **coord = new double* [M]; // coordinates
        double **ang = new double* [M]; // direction
        double *energy = new double [M]; // energies
        double *length = new double [M]; // free path length
    } AllQ[N] = {};

    double SigmaP, SigmaC, Sigma, P1;
    double psi, mu, X, Y, Z, x0, x1, x3;
    double gamma, gamma1, gamma2;
    double alpha, distance2, weight;
    double om[6] = {}; //body angles

    SigmaC = IncohScattering(2.5); // Compton scattering
    SigmaP = PhAbsorbtion(2.5); // Photoelectric absorption
    Sigma = SigmaC + SigmaP; // interaction cross section for quanta with energy 2.5 MeV in AL
    P1 = SigmaC / Sigma;

    // Initial coordinates, initial directions of quanta and free path length
    for (auto & i : AllQ){
        for (int j = 0; j < M; j++){
            i.coord[j] = new double [3];
            i.ang[j] = new double [4];
        }
    }

    // Further trajectory of movement of the quanta
    int num = 0;

    for (auto & i : AllQ){
        i.coord[0][0] = a * (dist(gen) - 1. / 2);
        i.coord[0][1] = b * (dist(gen) - 1. / 2);
        i.coord[0][2] = 0;
        i.length[0] = -log(dist(gen)) / (Sigma * Rho);
        //0
        x0 = M_PI * dist(gen); // theta
        x1 = 2 * M_PI * dist(gen); // psi
        i.ang[0][0] = cos(x0); // cos(theta)
        i.ang[0][1] = sin(x0); // sin(theta)
        i.ang[0][2] = cos(x1); // cos(psi)
        i.ang[0][3] = sin(x1); // sin(psi)

        weight = 1; //each particle starts with the weight = 1

        i.energy[0] = 2.5; //initial energy
        i.energy[1] = 2.5;



        X = i.coord[0][0] + i.length[0] * i.ang[0][1] * i.ang[0][2]; //coordinates of the first move
        Y = i.coord[0][1] + i.length[0] * i.ang[0][1] * i.ang[0][3];
        Z = i.coord[0][2] + i.length[0] * i.ang[0][0];

        om[3] = i.ang[0][1] * i.ang[0][2];
        om[4] = i.ang[0][1] * i.ang[0][3];
        om[5] = i.ang[0][0];

        if (X * X + Y * Y <= R * R && Z >= 0 && Z <= H){ //if the particle is still inside after the first move
            i.coord[1][0] = X;
            i.coord[1][1] = Y;
            i.coord[1][2] = Z;
            p << i.coord[0][0] << " " << i.coord[0][1] << " " << i.coord[0][2];
            p << " " << X << " " << Y << " " << Z << endl;

            int ident = 0, j = 1; //"ident" is for immediate exit if necessary; j - number of moves

            while (ident == 0) {
                gamma = dist(gen);
                ident = 1;

                if (gamma < P1) // Compton scattreing
                {

                    alpha = i.energy[j] / relatConst; //alpha, which is from the formula
                    gamma1 = dist(gen);
                    gamma2 = dist(gen);
                    x3 = alpha * (1 + 2 * alpha * gamma1) / (1 + 2 * alpha); //x, which is from the formula
                    //algorithm of the exception method
                    while (gamma2 * (1 + 2 * alpha + 1 / (1 + 2 * alpha)) / (x3 / alpha + alpha / x3 + (1 / alpha - 1 / x3) * (2 + 1 / alpha - 1 / x3)) >= 1)
                    {
                        gamma1 = dist(gen);
                        gamma2 = dist(gen);
                        x3 = alpha * (1 + 2 * alpha * gamma1) / (1 + 2 * alpha);
                    }
                    i.energy[j + 1] = x3 * relatConst; //new energy after scattering

                    mu = 1 - 1 / (i.energy[j + 1] / relatConst) + 1 / (i.energy[j] / relatConst); //angle after scattering
                    psi = 2 * M_PI * dist(gen);

                    om[0] = om[3]; //old coordinates
                    om[1] = om[4]; //old coordinates
                    om[2] = om[5]; //old coordinates

                    om[5] = om[2] * mu + pow((1 - mu * mu) * (1 - om[2] * om[2]), 0.5) * cos(psi); //new coordinates
                    om[4] = (om[1] * (mu - om[2] * om[5]) + om[0] * sin(psi) * pow((1 - mu * mu) * (1 - om[2] * om[2]), 0.5)) / (1 - om[2] * om[2]); //new coordinates
                    om[3] = (om[0] * (mu - om[2] * om[5]) - om[1] * sin(psi) * pow((1 - mu * mu) * (1 - om[2] * om[2]), 0.5)) / (1 - om[2] * om[2]); //new coordinates

                    SigmaC = IncohScattering(i.energy[j + 1]); //Sigma Scattering  and Photo Absobtion
                    SigmaP = PhAbsorbtion(i.energy[j + 1]);
                    Sigma = SigmaC + SigmaP;
                    P1 = SigmaC / Sigma;

                    i.length[j + 1] = -log(dist(gen)) / (Sigma * Rho); // length
                    X = i.coord[j][0] + i.length[j + 1] * om[3]; //new coordinates in сartesian coord system
                    Y = i.coord[j][1] + i.length[j + 1] * om[4]; //new coordinates in сartesian coord system
                    Z = i.coord[j][2] + i.length[j + 1] * om[5]; //new coordinates in сartesian coord system

                    if (X * X + Y * Y <= R * R && Z >= 0 && Z <= H) //if new coordinates are still inside
                    {
                        i.coord[j + 1][0] = X;
                        i.coord[j + 1][1] = Y;
                        i.coord[j + 1][2] = Z;
                        weight = weight * P1;
                        if (weight > pow(10, -11)){
                            ident = 0; //weight < 10**(-11)
                            num ++;
                        }

                        for(int q = 0; q < 20; q++){

                            double rad[3] = {r[q][0], r[q][1], r[q][2]};
                            distance2 = pow(pow(i.coord[j + 1][0] - rad[0], 2) + pow(i.coord[j + 1][1] - rad[1], 2) + pow(i.coord[j + 1][2] - rad[2], 2), 0.5);
                            if (distance2 < 3) distance2 = 3;
                            flux2[q] = weight * exp(-Sigma * distance2) * DiffCrossection(alpha, mu) / IntCrossection(alpha) /
                                           distance2 / distance2;

                        }
                        fs1 << i.energy[j + 1] << " " << flux2[0] << endl;
                        fs2 << i.energy[j + 1] << " " << flux2[1] << endl;
                        fs3 << i.energy[j + 1] << " " << flux2[2] << endl;
                        fs4 << i.energy[j + 1] << " " << flux2[3] << endl;
                        fs5 << i.energy[j + 1] << " " << flux2[4] << endl;
                        fs6 << i.energy[j + 1] << " " << flux2[5] << endl;
                        fs7 << i.energy[j + 1] << " " << flux2[6] << endl;
                        fs8 << i.energy[j + 1] << " " << flux2[7] << endl;
                        fs9 << i.energy[j + 1] << " " << flux2[8] << endl;
                        fs10 << i.energy[j + 1] << " " << flux2[9] << endl;
                        fs11 << i.energy[j + 1] << " " << flux2[10] << endl;
                        fs12 << i.energy[j + 1] << " " << flux2[11] << endl;
                        fs13 << i.energy[j + 1] << " " << flux2[12] << endl;
                        fs14 << i.energy[j + 1] << " " << flux2[13] << endl;
                        fs15 << i.energy[j + 1] << " " << flux2[14] << endl;
                        fs16 << i.energy[j + 1] << " " << flux2[15] << endl;
                        fs17 << i.energy[j + 1] << " " << flux2[16] << endl;
                        fs18 << i.energy[j + 1] << " " << flux2[17] << endl;
                        fs19 << i.energy[j + 1] << " " << flux2[18] << endl;
                        fs20 << i.energy[j + 1] << " " << flux2[19] << endl;

                    }
                }
                else{num ++;}
                j++;
            }
        }
    }

    fs1.close();
    fs2.close();
    fs3.close();
    fs4.close();
    fs5.close();
    fs6.close();
    fs7.close();
    fs8.close();
    fs9.close();
    fs10.close();
    fs11.close();
    fs12.close();
    fs13.close();
    fs14.close();
    fs15.close();
    fs16.close();
    fs17.close();
    fs18.close();
    fs19.close();
    fs20.close();
    p.close();

    cout << "Process has finished";
    return 0;
}
double PhAbsorbtion(double x){
    if (x < 0.1) x = 0.1;
    return 0.0017*pow(x + 0.8034, -23.1353);
}
double IncohScattering(double x){
    if (x < 0.1) x = 0.1;
    return -3.5342 - 0.0822*pow(x, -0.5955) + 0.2387*pow(x, -0.3955) + 3.439*pow(x, 0.0045);
}
double DiffCrossection(double a1, double m){
    double m1 = 1 - m;
    double m_c = 1 + a1*m1;
    return 0.5/m_c/m_c * (1 + m * m + a1 * a1 * m1 * m1/m_c);
}
double IntCrossection(double a1){
    double t1 = 1 + a1;
    double t2 = 1 + 2*a1;
    double t_log = log(t2)/a1;
    return 2 * (t1/a1/a1 * (2 * t1/t2 - t_log) + t_log/2 - (1 + 3 * a1)/t2/t2);
}