// TP 2022/2023: Zadaća 2, Zadatak 1
#include <cctype>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::vector<char>> Matrica;
Matrica PacMan(23, std::vector<char>(63, ' '));
bool vidis_me = true;
bool prazan = true;
bool dovidjenja = false;
enum class Pravci { Sjever,Sjeveroistok,Istok,Jugoistok,Jug,Jugozapad,Zapad, Sjeverozapad };
enum class KodoviGresaka { PogresnaKomanda,NedostajeParametar,SuvisanParametar,NeispravanParametar };
enum class Komande { Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj };

std::string Orijentacija(Pravci &orijentacija) {
  int i = 0;
  std::vector<std::string> Smjerovi{"sjever", "sjeveroistok", "istok", "jugoistok", "jug", "jugozapad", "zapad", "sjeverozapad"};
  for (i = 0; i < Smjerovi.size(); i++) {
    if (static_cast<int>(orijentacija) == i) {
      break;
    }
  }
  return Smjerovi.at(i);
}

void OkujMeCare() {
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 63; j++) {
    if(i==11 && j==31 && vidis_me) PacMan.at(i).at(j)='O';
      if (i == 0 || i == 22)
        PacMan.at(i).at(j) = '#';
      else if (j == 0 || j == 62)
        PacMan.at(i).at(j) = '#';
    }
  }
}

