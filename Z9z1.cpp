#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <iostream>
using namespace std;

template <typename tipKlj, typename tipVr> class Mapa {
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

  NizMapa(const NizMapa &pom)
      : kapacitet(pom.kapacitet), brElemenata(pom.brElemenata) {
    niz = new std::pair<tipKlj, tipVr>[kapacitet];
    for (int i = 0; i < brElemenata; i++) {
      niz[i] = pom.niz[i];
    }
  }

  NizMapa &operator=(const NizMapa &pom) {
    if (this == &pom)
      return *this;
    else {
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
      std::pair<tipKlj, tipVr> *noviNiz =
          new std::pair<tipKlj, tipVr>[kapacitet];
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
    Cvor(tipKlj k = tipKlj(), tipVr v = tipVr())
        : kljuc(k), vrijednost(v), desno(nullptr), lijevo(nullptr),
          roditelj(nullptr) {}
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
    if (k > cvor->kljuc)
      cvor->desno = DodajNovi(cvor->desno, k, v, cvor);
    else
      cvor->lijevo = DodajNovi(cvor->lijevo, k, v, cvor);
    return cvor;
  }

  Cvor *Sljedeci(Cvor *cvor) {
    auto pom = cvor;
    while (pom && pom->lijevo != nullptr)
      pom = pom->lijevo;
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
      cvor->vrijednost = slj->vrijednost;
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
    if (pom.br_el == 0)
      ccvor = nullptr;
    else {
      ccvor->vrijednost = pom.ccvor->vrijednost;
      ccvor->kljuc = pom.ccvor->kljuc;
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
    else
      ObrisiCvor(ccvor, kljuc);

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
class HashMapa : public Mapa<tipKlj, tipVr> {
protected:
  int kapacitet, br_el;
  bool *ispunjeno;
  std::pair<tipKlj, tipVr> **par;
  unsigned int (*funkcija)(tipKlj, unsigned int);
  void Prosiri(int rez = 10000) {
    std::pair<tipKlj, tipVr> **pom =
        new std::pair<tipKlj, tipVr> *[rez + kapacitet]();
    bool *k = new bool[rez + kapacitet]();

    for (int i = 0; i < kapacitet; i++) {
      if (par[i])
        pom[i] = new std::pair<tipKlj, tipVr>(*par[i]);
      delete par[i];
      k[i] = ispunjeno[i];
    }
    for (int i = 0; i < rez; i++)
      k[kapacitet + i] = false;

    kapacitet += rez;
    par = pom;
    ispunjeno = k;
    delete[] par;
    delete[] ispunjeno;
  }

public:
  ~HashMapa<tipKlj, tipVr>() {
    if (par) {
      for (int i = 0; i < kapacitet; i++)
        delete par[i];
      delete[] par;
    }

    if (ispunjeno)
      delete[] ispunjeno;
  }

  HashMapa()
      : par(new std::pair<tipKlj, tipVr> *[100000]()), kapacitet(100000),
        br_el(0), ispunjeno(new bool[100000]), funkcija(nullptr) {
    for (int i = 0; i < 100000; i++)
      ispunjeno[i] = false;
  }

  HashMapa<tipKlj, tipVr>(const HashMapa<tipKlj, tipVr> &pom) {

    br_el = pom.br_el;
    kapacitet = pom.kapacitet;
    funkcija = pom.funkcija;
    ispunjeno = new bool[kapacitet];

    if (pom.kapacitet == 0) {
      par = nullptr;
      for (int i = 0; i < kapacitet; i++)
        ispunjeno[i] = false;
    }

    else {
      par = new std::pair<tipKlj, tipVr> *[kapacitet]();

      for (int i = 0; i < pom.kapacitet; i++) {
        if (pom.par[i])
          par[i] = new std::pair<tipKlj, tipVr>(*pom.par[i]);
        ispunjeno[i] = pom.ispunjeno[i];
      }
    }
  }

  HashMapa<tipKlj, tipVr> &operator=(const HashMapa<tipKlj, tipVr> &pom) {

    if (this == &pom)
      return *this;

    if (pom.Kapacitet() > Kapacitet())
      Prosiri(pom.kapacitet);

    for (int i = 0; i < Kapacitet(); i++)
      ispunjeno[i] = false;

    br_el = pom.br_el;
    funkcija = pom.funkcija;

    for (int i = 0; i < pom.kapacitet; i++) {
      if (pom.par[i]) {
        delete par[i];
        par[i] = new std::pair<tipKlj, tipVr>(*pom.par[i]);
      }
      ispunjeno[i] = pom.ispunjeno[i];
    }

    return *this;
  }

  void obrisi() {
    if (br_el == 0)
      throw std::logic_error("Prazna mapa!");
    for (int i = 0; i < kapacitet; i++)
      ispunjeno[i] = false;
    br_el = 0;
  }

  void obrisi(const tipKlj &kljuc) {
    for (int i = 0; i < kapacitet; i++)
      if (par[i] && par[i]->first == kljuc) {
        ispunjeno[i] = false;
        br_el--;
        return;
      }
  }

  int brojElemenata() const { return br_el; }
  int Kapacitet() const { return kapacitet; }

  bool UmetniHash(const tipKlj &k) {
    int j, i = 1;
    do {
      do {
        j = funkcija(k, i);
        if (ispunjeno[j] == false) {
          delete par[j];
          par[j] = new std::pair<tipKlj, tipVr>(k, tipVr());
          ispunjeno[j] = true;
          return true;
        } else
          i++;
      } while (i < kapacitet);
      Prosiri();
    } while (kapacitet < 100000);
    return false;
  }

  int TraziHash(const tipKlj &k) const {
    int indeks, i(1);
    do {
      indeks = funkcija(k, i);
      if (ispunjeno[indeks] && par[indeks]->first == k)
        return indeks;
      else
        i = i + 1;
    } while ((ispunjeno[indeks] == true && i != kapacitet) ||
             ispunjeno[funkcija(k, i)] == true);

    return -1;
  }

  tipVr &operator[](tipKlj kljuc) {

    if (!funkcija)
      throw std::logic_error("Nije definisana funkcija heširanja!");

    if (br_el == kapacitet)
      Prosiri();

    int in = funkcija(kljuc, kapacitet);
    if (!ispunjeno[in]) {
      delete par[in];
      par[in] = new std::pair<tipKlj, tipVr>(kljuc, tipVr());
      br_el++;
      ispunjeno[in] = true;
      return par[in]->second;
    }
    if (ispunjeno[in] && par[in]->first == kljuc)
      return par[in]->second;
    else {
      in = TraziHash(kljuc);
      if (in == -1) {
        UmetniHash(kljuc);
        br_el++;
        in = TraziHash(kljuc);
        ispunjeno[in] = true;
      }
    }

    return par[in]->second;
  }

  const tipVr operator[](tipKlj kljuc) const {

    if (!funkcija)
      throw std::logic_error("Nije definisana funkcija heširanja!");

    int in = funkcija(kljuc, kapacitet);
    if (ispunjeno[in] && par[in]->first == kljuc)
      return par[in]->second;
    else {
      in = TraziHash(kljuc);
      if (in == -1)
        return tipVr();
    }

    return par[in]->second;
  }

  void definisiHashFunkciju(unsigned int (*func)(tipKlj, unsigned int)) {
    funkcija = func;
    return;
  }
};

void testirajHashMapu() {
  HashMapa<int, int> mapa;

  unsigned int (*hashFunkcija)(int, unsigned int) =
      [](int key, unsigned int size) { return key % size; };

  mapa.definisiHashFunkciju(hashFunkcija);

  mapa[1] = 10;
  mapa[2] = 20;
  mapa[3] = 30;

  std::cout << "Vrijednost za ključ 1: " << mapa[1] << std::endl;
  std::cout << "Vrijednost za ključ 2: " << mapa[2] << std::endl;
  std::cout << "Vrijednost za ključ 3: " << mapa[3] << std::endl;

  mapa[2] = 25;
  std::cout << "Nova vrijednost za ključ 2: " << mapa[2] << std::endl;

  mapa.obrisi(1);
  std::cout << "Broj elemenata nakon brisanja: " << mapa.brojElemenata()
            << std::endl;
  std::cout << "Vrijednost za ključ 1 nakon brisanja: " << mapa[1] << std::endl;

  mapa.obrisi();
  std::cout << "Broj elemenata nakon brisanja: " << mapa.brojElemenata()
            << std::endl;

  std::cout << "Bravo!" << std::endl;
}


int main() {
  testirajHashMapu();
  return 0;
}