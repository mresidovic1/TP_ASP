#include <iostream>
#include <string>
using namespace std;

template <typename tip> class Lista {
public:
  Lista(){};
  virtual ~Lista(){};
  virtual int brojElemenata() const = 0;
  virtual tip trenutni() const = 0;
  virtual tip &trenutni() = 0;
  virtual bool prethodni() = 0;
  virtual bool sljedeci() = 0;
  virtual void pocetak() = 0;
  virtual void kraj() = 0;
  virtual void obrisi() = 0;
  virtual void dodajIspred(const tip &el) = 0;
  virtual void dodajIza(const tip &el) = 0;
  virtual tip &operator[](int i) const = 0;
};

template <typename tip> struct Cvor {
  tip element;
  Cvor *prethodni;
  Cvor *veza;
  Cvor(const tip &el, Cvor *prethodni, Cvor *veza = nullptr)
      : element(el), prethodni(prethodni), veza(veza) {
    if (prethodni != nullptr)
      prethodni->veza = this;
    if (veza != nullptr)
      veza->prethodni = this;
  }
  Cvor(Cvor *prethodni = 0, Cvor *veza = 0) : prethodni(prethodni), veza(veza) {
    if (prethodni != nullptr)
      prethodni->veza = this;
    if (veza != nullptr)
      veza->prethodni = this;
  }
};

template <typename tip> class DvostrukaLista : public Lista<tip> {
  Cvor<tip> *prvi;
  Cvor<tip> *zadnji;
  Cvor<tip> *tekuci;
  template <typename Tip> friend class Iterator;
  int l_vel;
  int d_vel;
  void obrisi_sve() {
    while (prvi != nullptr) {
      tekuci = prvi;
      prvi = prvi->veza;
      delete tekuci;
    }
    d_vel = 0;
    l_vel = 0;
    prvi = nullptr;
    zadnji = nullptr;
    tekuci = nullptr;
  }
  void inicijaliziraj() {
    tekuci = prvi = new Cvor<tip>(0, 0);
    prvi->veza = zadnji = new Cvor<tip>(prvi, 0);
    l_vel = d_vel = 0;
  }

public:
  DvostrukaLista()
      : l_vel(0), d_vel(0), prvi(nullptr), zadnji(nullptr), tekuci(nullptr) {}
  ~DvostrukaLista() { obrisi_sve(); }
  DvostrukaLista(const DvostrukaLista &pom)
      : prvi(nullptr), zadnji(nullptr), l_vel(0), d_vel(0) {
    Cvor<tip> *temp(pom.prvi);
    if (prvi)
      pocetak();
    while (temp != nullptr) {
      dodajIza(temp->element);
      sljedeci();
      temp = temp->veza;
      zadnji = tekuci;
    }
  }
  DvostrukaLista &operator=(const DvostrukaLista &pom) {
    if (&pom == this)
      return *this;
    obrisi_sve();
    Cvor<tip> *temp(pom.prvi);
    while (temp != nullptr) {
      dodajIza(temp->element);
      sljedeci();
      temp = temp->veza;
      zadnji = tekuci;
    }
    return *this;
  }
  void obrisi() override {
    if (d_vel == 0)
      throw std::logic_error("Lista je prazna!");
    else if (brojElemenata() == 1) {
      delete tekuci;
      prvi = zadnji = tekuci = nullptr;
      l_vel = d_vel = 0;
      return;
    } else {
      Cvor<tip> *pom = tekuci;
      if (tekuci == zadnji) {
        prethodni();
        zadnji = tekuci;
        zadnji->veza = nullptr;
        delete pom;
        d_vel--;
      } else if (tekuci == prvi) {
        prvi = prvi->veza;
        delete tekuci;
        tekuci = prvi;
        l_vel--;
        if (l_vel == 0)
          zadnji = nullptr;
      } else {
        sljedeci();
        pom->prethodni->veza = tekuci;
        tekuci->prethodni = pom->prethodni;
        delete pom;
        l_vel--;
      }
    }
  }
  int brojElemenata() const override { return l_vel + d_vel; }
  tip trenutni() const override { return tekuci->element; }
  tip &trenutni() override { return tekuci->element; }
  bool prethodni() override {
    if (tekuci == prvi) {
      return false;
    }
    tekuci = tekuci->prethodni;
    l_vel--;
    d_vel++;
    return true;
  }
  bool sljedeci() override {
    if (tekuci == zadnji) {
      return false;
    }
    tekuci = tekuci->veza;
    l_vel++;
    d_vel--;
    return true;
  }
  void pocetak() override {
    tekuci = prvi;
    d_vel += l_vel;
    l_vel = 0;
  }
  void kraj() override {
    tekuci = zadnji;
    l_vel += d_vel;
    d_vel = 0;
  }
  void dodajIspred(const tip &el) override {
    if (d_vel == 0) {
      prvi = new Cvor<tip>(el, nullptr, nullptr);
      tekuci = zadnji = prvi;
      d_vel++;
    } else {
      new Cvor<tip>(el, tekuci->prethodni, tekuci);
      if (prvi == tekuci) {
        prvi = tekuci->prethodni;
      }
      l_vel++;
    }
  }
  void dodajIza(const tip &el) override {
    if (d_vel == 0) {
      prvi = new Cvor<tip>(el, nullptr, nullptr);
      tekuci = zadnji = prvi;
      d_vel++;
    } else {
      new Cvor<tip>(el, tekuci, tekuci->veza);
      if (zadnji == tekuci) {
        zadnji = tekuci->veza;
      }
      d_vel++;
    }
  }
  tip &operator[](int i) const override {
    if (i < 0 || i >= brojElemenata())
      throw std::domain_error(
          "Lista pristupa indeksu na nedozvoljenoj lokaciji");
    Cvor<tip> *pom = prvi;
    int k = i;
    if (abs(i - l_vel) < k) {
      pom = tekuci;
      k = i - l_vel;
    }
    if (abs(i - brojElemenata()) < k) {
      pom = zadnji;
      k = brojElemenata();
    }
    if (k < 0) {
      for (int j = 0; j < abs(k); j++) {
        pom = pom->prethodni;
      }
    } else if (k > 0) {
      for (int j = 0; j < k; j++) {
        pom = pom->veza;
      }
    }
    return pom->element;
  }
};