void PrijaviGresku(KodoviGresaka kod_greske) {
  switch (kod_greske) {
  case KodoviGresaka::NedostajeParametar:
    std::cout << "Komanda trazi parametar koji nije naveden!" << std::endl;
    break;
  case KodoviGresaka::PogresnaKomanda:
    std::cout << "Nerazumljiva komanda!" << std::endl;
    break;
  case KodoviGresaka::NeispravanParametar:
    std::cout << "Parametar komande nije ispravan!" << std::endl;
    break;
  case KodoviGresaka::SuvisanParametar:
    std::cout << "Zadan je suvisan parametar nakon komande!" << std::endl;
    break;
  }
}
bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske) {
  // stoti pokusaj
  char unos;
  parametar = 0;
  bool negativan = false;
  std::cout << "Unesi komandu: ";
  unos = std::cin.get();
  while (unos != '\n') {
    while (unos == '\t' || unos == ' ')
      unos = std::cin.get();
    if (unos == 'I') {
      komanda = Komande::Idi;
      unos = std::cin.get();
      while (unos == '\t' || unos == ' ')
        unos = std::cin.get();
      if (unos == '\n') {
        kod_greske = KodoviGresaka::NedostajeParametar;
        return false;
      }
      while (unos == '\t' || unos == ' ')
        unos = std::cin.get();
      if (unos == '-') {
        negativan = true;
        unos = std::cin.get();
      }
      while (unos == '\t' || unos == ' ')
        unos = std::cin.get();
      if (!std::isdigit(unos)) {
        kod_greske = KodoviGresaka::NeispravanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      parametar = 0;
      while (std::isdigit(unos)) {
        parametar *= 10;
        parametar += unos - '0';
        unos = std::cin.get();
      }
      if (unos != isdigit(unos) && unos!=' ' && unos!='\n') {
        kod_greske = KodoviGresaka::NeispravanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      if (negativan)
        parametar *= (-1);
      while (unos == '\t' || unos == ' ')
        unos = std::cin.get();
      if (unos != '\n') {
        kod_greske = KodoviGresaka::SuvisanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      return true;
    } else if (unos == 'R') {
      komanda = Komande::Rotiraj;
      unos = std::cin.get();
      while (unos == ' ' || unos == '\t')
        unos = std::cin.get();
      if (unos == '\n') {
        kod_greske = KodoviGresaka::NedostajeParametar;
        return false;
      }
      while (unos == ' ' || unos == '\t')
        unos = std::cin.get();
      if (unos == '-') {
        negativan = true;
        unos = std::cin.get();
      }
      while (unos == ' ')
        unos = std::cin.get();
      if (!std::isdigit(unos)) {
        kod_greske = KodoviGresaka::NeispravanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      parametar = 0;
      while (std::isdigit(unos)) {
        parametar *= 10;
        parametar += unos - '0';
        unos = std::cin.get();
      }
      if (unos != isdigit(unos) && unos!=' ' && unos!='\n') {
        kod_greske = KodoviGresaka::NeispravanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      if (negativan)
        parametar *= (-1);
      while (unos == '\t' || unos == ' ')
        unos = std::cin.get();
      if (unos != '\n') {
        kod_greske = KodoviGresaka::SuvisanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      return true;
    } else if (unos == 'T') {
      komanda = Komande::PrikaziTeren;
      unos = std::cin.get();
      while (unos == ' ') {
        unos = std::cin.get();
      }
      if (unos != '\n') {
        kod_greske = KodoviGresaka::SuvisanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      return true;
    } else if (unos == 'S') {
      unos = std::cin.get();
       while (unos == ' ') {
          unos = std::cin.get();
        }
      if(unos!='\n' && unos!='+' && unos!='-'){
          kod_greske=KodoviGresaka::PogresnaKomanda;
          std::cin.ignore(10000,'\n');
          return false;
      }
      if (unos == '\n') {
        kod_greske = KodoviGresaka::NeispravanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      }
      if (unos == '+') {
        komanda = Komande::Sakrij;
        unos = std::cin.get();
        while (unos == ' ') {
          unos = std::cin.get();
        }
        if (unos != '\n') {
          kod_greske = KodoviGresaka::SuvisanParametar;
          std::cin.ignore(10000, '\n');
          return false;
        }
      } else if (unos == '-') {
        komanda = Komande::Otkrij;
        unos = std::cin.get();
        while (unos == ' ') {
          unos = std::cin.get();
        }
        if (unos != '\n') {
          kod_greske = KodoviGresaka::SuvisanParametar;
          std::cin.ignore(10000, '\n');
          return false;
        }
      }
      return true;
    } else if (unos == 'K') {
      komanda = Komande::Kraj;
      unos = std::cin.get();
      while (unos == ' ') {
        unos = std::cin.get();
      }
      if (unos != '\n') {
        kod_greske = KodoviGresaka::SuvisanParametar;
        std::cin.ignore(10000, '\n');
        return false;
      } 
      return true;
    } else {
      kod_greske = KodoviGresaka::PogresnaKomanda;
      std::cin.ignore(10000, '\n');
      return false;
    }
    unos = std::cin.get();
  }
  return true;
}

void Idi(int &x, int &y, Pravci orijentacija, int korak) {

  bool pozitivan = korak > 0;
  if(vidis_me) PacMan.at(-y+11).at(x+31)='*';
  for (int i = 0; i < std::abs(korak); i++) {
    if (korak != 0)
      prazan = false;
    if (korak > 0) {
      switch (orijentacija) {
      case Pravci::Sjever:
        y++;
        if (y > 10)
          y = -10;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Jug:
        y--;
        if (y < -10)
          y = 10;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Istok:
        x++;
        if (x > 30)
          x = -30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Zapad:
        x--;
        if (x < -30)
          x = 30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Sjeveroistok:
        x++;
        y++;
        if (y > 10)
          y = -10;
        if (x > 30)
          x = -30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Sjeverozapad:
        x--;
        y++;
        if (y > 10)
          y = -10;
        if (x < -30)
          x = 30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Jugoistok:
        x++;
        y--;
        if (y < -10)
          y = 10;
        if (x > 30)
          x = -30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Jugozapad:
        x--;
        y--;
        if (y < -10)
          y = 10;
        if (x < -30)
          x = 30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      }
    } else if (korak < 0) {
      switch (orijentacija) {
      case Pravci::Sjever:
        y--;
        if (y < -10)
          y = 10;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Jug:
        y++;
        if (y > 10)
          y = -10;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Istok:
        x--;
        if (x < -30)
          x = 30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Zapad:
        x++;

        if (x > 30)
          x = -30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Sjeveroistok:
        x--;
        y--;
        if (y < -10)
          y = 10;
        if (x < -30)
          x = 30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Sjeverozapad:
        x++;
        y--;
        if (y < -10)
          y = 10;
        if (x > 30)
          x = -30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Jugoistok:
        x--;
        y++;
        if (y > 10)
          y = -10;
        if (x < -30)
          x = 30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      case Pravci::Jugozapad:
        x++;
        y++;
        if (y > 10)
          y = -10;
        if (x > 30)
          x = -30;
        if (vidis_me) {
          PacMan.at(-y+11).at(x+31) = '*';
        }
        break;
      }
    }
  }
  if(vidis_me)
  PacMan.at(-y+11).at(x+31) = 'O';
}

void Rotiraj(Pravci &orijentacija, int ugao) {
  int brPrvc = 8;
  int trenutna = static_cast<int>(orijentacija);
  int nova = (trenutna - ugao + brPrvc) % brPrvc;
  orijentacija = static_cast<Pravci>(nova);
}

void PostaviVidljivost(bool vidljiv) { vidis_me = vidljiv; }

void IspisiPoziciju(int x, int y, Pravci orijentacija) {
  if (vidis_me) {
    std::cout << "Robot je vidljiv, nalazi se na poziciji (" << x << "," << y<< ") i gleda na " << Orijentacija(orijentacija) << ".";
  } else if (!vidis_me) {
    std::cout << "Robot je nevidljiv, nalazi se na poziciji (" << x << "," << y<< ") i gleda na " << Orijentacija(orijentacija) << ".";
  }
  std::cout<<std::endl;
}

void PrikaziTeren() {
  OkujMeCare();
  if (!prazan)
    PacMan[11][31] = '*';
  for (int i = 0; i < 23; i++) {
    for (int j = 0; j < 63; j++) {
      std::cout << PacMan.at(i).at(j);
    }
    std::cout << std::endl;
  }
}

void IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y,
                   Pravci &orijentacija) {
  switch (komanda) {
  case Komande::Idi:
    Idi(x, y, orijentacija, parametar);
    break;
  case Komande::Rotiraj:
    Rotiraj(orijentacija, parametar);
    break;
  case Komande::Otkrij:
    PostaviVidljivost(true);
    break;
  case Komande::Sakrij:
    PostaviVidljivost(false);
    if(PacMan.at(-y+11).at(x+31)=='O'){
        PacMan.at(-y+11).at(x+31)='*';
    }
    break;
  case Komande::PrikaziTeren:
    PrikaziTeren();
    break;
  case Komande::Kraj:
    dovidjenja=true;
    break;
  }
}

int main() {

  Komande komanda;
  Pravci orijentacija = Pravci::Sjever;
  KodoviGresaka greska;
  int x = 0, y = 0, parametar = 0;
  bool bila_greska = false;
  IspisiPoziciju(x, y, orijentacija);
  while (!dovidjenja) {
    if (UnosKomande(komanda, parametar, greska)) {
      IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
      if (komanda != Komande::PrikaziTeren && !bila_greska &&
          komanda != Komande::Kraj)
        IspisiPoziciju(x, y, orijentacija);
      if (!bila_greska)
        std::cout << std::endl;
    } else {
      PrijaviGresku(greska);
    }
  }
  if(dovidjenja)
  std::cout<<"Dovidjenja!";

  return 0;
}
