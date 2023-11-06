#include <functions/header.h>
#include <iostream>

int main() {
    Point<int> t(2, 1);
    std::cout << t << std::endl;
    broken_line<int> a(1, 3, 4);
    broken_line<int> b(2, 4, 5);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    broken_line<int> c = a + b;
    c.push_point(t);
    std::cout << c << std::endl;
    auto len_line = c.lenght();
    std::cout << len_line << std::endl;
    broken_line<int> pol;
    pol.make_polygon(6, 5);
}
