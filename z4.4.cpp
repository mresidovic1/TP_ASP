// TP 2022/2023: Zadaća 1, Zadatak 4
#include <cctype>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool DaLiJeSlovoiliCifra(char znak) {
  if ((std::toupper(znak) >= 'A' && std::toupper(znak) <= 'Z') ||
      (znak >= 48 && znak <= 57))
    return true;
  else
    return false;
}

std::string Cenzura(std::string recenica, std::vector<std::string> cenzura) {
  bool vidjena = false;
  for (int i = 0; i < cenzura.size(); i++) {
    for (int j = 0; j < cenzura.at(i).length(); j++) {

      if (!DaLiJeSlovoiliCifra(cenzura.at(i).at(j)) && vidjena) {
        throw std::logic_error("GRESKA: Nelegalne zabranjene rijeci!");
      }

      if (!DaLiJeSlovoiliCifra(cenzura.at(i).at(j))) {
        vidjena = true;
        break;
      }
    }
  }
  if (vidjena)
    throw std::logic_error("Neispravna riječ");

  int vel_rijeci = 0;
  int pocetni_indeks = 0;
  for (int i = 0; i < recenica.length(); i++) {
    vel_rijeci = 0;

    while (!DaLiJeSlovoiliCifra(recenica.at(i)) && i < recenica.length()) {
      i++;
      if (i >= recenica.length()-1)
        break;
    }

    if (DaLiJeSlovoiliCifra(recenica.at(i)) && i < recenica.length())
      pocetni_indeks = i;

    while (DaLiJeSlovoiliCifra(recenica.at(i)) && i < recenica.length()) {
      vel_rijeci++;
      i++;
      if (i >= recenica.length())
        break;
    }

    for (int j = 0; j < cenzura.size(); j++) {
      std::string pom;
      for (int l = pocetni_indeks; l < pocetni_indeks + vel_rijeci; l++) {
        pom.push_back(std::toupper(recenica.at(l)));
      }
      std::string provjera;
      for (int m = 0; m < cenzura.at(j).size(); m++) {
        provjera.push_back(std::toupper(cenzura.at(j).at(m)));
      }
      if (pom == provjera) {
        for (int k = pocetni_indeks; k < pocetni_indeks + vel_rijeci; k++) {
          recenica.at(k) = '*';
        }
      } else {
        pom.clear();
        provjera.clear();
        continue;
      }
    }
  }
  return recenica;
}

int main() {
  std::string recenica;
  std::vector<std::string> cenzurisani;
  std::cout << "Unesite recenicu: ";
  std::getline(std::cin, recenica);
  std::cout << std::endl;
  std::cout << "Unesite zabranjene rijeci (. za kraj): ";
  int i = 0;
  std::string unos;
  while (std::cin >> unos && unos != ".") {
    cenzurisani.push_back(unos);
  }
  std::cout << std::endl;
  try {
    Cenzura(recenica, cenzurisani);
    std::cout << std::endl;
    std::cout << "Cenzurisana recenica: " << Cenzura(recenica, cenzurisani);
  } catch (std::logic_error greska) {
    std::cout << greska.what();
  }

  return 0;
}
