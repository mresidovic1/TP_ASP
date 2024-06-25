// TP 2022/2023: Zadaća 4, Zadatak 4
#include <cmath>
#include <iostream>
#include <map>
#include <memory>

class Korisnik {
  int clanski_broj;
  std::string ime_i_prezime;
  std::string adresa;
  std::string telefon;

public:
  Korisnik(int br, const std::string &I_I_P, const std::string &adr,const std::string &phone)
      : clanski_broj(br), ime_i_prezime(I_I_P), adresa(adr), telefon(phone) {}

  int DajClanskiBroj() const { return clanski_broj; }
  std::string DajImeIPrezime() const { return ime_i_prezime; }
  std::string DajAdresu() const { return adresa; }
  std::string DajTelefon() const { return telefon; }

  void Ispisi() const {
    std::cout << "Clanski broj: " << clanski_broj << std::endl;
    std::cout << "Ime i prezime: " << ime_i_prezime << std::endl;
    std::cout << "Adresa: " << adresa << std::endl;
    std::cout << "Telefon: " << telefon << std::endl;
  }
};

class Film {
  int ev_broj;
  int god_izd;
  bool cd;
  std::string naziv;
  std::string zanr;
  Korisnik *zaduzenje;

public:
  Film(int broj, bool dvd, const std::string &ime, const std::string &tip, int g)
      : ev_broj(broj), cd(dvd), naziv(ime), zanr(tip), god_izd(g), zaduzenje(nullptr) {}

  int DajEvidencijskiBroj() const { return ev_broj; }
  std::string DajNaziv() const { return naziv; }
  std::string DajZanr() const { return zanr; }
  int DajGodinuProdukcije() const { return god_izd; }
  bool DaLiJeDVD() const { return cd; }
  bool DaLiJeZaduzen() const { return zaduzenje != nullptr; }

  void ZaduziFilm(Korisnik *nn_lice) {
    if (DaLiJeZaduzen()) {
      throw std::domain_error("Film je vec zaduzen");
    }
    zaduzenje = nn_lice;
  }

  void RazduziFilm() {
    zaduzenje = nullptr;
  }

  Korisnik *DajKodKogaJe() {
    if (!DaLiJeZaduzen()) {
      throw std::domain_error("Film nije zaduzen");
    }
    return zaduzenje;
  }

  Korisnik *DajPokKodKogaJe() { 
      if(!DaLiJeZaduzen()) return nullptr;
      return zaduzenje; }

  void Ispisi() const {
    std::cout << "Evidencijski broj: " << ev_broj << std::endl;
    if (cd)
      std::cout << "Medij: DVD" << std::endl;
    else
      std::cout << "Medij: Video traka" << std::endl;
    std::cout << "Naziv filma: " << naziv << std::endl;
    std::cout << "Zanr: " << zanr << std::endl;
    std::cout << "Godina produkcije: " << god_izd << std::endl;
  }
};

class Videoteka {
  std::map<int, std::shared_ptr<Korisnik>> korisnici;
  std::map<int, std::shared_ptr<Film>> filmovi;

public:
  Videoteka() = default;

  Videoteka(const Videoteka& novi){
      for(const auto& pom : novi.korisnici){
          korisnici[pom.first]=std::make_shared<Korisnik>(*pom.second);
      }
      for(const auto& pom : novi.filmovi){
          filmovi[pom.first]=std::make_shared<Film>(*pom.second);
      }
  }
  Videoteka(Videoteka&& novi){
      korisnici=std::move(novi.korisnici);
      filmovi=std::move(novi.filmovi);
  }
  Videoteka& operator=(const Videoteka& novi){
      if(this==&novi){
          return *this;
      }
      korisnici.clear();
      filmovi.clear();
      for(const auto& pom : novi.korisnici){
          korisnici[pom.first]=std::make_shared<Korisnik>(*pom.second);
      }
      for(const auto& pom : novi.filmovi){
          filmovi[pom.first]=std::make_shared<Film>(*pom.second);
      }
    return *this;
  }
  Videoteka& operator=(Videoteka&& novi){
      if(this==&novi){
          return *this;
      }
      korisnici.clear();
      filmovi.clear();

      korisnici=std::move(novi.korisnici);
      filmovi=std::move(novi.filmovi);

      return *this;
  }

