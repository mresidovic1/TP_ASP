// TP 2022/2023: Zadaća 4, Zadatak 3
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>


class Polazak {
  std::string naziv_podredista, oznaka_voznje;
  int br_perona, sati, minute, trajanje, kasnjenje;

public:
  Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje, int kasnjenje);
  void PostaviKasnjenje(int kasnjenje) {
    if (kasnjenje < 0)
      throw std::domain_error("Nemoguca situacija");
    this->kasnjenje = kasnjenje;
  }
  bool DaLiKasni() const { return kasnjenje > 0; }
  int DajTrajanje() const { return trajanje; }
  void OcekivanoVrijemePolaska(int &sati, int &minute) const ;
  void OcekivanoVrijemeDolaska(int &sati, int &minute) const;
  void Ispisi() const ;
};

Polazak::Polazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska, int trajanje_voznje, int kasnjenje=0) {
    if (broj_perona < 1 || broj_perona > 15)
      throw std::domain_error("Broj perona mora biti u opsegu 1-15.");
    if (sat_polaska < 0 || sat_polaska > 24)
      throw std::domain_error("Netacno vrijeme!");
    if (kasnjenje < 0)
      throw std::domain_error("Nemoguca situacija");
    if (minute_polaska < 0 || minute_polaska > 60)
      throw std::domain_error("Netacno vrijeme!");
    if (trajanje_voznje < 0)
      throw std::domain_error("Nemoguca situacija");
    naziv_podredista = odrediste;
    this->oznaka_voznje = oznaka_voznje;
    br_perona = broj_perona;
    sati = sat_polaska;
    minute = minute_polaska;
    trajanje = trajanje_voznje;
    this->kasnjenje = kasnjenje;
  }

   void Polazak::OcekivanoVrijemePolaska(int &sati, int &minute) const {
    minute = this->minute;
    sati = this->sati;
    minute += kasnjenje;
    while (minute >= 60) {
      sati++;
      minute -= 60;
    }
    if (sati == 24)
      sati = 0;
  }

  void Polazak::OcekivanoVrijemeDolaska(int &sati, int &minute) const {
    minute = this->minute;
    sati = this->sati;
    minute += kasnjenje + trajanje;
    while (minute >= 60) {
      sati++;
      minute -= 60;
    }
    if (sati == 24)
      sati = 0;
  }

  void Polazak::Ispisi() const {
    int novi_sati = sati;
    int nove_minute = minute;
    OcekivanoVrijemePolaska(novi_sati, nove_minute);
    bool kasni = false;
    if (minute != nove_minute) {
      kasni = true;
    }
    if (nove_minute < 10) {
      std::cout << std::setfill(' ') << std::right << oznaka_voznje << "  "
                << std::setw(8) << std::right << naziv_podredista
                << std::setw(35) << "   " << std::right << novi_sati << ":"
                << std::right << "0" << std::right << nove_minute << "   ";
      if (kasni) {
        if (std::fabs(nove_minute - minute < 10))
          std::cout << std::right << "(Planirano " << std::right << sati << ":0"
                    << std::right << minute << ", Kasni " << std::right
                    << std::fabs(nove_minute - minute) << " min)" << std::endl;
        else
          std::cout << std::right << "(Planirano " << std::right << sati << ":"
                    << std::right << minute << ", Kasni " << std::right
                    << std::fabs(nove_minute - minute) << " min)" << std::endl;
      } else {
        OcekivanoVrijemeDolaska(novi_sati, nove_minute);
        std::cout << std::right << novi_sati << std::right << ":"
                  << "0" << std::right << nove_minute << std::right << "   "
                  << br_perona << std::endl;
      }
    } else {
      std::cout << std::setfill(' ') << std::right << oznaka_voznje << "  "
                << std::setw(8) << naziv_podredista << std::setw(35) << "   "
                << std::left << novi_sati << ":" << std::left << nove_minute
                << "   ";
      OcekivanoVrijemeDolaska(novi_sati, nove_minute);
      std::cout << novi_sati << std::left << ":" << nove_minute << std::left
                << "   " << br_perona << std::endl;
    }
  }
  

