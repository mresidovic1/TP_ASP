#include <exception>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const float konst = 9999999;

template <typename tip> class UsmjereniGraf;
template <typename tip> class Grana;
template <typename tip> class Cvor;
template <typename tip> class GranaIterator;

template <typename tip> class UsmjereniGraf {
protected:
  UsmjereniGraf() {}

public:
  UsmjereniGraf(int) {}
  virtual ~UsmjereniGraf(){};
  virtual int dajBrojCvorova() const = 0;
  virtual void postaviBrojCvorova(int) = 0;
  virtual void dodajGranu(int, int, float = 0) = 0;
  virtual void obrisiGranu(int, int) = 0;
  virtual void postaviTezinuGrane(int, int, float = 0) = 0;
  virtual float dajTezinuGrane(int, int) const = 0;
  virtual bool postojiGrana(int, int) const = 0;
  virtual void postaviOznakuCvora(int, tip) = 0;
  virtual tip dajOznakuCvora(int) const = 0;
  virtual void postaviOznakuGrane(int, int, tip) = 0;
  virtual tip dajOznakuGrane(int, int) const = 0;
  virtual Grana<tip> dajGranu(int, int) = 0;
  virtual const Grana<tip> dajGranu(int, int) const = 0;
  virtual Cvor<tip> dajCvor(int) = 0;
  virtual const Cvor<tip> dajCvor(int) const = 0;
  GranaIterator<tip> dajGranePocetak() {
    return ++GranaIterator<tip>(this, 0, -1);
  }
  const GranaIterator<tip> dajGranePocetak() const {
    return ++GranaIterator<tip>(const_cast<UsmjereniGraf *>(this), 0, -1);
  }
  GranaIterator<tip> dajGraneKraj() {
    return GranaIterator<tip>(this, dajBrojCvorova(), 0);
  }
  const GranaIterator<tip> dajGraneKraj() const {
    return GranaIterator<tip>(const_cast<UsmjereniGraf *>(this), dajBrojCvorova(), 0);
  }
};

template <typename tip> class Grana {
  UsmjereniGraf<tip> *graf;
  int polazniCvor, dolazniCvor;

public:
  Grana(UsmjereniGraf<tip> *graf, int polazniCvor, int dolazniCvor) : graf(graf), polazniCvor(polazniCvor), dolazniCvor(dolazniCvor) {}
  float dajTezinu() const {
    return graf->dajTezinuGrane(polazniCvor, dolazniCvor);
  }
  void postaviTezinu(float tezina) {
    graf->postaviTezinuGrane(polazniCvor, dolazniCvor, tezina);
  }
  tip dajOznaku() const {
    return graf->dajOznakuGrane(polazniCvor, dolazniCvor);
  }
  void postaviOznaku(tip oznaka) {
    graf->postaviOznakuGrane(polazniCvor, dolazniCvor, oznaka);
  }
  Cvor<tip> dajPolazniCvor() { return graf->dajCvor(polazniCvor); }
  const Cvor<tip> dajpPolazniCvor() const { return graf->dajCvor(polazniCvor); }
  Cvor<tip> dajDolazniCvor() { return graf->dajCvor(dolazniCvor); }
  const Cvor<tip> dajDolazniCvor() const { return graf->dajCvor(dolazniCvor); }
};

template <typename tip> class Cvor {
  int br;
  UsmjereniGraf<tip> *graf;
public:
  Cvor(UsmjereniGraf<tip> *graf, int br) : graf(graf), br(br) {}
  tip dajOznaku() const { return graf->dajOznakuCvora(br); }
  void postaviOznaku(tip oznaka) { graf->postaviOznakuCvora(br, oznaka); }
  int dajRedniBroj() const { return br; }
};

template <typename tip> class GranaIterator {
  UsmjereniGraf<tip> *graf;
  int i, j;
public:
  GranaIterator(UsmjereniGraf<tip> *graf, int i, int j) : graf(graf), i(i), j(j) {}
  Grana<tip> operator*() { return graf->dajGranu(i, j); }
  const Grana<tip> operator*() const { return graf->dajGranu(i, j); }
  bool operator==(const GranaIterator &iter) const {
    return i == iter.i && j == iter.j && graf == iter.graf;
  }
  bool operator!=(const GranaIterator &iter) const { return !(*this == iter); }
  GranaIterator &operator++() {
    do {
      if (j + 1 >= graf->dajBrojCvorova()) {
        i++;
        j = 0;
      } else
        j++;
    } while (i < graf->dajBrojCvorova() && !graf->postojiGrana(i, j));
    return *this;
  }
  GranaIterator operator++(int) {
    auto pom(*this);
    ++(*this);
    return pom;
  }
};

