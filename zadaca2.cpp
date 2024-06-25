#include <iostream>

template <typename tip> class DvostraniRed {
  struct Cvor {
    tip element;
    Cvor *prethodni;
    Cvor *veza;
    Cvor(const tip &el, Cvor *prethodni, Cvor *v)
        : element(el), veza(v), prethodni(prethodni) {}
  };
  Cvor *prvi;
  Cvor *kraj;
  int br_el;
  void kopiraj(const DvostraniRed &pom) {
    Cvor *copy = pom.prvi;
    while (copy != nullptr) {
      staviNaVrh(copy->element);
      copy = copy->veza;
    }
  }

public:
  DvostraniRed() : prvi(nullptr), kraj(nullptr), br_el(0) {}
  DvostraniRed(const DvostraniRed &pom)
      : prvi(nullptr), kraj(nullptr), br_el(0) {
    kopiraj(pom);
  }
  DvostraniRed &operator=(const DvostraniRed &pom) {
    if (this == &pom)
      return *this;
    else {
      brisi();
      kopiraj(pom);
      return *this;
    }
  }
  ~DvostraniRed() { brisi(); }
  void brisi() {
    while (br_el != 0) {
      skiniSaVrha();
    }
  }
  int brojElemenata() const { return br_el; }
  void staviNaVrh(const tip &el) {
    Cvor *novi = new Cvor(el, nullptr, kraj);
    if (br_el == 0){
      prvi = novi;
      kraj=novi;
    }
    else {
      kraj->veza = novi;
      novi->prethodni=kraj;
    }
    kraj = novi;
    kraj->veza=nullptr;
    br_el++;
  }
  tip skiniSaVrha() {
    if (br_el == 0)
      throw std::logic_error("Nema elemenata!");
    Cvor *pom = kraj;
    tip el = pom->element;
    if (prvi == kraj) {
      prvi = nullptr;
      kraj = nullptr;
    } else {
      kraj = kraj->prethodni;
      kraj->veza = nullptr;
    }
    delete pom;
    br_el--;
    return el;
  }
  void staviNaCelo(const tip &el) {
    Cvor *novi = new Cvor(el, prvi, nullptr);
    if (br_el == 0){
      kraj = novi;
      prvi=novi;
    }
    else {
      novi->veza=prvi;
      prvi->prethodni = novi;
    }
    prvi = novi;
    prvi->prethodni=nullptr;
    br_el++;
  }
  tip skiniSaCela() {
    if (br_el == 0)
      throw std::logic_error("Nema elemenata!");
    Cvor *pom = prvi;
    tip el = pom->element;
    if (prvi == kraj) {
      prvi = nullptr;
      kraj = nullptr;
    } else {
      prvi = prvi->veza;
      prvi->prethodni = nullptr;
    }
    delete pom;
    br_el--;
    return el;
  }
  tip vrh() const {
    if (br_el == 0)
      throw std::logic_error("Nema elemenata!");
    return kraj->element;
  }
  tip celo() const {
    if (br_el == 0)
      throw std::logic_error("Nema elemenata!");
    return prvi->element;
  }
};

template<typename tip>
void testirajStaviNaVrh(DvostraniRed<tip>& red){
    for(int i=1;i<10000;i*=2){
        red.staviNaVrh(i);
    }
}

template<typename tip>
void testirajSkiniSaVrha(DvostraniRed<tip>& red){
for(int i=1;i<=5;i++){
    red.staviNaVrh(i*100);
}
    std::cout<<red.skiniSaVrha()<<" ";
std::cout<<std::endl;
}

template<typename tip>
void testirajStaviNaCelo(DvostraniRed<tip>& red){
    int brojac=10;
    while(brojac!=0){
        red.staviNaCelo(brojac);
        brojac--;
    }
}

template<typename tip>
void testirajSkiniSaCela(DvostraniRed<tip>& red){
    for(int i=0;i<red.brojElemenata()/3;i++){
        std::cout<<red.skiniSaCela()<<" ";
    }
    std::cout<<std::endl;
}

template<typename tip>
void testirajKombinovano(DvostraniRed<tip>& red){
    DvostraniRed<tip> pom=red;
    pom.brisi();
    pom.staviNaVrh(5);
    red.brisi();
    std::cout<<"Broj elemenata je: "<<red.brojElemenata()<<std::endl;
    if(red.brojElemenata()==0) std::cout<<"Kraj!";
}

int main() {
    DvostraniRed<int> test;
    testirajStaviNaVrh(test);
    testirajSkiniSaVrha(test);
    testirajStaviNaCelo(test);
    testirajSkiniSaCela(test);
    testirajKombinovano(test);
  return 0;
}