template <typename tip> class Iterator {
  const DvostrukaLista<tip> *l;
  Cvor<tip> *trenutni;

public:
  Iterator(const DvostrukaLista<tip> &pom) {
    l = &pom;
    trenutni = (pom.brojElemenata() > 0) ? pom.prvi : nullptr;
  }
  tip Trenutni() {
    if (l->brojElemenata() == 0)
      throw std::logic_error("Prazna lista!");
    return trenutni->element;
  }
  bool Sljedeci() {
    if (l->brojElemenata() == 0)
      throw std::logic_error("Prazna lista!");
    if (trenutni->veza == nullptr)
      return false;
    trenutni = trenutni->veza;
    return true;
  }
};

template <typename Tip> Tip dajMaksimum(const Lista<Tip> &n) {
  if (n.brojElemenata() == 0)
    throw std::logic_error("Prazna lista!");
  Iterator<Tip> it = dynamic_cast<const DvostrukaLista<Tip> &>(n);
  Tip najveci = it.Trenutni();
  while (it.Sljedeci()) {
    if (it.Trenutni() > najveci)
      najveci = it.Trenutni();
  }
  return najveci;
}

//***
// TESTOVI
//***

template <typename tip> void testirajBrojElemenata(DvostrukaLista<tip> &lista) {
  for (int i = 0; i < 15; i++) {
    lista.dodajIspred(i);
  }
  std::cout << "Broj elemenata bi trebao biti 15 i zaista je: "
            << lista.brojElemenata() << std::endl;
}

template <typename tip> void testirajTrenutni(DvostrukaLista<tip> &lista) {
  for (int k = 0; k < 3; k++) {
    lista.dodajIspred(k);
    lista.dodajIza(k - 1);
  }
  std::cout << "Trenutni element je: " << lista.trenutni() << std::endl;
}

template <typename tip> void testirajPrethodni(DvostrukaLista<tip> &lista) {
  int brojac = 0;
  while (1) {
    lista.dodajIspred(3);
    if (brojac == lista.trenutni())
      break;
  }
  std::cout << "Prethodni element je: " << lista.prethodni() << std::endl;
}

template <typename tip> void testirajSljedeci(DvostrukaLista<tip> &lista) {
  std::cout << "Sljedeci element u listi je: " << lista.sljedeci() << std::endl;
}

template <typename tip> void testirajPocetak(DvostrukaLista<tip> &lista) {
  lista.pocetak();
  std::cout << "Pocetni element je: " << lista.trenutni() << std::endl;
}

template <typename tip> void testirajKraj(DvostrukaLista<tip> &lista) {
  lista.kraj();
  std::cout << "Zadnji element u listi je: " << lista.trenutni() << std::endl;
}

template <typename tip> void testirajObrisi(DvostrukaLista<tip> &lista) {
  lista.obrisi();
  std::cout << "Uspjesno obrisano! "<< std::endl;
}

template <typename tip> void testirajDodajIspred(DvostrukaLista<tip> &lista) {
    lista.obrisi();
    int br_el=lista.brojElemenata();
  lista.dodajIspred(5);
  lista.dodajIspred(10);
  lista.dodajIspred(15);
  std::cout << "Da li su uspjesno dodani elementi? " << std::endl;
  if (lista.brojElemenata() == br_el+3)
    std::cout << "Jesu!" << std::endl;
}

template <typename tip> void testirajDodajIza(Lista<tip> &lista) {
  lista.obrisi();
  int br_el=lista.brojElemenata();
  lista.dodajIza(1);
  lista.dodajIza(3);
  lista.dodajIza(5);
  std::cout << "Da li su uspjesno dodani elementi? " << std::endl;
  if (lista.brojElemenata()==br_el+3)
    std::cout << "Jesu!" << std::endl;
}

template <typename tip> void testirajOperator(Lista<tip> &lista) {
  for (int i = 0; i < lista.brojElemenata(); i++) {
    if (lista[i] == 3)
      std::cout << "Pozicija elementa 3 je: " << i << std::endl;
      break;
  }
}

template <typename tip> void testirajDajMaksimum(Lista<tip> &lista) {
  lista.obrisi();
  lista.dodajIspred(1);
  lista.dodajIspred(11);
  lista.dodajIspred(121);
  std::cout << "Najveci element je: " << dajMaksimum(lista) << std::endl;
}

template <typename tip> void testirajIterator(DvostrukaLista<tip> &lista) {
  Iterator<tip> it(lista);
  std::cout << "Elementi liste nakon svega su: " << std::endl;
  while (it.Sljedeci()) {
    std::cout << it.Trenutni() <<", ";
  }
  std::cout<<std::endl;
}

int main() {
  DvostrukaLista<int> lista;
  testirajBrojElemenata(lista);
  testirajTrenutni(lista);
  testirajPrethodni(lista);
  testirajSljedeci(lista);
  testirajObrisi(lista);
  testirajDodajIspred(lista);
  testirajDodajIza(lista);
  testirajPocetak(lista);
  testirajDajMaksimum(lista);
  testirajKraj(lista);
  testirajOperator(lista);
  testirajIterator(lista);

  return 0;
}