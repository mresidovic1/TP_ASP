// TP 2022/2023: Zadaća 2, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

bool KvadratJe(int p) { return (int(std::sqrt(p)) * int(std::sqrt(p)) == p); }

bool SlobodanOdKvadrata(int broj) {
  std::vector<int> kvadrati;
  for (int k = 4; k <= std::sqrt(broj); k++) {
    if (KvadratJe(k))
      kvadrati.push_back(k);
  }

  for (int k = 0; k < kvadrati.size(); k++) {
    if (broj % kvadrati.at(k) == 0)
      return false;
    else
      continue;
  }

  return true;
}

void RastavaBroja(int n, int &p, int &q) {
  int pomocni = 0;
  bool negativan = false;
  if (n < 0) {
    negativan = true;
    n = -n;
  }
  if (n == 0) {
    p = 0;
    q = 1;
  }
  for (int i = 1; i <= std::sqrt(n) ; i++) {
    if ((i * i <= n) && (n % (i * i) == 0)) {
      pomocni = n / (i * i);
      if (SlobodanOdKvadrata(pomocni)) {
        p = pomocni;
        q = i;
      }
    }
  }
  if (negativan) {
    p = -p;
  }
}

int main() {

  int n, p, q;
  std::cout << "Unesi broj: ";
  std::cin >> n;
  std::cout << std::endl;
  RastavaBroja(n, p, q);
  std::cout << n << " = " << p << "*" << q << "^2" << std::endl;

  return 0;
}
