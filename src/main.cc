#include <functions/header.h>
#include <iostream>
#include <complex>

int main() {
    Point<int> t(2, 1);
    Point<double> t1(2, 1);
    std::cout << t << std::endl;
    double f1 = 4;
    double f2 = 7;
    double f3 = 1;
    double f4 = 5;
    broken_line<double> a(f1, f2, 4);
    broken_line<double> b(f3, f4, 5);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    broken_line<double> c = a + b;
    c.push_point(t1);
    std::cout << c << std::endl;
    auto len_line = c.length();
    std::cout << len_line << std::endl;
    broken_line<double> pol;
    pol.make_polygon(6, 5);
     С комплексными числами:
    std::complex <double> c(4, 2);
    std::complex <double> v(1, 8);
    std::complex <double> y(3, 1);
    std::complex <double> u(5, 6);
    Point<std::complex <double>> k(y, u);
    Point<std::complex <double>> j(c, v);
    broken_line< std::complex <double>> d(c, v, 5);
    broken_line< std::complex <double>> q(y, u, 7);
    std::cout << d << std::endl;
    broken_line< std::complex <double>> m = d + q;
    std::cout << m << std::endl;
    auto len_line = d.length_complex();
    std::cout << len_line << std::endl;
    broken_line<std::complex <double>> pol;
    pol.make_polygon(6, 5);
}
