#include <cmath>
#include <iostream>
#include <ctime>

bool DaLiJeProst(int n) {
  if (n == 1)
    return false;
  for (int i = 2; i <= std::sqrt(n); i++) {
    if (n % i == 0)
      return false;
  }
  return true;
}

void Goldbach(int n, int &p, int &q) {
  if (n % 2 != 0 || n <= 2)
    throw std::domain_error("Broj nije validan!");
  for (int i = 1; i < n; i++) {
    if (DaLiJeProst(i)) {
      if (DaLiJeProst(n - i)) {
        p = i;
        q = n - i;
        break;
      } else
        continue;
    }
  }
}

int main() {
  int n;
  /*std::cout << "Unesite broj n: ";
  std::cin >> n; */
  int p, q;
  clock_t vrijeme1 = clock();
  Goldbach(std::pow(2,16), p, q);
  clock_t vrijeme2 = clock();
  int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC/1000);
  std::cout<<"Vrijeme izvrsavanja: "<<ukvrijeme<<" ms."<<std::endl;
  Goldbach(n, p, q);
  std::cout << "Uneseni broj n se moze rastaviti kao: " << p << " + " << q;
}