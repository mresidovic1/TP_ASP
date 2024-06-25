// TP 2022/2023: LV 4, Zadatak 5
#include <cmath>
#include <iostream>
#include <string>
#include <vector>


template <typename Tip>
std::vector<Tip> Presjek(std::vector<Tip> v1, std::vector<Tip> v2) {

  std::vector<Tip> v;
  for (int i = 0; i < v1.size(); i++) {
    for (int j = 0; j < v2.size(); j++) {
      if (v1[i] == v2[j]) {
        v.push_back(v1[i]);
        break;
      }
    }
  }

  for (int k = 0; k < v.size(); k++) {
    for (int l = k + 1; l < v.size(); l++) {
      if (v[k] == v[l]) {
        v.erase(v.begin() + l);
        k--;
        break;
      }
    }
  }
  return v;
}

int main() {
  int n1;
  std::vector<double>v;
  int n2;
  std::vector<double>v2;
  std::cout<<"Test za realne brojeve...";
  std::cout<<std::endl;
  std::cout<<"Unesite broj elemenata prvog vektora: ";
  std::cin>>n1;
  std::cout<<"Unesite elemente prvog vektora: ";
  for(int i=0;i<n1;i++){
      double broj;
      std::cin>>broj;
      v.push_back(broj);
  }
  std::cout<<"Unesite broj elemenata drugog vektora: ";
  std::cin>>n2;
  std::cout<<"Unesite elemente drugog vektora: ";
  for(int i=0;i<n2;i++){
      double broj;
      std::cin>>broj;
      v2.push_back(broj);
  }
  std::cout<<"Zajednicki elementi su: ";
  for(double x : Presjek(v,v2)){
      std::cout<<x<<" ";
  }
    std::cout<<std::endl;
    std::cout<<std::endl;


  int vel1;
  std::vector<std::string>s1;
  int vel2;
  std::vector<std::string>s2;
  std::cout<<"Test za stringove...";
  std::cout<<std::endl;
  std::cout<<"Unesite broj elemenata prvog vektora: ";
  std::cin>>vel1;
  std::cin.ignore(10000,'\n');
  std::cin.clear();
  std::cout<<"Unesite elemente prvog vektora (ENTER nakon svakog unosa): ";
  for(int i=0;i<vel1;i++){
      std::string rijec;
      getline(std::cin,rijec);
      s1.push_back(rijec);
  }
  std::cout<<"Unesite broj elemenata drugog vektora: ";
  std::cin>>vel2;
  std::cin.ignore(10000,'\n');
  std::cin.clear();
  std::cout<<"Unesite elemente drugog vektora (ENTER nakon svakog unosa): ";
  for(int i=0;i<vel2;i++){
      std::string rijec;
    getline(std::cin,rijec);
    s2.push_back(rijec);
  }
    std::cout<<std::endl;

  std::cout<<"Zajednicki elementi su: ";
  for(std::string x : Presjek(s1,s2)){
      std::cout<<x<<" ";
  }

  return 0;
}
