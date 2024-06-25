// TP 2022/2023: Zadaća 5, Zadatak 4
#include <cmath>
#include <cstring>
#include <fstream>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>

template <typename TipEl> class Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipEl **elementi;
  static TipEl **AlocirajMemoriju(int br_redova, int br_kolona);
  static void DealocirajMemoriju(TipEl **elementi, int br_redova);
  void KopirajElemente(TipEl **elementi);
  std::string String(double broj) const {
    std::string pom;
    pom += std::to_string(broj);
    int duzina = pom.length();
    for (; duzina > 0 && pom[duzina - 1] == '0'; duzina--)
      pom.resize(duzina);
    if (pom[duzina - 1] == '.')
      pom.resize(duzina - 1);
    return pom;
  }
  bool ProvjeriLiniju(const std::string &linija) {
    for (char c : linija) {
      if (c != ',' && c != '.' && c != '-' && !std::isdigit(c) &&
          !std::isspace(c)) {
        return false;
      }
    }
    return true;
  }

public:
  Matrica() : br_redova(0), br_kolona(0), elementi(nullptr) {}
  Matrica(int br_redova, int br_kolona, char ime = 0);
  Matrica(const std::string &ime, bool bin);
  Matrica(const Matrica &m);
  Matrica(Matrica &&m);
  ~Matrica() { DealocirajMemoriju(elementi, br_redova); }
  Matrica &operator=(const Matrica &m);
  Matrica &operator=(Matrica &&m);
  void Unesi();
  void Ispisi(int sirina_ispisa) const;

  template <typename Tip2>
  friend Matrica<Tip2> ZbirMatrica(const Matrica<Tip2> &m1,
                                   const Matrica<Tip2> &m2);
  Matrica operator+(const Matrica &m) const {
    if (br_redova != m.br_redova || br_kolona != m.br_kolona)
      throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica rezultat(br_redova, br_kolona);
    for (int i = 0; i < br_redova; i++) {
      for (int j = 0; j < br_kolona; j++) {
        rezultat.elementi[i][j] = elementi[i][j] + m.elementi[i][j];
      }
    }
    return rezultat;
  }
  operator std::string() const;
  Matrica operator-(const Matrica &m) const {
    if (br_redova != m.br_redova || br_kolona != m.br_kolona)
      throw std::domain_error("Matrice nemaju jednake dimenzije!");
    Matrica rezultat(br_redova, br_kolona);
    for (int i = 0; i < br_redova; i++) {
      for (int j = 0; j < br_kolona; j++) {
        rezultat.elementi[i][j] = elementi[i][j] - m.elementi[i][j];
      }
    }
    return rezultat;
  }

  Matrica &operator+=(const Matrica &m) {
    if (br_redova != m.br_redova || br_kolona != m.br_kolona) {
      throw std::domain_error("Matrice nemaju jednake dimenzije!");
    }
    for (int i = 0; i < br_redova; i++) {
      for (int j = 0; j < br_kolona; j++) {
        elementi[i][j] += m.elementi[i][j];
      }
    }
    return *this;
  }
  Matrica &operator-=(const Matrica &m) {
    if (br_redova != m.br_redova || br_kolona != m.br_kolona) {
      throw std::domain_error("Matrice nemaju jednake dimenzije!");
    }
    for (int i = 0; i < br_redova; i++) {
      for (int j = 0; j < br_kolona; j++) {
        elementi[i][j] -= m.elementi[i][j];
      }
    }
    return *this;
  }

  friend Matrica<TipEl> operator*(const Matrica<TipEl> &m1, const Matrica &m2) {
    if (m1.br_redova != m2.br_kolona)
      throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica rezultat(m1.br_redova, m2.br_kolona);
    for (int i = 0; i < m1.br_redova; i++) {
      for (int j = 0; j < m2.br_kolona; j++) {
        double suma = 0;
        for (int k = 0; k < m1.br_kolona; k++) {
          suma += m1.elementi[i][k] * m2.elementi[k][j];
        }
        rezultat.elementi[i][j] = suma;
      }
    }
    return rezultat;
  }

  friend Matrica<TipEl> operator*(const Matrica<TipEl> mat, double skalar) {
    Matrica rezultat(mat.br_redova, mat.br_kolona);
    for (int i = 0; i < mat.br_redova; i++) {
      for (int j = 0; j < mat.br_kolona; j++) {
        rezultat.elementi[i][j] = skalar * mat.elementi[i][j];
      }
    }
    return rezultat;
  }
  friend Matrica<TipEl> operator*(double a, const Matrica<TipEl> &mat) {
    return mat * a;
  }
  Matrica<TipEl> operator*=(double x) {
    for (int i = 0; i < br_redova; i++) {
      for (int j = 0; j < br_redova; j++) {
        elementi[i][j] *= x;
      }
    }
    return *this;
  }
  Matrica &operator*=(const Matrica &m) {
    if (br_kolona != m.br_redova)
      throw std::domain_error("Matrice nisu saglasne za mnozenje");
    Matrica rezultat(br_redova, m.br_kolona);
    for (int i = 0; i < br_redova; i++) {
      for (int j = 0; j < m.br_kolona; j++) {
        rezultat.elementi[i][j] = 0;
        for (int k = 0; k < br_kolona; k++) {
          rezultat.elementi[i][j] += elementi[i][k] * m.elementi[k][j];
        }
      }
    }
    *this = rezultat;
    return *this;
  }
  TipEl &operator()(int i, int j) {
    if (i < 1 || i > br_redova || j < 1 || j > br_kolona)
      throw std::range_error("Neispravan indeks");
    return elementi[i - 1][j - 1];
  }
  const TipEl &operator()(int i, int j) const {
    if (i < 1 || i > br_redova || j < 1 || j > br_kolona)
      throw std::range_error("Neispravan indeks");
    return elementi[i - 1][j - 1];
  }
  friend std::istream &operator>>(std::istream &ulaz, Matrica &m) {
    for (int i = 0; i < m.br_redova; i++) {
      for (int j = 0; j < m.br_kolona; j++) {
        std::cout << m.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
        ulaz >> m.elementi[i][j];
      }
    }
    return ulaz;
  }

  friend std::ostream &operator<<(std::ostream &izlaz,
                                  const Matrica<TipEl> &m) {
    int duzina = izlaz.width();
    for (int i = 0; i < m.br_redova; i++) {
      for (int j = 0; j < m.br_kolona; j++) {
        izlaz.width(duzina);
        izlaz << m.elementi[i][j];
      }
      std::cout << std::endl;
    }

    return izlaz;
  }

  TipEl *operator[](int indeks) {
    if (indeks < 0 || indeks >= br_redova)
      throw std::range_error("Neispravan indeks");
    return elementi[indeks];
  }
  const TipEl *operator[](int indeks) const {
    if (indeks < 0 || indeks >= br_redova)
      throw std::range_error("Neispravan indeks");
    return elementi[indeks];
  }
  void SacuvajUTekstualnuDatoteku(const std::string &ime) const;
  void SacuvajUBinarnuDatoteku(const std::string &ime) const;
  void ObnoviIzTekstualneDatoteke(const std::string &ime);
  void ObnoviIzBinarneDatoteke(const std::string &ime);
};

