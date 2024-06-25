// TP 2022/2023: Zadaća 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <ios>
#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>

const double EPSILON=std::pow(10,-10);


class Krug {
  double r;
  std::pair<double, double> centar;
  static bool Jednaki(double x, double y) {
     return std::abs(x - y) <= EPSILON * (std::abs(x) + std::abs(y));
  }

public:
  explicit Krug(double poluprecnik = 0) : centar({0, 0}) {
    PostaviPoluprecnik(poluprecnik);
  }
  explicit Krug(const std::pair<double, double> &centar, double poluprecnik = 0) {
    PostaviPoluprecnik(poluprecnik);
    PostaviCentar(centar);
  }
  std::pair<double, double> DajCentar() const { return centar; }
  double DajPoluprecnik() const { return r; }
  double DajObim() const { return 8 * r * std::atan(1); }
  double DajPovrsinu() const { return 4 * r * r * std::atan(1); }
  Krug &PostaviCentar(const std::pair<double, double> &centar) {
    this->centar = centar;
    return *this;
  }
  Krug &PostaviPoluprecnik(double poluprecnik) {
    if (poluprecnik < 0) {
      throw std::domain_error("Nedozvoljen poluprecnik");
    }
    r = poluprecnik;
    return *this;
  }
  void Ispisi() const {
    std::cout << "{(" << DajCentar().first << "," << DajCentar().second << ")," << DajPoluprecnik() << "}";
  }
  Krug &Transliraj(double delta_x, double delta_y) {
    centar.first += delta_x;
    centar.second += delta_y;
    *this = PostaviCentar({centar.first, centar.second});
    return *this;
  }
  Krug &Rotiraj(double alpha) {
    // koordinatni pocetak (xc,yc)=(0,0)
    return Rotiraj({0, 0}, alpha);
  }
  Krug &Rotiraj(const std::pair<double, double> &centar_rotacije, double alpha) {
    double novo_x, novo_y;
    novo_x = centar_rotacije.first +
             (centar.first - centar_rotacije.first) * std::cos(alpha) -
             (centar.second - centar_rotacije.second) * std::sin(alpha);
    novo_y = centar_rotacije.second +
             (centar.first - centar_rotacije.first) * std::sin(alpha) +
             (centar.second - centar_rotacije.second) * std::cos(alpha);
    *this = PostaviCentar({novo_x, novo_y});
    return *this;
  }
  static double RastojanjeCentara(const Krug &k1, const Krug &k2) {
    double x1 = k1.DajCentar().first, y1 = k1.DajCentar().second,
           x2 = k2.DajCentar().first, y2 = k2.DajCentar().second;
    double d = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return d;
  }
  static bool DaLiSuIdenticni(const Krug &k1, const Krug &k2) {
    return (Jednaki(k1.centar.first, k2.centar.first) &&
            Jednaki(k1.centar.second, k2.centar.second) && Jednaki(k1.r, k2.r));
  }
  static bool DaLiSuPodudarni(const Krug &k1, const Krug &k2) {
    return Jednaki(k1.r, k2.r);
  }
  static bool DaLiSuKoncentricni(const Krug &k1, const Krug &k2) {
    return (Jednaki(k1.centar.first, k2.centar.first) &&
            Jednaki(k1.centar.second, k2.centar.second));
  }
  static bool DaLiSeDodirujuIzvani(const Krug &k1, const Krug &k2) {
    return (Jednaki((k1.r + k2.r), RastojanjeCentara(k1, k2)) || RastojanjeCentara(k1, k2)==(k1.r+k2.r));
  }
  static bool DaLiSeDodirujuIznutri(const Krug &k1, const Krug &k2) {
    return (Jednaki(RastojanjeCentara(k1, k2),(k1.r - k2.r)) || RastojanjeCentara(k1, k2)==std::fabs(k1.r-k2.r));
  }
  static bool DaLiSePreklapaju(const Krug &k1, const Krug &k2) {
    return (RastojanjeCentara(k1, k2) < (k1.r + k2.r));
  }
  static bool DaLiSeSijeku(const Krug &k1, const Krug &k2) {
    return (RastojanjeCentara(k1, k2) < (k1.r + k2.r) &&
            !DaLiSeDodirujuIznutri(k1, k2) && !DaLiSeDodirujuIzvani(k1, k2) &&
            !DaLiSuIdenticni(k1, k2) && !k2.DaLiSadrzi(k1) &&
            !k1.DaLiSadrzi(k2));
  }
  bool DaLiSadrzi(const Krug &k) const {
    std::pair<double, double> c = k.DajCentar();
    double d = std::sqrt((c.first - centar.first) * (c.first - centar.first) + (c.second - centar.second) * (c.second - centar.second));
    return (d + k.r < r);
  }
  friend Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y);
  friend Krug RotiraniKrug(const Krug &k, double alpha);
  friend Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rotacije, double alpha);
};

