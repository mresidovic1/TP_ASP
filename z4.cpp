#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

template <typename tipKlj, typename tipVr> class Mapa {
public:
  Mapa() {}
  virtual ~Mapa() {}
  virtual tipVr &operator[](const tipKlj &kljuc) = 0;
  virtual tipVr operator[](const tipKlj &kljuc) const = 0;
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const tipKlj &kljuc) = 0;
};

template <typename tipKlj, typename tipVr>
class AVLStabloMapa : public Mapa<tipKlj, tipVr> {
  struct Cvor {
  public:
    tipKlj kljuc;
    tipVr vrijednost;
    int balans = 0;
    Cvor *lijevo, *desno, *roditelj;
    Cvor() : lijevo(nullptr), desno(nullptr), roditelj(nullptr) {}
    Cvor(const tipKlj &k, const tipVr &v, Cvor *l = nullptr, Cvor *d = nullptr,
         Cvor *r = nullptr)
        : kljuc(k), vrijednost(v), lijevo(l), desno(d), roditelj(r) {}
  };
  Cvor *korijen = nullptr;
  int br_el = 0;
  void Obrisii(Cvor *r) {
    if (r) {
      Obrisii(r->lijevo);
      Obrisii(r->desno);
      delete r;
    }
    korijen = nullptr;
  }

public:
  AVLStabloMapa() {}

  void rotacijaLijevo(Cvor *&cvor) {
    if (cvor->roditelj && cvor->roditelj->lijevo == cvor)
      cvor->roditelj->lijevo = cvor->desno;
    else if (cvor->roditelj)
      cvor->roditelj->desno = cvor->desno;
    Cvor *pom = cvor->desno;
    bool desno = false;
    if (cvor->desno->lijevo) {
      cvor->desno = pom->lijevo;
      pom->lijevo->roditelj = cvor;
      pom->lijevo = nullptr;
      desno = true;
    }
    pom->roditelj = cvor->roditelj;
    if (cvor->roditelj)
      cvor->roditelj = pom;
    else {
      cvor->roditelj = pom;
      korijen = pom;
    }
    pom->lijevo = cvor;
    cvor->balans = 0;
    pom->balans = 0;
    if (!desno)
      cvor->desno = nullptr;
  }

  void rotacijaDesno(Cvor *&cvor) {
    if (cvor->roditelj && cvor->roditelj->lijevo == cvor)
      cvor->roditelj->lijevo = cvor->lijevo;
    else if (cvor->roditelj)
      cvor->roditelj->desno = cvor->lijevo;
    Cvor *pom = cvor->lijevo;
    bool lijevo = false;
    if (cvor->lijevo->desno) {
      cvor->lijevo = pom->desno;
      pom->desno->roditelj = cvor;
      pom->desno = nullptr;
      lijevo = true;
    }
    pom->roditelj = cvor->roditelj;
    if (cvor->roditelj)
      cvor->roditelj = pom;
    else {
      cvor->roditelj = pom;
      korijen = pom;
    }
    pom->desno = cvor;
    cvor->balans = 0;
    pom->balans = 0;
    if (!lijevo)
      cvor->lijevo = nullptr;
  }

  void azurirajBalans(Cvor *&pom) {
    if (pom->roditelj == nullptr)
      return;
    if (!(pom->lijevo && pom->desno && pom->balans == 0)) {
      if (pom->roditelj->lijevo == pom)
        pom->roditelj->balans++;
      else
        pom->roditelj->balans--;
    }
    bool dalje = true;
    Cvor *s = pom->roditelj;
    if (pom->roditelj->balans < -1) {
      rotacijaLijevo(s);
      dalje = false;
    } else if (pom->roditelj->balans > 1) {
      rotacijaDesno(s);
      dalje = false;
    }
    if (dalje)
      azurirajBalans(pom->roditelj);
  }

  void Umetni(Cvor *&pom) {
    Cvor *lft = nullptr;
    Cvor *rgt = korijen;
    while (rgt != nullptr) {
      lft = rgt;
      if (pom->kljuc < rgt->kljuc)
        rgt = rgt->lijevo;
      else
        rgt = rgt->desno;
    }
    bool hr = false;
    if (lft == nullptr) {
      korijen = pom;
      hr = true;
    } else {
      if (pom->kljuc < lft->kljuc) {
        lft->lijevo = pom;
        pom->roditelj = lft;
        if (lft->desno) {
          hr = true;
          lft->balans = 0;
        }
      } else {
        lft->desno = pom;
        pom->roditelj = lft;
        if (lft->lijevo) {
          hr = true;
          lft->balans = 0;
        }
      }
    }
    if (!hr)
      azurirajBalans(pom);
    br_el++;
  }
  tipVr &dodaj(tipKlj &pom) {
    Cvor*novi=new Cvor(pom,tipVr{});
        Umetni(novi);
        return novi->vrijednost;
  }
  void Preorder(Cvor *&r) {
    if (r != nullptr) {
    dodaj(r->kljuc)=r->vrijednost;
      Preorder(r->lijevo);
      Preorder(r->desno);
    }
  }

