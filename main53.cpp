//TP 2022/2023: LV 8, Zadatak 5
#include <iostream>
#include <tuple>
#include <cmath>

typedef std::tuple<double,double,double> Vektor3d;


void UnesiVektor(Vektor3d &v) {
 std::cout << "X = "; std::cin >> std::get<0>(v);
 std::cout << "Y = "; std::cin >> std::get<1>(v);
 std::cout << "Z = "; std::cin >> std::get<2>(v);
}
Vektor3d ZbirVektora(const Vektor3d &v1, const Vektor3d &v2) {
    double x1,y1,z1,x2,y2,z2;
    std::tie(x1,y1,z1)=v1;
    std::tie(x2,y2,z2)=v2;
 return {x1+x2,y1+y2,z1+z2};
}
Vektor3d VektorskiProizvod(const Vektor3d &v1, const Vektor3d &v2) {
    double x1,y1,z1,x2,y2,z2;
    std::tie(x1,y1,z1)=v1;
    std::tie(x2,y2,z2)=v2;
 return {y1*z2-z1*y2,z1*x2-x1*z2,x1*y2-y1*x2};
}
void IspisiVektor(const Vektor3d &v) {
 std::cout << "{" << std::get<0>(v) << "," << std::get<1>(v) << "," << std::get<2>(v) << "}";
}
int main() {
 Vektor3d a, b;
 std::cout << "Unesi prvi vektor:\n";
 UnesiVektor(a);
 std::cout << "Unesi drugi vektor:\n";
 UnesiVektor(b);
 std::cout << "Suma ova dva vektora je: ";
 IspisiVektor(ZbirVektora(a, b));
 std::cout << std::endl << "Njihov vektorski prozivod je: ";
 IspisiVektor(VektorskiProizvod(a, b));
 return 0;
}