Krug TransliraniKrug(const Krug &k, double delta_x, double delta_y) {
  Krug novi;
  novi.centar = k.centar;
  novi.r = k.r;
  novi.Transliraj(delta_x, delta_y);
  return novi;
}

Krug RotiraniKrug(const Krug &k, double alpha) {
  Krug novi;
  novi.centar = k.centar;
  novi.r = k.r;
  novi.Rotiraj({0, 0}, alpha);
  return novi;
}

Krug RotiraniKrug(const Krug &k, const std::pair<double, double> &centar_rotacije, double alpha) {
  Krug novi;
  novi.centar = k.centar;
  novi.r = k.r;
  novi.Rotiraj(centar_rotacije, alpha);
  return novi;
}

int main() {
   
  int n;
  std::cout << "Unesite broj krugova: ";
  std::cin >> n;
  if (n <= 0) {
    std::cout << "Uneseni broj nije prirodan!";
    return 0;
  }
  Krug **krugovi = nullptr;
  try {
    krugovi = new Krug *[n] {};
    bool greska = false;
    for (int i = 0; i < n; i++) {
      double x, y, r;
      std::cout << "Unesite centar " << i + 1 << ". kruga: ";
      if (!(std::cin >> x >> y)) {
        std::cout << "Neispravne koordinate centra! Pokusajte ponovo: ";
        std::cin.ignore(10000, '\n');
        std::cin.clear();
        i--;
        greska = true;
        continue;
      }
      greska = false;
      std::cout << "Unesite poluprecnik " << i + 1 << ". kruga: ";
      if (!(std::cin >> r) || r < 0) {
        std::cout << "Neispravan poluprecnik! Pokusajte ponovo: ";
        std::cin.ignore(10000, '\n');
        std::cin.clear();
        i--;
        greska = true;
        continue;
      }
      greska = false;
      Krug *krug = new Krug({x, y}, r);
      krugovi[i] = krug;
    }
    double delta_x, delta_y;
    std::cout << "Unesite parametre translacije (delta_x,delta_y): "<< std::endl;
    std::cin >> delta_x;
    std::cin >> delta_y;
    std::transform(krugovi, krugovi + n, krugovi, [&](Krug *krug) {
      return &krug->Transliraj(delta_x, delta_y);
    });
    double alpha;
    std::cout << "Unesite ugao rotacije oko tacke (0,0) u stepenima: ";
    std::cin >> alpha;
    alpha = alpha * 4 * std::atan(1) / 180;
    std::transform(krugovi, krugovi + n, krugovi, [&](Krug *krug) {
      return &krug->Rotiraj({0, 0}, alpha);
    });
    std::sort(krugovi, krugovi + n, [](const Krug *k1, const Krug *k2) {
      return k1->DajPovrsinu() < k2->DajPovrsinu();
    });
    std::cout << "Parametri krugova nakon obavljene transformacije su:\n ";
    std::for_each(krugovi, krugovi + n, [](const Krug *k) {
      k->Ispisi();
      std::cout << std::endl;
    });
    Krug *max_obim = *std::max_element(krugovi, krugovi + n, [](const Krug *k1, const Krug *k2) { return k1->DajObim() < k2->DajObim();  });
    std::cout << "Krug sa najvecim obimom je: ";
    max_obim->Ispisi();
    bool presjek = false;
    std::cout << std::endl;
    std::for_each(krugovi, krugovi + n, [&](const Krug *k1) {
      std::for_each(krugovi, krugovi + n, [&](const Krug *k2) {
        if (k1 != k2 && Krug::DaLiSeSijeku(*k1, *k2) && k1 < k2) {
          std::cout << "Presjecaju se krugovi: \n";
          k1->Ispisi();
          std::cout << " i ";
          k2->Ispisi();
          std::cout << std::endl;
          presjek = true;
        }
      });
    });
    std::cout << std::endl;
    if (!presjek) {
      std::cout << "Ne postoje krugovi koji se presjecaju!";
    }
    for (int i = 0; i < n; i++) {
      delete krugovi[i];
    }
    delete[] krugovi;
  } catch (std::bad_alloc) {
    std::cout << "Problemi sa alokacijom memorije!";
  } catch (std::domain_error e) {
    std::cout << e.what();
  }
  return 0;  

}