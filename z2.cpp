// TP 2022/2023: Zadaća 1, Zadatak 2
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

typedef std::vector<std::vector<double>> Matrica;

Matrica UsrednjavajuciFilter(Matrica a, int N) {
  if (N < 0)
    throw std::domain_error("Neispravan red filtriranja");
  Matrica Filter(a.size());
  int j = 0;
  for (int i = 0; i < a.size(); i++) {
    double prosjek = 0;
    int brojac = 0;
    Filter.at(i).resize(a.at(i).size());
    for (j = 0; j < a.at(i).size(); j++) {
      for (int k = i - N; k <= i + N; k++) {
        if (k >= 0 && k < a.size()) {
          for (int l = j - N; l <= j + N; l++) {
            if (l >= 0 && l < a.at(k).size()) {
              prosjek += a.at(k).at(l);
              brojac++;
            }
          }
        }
      }
      Filter.at(i).at(j) = prosjek / brojac;
      brojac = 0;
      prosjek = 0;
    }
  }

  return Filter;
}

int main() {

  int N, a, b;
  std::cout << "Unesite broj redova i kolona matrice: ";
  std::cin >> a >> b;
  std::cout << "Unesite elemente matrice: ";
  
  Matrica mat(a, std::vector<double>(b));
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
      std::cin >> mat.at(i).at(j);
    }
  }
  std::cout << "Unesite red filtriranja: ";
  std::cin >> N;
  std::cout << std::endl;

  try {
    UsrednjavajuciFilter(mat, N);
    std::cout << "Matrica nakon filtriranja: " << std::endl;
    for (std::vector<double> red : UsrednjavajuciFilter(mat, N)) {
      for (double x : red) {
        std::cout << std::setw(7) << std::right << std::fixed
                  << std::setprecision(2) << x << " ";
      }
      std::cout << std::endl;
    }
  } catch (std::domain_error negativan) {
    std::cout << "GRESKA: " << negativan.what() << "!";
  }

  return 0;
}
