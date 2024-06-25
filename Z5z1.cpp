#include <iostream>
#include <exception>
#include <queue>
#include <vector>

using namespace std;
const float konst = 9999999;

template <typename tip> class UsmjereniGraf;
template <typename tip> class Grana;
template <typename tip> class Cvor;
template <typename tip> class GranaIterator;

template <typename tip>
class UsmjereniGraf {
public:
    UsmjereniGraf(int) {}
    virtual ~UsmjereniGraf() {}
    virtual void postaviBrojCvorova(int) = 0;
    virtual void postaviTezinuGrane(int, int, double) = 0;
    virtual void postaviOznakuCvora(int, tip) = 0;
    virtual void postaviOznakuGrane(int, int, tip) = 0;
    virtual void dodajGranu(int, int, double) = 0;
    virtual void obrisiGranu(int, int) = 0;
    virtual int dajBrojCvorova() const = 0;
    virtual double dajTezinuGrane(int, int)  = 0;
    virtual tip dajOznakuCvora(int)  = 0;
    virtual tip dajOznakuGrane(int, int)  = 0;
    virtual GranaIterator<tip> dajGranePocetak() = 0;
    virtual GranaIterator<tip> dajGraneKraj() = 0;
    virtual GranaIterator<tip> dajSljedecuGranu(int, int) = 0;
    virtual bool postojiGrana(int, int) = 0;
    Cvor<tip> dajCvor(int cvor) {
        return Cvor<tip>(this, cvor);
    }
    Grana<tip> dajGranu(int poz, int klj) {
        return Grana<tip>(this, poz, klj);
    }
};

template <typename tip>
class Grana {
    int pocetak, kraj;
    bool postojiGrana;
    UsmjereniGraf<tip> *usmjereniGraf;

public:
    Grana(UsmjereniGraf<tip> *usmjereniGraf, int poc, int kr) : pocetak(poc), kraj(kr), usmjereniGraf(usmjereniGraf) {}

    Cvor<tip> dajPolazniCvor() {
       return usmjereniGraf -> dajCvor(pocetak);
    }
    Cvor<tip> dajDolazniCvor() {
        return usmjereniGraf -> dajCvor(kraj);
    }

    tip dajOznaku() const {
        return usmjereniGraf -> dajOznakuGrane(pocetak, kraj);
    }
    double dajTezinu() const {
        return usmjereniGraf -> dajTezinuGrane(pocetak, kraj);
    }

    void postaviOznaku(tip oznaka) {
        usmjereniGraf -> postaviOznakuGrane(pocetak, kraj, oznaka);
    }
    void postaviTezinu(double tezina) {
        usmjereniGraf -> postaviTezinuGrane(pocetak, kraj, tezina);
    } 
};


template <typename tip>
class Cvor {
    int redniBr;
    UsmjereniGraf<tip> *usmjereniGraf;

public:
    Cvor(UsmjereniGraf<tip> *usmjereniGraf, int redniBr) : usmjereniGraf(usmjereniGraf), redniBr(redniBr) {}

    void postaviOznaku(tip oznaka) {
        usmjereniGraf -> postaviOznakuCvora(redniBr, oznaka);
    }

    tip dajOznaku() const {
        return usmjereniGraf -> dajOznakuCvora(redniBr);
    }

    int dajRedniBroj() const {
        return redniBr;
    }
};

template <typename tip>
class GranaIterator {
    int polazniCvor, dolazniCvor;
    UsmjereniGraf<tip> *usmjereniGraf;
public:
    GranaIterator(UsmjereniGraf<tip> *usmjereniGr, int poc, int kr) {
        usmjereniGraf = usmjereniGr;
        polazniCvor = poc;
        dolazniCvor = kr;
    }
    GranaIterator &operator ++() {
        if(polazniCvor == -1 && dolazniCvor == -1)  throw std::logic_error("Vratite se u domen!");
        GranaIterator<tip> it = usmjereniGraf -> dajSljedecuGranu(polazniCvor, dolazniCvor);
        polazniCvor = it.polazniCvor;
        dolazniCvor = it.dolazniCvor;
        return *this;
    }
    GranaIterator operator ++(int) {
        GranaIterator pom = *this;
        ++*this;
        return pom;
    }
    bool operator !=(GranaIterator it) {
        return !(it == *this);
    }
    bool operator !=(const GranaIterator &it) const {
        return !(it == *this);
    }
    bool operator ==(const GranaIterator &it) const {
        return (usmjereniGraf == it.usmjereniGraf && polazniCvor == it.polazniCvor && dolazniCvor == it.dolazniCvor);
    }
    Grana<tip> operator *() {
        return Grana<tip>(usmjereniGraf, polazniCvor, dolazniCvor);
    }
};


template <typename tip>
class ListaGraf : public UsmjereniGraf<tip> {
    struct Cvor {
        tip oznaka;
        double tezina;
        bool postojiGrana;
    };

    std::vector<tip> oznake;
    std::vector<std::vector<Cvor>> tezineOznake;

public:

    void postaviOznakuCvora(int cvor, tip o) override {
        oznake[cvor] = o;
    }
    void postaviOznakuGrane(int p, int k, tip o) override {
        tezineOznake[p][k].oznaka = o;
    }

    ListaGraf(int brojCv) : UsmjereniGraf<tip>(brojCv) {
        postaviBrojCvorova(brojCv);
    }

    int dajBrojCvorova() const override {
        return tezineOznake.size();
    }

    tip dajOznakuCvora(int cvor) override {
        return oznake[cvor];
    }
    tip dajOznakuGrane(int p, int k) override  {
        return tezineOznake[p][k].oznaka;
    }

    void postaviBrojCvorova(int brojCv) override  {
        Cvor pom;
        pom.postojiGrana = false;
        for(int i = 0; i < tezineOznake.size(); i++) {
            tezineOznake[i].resize(brojCv, pom);
        }
        std::vector<Cvor> noviRed(brojCv, pom);
        oznake.resize(brojCv);
        tezineOznake.resize(brojCv, noviRed);
    }

    void dodajGranu(int poc, int kr, double tez) override {
        Cvor pom;
        pom.tezina = tez;
        pom.postojiGrana = true;
        tezineOznake[poc][kr] = pom;
    }

    void obrisiGranu(int poc, int kr) override {
        tezineOznake[poc][kr].postojiGrana = false;
    }

    void postaviTezinuGrane(int poc, int kr, double tez) override{
        tezineOznake[poc][kr].tezina = tez;
    }

    bool postojiGrana(int poc, int kr) override{
        return tezineOznake[poc][kr].postojiGrana;
    }

    double dajTezinuGrane(int poc, int kr) override {
        return tezineOznake[poc][kr].tezina;
    }

    GranaIterator<tip> dajGranePocetak() override {
        GranaIterator<tip> it(this, 0, -1);
        ++it;
        return it;
    }
    GranaIterator<tip> dajGraneKraj() override {
        GranaIterator<tip> it(this, -1, -1);
        return it;
    }
    GranaIterator<tip> dajSljedecuGranu(int poc, int kr) override {
        for(int i = poc; i < tezineOznake.size(); i++)  {
            for(int j = 0; j < tezineOznake.size(); j++) {
                if(i == poc && j <= kr) continue;
                if(tezineOznake[i][j].postojiGrana)
                    return GranaIterator<tip>(this, i, j);
            }
        }
        return GranaIterator<tip>(this, -1, -1);
    }
};

template <typename tip>
void dfs(UsmjereniGraf<tip> *usmjereniGraf, std::vector<Cvor<tip>> &obilazak, Cvor<tip> cvor) {
    bool posjecen = false; 
    for(int i = 0; i < obilazak.size(); i++) {
        if(cvor.dajRedniBroj() == obilazak[i].dajRedniBroj()) {
            posjecen = true; break;
        }
    }
    if(!posjecen)
        obilazak.push_back(cvor);
    int brojCvorova = usmjereniGraf -> dajBrojCvorova();
    for(int i = 0; i < brojCvorova; i++) {
        if(usmjereniGraf -> postojiGrana(cvor.dajRedniBroj(), i) && !posjecen) 
            if(!posjecen)
                dfs(usmjereniGraf, obilazak, usmjereniGraf -> dajCvor(i));
    }
}

template <typename tip>
void bfs(UsmjereniGraf<tip> *usmjereniGraf, std::vector<Cvor<tip>> &obilazak, Cvor<tip> cvor) {
    bool posjecen = false; 
    for(int i = 0; i < obilazak.size(); i++) {
        if(cvor.dajRedniBroj() == obilazak[i].dajRedniBroj()) {
            posjecen = true; break;
        }
    }
    if(!posjecen)
        obilazak.push_back(cvor);
    int brojCvorova = usmjereniGraf -> dajBrojCvorova();
    for(int i = 0; i < brojCvorova; i++) {
        if(!posjecen)
            bfs(usmjereniGraf, obilazak, usmjereniGraf -> dajCvor(i));
    }
}

template <typename tipKlj, typename tipVr> class Mapa {
public:
  Mapa() {}
  virtual ~Mapa() {}
  virtual tipVr &operator[](tipKlj i) = 0;
  virtual tipVr operator[](tipKlj i) const = 0;
  virtual int brojElemenata() const = 0;
  virtual void obrisi() = 0;
  virtual void obrisi(const tipKlj &kljuc) = 0;
};


