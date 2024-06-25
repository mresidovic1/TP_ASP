// TP 2022/2023: Zadaća 5, Zadatak 5
#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>


template <typename TipElemenata> 
class DatotecniKontejner {
  std::fstream tok;
public:
  DatotecniKontejner(const std::string &ime) {
      tok.open(ime, std::ios::binary | std::ios::out);
      if(!tok){
        throw std::logic_error( "Problemi prilikom otvaranja ili kreiranja datoteke");
      }
      tok.close();
      tok.open(ime, std::ios::binary | std::ios::out | std::ios::in);
  }
  void DodajNoviElement(const TipElemenata &element) {
    tok.seekp(0,std::ios::end);
    try{
    tok.write(reinterpret_cast<const char *>(&element), sizeof(TipElemenata));
    tok.flush();
    }
    catch(...){
        throw std::logic_error("Problemi prilikom pristupa datoteci");
    }
  }
  int DajBrojElemenata() {
    tok.seekg(0, std::ios::end);
    auto trenutna_poz=tok.tellg();
    int br_el= tok.tellg() / sizeof(TipElemenata);
    tok.seekp(trenutna_poz);
    return br_el;
  }
  TipElemenata DajElement(int pozicija) {
    if (pozicija < 0 || pozicija >= DajBrojElemenata()) {
      throw std::range_error("Neispravna pozicija");
    }
    tok.seekg(pozicija * sizeof(TipElemenata), std::ios::beg);
    TipElemenata el;
    try{
    tok.read(reinterpret_cast<char *>(&el), sizeof(TipElemenata));
    }
    catch(...){
        throw std::logic_error("Problemi prilikom pristupa datoteci");
    }
    return el;
  }
  void IzmijeniElement(int pozicija, const TipElemenata &element) {
    if (pozicija < 0 || pozicija >= DajBrojElemenata()) {
      throw std::range_error("Neispravna pozicija");
    }
    tok.seekp(pozicija * sizeof(TipElemenata), std::ios::beg);
    try{
    tok.write(reinterpret_cast<const char *>(&element), sizeof(TipElemenata));
    }
    catch(...){
        throw std::logic_error("Problemi prilikom pristupa datoteci");
    }
  }
  void Sortiraj(std::function<bool(const TipElemenata &, const TipElemenata &)>
                    kriterij = std::less<TipElemenata>()) {
    int br_el = DajBrojElemenata();
    for (int i = 0; i < br_el - 1; i++) {
      for (int j = 0; j < br_el - i - 1; j++) {
        TipElemenata pom1 = DajElement(j);
        TipElemenata pom2 = DajElement(j + 1);
        if (kriterij(pom2, pom1)) {
          IzmijeniElement(j, pom2);
          IzmijeniElement(j + 1, pom1);
        }
      }
    }
  }
};

int main() {
   try{
        DatotecniKontejner<int> dat("dat.bin");
        dat.DodajNoviElement(1);
        dat.DodajNoviElement(3);
        dat.DodajNoviElement(5);
        dat.DodajNoviElement(7);
        dat.DodajNoviElement(9);

        std::cout<<"Broj elemenata: "<<dat.DajBrojElemenata()<<std::endl;

        for(int i=0;i<dat.DajBrojElemenata();i++){
            int el=dat.DajElement(i);
            std::cout<<el<<" "<<std::endl;
        }
        dat.Sortiraj();

        std::cout<<"Sortirani: "<<std::endl;
        for(int i=0;i<dat.DajBrojElemenata();i++){
            int el=dat.DajElement(i);
            std::cout<<el<<" "<<std::endl;
        }
    }
    catch(std::range_error e){
        std::cout<<e.what();
    }
    catch(std::logic_error e){
        std::cout<<e.what();
    }
  return 0;
}