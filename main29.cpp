// TP 2022/2023: LV 5, Zadatak 6
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

void UNOS(int &a){
    std::cin>>a;
}

int Cifre(int x) {
  if (x == 0)
    return 0;
  return (std::abs(x) % 10 + Cifre(std::abs(x) / 10));
}

void Ispisi(int x) { std::cout << x << " "; }

int main() {
  int n;
  std::cout << "Unesite broj elemenata: ";
  std::cin >> n;
  std::vector<int> elementi(n);
  std::cout<<"Unesite elemente: ";
  std::for_each(elementi.begin(),elementi.end(),UNOS);
  std::sort(elementi.begin(), elementi.end(), [](int x, int y) { 
      int suma1=Cifre(x);
      int suma2=Cifre(y);
      if(suma1==suma2) return x<y;
      return suma1<suma2;
   });

  std::cout<<"Niz sortiran po sumi cifara glasi: ";
  std::for_each(elementi.begin(), elementi.end(), Ispisi);

  std::cout<<std::endl;
  std::cout<<"Unesite broj koji trazite: ";
  int broj;
  std::cin>>broj;

  if(std::lower_bound(elementi.begin(),elementi.end(),broj,[](int x, int y) { 
      int suma1=Cifre(x);
      int suma2=Cifre(y);
      if(suma1==suma2) return x<y;
      return suma1<suma2;
   })==elementi.end() || *std::lower_bound(elementi.begin(),elementi.end(),broj,[](int x, int y) { 
      int suma1=Cifre(x);
      int suma2=Cifre(y);
      if(suma1==suma2) return x<y;
      return suma1<suma2;
   })!=broj){
        std::cout<<"Trazeni broj ne nalazi se u nizu!";
        return 0;
   }

  std::cout<<"Trazeni broj nalazi se na poziciji "<< (std::lower_bound(elementi.begin(),elementi.end(),broj,[](int x, int y) { 
      int suma1=Cifre(x);
      int suma2=Cifre(y);
      if(suma1==suma2) return x<y;
      return suma1<suma2;
   })-elementi.begin());

  return 0;
}