template <typename tip> class MatricaGraf : public UsmjereniGraf<tip> {
  vector<vector<float>> mat;
  vector<tip> Cvorovi;
  vector<vector<tip>> Grane;

  void validirajCvor(int indeks) const {
    if (indeks < 0 || indeks >= dajBrojCvorova())
      throw std::logic_error("Broj cvorova ne odgovara ocekivanom!");
  }
  void validirajGranu(int i, int j) const {
    validirajCvor(i);  validirajCvor(j);
  }
  void validirajPostojanjeGrane(int i, int j) const {
    validirajGranu(i, j);
    if (!postojiGrana(i, j)) throw std::logic_error("Ne postoji grana!");
  }
public:
  MatricaGraf(int brojCvorova) {
    if (brojCvorova < 0) throw std::logic_error("Negativan broj cvorova!");
    mat = vector<vector<float>>(brojCvorova, vector<float>(brojCvorova, konst));
    Cvorovi = vector<tip>(brojCvorova);
    Grane = vector<vector<tip>>(brojCvorova, vector<tip>(brojCvorova));
  }

  int dajBrojCvorova() const { return mat.size(); }
  void postaviBrojCvorova(int noviBrojCvorova) {
    if (noviBrojCvorova < dajBrojCvorova())  throw std::logic_error("Broj cvorova je manji od trenutnog");
    mat.resize(noviBrojCvorova);
    for (auto &pom : mat) pom.resize(noviBrojCvorova, konst);
    Cvorovi.resize(noviBrojCvorova);
    Grane.resize(noviBrojCvorova);
    for (auto &pom : Grane) pom.resize(noviBrojCvorova);
  }

  void dodajGranu(int i, int j, float vr = 0) {
    validirajGranu(i, j);
    mat[i][j] = vr;
  }
  void obrisiGranu(int i, int j) {
    validirajPostojanjeGrane(i, j);
    mat[i][j] = konst;
  }
  void postaviTezinuGrane(int i, int j, float vr = 0) {
    validirajPostojanjeGrane(i, j);
    mat[i][j] = vr;
  }
  float dajTezinuGrane(int i, int j) const {
    validirajPostojanjeGrane(i, j);
    return mat[i][j];
  }
  bool postojiGrana(int i, int j) const {
    validirajGranu(i, j);
    return mat[i][j] != konst;
  }

  void postaviOznakuCvora(int i, tip oznaka) {
    validirajCvor(i);
    Cvorovi[i] = oznaka;
  }
  tip dajOznakuCvora(int i) const {
    validirajCvor(i);
    return Cvorovi[i];
  }
  void postaviOznakuGrane(int i, int j, tip oznaka) {
    validirajPostojanjeGrane(i, j);
    Grane[i][j] = oznaka;
  }
  tip dajOznakuGrane(int i, int j) const {
    validirajPostojanjeGrane(i, j);
    return Grane[i][j];
  }

  Grana<tip> dajGranu(int i, int j) {
    validirajPostojanjeGrane(i, j);
    return Grana<tip>(this, i, j);
  }
  const Grana<tip> dajGranu(int i, int j) const {
    validirajPostojanjeGrane(i, j);
    return Grana<tip>(const_cast<MatricaGraf *>(this), i, j);
  }
  Cvor<tip> dajCvor(int i) {
    validirajCvor(i);
    return Cvor<tip>(this, i);
  }
  const Cvor<tip> dajCvor(int i) const {
    validirajCvor(i);
    return Cvor<tip>(const_cast<MatricaGraf *>(this), i);
  }
};

template <typename tip>
void dfs(UsmjereniGraf<tip> *graf, vector<Cvor<tip>> &posjeceni, Cvor<tip> cvor) {
  cvor.postaviOznaku(1);
  posjeceni.push_back(cvor);
  for (auto it = graf->dajGranePocetak(); it != graf->dajGraneKraj(); ++it) {
    Cvor<tip> susjedni = (*it).dajDolazniCvor();
    if ((*it).dajPolazniCvor().dajRedniBroj() == cvor.dajRedniBroj() && susjedni.dajOznaku() != 1) dfs(graf, posjeceni, susjedni);
  }
}

template <typename tip>
void bfs(UsmjereniGraf<tip> *graf, vector<Cvor<tip>> &posjeceni, Cvor<tip> pocetni) {
  pocetni.postaviOznaku(1);
  posjeceni.push_back(pocetni);
  queue<Cvor<tip>> red;
  red.push(pocetni);
  while (!red.empty()) {
    Cvor<tip> pom = red.front();
    red.pop();
    for (GranaIterator<tip> it = graf->dajGranePocetak();
         it != graf->dajGraneKraj(); ++it) {
      Cvor<tip> susjedni = (*it).dajDolazniCvor();
      if ((*it).dajPolazniCvor().dajRedniBroj() == pom.dajRedniBroj() &&
          susjedni.dajOznaku() != 1) {
        susjedni.postaviOznaku(1);
        posjeceni.push_back(susjedni);
        red.push(susjedni);
      }
    }
  }
}

int main() {
    try {
    MatricaGraf<char> graf(6);
    graf.dodajGranu(0, 1);
    graf.dodajGranu(0, 2);
    graf.dodajGranu(1, 3);
    graf.dodajGranu(2, 4);
    graf.dodajGranu(3, 5);
    vector<Cvor<char>> dfsPosjeceni;
    cout << "DFS pretraga: ";
    dfs(&graf, dfsPosjeceni, graf.dajCvor(0));
    for (const auto &cvor : dfsPosjeceni) {
      cout << cvor.dajRedniBroj() << " ";
    }
    cout << endl;
    for (auto &cvor : dfsPosjeceni) {
      cvor.postaviOznaku(0);
    }
    vector<Cvor<char>> bfsPosjeceni;
    cout << "BFS pretraga: ";
    bfs(&graf, bfsPosjeceni, graf.dajCvor(0));
    for (const auto &cvor : bfsPosjeceni) {
      cout << cvor.dajRedniBroj() << " ";
    }
    cout << endl;
  } catch (exception e) {
    cout << e.what() << endl;
  }
  
  return 0;
  
}