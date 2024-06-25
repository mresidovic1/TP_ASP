#include <iostream>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename tipKlj, typename tipVr> 
class Mapa {
public:
  Mapa() {}
  virtual ~Mapa() {}
  virtual tipVr &operator[](tipKlj i) = 0;
  virtual const tipVr operator[](tipKlj i) const = 0;
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

  tipVr &operator[](tipKlj kljuc) override {
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

  const tipVr operator[](tipKlj kljuc) const override {
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

template <typename tipKlj, typename tipVr>
class BinStabloMapa : public Mapa<tipKlj, tipVr> {
  struct Cvor {
    tipKlj kljuc;
    tipVr vrijednost;
    Cvor *lijevo, *desno, *roditelj;
    Cvor(tipKlj k = tipKlj(), tipVr v = tipVr()) : kljuc(k), vrijednost(v), desno(nullptr), lijevo(nullptr), roditelj(nullptr) {}
  };      

    Cvor *Stvori(tipKlj k = tipKlj(), tipVr v = tipVr()) {
      Cvor *temp = new Cvor();
      temp->kljuc = k;
      temp->vrijednost = v;
      temp->desno = nullptr;
      temp->roditelj = nullptr;
      temp->lijevo = nullptr;
      return temp;
    }

    Cvor *Pretrazi(Cvor *cvor, tipKlj k) const {
      if (cvor == nullptr || cvor->kljuc == k)
        return cvor;
      if (cvor->kljuc < k)
        return Pretrazi(cvor->desno, k);
      else if (cvor->kljuc > k)
        return Pretrazi(cvor->lijevo, k);
      return cvor;
    }

    Cvor *DodajNovi(Cvor *cvor, tipKlj k, tipVr v = tipVr(), Cvor *r = nullptr) {
      if (cvor == nullptr) {
        cvor = Stvori(k, v);
        cvor->roditelj = r;
        return cvor;
      }
      if (k > cvor->kljuc) cvor->desno = DodajNovi(cvor->desno, k, v, cvor);
      else cvor->lijevo = DodajNovi(cvor->lijevo, k, v, cvor);
      return cvor;
    }

    Cvor *Sljedeci(Cvor *cvor) {
      auto pom = cvor;
      while (pom && pom->lijevo != nullptr) pom = pom->lijevo;
      return pom;
    }

    void Inicijaliziraj(Cvor *cvor1, Cvor *cvor2) {
      if (cvor2 == nullptr)
        return;
      Inicijaliziraj(cvor1, cvor2->lijevo);
      Inicijaliziraj(cvor1, cvor2->desno);
      DodajNovi(cvor1, cvor2->kljuc, cvor2->vrijednost);
    }

    Cvor *ObrisiCvor(Cvor *cvor, tipKlj k) {
      if (cvor == nullptr)
        return cvor;
      if (k < cvor->kljuc)
        cvor->lijevo = ObrisiCvor(cvor->lijevo, k);
      else if (k > cvor->kljuc)
        cvor->desno = ObrisiCvor(cvor->desno, k);
      else {
        if (cvor->lijevo == nullptr) {
          Cvor *temp = cvor->desno;
          delete cvor;
          return temp;
        } else if (cvor->desno == nullptr) {
          Cvor *temp = cvor->lijevo;
          delete cvor;
          return temp;
        }
        auto slj = Sljedeci(cvor->desno);
        cvor->kljuc = slj->kljuc;
        cvor->vrijednost=slj->vrijednost;
        cvor->desno = ObrisiCvor(cvor->desno, slj->kljuc);
      }

      return cvor;
    }

    void ObrisiStablo(Cvor *cvor) {
      if (cvor == nullptr)
        return;
      ObrisiStablo(cvor->lijevo);
      ObrisiStablo(cvor->desno);
      delete cvor;
    }

  int br_el;
  Cvor *ccvor;

public:
  BinStabloMapa() : br_el(0), ccvor(nullptr) {}

  ~BinStabloMapa() { ObrisiStablo(ccvor); }

  BinStabloMapa(const BinStabloMapa<tipKlj, tipVr> &pom) {
    br_el = pom.br_el;
    if (pom.br_el == 0)
      ccvor = nullptr;

    else {
      ccvor = Stvori(pom.ccvor->kljuc, pom.ccvor->vrijednost);
      Inicijaliziraj(ccvor, pom.ccvor);
    }
  }

  BinStabloMapa &operator=(const BinStabloMapa<tipKlj, tipVr> &pom) {
    if (this == &pom)
      return *this;
    obrisi();
    br_el = pom.br_el;
    if (pom.br_el == 0) ccvor = nullptr;
    else {
      ccvor->vrijednost=pom.ccvor->vrijednost;  
      ccvor->kljuc=pom.ccvor->kljuc; 
      Inicijaliziraj(ccvor, pom.ccvor);
    }
    return *this;
  }

  int brojElemenata() const { return br_el; }

  void obrisi() {
    ObrisiStablo(ccvor);
    ccvor = Stvori();
    br_el = 0;
  }

  void obrisi(const tipKlj &kljuc) {
    if (ccvor->kljuc == kljuc)
      ccvor = ObrisiCvor(ccvor, kljuc);
    else ObrisiCvor(ccvor, kljuc);

      br_el--;
  }

  tipVr &operator[](tipKlj i) {
    if (ccvor == nullptr) {
      ccvor = Stvori(i);
      br_el++;
      return ccvor->vrijednost;
    }
    auto tragac = Pretrazi(ccvor, i);
    if (tragac == nullptr) {
      DodajNovi(ccvor, i);
      br_el++;
      tragac = Pretrazi(ccvor, i);
    }
    return tragac->vrijednost;
  }

  const tipVr operator[](tipKlj i) const {
    auto tragac = Pretrazi(ccvor, i);
    if (tragac != nullptr)
      return tragac->vrijednost;
    return tipVr();
  }
};


template <typename tipKlj, typename tipVr>
void testirajPerformanse(Mapa<tipKlj, tipVr> &mapa, const char *tipMape) {
    srand(static_cast<unsigned>(time(nullptr)));
    auto pocetak = chrono::high_resolution_clock::now();

    for (int i = 0; i < 10000; i++) {
        tipKlj kljuc = rand() % 100000;
        tipVr vrijednost = rand() % 100000;
        mapa[kljuc] = vrijednost;
    }

    auto kraj = chrono::high_resolution_clock::now();
    auto trajanje = chrono::duration_cast<chrono::milliseconds>(kraj - pocetak).count();
    cout << "Vrijeme dodavanja elemenata " << tipMape << ": " << trajanje << " milliseconds\n";

    pocetak = chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; i++) {
        tipKlj kljuc = rand() % 1000;
        tipVr vrijednost = mapa[kljuc];
        if (vrijednost == tipVr()) {
            cout << "Vrijednost nije pronađena!\n";
        }
    }

    kraj = chrono::high_resolution_clock::now();
    trajanje = chrono::duration_cast<chrono::milliseconds>(kraj - pocetak).count();
    cout << "Vrijeme pristupa elementu: " << tipMape << ": " << trajanje << " milliseconds\n\n";
}

int main() {
    NizMapa<int, int> nizMapa;
    BinStabloMapa<int, int> binStabloMapa;
    testirajPerformanse(nizMapa, "NizMapa");
    testirajPerformanse(binStabloMapa, "BinStabloMapa");
    return 0;
}