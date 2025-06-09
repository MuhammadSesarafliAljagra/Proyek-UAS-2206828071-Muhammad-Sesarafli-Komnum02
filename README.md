# Simulasi Pergerakan Mobil dalam Jalur Variabel
## Metode Numerik: Runge-Kutta, Polynomial Regression, dan Trapezoidal Rule

### Nama: Muhammad Sesarafli Aljagra  
### NPM: 2206828071

### Komputasi Numerik - 02

---

## Deskripsi

Studi kasus yang diambil adalah **simulasi pergerakan mobil** pada jalur variabel, dimana kecepatan mobil dipengaruhi oleh model percepatan nonlinier sebagai berikut:

$\frac{dv}{dt} = 2 \cdot \sin(t) + 0.1 \cdot v(t)$

Program ini menerapkan **tiga metode numerik** sesuai dengan buku *Numerical Methods for Engineers* (Chapman):

- **Part 7:** Runge-Kutta Orde 4 → untuk menyelesaikan ODE dan mendapatkan *v(t)*.
- **Part 6:** Trapezoidal Rule → untuk menghitung integral *v(t)* → total jarak tempuh.
- **Part 5:** Polynomial Regression → untuk melakukan *curve fitting* terhadap data kecepatan *v(t)*.

---

## Cara Penggunaan

1. Pastikan compiler **g++** sudah tersedia.
2. Pastikan **gnuplot** terinstall di sistem.
3. Compile program:

    ```bash
    g++ -o simulasi_pergerakan_mobil simulasi_pergerakan_mobil.cpp
    ```
4. Jalankan program:

    ```bash
    ./simulasi_pergerakan_mobil
    ```
5. Program akan menampilkan:

    - Hasil simulasi Runge-Kutta

    - Persamaan Polynomial Regression

    - Estimasi jarak tempuh total

    - Visualisasi plot otomatis menggunakan gnuplot

## Struktur Program
- Runge-Kutta 4th Order untuk solusi ODE dv/dt.

- Polynomial Regression untuk fitting v(t) → v_fit(t).

- Trapezoidal Rule untuk menghitung total jarak tempuh.

- gnuplot sebagai visualisasi grafik v(t) vs waktu.

## Referensi
- Steven C. Chapra & Raymond P. Canale, Numerical Methods for Engineers, 7th Edition.
- J. C. Butcher, Numerical Methods for Ordinary Differential Equations, 2nd ed., Wiley, 2008.
- R. L. Burden and J. D. Faires, Numerical Analysis, 9th ed., Brooks/Cole Cengage Learning, 2011.
- D. C. Montgomery, E. A. Peck, and G. G. Vining, Introduction to Linear Regression Analysis, 5th ed., Wiley, 2012.



## Link Video Demonstrasi Youtube
[Klik untuk Menonton Vidio](https://youtu.be/7ehESKATO-4)

