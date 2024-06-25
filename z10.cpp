// TP 2022/2023: Zadaća 3, Zadatak 1
#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

using Funkcija = std::function<double(double)>;
using Parovi = std::vector<std::pair<double, double>>;

Funkcija LagrangeovaInterpolacija(const Parovi &cvorovi) {
  for (int i = 0; i < cvorovi.size(); i++) {
    for (int j = i+1; j < cvorovi.size(); j++) {
      if (cvorovi.at(i).first == cvorovi.at(j).first) {
        throw std::domain_error("Neispravni cvorovi");
      }
    }
  }
  return [=](double x) -> double {
    double rezultat = 0;
    for (int i = 0; i < cvorovi.size(); i++) {
      double Lag_proizvod = 1;
      for (int j = 0; j < cvorovi.size(); j++) {
        if (i != j) {
          Lag_proizvod *=
              (x - cvorovi.at(j).first) / (cvorovi.at(i).first - cvorovi.at(j).first);
        }
      }
      Lag_proizvod *= cvorovi.at(i).second;
      rezultat += Lag_proizvod;
    }
    return rezultat;
  };
}

Funkcija LagrangeovaInterpolacija(Funkcija test, double pocetak, double kraj, double korak) {
    if(pocetak>kraj || korak<=0) throw std::domain_error("Nekorektni parametri");
  Parovi cvorovi;
  while (pocetak <= kraj) {
    cvorovi.push_back(std::make_pair(pocetak, test(pocetak)));
    pocetak += korak;
  }
  return [=](double x) -> double {
    double rezultat = 0;
    for (int i = 0; i < cvorovi.size(); i++) {
      double Lag_proizvod = 1;
      for (int j = 0; j < cvorovi.size(); j++) {
        if (i != j) {
          Lag_proizvod *=
              (x - cvorovi.at(j).first) / (cvorovi.at(i).first - cvorovi.at(j).first);
        }
      }
      Lag_proizvod *= cvorovi.at(i).second;
      rezultat += Lag_proizvod;
    }
    return rezultat;
  };
}

double funkcija(double x){
    return x*x+std::sin(x)+std::log(x+1);
}

int main() {
    int a;
    std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): ";
    std::cin>>a;
    try{
    if(a==1){
        int n;
        Parovi cvorovi;
        std::cout<<"Unesite broj cvorova: ";
        std::cin>>n;
        std::cout<<"Unesite cvorove kao parove x y: ";
        for(int i=0;i<n;i++){
            double x,y;
            std::cin>>x>>y;
            cvorovi.push_back(std::make_pair(x,y));
        }
        double max=cvorovi.at(0).first;
        double min=cvorovi.at(0).first;
        for(int k=0;k<n;k++){
            if(cvorovi.at(k).first>max) max=cvorovi.at(k).first;
            if(cvorovi.at(k).first<min) min=cvorovi.at(k).first;
        }
        double arg;
        auto LagInt=LagrangeovaInterpolacija(cvorovi);
        for(;;){
        std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
        if(std::cin>>arg){
            if(arg>max || arg<min){
            std::cout<<"f("<<arg<<") = "<<LagInt(arg)<<" [ekstrapolacija]"<<std::endl;
            }
            else
            std::cout<<"f("<<arg<<") = "<<LagInt(arg)<<std::endl;
        }
        else return 0;
        }
    }
    else if(a==2){
        double p,q,k;
        std::cout<<"Unesite krajeve intervala i korak: ";
        double arg;
        std::cin>>p>>q>>k;
        auto LagInt=LagrangeovaInterpolacija([](double x) { return x*x+std::sin(x)+std::log(x+1);},p,q,k);
        for(;;){
        std::cout<<"Unesite argument (ili \"kraj\" za kraj): ";
        if(std::cin>>arg){
            if(arg<p || arg>q)
        std::cout<<"f("<<arg<<") = "<<funkcija(arg)<<" P("<<arg<<") = "<<LagInt(arg)<<" [ekstrapolacija]"<<std::endl;
            else 
        std::cout<<"f("<<arg<<") = "<<funkcija(arg)<<" P("<<arg<<") = "<<LagInt(arg)<<std::endl;
        }
        else return 0;
        }
    }
    }
    catch(std::domain_error e){
        std::cout<<e.what();
    }

  return 0;
}