class Polasci {
  Polazak **polasci;
  int max_prolasci;
  int trenutni_prolasci;

public:
  explicit Polasci(int max_broj_polazaka)
      : max_prolasci(max_broj_polazaka), trenutni_prolasci(0) {
    polasci = new Polazak *[max_prolasci];
  }
  Polasci(std::initializer_list<Polazak> lista_polazaka) : max_prolasci(lista_polazaka.size()), trenutni_prolasci(0) {
    polasci = new Polazak *[max_prolasci];
    for (const Polazak &polazak : lista_polazaka) {
      Polazak *novi_polazak = new Polazak(polazak);
      polasci[trenutni_prolasci++] = novi_polazak;
    }
  }
  ~Polasci() {
    IsprazniKolekciju();
    delete[] polasci;
  }
  Polasci(const Polasci &polasci) : max_prolasci(polasci.max_prolasci), trenutni_prolasci(0) {
    this->polasci = new Polazak *[max_prolasci];
    for (int i = 0; i < polasci.trenutni_prolasci; i++) {
      Polazak *novi = new Polazak(*polasci.polasci[i]);
      this->polasci[trenutni_prolasci++] = novi;
    }
  }
  Polasci(Polasci &&polasci) : max_prolasci(polasci.max_prolasci), polasci(polasci.polasci), trenutni_prolasci(polasci.trenutni_prolasci) {
    polasci.polasci = nullptr;
    polasci.max_prolasci = 0;
    polasci.trenutni_prolasci = 0;
  }
  Polasci &operator=(const Polasci &polasci);
  Polasci &operator=(Polasci &&polasci);
  void RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska,int trajanje_voznje);
  void RegistrirajPolazak(Polazak *polazak);
  int DajBrojPolazaka() const { return trenutni_prolasci; }
  int DajBrojPolazakaKojiKasne() const ;
  Polazak &DajPrviPolazak() ;
  Polazak DajPrviPolazak() const ;
  Polazak &DajPosljednjiPolazak();
  Polazak DajPosljednjiPolazak() const;
  void Ispisi() const ;
  void IsprazniKolekciju() {
    for (int i = 0; i < trenutni_prolasci; i++) {
      delete polasci[i];
    }
    trenutni_prolasci = 0;
  }
};

Polasci &Polasci::operator=(const Polasci &polasci) {
    if (this == &polasci) {
      return *this;
    }
    IsprazniKolekciju();
    delete[] this->polasci;
    this->max_prolasci = polasci.max_prolasci;
    this->polasci = new Polazak *[max_prolasci];
    this->trenutni_prolasci = 0;
    for (int i = 0; i < polasci.trenutni_prolasci; i++) {
      Polazak *novi = new Polazak(*polasci.polasci[i]);
      this->polasci[trenutni_prolasci++] = novi;
    }
    return *this;
  }

    Polasci &Polasci::operator=(Polasci &&polasci) {
    if (this == &polasci) {
      return *this;
    }
    IsprazniKolekciju();
    delete[] this->polasci;
    this->polasci = polasci.polasci;
    this->max_prolasci = polasci.max_prolasci;
    this->trenutni_prolasci = polasci.trenutni_prolasci;
    polasci.polasci = nullptr;
    polasci.max_prolasci = 0;
    polasci.trenutni_prolasci = 0;
    return *this;
  }

    void Polasci::RegistrirajPolazak(std::string odrediste, std::string oznaka_voznje, int broj_perona, int sat_polaska, int minute_polaska,int trajanje_voznje) {
    if (trenutni_prolasci == max_prolasci) {
      throw std::range_error("Dostignut maksimalni broj polazaka");
    }
    Polazak *novi = new Polazak(odrediste, oznaka_voznje, broj_perona, sat_polaska, minute_polaska, trajanje_voznje);
    polasci[trenutni_prolasci++] = novi;
  }

    void Polasci::RegistrirajPolazak(Polazak *polazak) {
    if (trenutni_prolasci == max_prolasci) {
      throw std::range_error("Dostignut maksimalni broj polazaka");
    }
    polasci[trenutni_prolasci++] = polazak;
  }

  int Polasci::DajBrojPolazakaKojiKasne() const {
    int br_kasne = 0;
    for (int i = 0; i < trenutni_prolasci; i++) {
      if (polasci[i]->DaLiKasni()) {
        br_kasne++;
      }
    }
    return br_kasne;
  }

  Polazak &Polasci::DajPrviPolazak() {
    if (trenutni_prolasci == 0) {
      throw std::logic_error("Nema registriranih polazaka");
    }
    Polazak** it=std::min_element(polasci, polasci+trenutni_prolasci,[](const Polazak *p1, const Polazak *p2){
        int sati_x, minute_x, sati_y, minute_y;
                p1->OcekivanoVrijemePolaska(sati_x, minute_x);
                p2->OcekivanoVrijemePolaska(sati_y, minute_y);
                if (sati_x < sati_y)
                  return true;
                else if (sati_x == sati_y && minute_x < minute_y)
                  return true;
                else
                  return false;
    });
    return **it;
  }

  Polazak Polasci::DajPrviPolazak() const {
     if (trenutni_prolasci == 0) {
      throw std::logic_error("Nema registriranih polazaka");
    }
    Polazak** it=std::min_element(polasci, polasci+trenutni_prolasci,[](const Polazak *p1, const Polazak *p2){
        int sati_x, minute_x, sati_y, minute_y;
                p1->OcekivanoVrijemePolaska(sati_x, minute_x);
                p2->OcekivanoVrijemePolaska(sati_y, minute_y);
                if (sati_x < sati_y)
                  return true;
                else if (sati_x == sati_y && minute_x < minute_y)
                  return true;
                else
                  return false;
    });
    return **it;
  }

   Polazak &Polasci::DajPosljednjiPolazak() {
    if (trenutni_prolasci == 0) {
      throw std::logic_error("Nema registriranih polazaka");
    }
    Polazak** it=std::max_element(polasci, polasci+trenutni_prolasci,[](const Polazak *p1, const Polazak *p2){
        int sati_x, minute_x, sati_y, minute_y;
                p1->OcekivanoVrijemePolaska(sati_x, minute_x);
                p2->OcekivanoVrijemePolaska(sati_y, minute_y);
                if (sati_x < sati_y)
                  return true;
                else if (sati_x == sati_y && minute_x < minute_y)
                  return true;
                else
                  return false;
    });
    return **it;
  }

  Polazak Polasci::DajPosljednjiPolazak() const {
    if (trenutni_prolasci == 0) {
      throw std::logic_error("Nema registriranih polazaka");
    }
    Polazak** it=std::max_element(polasci, polasci+trenutni_prolasci,[](const Polazak *p1, const Polazak *p2){
        int sati_x, minute_x, sati_y, minute_y;
                p1->OcekivanoVrijemePolaska(sati_x, minute_x);
                p2->OcekivanoVrijemePolaska(sati_y, minute_y);
                if (sati_x < sati_y)
                  return true;
                else if (sati_x == sati_y && minute_x < minute_y)
                  return true;
                else
                  return false;
    });
    return **it;
  }

  void Polasci::Ispisi() const {
    std::sort(polasci, polasci + trenutni_prolasci, [](const Polazak *x, const Polazak *y) {
                int sati_x, minute_x, sati_y, minute_y;
                x->OcekivanoVrijemePolaska(sati_x, minute_x);
                y->OcekivanoVrijemePolaska(sati_y, minute_y);
                if (sati_x < sati_y)
                  return true;
                else if (sati_x == sati_y && minute_x < minute_y)
                  return true;
                else
                  return false;
              });
    std::cout << std::setw(10) << "Voznja" << std::setw(20) << " " << std::setw(10) << "Odrediste" << std::setw(10) << "Polazak" << std::setw(10) << "Dolazak" << std::setw(10) << "Peron" << std::endl;
    std::cout << std::setfill('-') << std::setw(70) << "-" << std::endl;
    std::setfill(' ');
    for (int i = 0; i < trenutni_prolasci; i++) {
      polasci[i]->Ispisi();
    }
  }

