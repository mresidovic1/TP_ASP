// TP 2022/2023: LV 4, Zadatak 2
#include <cmath>
#include <iostream>
#include <string>

std::string IzvrniString(std::string &a) {

  int j = a.length() - 1;
  for (int i = 0; i < a.length()/2; i++) {
    char prebacaj;
    prebacaj = a[i];
    a[i] = a[j];
    a[j] = prebacaj;
    j--;
  }

  return a;
}

int main() {
  std::string a;
  std::cout << "Unesi string: ";
  std::getline(std::cin, a);
  std::cout << "Izvrnuti string je: ";
  for (char i : IzvrniString(a))
    std::cout << i;

  return 0;
}
