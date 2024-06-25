// TP 2022/2023: LV 4, Zadatak 1
#include <cmath>
#include <iostream>
#include <limits>

int Cifre(long long int n, int &c_min, int &c_max) {
  c_min = 9;
  c_max = 0;
  int cifra = 0;
  int brojac = 0;
  for (;;) {
    brojac++;
    cifra = n % 10;
    if(cifra<0) cifra*=(-1);
    if (cifra <= c_min)
      c_min = cifra;
    if (cifra >= c_max)
      c_max = cifra;
    n /= 10;
    if (n == 0)
      break;
  }

  return brojac;
}

int main() {

  long long int n;
  int a, b;
  std::cout << "Unesite broj: ";
  std::cin >> n;
  std::cout << "Broj " <<n<< " ima "<<Cifre(n, a, b)<<" cifara, najveca je "<<b<<" a najmanja "<<a<<".";

  return 0;
}