int main() {
try{
  Polasci linije(5);

  linije.RegistrirajPolazak("Maglaj","AB123",7, 10, 30, 50);
  linije.RegistrirajPolazak("Zepce","BA321",8, 12, 40, 20);
  linije.RegistrirajPolazak("Zenica","CD456",9, 14, 35, 30);
  linije.RegistrirajPolazak("Tesanj","DC654",10, 16, 45, 40);
  linije.RegistrirajPolazak("Tuzla","FF115",11, 18, 50, 80);

linije.Ispisi();

int br_polazaka=linije.DajBrojPolazaka();
std::cout<<"Broj polazaka: "<<br_polazaka<<std::endl;

int kasne=linije.DajBrojPolazakaKojiKasne();
std::cout<<"Broj polazaka koji kasne: "<<kasne<<std::endl;

Polazak& prvi=linije.DajPrviPolazak();
std::cout<<"Prvi polazak je: "<<std::endl;
prvi.Ispisi();
std::cout<<std::endl;

Polazak& posljednji=linije.DajPosljednjiPolazak();
std::cout<<"Posljednji polazak je: "<<std::endl;
posljednji.Ispisi();
std::cout<<std::endl;

Polazak linija1("Maglaj","AB123",7, 15, 30, 100);
Polazak linija2("Zepce","BA321",8, 12, 30, 100);
Polazak linija3("Zenica","CD456",9, 40, 30, 100);
Polazak linija4("Tesanj","DC654",10, 30, 30, 100);
Polazak linija5("Tuzla","FF115",11, 50, 30, 100);

std::cout<<"Informacije o polascima: "<<std::endl;
linija1.Ispisi();
linija2.Ispisi();
linija3.Ispisi();
linija4.Ispisi();
linija5.Ispisi();

std::cout<<"Linija1 ce mozda kasniti: "<<std::endl;
linija1.PostaviKasnjenje(10);
linija1.Ispisi();

std::cout<<"Linija2 ce voziti tacno: "<<linija2.DajTrajanje()<<std::endl;
int min,sec;
linija3.PostaviKasnjenje(44);
linija3.OcekivanoVrijemePolaska(min, sec);
std::cout<<"Linija3 ce krenuti u: "<<min<<":"<<sec<<std::endl;
linija3.OcekivanoVrijemeDolaska(min, sec);
std::cout<<"Linija 3 ce stici u: "<<min<<":"<<sec;
}
catch(std::domain_error e){
    std::cout<<"GRESKA: "<<e.what();
}
catch(std::logic_error e){
    std::cout<<"GRESKA: "<<e.what();
}
catch(...){
    std::cout<<"Neka greska";
}

return 0;

}
