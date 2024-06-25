// TP 2022/2023: Zadaća 2, Zadatak 4
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

template <typename tip>
bool Kriterij(const std::vector<tip> &red1, const std::vector<tip> &red2) {
  tip p1 = red1[0];
  tip p2 = red2[0];
  for (int i = 1; i < red1.size(); i++) {
    p1 *= red1.at(i);
  }
  for (int i = 1; i < red2.size(); i++) {
    p2 *= red2.at(i);
  }

  if (p1 == p2) {
    return red1 < red2;
  }

  return !(p1 >= p2);
}

template <typename tip>
void SortirajPoProizvoduRedova(std::vector<std::vector<tip>> &Matrica) {
  
    std::sort(Matrica.begin(), Matrica.end(), Kriterij<tip>);
  
}

int main() {
  std::vector<std::vector<int>> grbava_mat;
  std::cout
      << "Unesi elemente (* za kraj reda, * na pocetku reda za kraj unosa): "
      << std::endl;
  int broj;

  while (true) {
    std::vector<int> pom;
    while (std::cin >> broj) {
      pom.push_back(broj);
    }
    if (pom.size() == 0)
      break;
    grbava_mat.push_back(pom);
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    pom.clear();
  }

  std::cout << std::endl;
  std::cout << "Matrica nakon sortiranja: " << std::endl;
  SortirajPoProizvoduRedova(grbava_mat);
  for (std::vector<int> &red : grbava_mat) {
    for (int &el : red) {
      std::cout << el << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Unesite elemente sekvence koja se trazi (* za kraj reda): ";
  std::vector<int> sekvenca;
  int el;
  std::cin.clear();
  std::cin.ignore(10000, '\n');
  while (std::cin >> el) {
    sekvenca.push_back(el);
  }
  auto pronalazac = std::lower_bound(grbava_mat.begin(), grbava_mat.end(),
                                     sekvenca, Kriterij<int>);
  if (pronalazac == grbava_mat.end() || *pronalazac != sekvenca) {
    std::cout << std::endl;
    std::cout << "Trazena sekvenca se ne nalazi u matrici";
    return 0;
  }
  std::cout << std::endl;
  std::cout << "Trazena sekvenca se nalazi u "
            << pronalazac - grbava_mat.begin() + 1
            << ". redu (nakon sortiranja)";

  return 0;
}
