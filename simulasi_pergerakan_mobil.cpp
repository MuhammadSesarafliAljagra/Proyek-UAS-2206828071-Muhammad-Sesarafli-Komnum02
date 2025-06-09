// Simulasi Pergerakan Mobil dalam Jalur Variabel
// Menerapkan Runge-Kutta, Polynomial Regression, dan Trapezoidal Rule
// Nama: Muhammad Sesarafli Aljagra
// NPM: 2206828071

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream> // untuk save CSV
#include <cstdlib> // untuk system()

using namespace std;

// -------------------- Parameter Simulasi --------------------

// Fungsi ODE: dv/dt = 2 * sin(t) + 0.1 * v(t)
double acceleration(double t, double v)
{
    return 2 * sin(t) + 0.1 * v;
}

// Runge-Kutta 4th Order untuk v(t)
void rungeKutta(vector<double> &t_vals, vector<double> &v_vals, double v0, double t0, double tf, double h)
{
    double t = t0;
    double v = v0;

    while (t <= tf)
    {
        t_vals.push_back(t);
        v_vals.push_back(v);

        double k1 = h * acceleration(t, v);
        double k2 = h * acceleration(t + 0.5 * h, v + 0.5 * k1);
        double k3 = h * acceleration(t + 0.5 * h, v + 0.5 * k2);
        double k4 = h * acceleration(t + h, v + k3);

        v = v + (1.0 / 6.0) * (k1 + 2 * k2 + 2 * k3 + k4);
        t += h;
    }
}

// Polynomial Regression (Degree 2)
void polynomialRegression(const vector<double> &t_vals, const vector<double> &v_vals, double coeffs[3])
{
    int n = t_vals.size();
    double sum_t = 0, sum_t2 = 0, sum_t3 = 0, sum_t4 = 0;
    double sum_v = 0, sum_tv = 0, sum_t2v = 0;

    for (int i = 0; i < n; i++)
    {
        double t = t_vals[i];
        double v = v_vals[i];
        sum_t += t;
        sum_t2 += t * t;
        sum_t3 += pow(t, 3);
        sum_t4 += pow(t, 4);
        sum_v += v;
        sum_tv += t * v;
        sum_t2v += t * t * v;
    }

    // Matriks normal equation
    double A[3][4] = {
        {double(n), sum_t, sum_t2, sum_v},
        {sum_t, sum_t2, sum_t3, sum_tv},
        {sum_t2, sum_t3, sum_t4, sum_t2v}};

    // Eliminasi Gauss sederhana
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            double ratio = A[j][i] / A[i][i];
            for (int k = 0; k < 4; k++)
            {
                A[j][k] -= ratio * A[i][k];
            }
        }
    }

    // Back substitution
    for (int i = 2; i >= 0; i--)
    {
        coeffs[i] = A[i][3];
        for (int j = i + 1; j < 3; j++)
        {
            coeffs[i] -= A[i][j] * coeffs[j];
        }
        coeffs[i] /= A[i][i];
    }
}

// Trapezoidal Rule untuk integral kecepatan → jarak tempuh
double trapezoidalIntegration(const vector<double> &t_vals, const vector<double> &v_vals)
{
    int n = t_vals.size();
    double integral = 0.0;

    for (int i = 0; i < n - 1; i++)
    {
        double dt = t_vals[i + 1] - t_vals[i];
        integral += 0.5 * dt * (v_vals[i] + v_vals[i + 1]);
    }

    return integral;
}

// -------------------- Main Program --------------------
int main()
{
    vector<double> t_vals, v_vals;

    // Parameter awal
    double v0 = 0.0;  // initial velocity
    double t0 = 0.0;  // initial time
    double tf = 10.0; // final time (bisa diganti sesuai keperluan)
    double h = 0.1;   // step size

    cout << "============================================\n";
    cout << " Simulasi Pergerakan Mobil dalam Jalur Variabel\n";
    cout << " Metode: Runge-Kutta 4, Polynomial Regression, Trapezoidal Rule\n";
    cout << "============================================\n";

    // Step 1: Simulasi ODE dengan Runge-Kutta
    rungeKutta(t_vals, v_vals, v0, t0, tf, h);
    cout << "Runge-Kutta selesai, total data: " << t_vals.size() << " titik.\n";

    // Step 2: Polynomial Regression (degree 2)
    double coeffs[3];
    polynomialRegression(t_vals, v_vals, coeffs);
    cout << "\nHasil Polynomial Regression (v_fit(t)):\n";
    cout << "v_fit(t) = " << coeffs[0] << " + " << coeffs[1] << "*t + " << coeffs[2] << "*t^2\n";

    // Step 3: Trapezoidal Rule → Hitung total jarak tempuh
    double total_distance = trapezoidalIntegration(t_vals, v_vals);
    cout << "\nEstimasi jarak tempuh total (integrasi Trapezoidal): " << total_distance << " m\n";

    // Optional: simpan data ke CSV (bisa untuk plot)
    ofstream fout("data_simulasi.csv");
    fout << "t,v\n";
    for (size_t i = 0; i < t_vals.size(); i++)
    {
        fout << t_vals[i] << "," << v_vals[i] << "\n";
    }
    fout.close();
    cout << "Data simulasi disimpan ke data_simulasi.csv\n";

    // Plot pakai gnuplot
    cout << "Menampilkan plot dengan gnuplot...\n";
    system("gnuplot -p -e \"set datafile separator ','; set title 'Kecepatan Mobil vs Waktu'; set xlabel 'Waktu (s)'; set ylabel 'Kecepatan (m/s)'; plot 'data_simulasi.csv' using 1:2 with lines lw 2 lc rgb 'blue' title 'v(t)'\"");

    cout << "\nProgram selesai.\n";
    return 0;
}