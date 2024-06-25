// TP 2022/2023: LV 4, Zadatak 3
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

std::string Veliko(std::string a) {
  for (int i = 0; i < a.length(); i++) {
    a[i] = std::toupper(a[i]);
  }
  return a;
}

void IzdvojiKrajnjeRijeci(std::vector<std::string> &a, std::string &prva,
                          std::string &druga) {
  if (a.size() == 0) {
    prva = "";
    druga = "";
    return;
  }
  prva = a[0];
  druga = a[0];
  for (int i = 0; i < a.size(); i++) {
    if (Veliko(a[i]) <= Veliko(prva)) {
      prva = a[i];
    }
    if (Veliko(a[i]) >= Veliko(druga)) {
      druga = a[i];
    }
  }
}

void ZadrziDuplikate(std::vector<std::string> &a) {

  std::vector<std::string> vidjeni;
  int brojac = 0;
  std::string vidjen;
  for (int i = 0; i < a.size(); i++) {
    bool duplikat = false;
    for (int j = i + 1; j < a.size(); j++) {
      if (a[i] == a[j] && a[j]!=vidjen) {
          vidjen=a[i];
        if (!duplikat) {
          vidjeni.push_back(a[i]);
          duplikat = true;
        }
        a[j] = std::move(a[brojac]);
        a[brojac] = std::move(a[i]);
        brojac++;
      }
    }
  }

  a.resize(brojac);
  a = vidjeni;
}

int main() {
  int n;
  std::string prva, druga;
  std::cout<<"Koliko zelite unijeti rijeci: ";
  std::cin>>n;
  std::vector<std::string> a(n);
  std::cout<<"Unesite rijeci: ";
  for(int i=0;i<a.size();i++){
      std::cin>>a[i];
  }
  std::cout<<std::endl;
  IzdvojiKrajnjeRijeci(a, prva, druga);
  std::cout<<"Prva rijec po abecednom poretku je: "<<prva<<std::endl;
  std::cout<<"Posljednja rijec po abecednom poretku je: "<<druga<<std::endl;
  std::cout<<"Rijeci koje se ponavljaju su: ";
  ZadrziDuplikate(a);
  for(std::string x : a){
      for(char p : x) std::cout<<p;
      std::cout<<" ";
  }

  return 0;
}
