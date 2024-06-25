// TP 2022/2023: Zadaća 4, Zadatak 2
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

class NepreklapajuciKrug {
  double r;
  std::pair<double, double> centar;
  NepreklapajuciKrug *prethodni;
  static NepreklapajuciKrug *posljednji;

  bool Preklopljen() const {
    NepreklapajuciKrug *trenutni = posljednji;
    while (trenutni != nullptr) {
      if (trenutni == this) {
        trenutni = trenutni->prethodni;
        continue;
      }
      double d = std::sqrt((trenutni->centar.first - centar.first) *
                               (trenutni->centar.first - centar.first) +
                           (trenutni->centar.second - centar.second) *
                               (trenutni->centar.second - centar.second));
      if (d <= trenutni->r + r) {
        return true;
      }
      trenutni = trenutni->prethodni;
    }
    return false;
  }
  NepreklapajuciKrug(const NepreklapajuciKrug &);
  NepreklapajuciKrug &operator=(const NepreklapajuciKrug &);

public:
  explicit NepreklapajuciKrug(double poluprecnik = 0)
      : r(poluprecnik), centar({0, 0}), prethodni(nullptr) {
    if (r < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    if (Preklopljen()) {
      throw std::logic_error("Nedozvoljeno preklapanje");
    }
    if (posljednji == nullptr) {
      posljednji = this;
    } else {
      this->prethodni = posljednji;
      posljednji = this;
    }
  }
  explicit NepreklapajuciKrug(const std::pair<double, double> &centar,
                              double poluprecnik = 0)
      : r(poluprecnik), centar(centar), prethodni(nullptr) {
    if (r < 0)
      throw std::domain_error("Nedozvoljen poluprecnik");
    if (Preklopljen()) {
      throw std::logic_error("Nedozvoljeno preklapanje");
    }
    if (posljednji == nullptr) {
      posljednji = this;
    } else {
      this->prethodni = posljednji;
      posljednji = this;
    }
  }

  ~NepreklapajuciKrug() {
    if (posljednji == this) {
      posljednji = prethodni;
    } else {
      NepreklapajuciKrug *trenutni = posljednji;
      while (trenutni != nullptr) {
        if (trenutni->prethodni == this) {
          trenutni->prethodni = prethodni;
          break;
        }
        trenutni = trenutni->prethodni;
      }
    }
  }

  std::pair<double, double> DajCentar() const { return centar; }
  double DajPoluprecnik() const { return r; }
  double DajObim() const { return 8 * r * std::atan(1); }
  double DajPovrsinu() const { return 4 * r * r * std::atan(1); }
  NepreklapajuciKrug &PostaviCentar(const std::pair<double, double> &centar) {
    std::pair<double, double> stari = this->centar;
    this->centar = centar;
    if (Preklopljen()) {
      this->centar = stari;
      throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
  }
  NepreklapajuciKrug &PostaviPoluprecnik(double poluprecnik) {
    if (poluprecnik < 0) {
      throw std::domain_error("Nedozvoljen poluprecnik");
    }
    double stari=r;
    r = poluprecnik;
    if(Preklopljen()){
        r=stari;
        throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
  }
  void Ispisi() const {
    std::cout << "{(" << DajCentar().first << "," << DajCentar().second << "),"
              << DajPoluprecnik() << "}" << std::endl;
  }
  NepreklapajuciKrug &Transliraj(double delta_x, double delta_y) {
    centar.first += delta_x;
    centar.second += delta_y;
    if (Preklopljen()) {
      centar.first -= delta_x;
      centar.second -= delta_y;
      throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
  }
  NepreklapajuciKrug &Rotiraj(double alpha) {
    // koordinatni pocetak (xc,yc)=(0,0)
    return Rotiraj({0, 0}, alpha);
  }
  NepreklapajuciKrug &Rotiraj(const std::pair<double, double> &centar_rotacije,
                              double alpha) {
    alpha *= 4 * std::atan(1) / 180;
    double x, y;
    x = centar_rotacije.first +
        (centar.first - centar_rotacije.first) * std::cos(alpha) -
        (centar.second - centar_rotacije.second) * std::sin(alpha);
    y = centar_rotacije.second +
        (centar.first - centar_rotacije.first) * std::sin(alpha) +
        (centar.second - centar_rotacije.second) * std::cos(alpha);
    std::pair<double, double> stari = centar;
    PostaviCentar({x, y});
    if (Preklopljen()) {
      PostaviCentar(stari);
      throw std::logic_error("Nedozvoljeno preklapanje");
    }
    return *this;
  }
  static double RastojanjeCentara(const NepreklapajuciKrug &k1,
                                  const NepreklapajuciKrug &k2) {
    std::pair<double, double> centar1 = k1.DajCentar();
    std::pair<double, double> centar2 = k2.DajCentar();
    double x1 = centar1.first, y1 = centar1.second, x2 = centar2.first,
           y2 = centar2.second;
    static double rastojanje =
        std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return rastojanje;
  }
  bool DaLiSadrzi(const NepreklapajuciKrug &k) const {
    std::pair<double, double> c = k.DajCentar();
    double d =
        std::sqrt((c.first - centar.first) * (c.first - centar.first) +
                  (c.second - centar.second) * (c.second - centar.second));
    return (d + k.r <= r);
  }
  friend NepreklapajuciKrug
  TransliraniNepreklapajuciKrug(const NepreklapajuciKrug &k, double delta_x,
                                double delta_y);
  friend NepreklapajuciKrug
  RotiraniNepreklapajuciKrug(const NepreklapajuciKrug &k, double alpha);
  friend NepreklapajuciKrug
  RotiraniNepreklapajuciKrug(const NepreklapajuciKrug &k,
                             const std::pair<double, double> &centar_rotacije,
                             double alpha);
};

NepreklapajuciKrug *NepreklapajuciKrug::posljednji = nullptr;

NepreklapajuciKrug TransliraniNepreklapajuciKrug(const NepreklapajuciKrug &k,
                                                 double delta_x,
                                                 double delta_y) {
  NepreklapajuciKrug novi;
  novi.centar = k.centar;
  novi.r = k.r;
  novi.Transliraj(delta_x, delta_y);
  return novi;
}

NepreklapajuciKrug RotiraniNepreklapajuciKrug(const NepreklapajuciKrug &k,
                                              double alpha) {
  NepreklapajuciKrug novi;
  novi.centar = k.centar;
  novi.r = k.r;
  novi.Rotiraj(alpha);
  return novi;
}

NepreklapajuciKrug
RotiraniNepreklapajuciKrug(const NepreklapajuciKrug &k,
                           const std::pair<double, double> &centar_rotacije,
                           double alpha) {
  NepreklapajuciKrug novi;
  novi.centar = k.centar;
  novi.r = k.r;
  novi.Rotiraj(centar_rotacije, alpha);
  return novi;
}

int main() {
  
      int n;
      std::cout << "Unesite broj krugova: ";
      while (!(std::cin >> n) || n <= 0) {
        std::cout << "Neispravan broj krugova, unesite ponovo! ";
        std::cin.ignore(10000, '\n');
        std::cin.clear();
      }
      std::vector<std::shared_ptr<NepreklapajuciKrug>> krugovi;
      for (int i = 0; i < n; i++) {
        double r;
        std::pair<double, double> centar;
          std::cout << "Unesite centar za " << i + 1 << ". krug: ";
          while (!(std::cin >> centar.first >> centar.second)) {
            std::cout << "Neispravan centar!" << std::endl << "Unesite ponovo centar za " << i + 1 << ". krug: "; 
            std::cin.clear();
            std::cin.ignore(10000,'\n');
          }
          std::cout << "Unesite poluprecnik: ";
        try {
          while (!( std::cin >> r) || r < 0) {
            std::cout << "Neispravan poluprecnik!" << std::endl << "Unesite ponovo poluprecnik za " << i + 1 << ". krug: "; std::cin.clear();
            std::cin.ignore(10000, '\n');
          }
          std::shared_ptr<NepreklapajuciKrug> krug =
              std::make_shared<NepreklapajuciKrug>(centar, r);
          krugovi.push_back(std::move(krug));
        } catch (std::logic_error e) {
          std::cout << e.what() << std::endl;
          i--;
        }
      }
      std::sort(krugovi.begin(), krugovi.end(),
                [](const std::shared_ptr<NepreklapajuciKrug> &k1,
                   const std::shared_ptr<NepreklapajuciKrug> &k2) {
                  return k1->DajPovrsinu() >= k2->DajPovrsinu();
                });
      std::cout << "Krugovi nakon obavljenog sortiranja: " << std::endl;
      for (const auto &krug : krugovi) {
        krug->Ispisi();
      }

  return 0;
}