  void Preorder() { Preorder(korijen); }

  AVLStabloMapa(const AVLStabloMapa<tipKlj, tipVr> &drugi) {
    Cvor *pom = drugi.korijen;
    Preorder(pom);
  }

  AVLStabloMapa &operator=(const AVLStabloMapa<tipKlj, tipVr> &drugi) {
    if (this == &drugi)
      return *this;
    obrisi();
    korijen = nullptr;
    Cvor *novi = drugi.korijen;
    Preorder(novi);
    return *this;
  }

  ~AVLStabloMapa() { Obrisii(korijen); }

  tipVr &operator[](const tipKlj &kljuc) {
    Cvor *pom = korijen;
    while (pom != nullptr && kljuc != pom->kljuc) {
      if (kljuc < pom->kljuc)
        pom = pom->lijevo;
      else
        pom = pom->desno;
    }
    if (pom != nullptr)
      return pom->vrijednost;
    Cvor *novi = new Cvor{kljuc, tipVr{}};
    Umetni(novi);
    return novi->vrijednost;
  }
  tipVr operator[](const tipKlj &kljuc) const {
    Cvor *pom = korijen;
    while (pom != nullptr && kljuc != pom->kljuc) {
      if (kljuc < pom->kljuc)
        pom = pom->lijevo;
      else
        pom = pom->desno;
    }
    if (pom != nullptr)
      return pom->vrijednost;
    return tipVr{};
  }
  int brojElemenata() const { return br_el; }
  void obrisi() {
    Obrisii(korijen);
    br_el = 0;
  }
  void obrisi(const tipKlj &kljuc) {
    Cvor *k = korijen;
    Cvor *roditelj = nullptr, *lft = nullptr, *rgt = nullptr, *pom = nullptr;
    while (k != nullptr && kljuc != k->kljuc) {
      roditelj = k;
      if (kljuc < k->kljuc)
        k = k->lijevo;
      else
        k = k->desno;
    }
    if (k == nullptr)
      return;
    if (k->lijevo == nullptr)
      lft = k->desno;
    else if (k->desno == nullptr)
      lft = k->lijevo;
    else {
      rgt = k;
      lft = k->lijevo;
      pom = lft->desno;
      while (pom != nullptr) {
        rgt = lft;
        lft = pom;
        pom = lft->desno;
      }
      if (rgt != k) {
        rgt->desno = lft->lijevo;
        lft->lijevo = k->lijevo;
        rgt->roditelj = lft;
        lft->roditelj = roditelj;
        if (rgt->desno)
          rgt->desno->roditelj = rgt;
      }
      lft->desno = k->desno;
      k->desno->roditelj = lft;
    }
    if (roditelj == nullptr) {
      korijen = lft;
      if (korijen)
        korijen->roditelj = nullptr;
    } else if (k == roditelj->lijevo) {
      roditelj->lijevo = lft;
      if (lft)
        lft->roditelj = roditelj;
    } else {
      roditelj->desno = lft;
      if (lft)
        lft->roditelj = roditelj;
    }
    if (k->roditelj && k->roditelj->lijevo == k)
      k->roditelj->balans--;
    else if (k->roditelj)
      k->roditelj->balans++;
    delete k;
    br_el--;
  }
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
void testirajAVLStabloPerformanse(int vel) {
  AVLStabloMapa<tipKlj, tipVr> avlStabloMapa;
  srand(time(0));
  for (int i = 0; i < vel; ++i) {
    tipKlj kljuc = rand();
    tipVr vrijednost = rand();
    avlStabloMapa[kljuc] = vrijednost;
  }
  auto pocetak = std::chrono::high_resolution_clock::now();
  auto kraj = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> trajanje = kraj - pocetak;
  std::cout << "Vrijeme za dodavanje " << vel
            << " elemenata u AVL stablo: " << trajanje.count() << " s\n";
}

int main() {
  AVLStabloMapa<int, int> avl;
  avl[3] = 3;
  avl[5] = 5;
  avl[8] = 8;
  avl[10] = 10;
  avl[9] = 9;
  avl[11] = 11;
  avl.Preorder();
  std::cout << endl;
  return 0;
}