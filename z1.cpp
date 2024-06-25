// TP 2022/2023: Zadaća 1, Zadatak 1
#include <array>
#include <climits>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

enum class TretmanNegativnih { IgnorirajZnak, Odbaci, PrijaviGresku };

std::vector<long long int> VratiNovi(long long int broj, int baza) {
  int ostatak = 0;
  long long int rezultat = broj;
  std::vector<long long int> novabaza;
  for (;;) {
    ostatak = rezultat % baza;
    novabaza.push_back(ostatak);
    rezultat /= baza;
    if (rezultat == 0)
      break;
  }
  return novabaza;
}

long long int MultiplikativniDigitalniKorijen(long long int broj, int baza) {
  if (baza <= 1)
    throw std::domain_error("Neispravna baza");
  long long int ostatak = 0, rezultat = broj;
  std::vector<long long int> novabaza;
  novabaza = VratiNovi(broj, baza);
  long long int digitalnikorijen = 1;
  for (int x : novabaza) {
    digitalnikorijen *= x;
  }
  novabaza = VratiNovi(digitalnikorijen, baza);
  while (novabaza.size() != 1) {
    digitalnikorijen = 1;
    for (int x : novabaza) {
      digitalnikorijen *= x;
    }
    novabaza = VratiNovi(digitalnikorijen, baza);
  }
  return digitalnikorijen;
}

std::array<std::vector<long long int>, 10>
RazvrstajBrojeve(std::vector<long long int> brojevi, TretmanNegativnih odluci) {

  std::vector<long long int> digitalnikorijeni;
  std::array<std::vector<long long int>, 10> Razvrstani;
  for (int i = 0; i < 10; i++) {
    int brojac = 0;
    digitalnikorijeni.clear();
    while (brojac < brojevi.size()) {
      if (brojevi.at(brojac) < 0 &&
          odluci == TretmanNegativnih::IgnorirajZnak) {
        brojevi.at(brojac) = std::abs(brojevi.at(brojac));
      } else if (brojevi.at(brojac) < 0 && odluci == TretmanNegativnih::Odbaci){
          brojac++;
        continue;}
      else if (brojevi.at(brojac) < 0 &&
               odluci == TretmanNegativnih::PrijaviGresku)
        throw std::domain_error(
            "Nije predvidjeno razvrstavanje negativnih brojeva");
      if (MultiplikativniDigitalniKorijen(brojevi.at(brojac), 10) == i) {
        digitalnikorijeni.push_back(brojevi.at(brojac));
        brojac++;
      }

      else
        brojac++;
    }
    Razvrstani.at(i).resize(digitalnikorijeni.size());
    for (int j = 0; j < digitalnikorijeni.size(); j++) {
      Razvrstani.at(i).at(j) = digitalnikorijeni.at(j);
    }
  }
  return Razvrstani;
}

int main() {

  std::vector<long long int> brojevi;
  long long int unos;
  std::cout << "Unesite brojeve (bilo koji ne-broj oznacava kraj): ";
  int m = 0;
  while (std::cin >> unos) {
    brojevi.push_back(unos);
    if(brojevi.at(m)<0){
        std::cout<<"Nije podrzano razvrstavanje negativnih brojeva!";
        return 0;
    }
    m++;
  }
  try {
    auto razvrstani = RazvrstajBrojeve(brojevi, TretmanNegativnih::PrijaviGresku);
    std::cout
        << "Rezultati razvrstavanja po multiplikativnom digitalnom korijenu: "
        << std::endl;
    for (int i = 0; i < 10; i++) {
      if (razvrstani.at(i).size() == 0)
        continue;
      std::cout << i << ": ";
      for (int j = 0; j < razvrstani.at(i).size(); j++) {
        std::cout << razvrstani.at(i).at(j) << " ";
        if (j == razvrstani.at(i).size())
          break;
      }
      std::cout << std::endl;
    }
  } catch (std::domain_error negativan) {
    std::cout << negativan.what();
  }

  return 0;
}