template <typename tipKlj, typename tipVr>
class HashMapaLan : public Mapa<tipKlj, tipVr> {
  std::pair<tipKlj, tipVr> *par;
  int vel;
  int kap;
  unsigned int (*hashFunkcija)(tipKlj, unsigned int) = nullptr;
  void kopirajMapu(const HashMapaLan<tipKlj, tipVr> &mapa) {
    par = new std::pair<tipKlj, tipVr>[mapa.kap];
    for (int i = 0; i < mapa.kap; i++) {
      par[i] = mapa.par[i];
    }
    kap = mapa.kap;
    vel = mapa.vel;
    hashFunkcija = mapa.hashFunkcija;
  }

public:
  HashMapaLan() : par(nullptr), kap(10000), vel(0), hashFunkcija(nullptr) {}
  ~HashMapaLan() {
    delete[] par;
    vel = 0;
    kap = 10000;
  }
  HashMapaLan(const HashMapaLan &pom) { kopirajMapu(pom); }
  HashMapaLan &operator=(const HashMapaLan &pom) {
    if (&pom == this)
      return *this;
    else {
      delete[] par;
      par = nullptr;
      kopirajMapu(pom);
      return *this;
    }
  }
  int brojElemenata() const override { return vel; }
  void definisiHashFunkciju(unsigned int (*hashF)(tipKlj, unsigned int pom)) {
    hashFunkcija = hashF;
  }
  void obrisi() override {
    vel = 0;
    kap = 10000;
    delete[] par;
  }
  void obrisi(const tipKlj &kljuc) override {
    if (vel == 0)
      return;
    unsigned int hash = hashFunkcija(kljuc, kap);
    int poz = vel;
    if (par[hash].first == kljuc)
      poz = hash;
    else {
      for (int i = 0; i < kap; i++) {
        if (i != hash && par[i].first == kljuc) {
          poz = i;
          break;
        }
      }
    }
    if (poz == vel)
      return;
    par[poz].first = tipKlj();
    par[poz].second = tipVr();
    vel--;
  }
  tipVr operator[](tipKlj kljuc) const override {
    unsigned int hash = hashFunkcija(kljuc, kap);
    if (par[hash].first == kljuc)
      return par[kap].second;
    for (int i = hash + 1; i < vel; i++) {
      if (par[i].first == kljuc)
        return par[i].second;
    }
    for (int i = 0; i < hash; i++) {
      if (par[i].first == kljuc)
        return par[i].second;
    }
    return tipVr();
  }
  tipVr &operator[](tipKlj kljuc) override {
    if (hashFunkcija == nullptr)
      throw std::logic_error("Hash funkcija nije definisana!");

    unsigned int hash = hashFunkcija(kljuc, kap);
    if (vel == 0) {
      par = new std::pair<tipKlj, tipVr>[kap];
      par[hash].first = kljuc;
      par[hash].second = tipVr();
      vel++;
      for (int i = 0; i < kap; i++) {
        if (i != hash)
          par[i].first = tipKlj();
      }
      return par[hash].second;
    } else {
      if (par[hash].first == kljuc)
        return par[hash].second;
      for (int i = hash + 1; i < kap; i++) {
        if (par[i].first == kljuc)
          return par[i].second;
      }
      for (int i = 0; i < hash; i++) {
        if (par[i].first == kljuc)
          return par[i].second;
      }
      for (int i = 0; i < kap; i++) {
        if (i != hash && par[i].first == tipKlj()) {
          par[i].first = kljuc;
          par[i].second = tipVr();
          vel++;
          return par[i].second;
        }
      }
      if (vel == kap) {
        kap *= 2;
        std::pair<tipKlj, tipVr> *pom = new std::pair<tipKlj, tipVr>[kap];
        for (int i = 0; i < vel; i++) {
          pom[i].first = par[i].first;
          pom[i].second = par[i].second;
        }
        delete[] par;
        par = pom;
        pom = nullptr;
      }
      par[vel].first = kljuc;
      par[vel].second = tipVr();
      vel++;
      return par[vel - 1].second;
    }
  }
};


int main() {
    ListaGraf<int> graf(6);
    graf.dodajGranu(0, 1, 1);
    graf.dodajGranu(0, 2, 1);
    graf.dodajGranu(1, 3, 1);
    graf.dodajGranu(1, 4, 1);
    graf.dodajGranu(2, 5, 1);
    std::cout << "Graf:" << std::endl;
    for (int i = 0; i < graf.dajBrojCvorova(); i++) {
        std::cout << "Cvor " << i << ": ";
        auto it = graf.dajGranePocetak();
        while (it != graf.dajGraneKraj()) {
            auto grana = *it;
            if (grana.dajPolazniCvor().dajRedniBroj() == i) {
                std::cout << grana.dajDolazniCvor().dajRedniBroj() << " ";
            }
            ++it;
        }
        std::cout << std::endl;
    }
    std::cout << "BFS obilazak: ";
    std::vector<Cvor<int>> bfsObilazak;
    bfs(&graf, bfsObilazak, graf.dajCvor(0));
    for (const auto& cvor : bfsObilazak) {
        std::cout << cvor.dajRedniBroj() << " ";
    }
    std::cout << std::endl;
    std::cout << "DFS obilazak: ";
    std::vector<Cvor<int>> dfsObilazak;
    dfs(&graf, dfsObilazak, graf.dajCvor(0));
    for (const auto& cvor : dfsObilazak) {
        std::cout << cvor.dajRedniBroj() << " ";
    }
    std::cout << std::endl;
  return 0;
}