template <typename TipEl>
Matrica<TipEl>::Matrica(const std::string &ime, bool bin) {
  if (bin) {
    std::ifstream dat(ime, std::ios::binary);
    if (!dat)
      throw std::logic_error("Trazena datoteka ne postoji");
    dat.read(reinterpret_cast<char *>(this), sizeof(*this));
    elementi=AlocirajMemoriju(br_redova, br_kolona);
    try {
      for (int i = 0; i < br_redova; i++) {
        dat.read(reinterpret_cast<char *>(elementi[i]), br_kolona * sizeof(TipEl));
      }
      if (!dat) {
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      }
    } catch (...) {
      throw;
    }
    dat.close();
  } else {
    std::ifstream dat(ime);
    if (!dat)
      throw std::logic_error("Trazena datoteka ne postoji");
    std::string linija;
    int br_redova = 0;
    int br_kolona = 0;
    while (std::getline(dat, linija)) {
      std::istringstream iss(linija);
      std::string element;
      if (!ProvjeriLiniju(linija)) {
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      }
      int br_elemenata = 0;
      while (std::getline(iss, element, ',')) {
        br_elemenata++;
      }
      if (br_kolona == 0)
        br_kolona = br_elemenata;
      else if (br_elemenata != br_kolona)
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      br_redova++;
    }
    dat.clear();
    dat.seekg(0, std::ios::beg);
    int i = 0;
    this->br_redova = br_redova;
    this->br_kolona = br_kolona;
    elementi = AlocirajMemoriju(br_redova, br_kolona);
    while (std::getline(dat, linija)) {
      std::istringstream iss(linija);
      std::string element;
      int j = 0;
      while (std::getline(iss, element, ',')) {
        try {
          elementi[i][j] = std::stod(element);
        } catch (...) {
          throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
        j++;
      }
      i++;
    }

    dat.close();
  }
}

template <typename TipEl>
void Matrica<TipEl>::SacuvajUTekstualnuDatoteku(const std::string &ime) const {
  std::ofstream dat(ime);
  if (!dat) {
    throw std::logic_error("Problemi sa upisom u datoteku");
  }
  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++) {
      dat << String(elementi[i][j]);
      if (j != br_kolona - 1)
        dat << ",";
    }
    if (i != br_redova - 1)
      dat << std::endl;
  }
  dat.close();
}

