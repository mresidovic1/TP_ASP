// TP 2022/2023: LV 6, Zadatak 3
#include <cmath>
#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>

int **KreirajTrougao(int n) {
  if (n <= 0)
    throw std::domain_error("Broj redova mora biti pozitivan");
  int **mat = new int *[n] {};
  try {
    for (int i = 0; i < n; i++) {
      mat[i] = new int[2 * i + 1];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        int razlika = i - j;
        if (razlika >= 0) {
          mat[i][j] = razlika + 1;
        } else {
          mat[i][j] = j - i + 1;
        }
      }
    }
  } catch (std::bad_alloc) {
    for (int i = 0; i < n; i++)
      delete[] mat[i];
    delete[] mat;
    throw;
  }
  return mat;
}

int main() {
  int n;
  std::cout << "Koliko zelite redova: ";
  std::cin >> n;

  try {
    int **mat = KreirajTrougao(n);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2 * i + 1; j++) {
        std::cout << mat[i][j] << " ";
      }
      std::cout << std::endl;
    }
    for (int i = 0; i < n; i++) {
      delete[] mat[i];
    }
    delete[] mat;
  } catch (std::bad_alloc) {
    std::cout << "Izuzetak: Nedovoljno memorije!";
  } catch (std::domain_error &e) {
    std::cout << "Izuzetak: " << e.what() << std::endl;
  }

  return 0;
}
