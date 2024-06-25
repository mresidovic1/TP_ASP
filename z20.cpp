// TP 2022/2023: Zadaća 5, Zadatak 1
#include <cmath>
#include <iostream>
#include <tuple>

const double PI = 4 * std::atan(1);

class Sinusoida {
  double amplituda, frekvencija, faza;

public:
  Sinusoida(double amplituda, double frekvencija, double faza) {
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    } else
      this->amplituda = amplituda;
    if (frekvencija < 0) {
      this->frekvencija = std::fabs(frekvencija);
      faza += PI;
      faza = -faza;
    } else
      this->frekvencija = frekvencija;
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    this->faza = faza;
  }
  double DajAmplitudu() const { return amplituda; }
  double DajFrekvenciju() const { return frekvencija; }
  double DajFazu() const { return faza; }
  std::tuple<double, double, double> DajParametre() const {
    return std::make_tuple(amplituda, frekvencija, faza);
  }
  Sinusoida &PostaviAmplitudu(double amplituda) {
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    } else {
      this->amplituda = amplituda;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  Sinusoida &PostaviFrekvenciju(double frekvencija) {
    if (frekvencija < 0) {
      faza = -faza;
      this->frekvencija = std::fabs(frekvencija);
    } else {
      this->frekvencija = frekvencija;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  Sinusoida &PostaviFazu(double faza) {
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    this->faza = faza;
    return *this;
  }
  Sinusoida &PostaviParametre(std::tuple<double, double, double> parametri) {
    amplituda = std::get<0>(parametri);
    frekvencija = std::get<1>(parametri);
    faza = std::get<2>(parametri);
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    }
    if (frekvencija < 0) {
      this->frekvencija = std::fabs(frekvencija);
      faza += PI;
      faza = -faza;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  Sinusoida operator+(const Sinusoida &pom) {
    if (frekvencija != pom.frekvencija) {
      throw std::domain_error("Razlicite frekvencije");
    }
    double amplituda_rez =
        std::sqrt(amplituda * amplituda + pom.amplituda * pom.amplituda -
                  2 * amplituda * pom.amplituda * std::cos(faza - pom.faza));
    double faza_rez;
    if (faza > 0) {
      faza_rez = std::atan2(
          amplituda * std::sin(faza) - pom.amplituda * std::sin(pom.faza),
          amplituda * std::cos(faza) - pom.amplituda * std::cos(pom.faza));
    } else {
      faza_rez = std::atan2(
          amplituda * std::sin(faza) + pom.amplituda * std::sin(pom.faza),
          amplituda * std::cos(faza) + pom.amplituda * std::cos(pom.faza));
    }
    return Sinusoida(amplituda_rez, frekvencija, faza_rez);
  }
  Sinusoida operator-(const Sinusoida &pom) {
    if (frekvencija != pom.frekvencija) {
      throw std::domain_error("Razlicite frekvencije");
    }
    double amplituda_rez =
        std::sqrt(amplituda * amplituda + pom.amplituda * pom.amplituda +
                  2 * amplituda * pom.amplituda * std::cos(faza - pom.faza));
    double faza_rez;
    if (faza > 0) {
      faza_rez = std::atan2(
          amplituda * std::sin(faza) + pom.amplituda * std::sin(pom.faza),
          amplituda * std::cos(faza) + pom.amplituda * std::cos(pom.faza));
    } else {
      faza_rez = std::atan2(
          amplituda * std::sin(faza) - pom.amplituda * std::sin(pom.faza),
          amplituda * std::cos(faza) - pom.amplituda * std::cos(pom.faza));
    }

    if (amplituda_rez < 0) {
      amplituda_rez = std::fabs(amplituda_rez);
      faza_rez += PI;
    }
    while (faza_rez < -PI) {
      faza_rez += 2 * PI;
    }
    while (faza_rez > PI) {
      faza_rez -= 2 * PI;
    }
    return Sinusoida(amplituda_rez, frekvencija, faza_rez);
  }
  Sinusoida operator-() {
    double amplituda_rez = -amplituda;
    double faza_rez = faza + PI;
    while (faza_rez > PI) {
      faza_rez -= 2 * PI;
    }
    while (faza_rez < -PI) {
      faza_rez += 2 * PI;
    }
    if (amplituda_rez < 0) {
      amplituda_rez = std::fabs(amplituda_rez);
      faza_rez += 2 * PI;
    }
    return Sinusoida(amplituda_rez, frekvencija, faza_rez);
  }
  Sinusoida operator*(double skalar) const {
    double amplituda_rez = amplituda * skalar;
    return Sinusoida(amplituda_rez, frekvencija, faza);
  }
  friend Sinusoida operator*(double skalar, const Sinusoida &sinusoida) {
    return sinusoida * skalar;
  }
  Sinusoida &operator/(double skalar) {
    amplituda/=skalar;
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    }
    if (frekvencija < 0) {
      this->frekvencija = std::fabs(frekvencija);
      faza += PI;
      faza = -faza;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  Sinusoida &operator+=(const Sinusoida &pom) {
    if (frekvencija != pom.frekvencija) {
      throw std::domain_error("Razlicite frekvencije");
    }
     double amplituda_rez =
        std::sqrt(amplituda * amplituda + pom.amplituda * pom.amplituda +
                  2 * amplituda * pom.amplituda * std::cos(faza - pom.faza));
    amplituda =amplituda_rez;
    faza+=pom.faza;
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    }
    if (frekvencija < 0) {
      this->frekvencija = std::fabs(frekvencija);
      faza += PI;
      faza = -faza;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  Sinusoida &operator-=(const Sinusoida &pom) {
    if (frekvencija != pom.frekvencija) {
      throw std::domain_error("Razlicite frekvencije");
    }
    double amplituda_rez =
        std::sqrt(amplituda * amplituda + pom.amplituda * pom.amplituda +
                  2 * amplituda * pom.amplituda * std::cos(faza - pom.faza));
    amplituda=amplituda_rez;
    faza-=pom.faza;
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    }
    if (frekvencija < 0) {
      this->frekvencija = std::fabs(frekvencija);
      faza += PI;
      faza = -faza;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  Sinusoida &operator*=(double skalar) {
    amplituda *= skalar;
    faza*=skalar;
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    }
    if (frekvencija < 0) {
      this->frekvencija = std::fabs(frekvencija);
      faza += PI;
      faza = -faza;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  Sinusoida &operator/=(double skalar) {
    amplituda /= skalar;
    if (amplituda < 0) {
      this->amplituda = std::fabs(amplituda);
      faza += PI;
    }
    if (frekvencija < 0) {
      this->frekvencija = std::fabs(frekvencija);
      faza += PI;
      faza = -faza;
    }
    while (faza > PI) {
      faza -= 2 * PI;
    }
    while (faza < -PI) {
      faza += 2 * PI;
    }
    return *this;
  }
  double operator()(double vrijeme) const {
    return amplituda * std::sin(frekvencija * vrijeme + faza);
  }
  double operator[](const std::string &naziv) const {
    if (naziv == "A") {
      return amplituda;
    } else if (naziv == "omega" || naziv == "w") {
      return frekvencija;
    } else if (naziv == "phi" || naziv == "fi") {
      return faza;
    } else {
      throw std::domain_error("Neispravan naziv parametra");
    }
  }
  double &operator[](const std::string &naziv) {
    if (naziv == "A") {
      return amplituda;
    } else if (naziv == "omega" || naziv == "w") {
      return frekvencija;
    } else if (naziv == "phi" || naziv == "fi") {
      return faza;
    } else {
      throw std::domain_error("Neispravan naziv parametra");
    }
  }
};

int main() {
 
  /*Sinusoida s1(10, 3, 20);
  Sinusoida s2(15, 2, 50);

  try {
    Sinusoida s3(s1 + s2);
    s3 = s1 - s2;
  } catch (std::domain_error e) {
    std::cout << e.what() << std::endl;
  }

  s2.PostaviFrekvenciju(-3);


       Sinusoida sin1(1.0,3.0,0.5);
       Sinusoida sin2(0.5,3.0,-2.0);

       Sinusoida sin3=sin1+sin2;
       std::cout<<"Amplituda: "<<sin3.DajAmplitudu()<<std::endl;
       std::cout<<"Frekvencija: "<<sin3.DajFrekvenciju()<<std::endl;
       std::cout<<"Faza: "<<sin3.DajFazu()<<std::endl;

       sin3*=4.0;
       std::cout<<"Amplituda: "<<sin3["A"]<<std::endl;
       std::cout<<"Frekvencija: "<<sin3["omega"]<<std::endl;
       std::cout<<"Faza: "<<sin3["phi"]<<std::endl;

       double vrijeme=0.4;
       double rez=sin3(vrijeme);
       std::cout<<"Vrijednost u vremenu t= "<<vrijeme<<": "<<rez<<std::endl;
*/

  return 0;
}
