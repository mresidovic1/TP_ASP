// TP 2022/2023: Zadaća 3, Zadatak 2
#include <cctype>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string, int, int>>> Pojmovi;

/*
Knjiga:
map.first je string
map.second je vektor stringova
Pojmovi:
map.first je string
map.second je skup
elementi skupa su tupleovi
tuple<0> je string
tuple<1> je int
tuple<2> je int
*/
std::string Pretvori(std::string &s) {
  for (char &c : s) {
    if (c >= 'A' && c <= 'Z') {
      c = 'a' + (c - 'A');
    }
  }
  return s;
}

Pojmovi KreirajIndeksPojmova(const Knjiga &tekst) {
  Pojmovi IndeksPojmova;
  int br_stranice = 0;
  // tip std::pair<const std::string,std::vector<std::string>>
  for (const auto &poglavlja : tekst) {
    br_stranice = 0;
    for (int i = 0; i < poglavlja.second.size(); i++) {
      br_stranice++;
      std::string pom = poglavlja.second[i];   
      int pocetak = 0, kraj = 0;
      for (int j = 0; j < pom.length(); j++) {
        while (!std::isdigit(pom[j]) && !std::isalpha(pom[j]))
          j++;
        pocetak = j;
        while (std::isdigit(pom[j]) || std::isalpha(pom[j]))
          j++;
        kraj = j;
        std::string rijec = pom.substr(pocetak, kraj - pocetak);
        rijec = Pretvori(rijec);
        auto &pozicija = IndeksPojmova[rijec];
        pozicija.insert(std::make_tuple(poglavlja.first, br_stranice, pocetak));
      }
    }
  }
  return IndeksPojmova;
}

std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(std::string &rijec, const Pojmovi &mapa) {
  rijec = Pretvori(rijec);
  auto it = mapa.find(rijec);
  if (it == mapa.end())
    throw std::logic_error("Pojam nije nadjen");
  return it->second;
}

void IspisiIndeksPojmova(Pojmovi &mapa) {
  for (const auto &element : mapa) {
    std::cout << element.first << ": ";
    int i = 0;
    for (const auto &ispis : element.second) {
      if (i > 0)
        std::cout << ", ";
      std::cout << std::get<0>(ispis) << "/" << std::get<1>(ispis) << "/" << std::get<2>(ispis);
      i++;
    }
    std::cout << std::endl;
  }
} 

int main() {
  Knjiga tekst;
  std::string poglavlje;
  std::string stranica;
  int i = 1;
  for (;;) {
    std::cout << "Unesite naziv poglavlja: ";
    std::getline(std::cin, poglavlje);
    std::cout << std::endl;
    if (poglavlje == ".")
      break;
    for (;;) {
      std::cout << "Unesite sadrzaj stranice " << i << ": ";
      i++;
      std::getline(std::cin, stranica);
      std::cout << std::endl;
      if (stranica == ".")
        break;
      tekst[poglavlje].push_back(stranica);
    }
    i = 1;
  }
  Pojmovi IndeksPojmova = KreirajIndeksPojmova(tekst);
  std::cout << "Kreirani indeks pojmova: " << std::endl;
  IspisiIndeksPojmova(IndeksPojmova);
  std::string rijec;
  for (;;) {
    std::cout << "Unesite rijec: ";
    std::cin >> rijec;
    std::cout << std::endl;
    if (rijec == ".")
      break;
    std::set<std::tuple<std::string, int, int>> rez;
    try{
    rez = PretraziIndeksPojmova(rijec, IndeksPojmova);
    }
    catch(std::logic_error e){
      std::cout<<"Unesena rijec nije nadjena!";
  }
    for (const auto &ispis : rez) {
        std::cout << std::get<0>(ispis) << "/" << std::get<1>(ispis) << "/"<< std::get<2>(ispis) << " ";
      }
      std::cout << std::endl;
  }

  return 0;
}