template <typename TipEl>
void Matrica<TipEl>::SacuvajUBinarnuDatoteku(const std::string &ime) const {
  std::ofstream dat(ime, std::ios::binary);
  if (!dat) {
    throw std::logic_error("Problemi sa upisom u datoteku");
  }
  dat.write(reinterpret_cast<const char *>(this), sizeof(*this));
  for (int i = 0; i < br_redova; i++) {
    dat.write(reinterpret_cast<const char *>(elementi[i]),
              br_kolona * sizeof(TipEl));
  }
  dat.close();
}

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzTekstualneDatoteke(const std::string &ime) {
  std::ifstream dat(ime);
  if (!dat)
    throw std::logic_error("Trazena datoteka ne postoji");
  std::string linija;
  int br_redova = 0;
  int br_kolona = 0;
  while (std::getline(dat, linija)) {
    std::istringstream iss(linija);
    std::string element;
    if (!ProvjeriLiniju(linija)) {
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
    int br_elemenata = 0;
    while (std::getline(iss, element, ',')) {
      br_elemenata++;
    }
    if (br_kolona == 0)
      br_kolona = br_elemenata;
    else if (br_elemenata != br_kolona)
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
    br_redova++;
  }
  dat.clear();
  dat.seekg(0, std::ios::beg);
  int i = 0;
  this->br_redova = br_redova;
  this->br_kolona = br_kolona;
  elementi = AlocirajMemoriju(br_redova, br_kolona);
  while (std::getline(dat, linija)) {
    std::istringstream iss(linija);
    std::string element;
    int j = 0;
    while (std::getline(iss, element, ',')) {
      try {
        elementi[i][j] = std::stod(element);
      } catch (...) {
        throw std::logic_error("Datoteka sadrzi besmislene podatke");
      }
      j++;
    }
    i++;
  }

  dat.close();
}

template <typename TipEl>
void Matrica<TipEl>::ObnoviIzBinarneDatoteke(const std::string &ime) {
  std::ifstream dat(ime, std::ios::binary);
  if (!dat)
    throw std::logic_error("Trazena datoteka ne postoji");
  dat.read(reinterpret_cast<char *>(this), sizeof(*this));
  try {
    for (int i = 0; i < br_redova; i++) {
      dat.read(reinterpret_cast<char *>(elementi[i]),
               br_kolona * sizeof(TipEl));
    }
    if (!dat) {
      throw std::logic_error("Datoteka sadrzi besmislene podatke");
    }
  } catch (...) {
    throw;
  }
  dat.close();
}

template <typename TipEl> Matrica<TipEl>::operator std::string() const {
  std::string pom;
  pom += '{';
  for (int i = 0; i < br_redova; i++) {
    pom += '{';
    for (int j = 0; j < br_kolona; j++) {
      pom += String(elementi[i][j]);
      if (j != br_kolona - 1)
        pom += ',';
    }
    pom += '}';
    if (i != br_redova - 1)
      pom += ',';
  }
  pom += '}';
  return pom;
}

template <typename TipEl>
TipEl **Matrica<TipEl>::AlocirajMemoriju(int br_redova, int br_kolona) {
  TipEl **elementi = new TipEl *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      elementi[i] = new TipEl[br_kolona];
  } catch (...) {
    DealocirajMemoriju(elementi, br_redova);
    throw;
  }
  return elementi;
}
template <typename TipEl>
void Matrica<TipEl>::DealocirajMemoriju(TipEl **elementi, int br_redova) {
  for (int i = 0; i < br_redova; i++)
    delete[] elementi[i];
  delete[] elementi;
}
template <typename TipEl>
Matrica<TipEl>::Matrica(int br_redova, int br_kolona, char ime)
    : br_redova(br_redova), br_kolona(br_kolona), ime_matrice(ime),
      elementi(AlocirajMemoriju(br_redova, br_kolona)) {}

