//TP 2022/2023: LV 6, Zadatak 4
#include <cmath>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

int **KreirajTrougao(int n) {
  if (n <= 0)
    throw std::domain_error("Broj redova mora biti pozitivan");
  int **niz=nullptr;
  try {
    niz=new int*[n];
    int *niz1=new int[n*(2*n+1)/2];
    int pom=0;
    for (int i = 0; i < n; i++) {
    niz[i]=&niz1[pom];
      for (int j = 0; j < 2 * i + 1; j++) {
        int razlika = i - j;
        if (razlika >= 0) {
          niz1[pom++]=razlika+1;
        } else {
          niz1[pom++] = j - i + 1;
        }
      }
    }
  } catch (std::bad_alloc) {
    delete[] niz;
    throw;
  }
  return niz;
}

int main() {
  int n;
  std::cout << "Koliko zelite redova: ";
  std::cin >> n;

  try {
    int **niz = KreirajTrougao(n);
    int pom=0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        std::cout << niz[i][j]<< " ";
      }
      std::cout << std::endl;
    }
    delete[] niz[0];
    delete[] niz;
  } catch (std::bad_alloc) {
    std::cout << "Izuzetak: Nedovoljno memorije!";
  } catch (std::domain_error &e) {
    std::cout << "Izuzetak: " << e.what() << std::endl;
  }

  return 0;
}
