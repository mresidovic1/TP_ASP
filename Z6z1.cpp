#include <iostream>
#include <string>
using namespace std;


template <typename tipKlj, typename tipVr> 
class Mapa {
public:
  virtual ~Mapa() {}
  virtual tipVr &operator[](const tipKlj &kljuc) = 0;
  virtual const tipVr &operator[](const tipKlj &kljuc) const = 0;
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const tipKlj &kljuc) = 0;
};


template <typename tipKlj, typename tipVr>
class NizMapa : public Mapa<tipKlj, tipVr> {
private:
  std::pair<tipKlj, tipVr> *niz;
  int kapacitet;
  int brElemenata;

public:
  NizMapa() : kapacitet(10), brElemenata(0) {
    niz = new std::pair<tipKlj, tipVr>[kapacitet];
  }

  NizMapa(const NizMapa &pom) : kapacitet(pom.kapacitet), brElemenata(pom.brElemenata) {
    niz = new std::pair<tipKlj, tipVr>[kapacitet];
    for (int i = 0; i < brElemenata; i++) {
      niz[i] = pom.niz[i];
    }
  }

  NizMapa &operator=(const NizMapa &pom) {
    if (this == &pom) return *this;
    else{
      delete[] niz;
      kapacitet = pom.kapacitet;
      brElemenata = pom.brElemenata;
      niz = new std::pair<tipKlj, tipVr>[kapacitet];
      for (int i = 0; i < brElemenata; i++) {
        niz[i] = pom.niz[i];
      }
    }
    return *this;
  }

  ~NizMapa() { delete[] niz; }

  tipVr &operator[](const tipKlj &kljuc) override {
    for (int i = 0; i < brElemenata; i++) {
      if (niz[i].first == kljuc) {
        return niz[i].second;
      }
    }
    if (brElemenata == kapacitet) {
      kapacitet *= 2;
      std::pair<tipKlj, tipVr> *noviNiz = new std::pair<tipKlj, tipVr>[kapacitet];
      for (int i = 0; i < brElemenata; i++) {
        noviNiz[i] = niz[i];
      }
      delete[] niz;
      niz = noviNiz;
    }
    niz[brElemenata++] = std::pair<tipKlj, tipVr>(kljuc, tipVr());
    return niz[brElemenata - 1].second;
  }

  const tipVr& operator[](const tipKlj& kljuc) const override {
    for (int i = 0; i < brElemenata; i++) {
        if (niz[i].first == kljuc) {
            return niz[i].second;
        }
    }
    static const tipVr povratnaVr = tipVr();
    return povratnaVr;
}

  int brojElemenata() const override { return brElemenata; }

  void obrisi() override { brElemenata = 0; }

  void obrisi(const tipKlj &kljuc) override {
    for (int i = 0; i < brElemenata; i++) {
      if (niz[i].first == kljuc) {
        for (int j = i; j < brElemenata - 1; j++) {
          niz[j] = niz[j + 1];
        }
        brElemenata--;
        return;
      }
    }
    throw std::logic_error("Ključ ne postoji u mapi");
  }
};

void testirajbrojElemenata(NizMapa<string,int>& mapa){
    std::string ime1="Mahir";
    std::string ime2="Darko";
    std::string ime3="Lejla";
    mapa[ime1]=1;
    mapa[ime2]=2;
    mapa[ime3]=3;
    std::cout<<"Broj elemenata mape je: "<<mapa.brojElemenata()<<std::endl;
}

//unutar ovog testa testiramo i metodu obrisi
void testirajKonstrKopijeIoperatorDodjele(NizMapa<string,int>&mapa){
    NizMapa<string,int> pom(mapa);
    std::cout<<"Broj elemenata kopirane mape pomocu konstr kopije je: "<<pom.brojElemenata()<<std::endl;
    pom.obrisi();
    std::cout<<"Broj elemenata kopirane mape nakon brisanja je: "<<pom.brojElemenata()<<std::endl;
    std::cout<<"Broj elemenata originalne mape nakon brisanja je: "<<mapa.brojElemenata()<<std::endl;
    NizMapa<string,int> pom2=mapa;
    std::cout<<"Broj elemenata kopirane mape pomocu operatora dodjele je: "<<pom2.brojElemenata()<<std::endl;
    pom2.obrisi();
    std::cout<<"Broj elemenata kopirane mape nakon brisanja je: "<<pom2.brojElemenata()<<std::endl;
    std::cout<<"Broj elemenata originalne mape nakon brisanja je: "<<mapa.brojElemenata()<<std::endl;
}

void testirajPretrazivanje(NizMapa<string,int>& mapa){
    std::cout<<"Mahir ima pridruzenu vrijednost: "<<mapa["Mahir"]<<std::endl;
    std::cout<<"Lejla ima pridruzenu vrijednost: "<<mapa["Lejla"]<<std::endl;
    std::cout<<"Darko ima pridruzenu vrijednost: "<<mapa["Darko"]<<std::endl;
}

int main() {
  NizMapa<string,int>mapa;
  testirajbrojElemenata(mapa);
  testirajKonstrKopijeIoperatorDodjele(mapa);
  testirajPretrazivanje(mapa);
  
  return 0;
}
