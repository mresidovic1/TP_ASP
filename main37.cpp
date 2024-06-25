// TP 2022/2023: LV 7, Zadatak 1
#include <cmath>
#include <cstring>
#include <iostream>

bool Kriterij(char *prvi, char *drugi) {
  while (*prvi != '\0' && *drugi!='\0') {
    if (std::tolower(*prvi) > std::tolower(*drugi))
      return true;
    else if(std::tolower(*prvi) < std::tolower(*drugi))
      return false;
    prvi++;
    drugi++;
  }
  return std::strlen(prvi)>std::strlen(drugi);
}

int main() {
  int vel;
  std::cout << "Koliko zelite recenica: ";
  std::cin >> vel;
  std::cin.ignore(10000, '\n');
  std::cin.clear();
  int brojac=0;
  char **recenice = nullptr;
  try {
    std::cout << "Unesite recenice: " << std::endl;
    recenice = new char *[vel];
    for (int i = 0; i < vel; i++) {
      char recenica[1000];
      std::cin.getline(recenica, sizeof(recenica));
      recenice[i]=nullptr;
      recenice[i] = new char[std::strlen(recenica) + 1];
      brojac++;
      std::strcpy(recenice[i], recenica);
    }
    for (int i = 0; i < vel; i++) {
      for (int k = i + 1; k < vel; k++) {
        if (Kriterij(recenice[i], recenice[k])) {
          auto pom = recenice[i];
          recenice[i] = recenice[k];
          recenice[k] = pom;
        }
      }
    }
    std::cout << "Sortirane recenice: " << std::endl;
    for (int i = 0; i < vel; i++) {
      std::cout << recenice[i] << std::endl;
    }
    for(int i=0;i<vel;i++) delete[] recenice[i];
    delete[] recenice;
  } catch (std::bad_alloc) {
    std::cout << std::endl;
    std::cout << "Problemi s memorijom!";
    if(brojac!=0)
    for(int i=0;i<vel && recenice[i]!=nullptr;i++) delete[] recenice[i];
    delete[] recenice;
  }

  return 0;
}
