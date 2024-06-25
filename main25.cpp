// TP 2022/2023: LV 5, Zadatak 2
#include <cmath>
#include <iostream>

template <typename tip1, typename tip2> 
tip2 RazmijeniBlokove(tip1 p1, tip1 p2, tip2 p3) {
  while (p1!=p2) {
   auto pom=*p1;
   *p1=*p3;
   *p3=pom;
   p1++;
   p3++;
  }
  return p3;
}

int main() {

    int a[]{2, 2, 2, 2, 2}, b[]{3, 3, 3, 3, 3};
    RazmijeniBlokove(std::begin(a), std::end(a), std::begin(b));
    std::cout << "Prvi niz: ";
    for(int x : a) std::cout << x << " ";
    std::cout << "\nDrugi niz: ";
    for(int x : b) std::cout << x << " ";

    std::cout<<std::endl;

    std::string s1("sehur"), s2("iftar");
    RazmijeniBlokove(s1.begin(), s1.end(), s2.begin());
    std::cout << "Prvi string: " << s1 << std::endl;
    std::cout << "Drugi string: " << s2 << std::endl;

  return 0;
}
