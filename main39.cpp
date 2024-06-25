//TP 2022/2023: LV 7, Zadatak 3
#include <cmath>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>

int main() {
  int vel;
  std::cout << "Koliko zelite recenica: ";
  std::cin >> vel;
  std::cin.ignore(10000, '\n');
  std::cin.clear();
  std::string *recenice = nullptr;
  try {
    std::cout << "Unesite recenice: " << std::endl;
    recenice = new std::string[vel];
    for (int i = 0; i < vel; i++) {
    std::string recenica;
      std::getline(std::cin, recenica);
      recenice[i]=recenica;
    }
    std::sort(recenice,recenice+vel,[](std::string prvi,std::string drugi){
    return (prvi<drugi);
    });
    std::cout << "Sortirane recenice: " << std::endl;
    for (int i = 0; i < vel; i++) {
      std::cout << recenice[i] << std::endl;
    }
    delete[] recenice;
  } catch (std::bad_alloc) {
    std::cout << std::endl;
    std::cout << "Problemi s memorijom!";
    delete[] recenice;
  }

  return 0;
}


