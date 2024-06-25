// TP 2022/2023: Zadaća 1, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

typedef std::vector<std::vector<int>> Matrica;

Matrica KreirajSpiralnuMatricu(int br_red, int br_kol, int pocetna,
                               bool smjer) {
  Matrica spiralna(br_red, std::vector<int>(br_kol));
  int istok = br_kol - 1, zapad = 0, sjever = 0, jug = br_red - 1;
  int pom = pocetna;
  bool prekoraceno = false;
  while (smjer) {
    for (int i = zapad; i <= istok; i++) {
      spiralna.at(sjever).at(i) = pocetna++;
      if (pocetna < pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    for (int j = sjever + 1; j <= jug; j++) {
      spiralna.at(j).at(istok) = pocetna++;
      if (pocetna < pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    for (int k = istok - 1; k >= zapad; k--) {
      spiralna.at(jug).at(k) = pocetna++;
      if (pocetna <= pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    for (int l = jug - 1; l > sjever; l--) {
      spiralna.at(l).at(zapad) = pocetna++;
      if (pocetna < pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    istok--;
    jug--;
    zapad++;
    sjever++;
  }

  while (!smjer) {

    for (int l = sjever; l <= jug; l++) {
      spiralna.at(l).at(zapad) = pocetna++;
      if (pocetna < pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    for (int k = zapad + 1; k <= istok; k++) {
      spiralna.at(jug).at(k) = pocetna++;
      if (pocetna < pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    for (int j = jug - 1; j >= sjever; j--) {
      spiralna.at(j).at(istok) = pocetna++;
      if (pocetna < pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    for (int i = istok - 1; i > zapad; i--) {
      spiralna.at(sjever).at(i) = pocetna++;
      if (pocetna < pocetna - 1)
        prekoraceno = true;
    }

    if (pocetna == br_kol * br_red + pom || prekoraceno)
      break;

    istok--;
    jug--;
    zapad++;
    sjever++;
  }

  return spiralna;
}

bool DaLiJeSpiralnaMatrica(Matrica a) {
  int br_red = a.size(), br_kol = a.at(0).size();
  int pocetak = a.at(0).at(0);
  int pocetna = a.at(0).at(0) - 1;
  int provjera = 0;

  while (pocetna < std::numeric_limits<int>::max()) {
    pocetna++;
    provjera++;
    if(provjera==br_red*br_kol) break;
  }

  if (provjera != br_red * br_kol)
    return false;

  if (a == KreirajSpiralnuMatricu(br_red, br_kol, pocetak, true))
    return true;
  else if (a == KreirajSpiralnuMatricu(br_red, br_kol, pocetak, false))
    return true;
  else
    return false;
}

int main() {
  int br_red, br_kol, pocetna;
  char smjer;
  std::cout << "Unesite broj redova i kolona matrice: ";
  std::cin >> br_red >> br_kol;
  std::cout << "Unesite pocetnu vrijednost: ";
  std::cin >> pocetna;
  std::cout << "Unesite L za lijevu, a D za desnu spiralnu matricu: ";
  std::cin >> smjer;
  std::cout << std::endl;
  if (smjer == 'D') {
    std::cout << "Kreirana spiralna matrica: ";
    std::cout << std::endl;
    for (std::vector<int> red :
         KreirajSpiralnuMatricu(br_red, br_kol, pocetna, true)) {
      for (int x : red) {
        std::cout << std::setw(5) << x;
      }
      std::cout << std::endl;
    }
  } else if (smjer == 'L') {
    std::cout << "Kreirana spiralna matrica: ";
    std::cout << std::endl;
    for (std::vector<int> red :
         KreirajSpiralnuMatricu(br_red, br_kol, pocetna, false)) {
      for (int x : red) {
        std::cout << std::setw(5) << x;
      }
      std::cout << std::endl;
    }
  } 

  return 0;
}