  void RegistrirajNovogKorisnika(int broj, const std::string &ime_i_prezime, const std::string &adresa, const std::string &telefon) {
    if (korisnici.count(broj) > 0) {
      throw std::logic_error("Vec postoji korisnik s tim clanskim brojem");
    }
    korisnici[broj] = std::make_shared<Korisnik>(broj, ime_i_prezime, adresa, telefon);
  }
  void RegistrirajNoviFilm(int broj, bool cd, const std::string &naziv,
                           const std::string &zanr, int god) {
    if (filmovi.count(broj) > 0) {
      throw std::logic_error("Film s tim evidencijskim brojem vec postoji");
    }
    filmovi[broj] = std::make_shared<Film>(broj, cd, naziv, zanr, god);
  }
  Korisnik &NadjiKorisnika(int broj) {
    auto it = korisnici.find(broj);
    if (it == korisnici.end()) {
      throw std::logic_error("Korisnik nije nadjen");
    }
    return *(it->second);
  }
  Film &NadjiFilm(int broj) {
    auto it = filmovi.find(broj);
    if (it == filmovi.end()) {
      throw std::logic_error("Film nije nadjen");
    }
    return *(it->second);
  }
  void IzlistajKorisnike() const {
    for (const auto &podaci : korisnici) {
      podaci.second->Ispisi();
      std::cout << std::endl;
    }
  }
  void IzlistajFilmove() const {
    for (const auto &podaci : filmovi) {
      podaci.second->Ispisi();
      if (podaci.second->DaLiJeZaduzen()) {
        std::cout << "Zaduzen kod korisnika: "
                  << podaci.second->DajKodKogaJe()->DajImeIPrezime() << " ("
                  << podaci.second->DajKodKogaJe()->DajClanskiBroj() << ")"<<std::endl;
      }
      std::cout << std::endl;
    }
  }
  void ZaduziFilm(int evid_broj, int cl_broj) {
    Film &film = NadjiFilm(evid_broj);
    if (film.DaLiJeZaduzen()) {
      throw std::logic_error("Film vec zaduzen");
    }
    Korisnik &korisnik = NadjiKorisnika(cl_broj);
    film.ZaduziFilm(&korisnik);
  }
  void RazduziFilm(int ev_broj) {
   auto it=filmovi.find(ev_broj);

   if(it==filmovi.end()){
       throw std::logic_error("Film nije nadjen");
   }
   std::shared_ptr<Film>& film=it->second;
   if(!film->DaLiJeZaduzen()){
       throw std::logic_error("Film nije zaduzen");
   }
   film->RazduziFilm();

  }
  void PrikaziZaduzenja(int cl_broj) const {
    auto it = korisnici.find(cl_broj);
    if (it == korisnici.end()) {
      throw std::logic_error("Korisnik nije nadjen");
    }
    bool pronadjeno = false;
    for (const auto &par : filmovi) {
      const std::shared_ptr<Film> &film = par.second;
      if (film->DaLiJeZaduzen() &&
          film->DajKodKogaJe()->DajClanskiBroj() == cl_broj) {
        pronadjeno = true;
        film->Ispisi();
        std::cout << std::endl;
      }
    }
    if (!pronadjeno) {
      std::cout << "Korisnik nema zaduzenja!" << std::endl;
    }
  }
};

int main() {
  Videoteka TP;
  std::cout << "*******VIDEOTEKA TP,IZVOLITE*********\n";
  std::cout << "*        IZABERITE OPCIJU:          *\n";
  std::cout << "* A~registriranje korisnika         *\n";
  std::cout << "* B~registriranje filma             *\n";
  std::cout << "* C~korisnik                        *\n";
  std::cout << "* D~filmovi                         *\n";
  std::cout << "* F~zaduzi se                       *\n";
  std::cout << "* F~razduzi se                      *\n";
  std::cout << "* G~zaduzenja.                      *\n";
  std::cout << "* H~dovidjenja                      *\n";
  std::cout << std::endl;
  char opcija;
  std::cout << "Molimo unesite opciju: \n";
  while (std::cin >> opcija && opcija != 'H') {
    if (opcija == 'A') {
      int n;
      std::string ime_i_prezime, adresa, br_telefona;
      std::cout << "Unesite broj korisnika: \n";
      std::cin >> n;
      std::cout << "Unesite ime i prezime korisnika: \n";
      std::cin.ignore(10000, '\n');
      std::cin.clear();
      std::getline(std::cin, ime_i_prezime);
      std::cout << "Unesite adresu korisnika: \n";
      std::getline(std::cin, adresa);
      std::cout << "Unesite broj telefona korisnika: \n";
      std::getline(std::cin, br_telefona);
      try {
        TP.RegistrirajNovogKorisnika(n, ime_i_prezime, adresa, br_telefona);
        continue;
      } catch (std::logic_error e) {
        std::cout << e.what();
      }
    } else if (opcija == 'B') {
      int n, god;
      bool cd;
      std::string ime, zanr;
      std::cout << "Evidencijski broj filma: \n";
      std::cin >> n;
      std::cout << "DVD (1-DA, 0-NE): \n";
      std::cin >> cd;
      std::cout << "Ime filma: \n";
      std::cin.ignore(10000, '\n');
      std::cin.clear();
      std::getline(std::cin, ime);
      std::cout << "Zanr filma: \n";
      std::getline(std::cin, zanr);
      std::cout << "Godina produkcije: \n";
      std::cin >> god;
      try {
        TP.RegistrirajNoviFilm(n, cd, ime, zanr, god);
        continue;
      } catch (std::logic_error e) {
        std::cout << e.what();
      }
    } else if (opcija == 'C') {
      std::cout << "Lista korisnika: \n";
      TP.IzlistajKorisnike();
      continue;
    } else if (opcija == 'D') {
      std::cout << "Lista filmova: \n";
      TP.IzlistajFilmove();
      continue;
    } else if (opcija == 'E') {
      int ev_broj, cl_broj;
      std::cout << "Evidencijski broj: \n";
      std::cin >> ev_broj;
      std::cout << "Clanski broj: \n";
      std::cin >> cl_broj;
      try {
        TP.ZaduziFilm(ev_broj, cl_broj);
        continue;
      } catch (std::logic_error e) {
        std::cout << e.what();
      }
    } else if (opcija == 'F') {
      int ev_broj;
      std::cout << "Evidencijski broj: \n";
      std::cin >> ev_broj;
      try {
        TP.RazduziFilm(ev_broj);
        continue;
      } catch (std::logic_error e) {
        std::cout << e.what();
      }
    } else if (opcija == 'G') {
      int cl_broj;
      std::cout << "Clanski broj: \n";
      std::cin >> cl_broj;
      try {
        TP.PrikaziZaduzenja(cl_broj);
        continue;
      } catch (std::logic_error e) {
        std::cout << e.what();
      }
    }
  }
  std::cout << "Hvala Vam na druzenju i dodjite nam opet!";
 

  return 0;
}
