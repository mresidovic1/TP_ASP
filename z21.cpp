// TP 2022/2023: Zadaća 5, Zadatak 2
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

class Padavine {
  std::vector<int> padavine;
  int max_kolicina_padavina;

public:
  Padavine(const std::vector<int> &padavine, int max_kol)
      : padavine(padavine), max_kolicina_padavina(max_kol) {}

  explicit Padavine(const int &max_kol) {
    if (max_kol < 0) {
      throw std::range_error("Ilegalna maksimalna kolicina");
    }
    max_kolicina_padavina = max_kol;
  }
  void RegistrirajPadavine(int padavina) {
    if (padavina < 0 || padavina > max_kolicina_padavina) {
      throw std::range_error("Ilegalna kolicina padavina");
    }
    padavine.push_back(padavina);
  }
  int DajBrojRegistriranihPadavina() const { return padavine.size(); }
  void BrisiSve() { padavine.clear(); }
  int DajMinimalnuKolicinuPadavina() const {
    if (padavine.empty())
      throw std::range_error("Nema registriranih padavina");
    int minimalna_kol = *std::min_element(padavine.begin(), padavine.end());
    return minimalna_kol;
  }
  int DajMaksimalnuKolicinuPadavina() const {
    if (padavine.empty())
      throw std::range_error("Nema registriranih padavina");
    int max_kol = *std::max_element(padavine.begin(), padavine.end());
    return max_kol;
  }
  int DajBrojDanaSaPadavinamaVecimOd(int limit) const {
    if (padavine.empty())
      throw std::range_error("Nema registriranih padavina");
    return std::count_if(
        padavine.begin(), padavine.end(),
        std::bind(std::greater<int>(), std::placeholders::_1, limit));
  }
  void Ispisi() const {
    std::vector<int> sortirani = padavine;
    std::sort(sortirani.begin(), sortirani.end(), std::greater<int>());
    for (int k : sortirani) {
      std::cout << k << std::endl;
    }
  }
  int operator[](int i) const {
    if (i < 1 || i > padavine.size())
      throw std::range_error("Neispravan indeks");
    return padavine[i - 1];
  }

  Padavine &operator-=(const Padavine &pom) {
    if (padavine.size() != pom.padavine.size()) {
      throw std::domain_error("Nesaglasni operandi");
    }
    std::transform(padavine.begin(), padavine.end(), pom.padavine.begin(), padavine.begin(), std::bind (std::minus<int>(), std::placeholders::_1, std::placeholders::_2));
    for (int i = 0; i < padavine.size(); i++) {
      if (padavine[i] < 0) {
        throw std::domain_error("Nekorektan rezultat operacije");
      }
    }
    
    return *this;
  }

  Padavine operator-(const Padavine &pom) const {
    if (padavine.size() != pom.padavine.size()) {
      throw std::domain_error("Nesaglasni operandi");
    }
    std::vector<int> rez(padavine.size());
    std::transform(padavine.begin(), padavine.end(), pom.padavine.begin(), rez.begin(), std::bind(std::minus<int>(), std::placeholders::_1, std::placeholders::_2));
    int max_kol = max_kolicina_padavina - pom.max_kolicina_padavina;
    return Padavine(rez, max_kol);
  }

  Padavine &operator++() {
    std::transform(padavine.begin(), padavine.end(), padavine.begin(), std::bind(std::plus<int>(), std::placeholders::_1, 1));
    max_kolicina_padavina++;
    return *this;
  }
  Padavine &operator++(int) { return ++(*this); }
  friend Padavine operator+(const Padavine &x, int y) {
    std::vector<int> transformirani = x.padavine;
    std::transform(transformirani.begin(), transformirani.end(), transformirani.begin(), std::bind(std::plus<int>(), std::placeholders::_1, y));
    int novi_max = x.max_kolicina_padavina + y;
    return Padavine(transformirani, novi_max);
  }
  friend Padavine operator+(int y, const Padavine &x) { return x + y; }
  friend Padavine operator-(const Padavine &x, int y) {
    if (x.max_kolicina_padavina - y)
      throw std::domain_error("Nekorektan rezultat operacije");
    std::vector<int> transformirani = x.padavine;
    std::transform(transformirani.begin(), transformirani.end(),transformirani.begin(), std::bind(std::minus<int>(), std::placeholders::_1, y));
    return Padavine(transformirani, x.max_kolicina_padavina - y);
  }
  friend Padavine operator-(int y, const Padavine &x) {
    std::vector<int> transformirani = x.padavine;
    std::transform(transformirani.begin(), transformirani.end(),transformirani.begin(), std::bind(std::minus<int>(), y, std::placeholders::_1));
    if (y < 0)
      throw std::domain_error("Nekorektan rezultat operacije");
    return Padavine(transformirani, y);
  }
  Padavine &operator+=(int y) {
    std::transform(padavine.begin(), padavine.end(), padavine.begin(), std::bind(std::plus<int>(), std::placeholders::_1, y));
    max_kolicina_padavina += y;
    return *this;
  }
  Padavine &operator-=(int y) {
    std::transform(padavine.begin(), padavine.end(), padavine.begin(), std::bind(std::minus<int>(), std::placeholders::_1, y));
    max_kolicina_padavina -= y;
    for (int i = 0; i < padavine.size(); i++) {
      if (padavine[i] < 0)
        throw std::domain_error("Nekorektan rezultat operacije");
    }
    if (max_kolicina_padavina < 0) {
      throw std::domain_error("Nekorektan rezultat operacije");
    }
    return *this;
  }
  Padavine &operator-() {
    std::transform(padavine.begin(), padavine.end(), padavine.begin(), std::bind(std::minus<int>(),max_kolicina_padavina,std::placeholders::_1));
    return *this;
  }
  bool operator==(const Padavine &provjera) const {
    return std::equal(padavine.begin(),padavine.end(),provjera.padavine.begin()) && padavine.size()==provjera.padavine.size();
  }
  bool operator!=(const Padavine &provjera) const {
    return !(padavine == provjera.padavine);
  }
};

int main() {
   try{
        Padavine kisa({12,13,24},40);

        kisa.Ispisi();

        kisa.RegistrirajPadavine(27);
        kisa.RegistrirajPadavine(11);

        std::cout<<"Broj registriranih padavina: "<<kisa.DajBrojRegistriranihPadavina()<<", broj minimalnih padavina: "<<kisa.DajMinimalnuKolicinuPadavina()<<" i broj maksimalnih padavina: "<<kisa.DajMaksimalnuKolicinuPadavina();

        int granica=15;
        std::cout<<"Iznad granice: "<<kisa.DajBrojDanaSaPadavinamaVecimOd(granica);

        Padavine led({10,11,12},30);
        Padavine snijeg=led-kisa;
        snijeg.Ispisi();
        snijeg+=22;
        snijeg.Ispisi();
        led-=44;
        led.Ispisi();
        led=-led;
        led.Ispisi();

        std::cout<<"Padavine prvi dan su bile uzasne: "<<kisa[1]<<std::endl;
    }
    catch(std::domain_error e){
        std::cout<<e.what()<<std::endl;
    }
   
  return 0;
}