template <typename TipEl>
void Matrica<TipEl>::KopirajElemente(TipEl **elementi) {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++)
      this->elementi[i][j] = elementi[i][j];
}
template <typename TipEl>
Matrica<TipEl>::Matrica(const Matrica<TipEl> &m)
    : br_redova(m.br_redova), br_kolona(m.br_kolona),
      ime_matrice(m.ime_matrice),
      elementi(AlocirajMemoriju(m.br_redova, m.br_kolona)) {
  KopirajElemente(m.elementi);
}
template <typename TipEl>
Matrica<TipEl>::Matrica(Matrica<TipEl> &&m)
    : br_redova(m.br_redova), br_kolona(m.br_kolona), elementi(m.elementi),
      ime_matrice(m.ime_matrice) {
  m.br_redova = 0;
  m.elementi = nullptr;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(const Matrica<TipEl> &m) {
  if (br_redova < m.br_redova || br_kolona < m.br_kolona) {
    TipEl **novi_prostor = AlocirajMemoriju(m.br_redova, m.br_kolona);
    DealocirajMemoriju(elementi, br_redova);
    elementi = novi_prostor;
  } else if (br_redova > m.br_redova)
    for (int i = m.br_redova; i < br_redova; i++)
      delete elementi[i];
  br_redova = m.br_redova;
  br_kolona = m.br_kolona;
  ime_matrice = m.ime_matrice;
  KopirajElemente(m.elementi);
  return *this;
}
template <typename TipEl>
Matrica<TipEl> &Matrica<TipEl>::operator=(Matrica<TipEl> &&m) {
  std::swap(br_redova, m.br_redova);
  std::swap(br_kolona, m.br_kolona);
  std::swap(ime_matrice, m.ime_matrice);
  std::swap(elementi, m.elementi);
  return *this;
}

template <typename TipEl> void Matrica<TipEl>::Unesi() {
  for (int i = 0; i < br_redova; i++)
    for (int j = 0; j < br_kolona; j++) {
      std::cout << ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> elementi[i][j];
    }
}
template <typename TipEl> void Matrica<TipEl>::Ispisi(int sirina_ispisa) const {
  for (int i = 0; i < br_redova; i++) {
    for (int j = 0; j < br_kolona; j++)
      std::cout << std::setw(sirina_ispisa) << elementi[i][j];
    std::cout << std::endl;
  }
}
template <typename TipEl>
Matrica<TipEl> ZbirMatrica(const Matrica<TipEl> &m1, const Matrica<TipEl> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  Matrica<TipEl> m3(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}

int main() {
  {
    try {
      Matrica<int> m0{2, 2};
      for (int i{0}; i < 2; i++)
        for (int j{0}; j < 2; j++)
          m0[i][j] = i + j;
      m0.SacuvajUBinarnuDatoteku("matrica1.DAT");
      Matrica<int> m1("matrica1.DAT", true);
      std::cout << std::setw(6) << m1;
    } catch (const std::logic_error &e) {
      std::cout << "Izuzetak: " << e.what() << std::endl;
    }

    std::cout << std::endl << std::endl;

    try {
      Matrica<double> m0{2, 2};
      for (int i{0}; i < 2; i++)
        for (int j{0}; j < 2; j++)
          m0[i][j] = i + j + 0.5;
      m0.SacuvajUBinarnuDatoteku("matrica2.DAT");
      Matrica<double> m1("matrica2.DAT", true);
      std::cout << std::setw(6) << m1;
    } catch (const std::logic_error &e) {
      std::cout << "Izuzetak: " << e.what() << std::endl;
    }
  }
  /*Matrica<double> mat(2,2,'A');
  std::cout<<"Unesite elemente matrice A: "<<std::endl;
  mat.Unesi();

  try{
      mat.SacuvajUTekstualnuDatoteku("mat.txt");
      std::cout<<"Uspjesno!";
  }
  catch(...){
      std::cout<<"Bezuspjesno";
  }
  try{
      Matrica<double>obnovljena("mat.txt",false);
      obnovljena.Ispisi(5);
      std::cout<<"Uspjesno!";
  }
  catch(...){
      std::cout<<"Bezuspjesno";
  }*/
}