//TP 2022/2023: LV 7, Zadatak 4
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <memory>

using Str=std::shared_ptr<std::string>;
using StrNiz=std::unique_ptr<Str[]>;

int main() {
  int vel;
  std::cout << "Koliko zelite recenica: ";
  std::cin >> vel;
  std::cin.ignore(10000, '\n');
  std::cin.clear();
  StrNiz recenice = nullptr;
  try {
    std::cout << "Unesite recenice: " << std::endl;
    recenice = std::make_unique<Str[]>(vel);
    for (int i = 0; i < vel; i++) {
    Str recenica= std::make_shared<std::string>();
      std::getline(std::cin, *recenica);
      recenice[i]=recenica;
    }
    std::sort(recenice.get(),recenice.get()+vel,[](Str prvi,Str drugi){
    return (*prvi<*drugi);
    });
    std::cout << "Sortirane recenice: " << std::endl;
    for (int i = 0; i < vel; i++) {
      std::cout << *recenice[i] << std::endl;
    }
  } catch (std::bad_alloc) {
    std::cout << std::endl;
    std::cout << "Problemi s memorijom!";
  }

  return 0;
}


