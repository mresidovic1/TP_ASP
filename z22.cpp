//TP 2022/2023: Zadaća 5, Zadatak 3
#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>


class ApstraktnoVozilo{
    int tezina;
    public:
    virtual ~ApstraktnoVozilo() {}
    ApstraktnoVozilo(int tezina) : tezina(tezina) {}
    virtual int DajTezinu() const { return tezina; }
    virtual int DajUkupnuTezinu() const = 0;
    virtual ApstraktnoVozilo* DajKopiju() const = 0;
    virtual void IspisiPodatke() const = 0;
};

class Automobil: public ApstraktnoVozilo{
    std::vector<int> putnici_kg;
    public:
    Automobil(int tezina, const std::vector<int>& t_putnika) : ApstraktnoVozilo(tezina),putnici_kg(t_putnika) {}
    int DajUkupnuTezinu() const override{
        int ukupno=DajTezinu();
        for(const int& pojedinacno: putnici_kg){
            ukupno+=pojedinacno;
        }
        return ukupno;
    }
    Automobil* DajKopiju() const override{
        return new Automobil(*this);
    }
    void IspisiPodatke() const override{
        std::cout<<"Vrsta vozila: Automobil"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Tezine putnika: ";
        int i=0;
        for(const int& pojedinacno : putnici_kg){
            if(i!=putnici_kg.size()-1){
            std::cout<<pojedinacno<<" kg, ";
            i++;
            }
            else {
            std::cout<<pojedinacno<<" kg";
            }
        }
        std::cout<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg "<<std::endl;
    }
};

class Kamion : public ApstraktnoVozilo{
    int teret;
    public:
    Kamion(int tezina, int teret) : ApstraktnoVozilo(tezina), teret(teret) {}
    int DajUkupnuTezinu() const override{
        return DajTezinu()+teret;
    }
    Kamion* DajKopiju() const override{
        return new Kamion(*this);
    }
    void IspisiPodatke() const override{
        std::cout<<"Vrsta vozila: Kamion"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Tezina tereta: "<<teret<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
};

class Autobus : public ApstraktnoVozilo{
    int putnici;
    int tezina_putnika;
    public:
    Autobus(int tezina, int putnici, int tezina_putnika) : ApstraktnoVozilo(tezina),putnici(putnici),tezina_putnika(tezina_putnika) {}
    int DajUkupnuTezinu() const override{
        return DajTezinu()+putnici*tezina_putnika;
    }
    Autobus* DajKopiju() const override{
        return new Autobus(*this);
    }
    void IspisiPodatke() const override{
        std::cout<<"Vrsta vozila: Autobus"<<std::endl;
        std::cout<<"Vlastita tezina: "<<DajTezinu()<<" kg"<<std::endl;
        std::cout<<"Broj putnika: "<<putnici<<std::endl;
        std::cout<<"Prosjecna tezina putnika: "<<tezina_putnika<<" kg"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" kg"<<std::endl;
    }
};

class Vozilo{
    ApstraktnoVozilo* vozilo;
    public:
    Vozilo(ApstraktnoVozilo* vozilo) : vozilo(vozilo) {}
    Vozilo() : vozilo(nullptr) {}
    ~Vozilo() {delete vozilo;}
    int DajTezinu() const{
        return vozilo->DajTezinu();
    }
    int DajUkupnuTezinu() const{
        return vozilo->DajUkupnuTezinu();
    }
    void IspisiPodatke() const{
        vozilo->IspisiPodatke();
    }
    Vozilo (const ApstraktnoVozilo& pom) : vozilo(pom.DajKopiju()) {}
    Vozilo(const Vozilo& pom){
        if(!pom.vozilo) vozilo=nullptr;
        else vozilo=pom.vozilo->DajKopiju();
    }
    Vozilo(Vozilo&& pom) { vozilo=pom.vozilo; pom.vozilo=nullptr; }
    Vozilo &operator=(const Vozilo& pom){
        ApstraktnoVozilo *novi=nullptr;
        if(pom.vozilo!=nullptr) novi=pom.vozilo->DajKopiju();
        delete vozilo;
        vozilo=novi;
        return *this;
    }
    Vozilo &operator=(Vozilo&& pom){
        std::swap(vozilo,pom.vozilo);
        return *this;
    }
};


int main ()
{

 std::vector<Vozilo> vozila;
    std::ifstream dat("VOZILA.TXT");
    if(!dat){
        std::cout<<"Otvaranje datoteke bezuspjesno.";
        return 0;
    }
    std::string podaci;
    while(std::getline(dat,podaci)){
        std::istringstream el(podaci);
        char tip=podaci[0];
        if(tip=='A'){
            std::istringstream citaj(podaci);
            int tezina;
            int br_putnika;
            std::vector<int> putnici;
            char oznaka;
            citaj>>oznaka>>tezina>>br_putnika;
            for(int i=0;i<br_putnika;i++){
                int tezina_put;
                citaj>>tezina_put;
                putnici.push_back(tezina_put);
            }
            Automobil skoda(tezina, putnici);
            vozila.push_back(Vozilo(skoda));
        }
        else if(tip=='K'){
            std::istringstream citaj(podaci);
            int tezina;
            int teret;
            char oznaka;
            citaj>>oznaka>>tezina>>teret;

            Kamion volvo(tezina,teret);
            vozila.push_back(Vozilo(volvo));
        }
        else if(tip=='B'){
            std::istringstream citaj(podaci);
            int tezina;
            int br_putnika;
            int prosjecna_tez;
            char oznaka;
            el>>oznaka>>tezina>>br_putnika>>prosjecna_tez;
            Autobus ikarus(tezina, br_putnika, prosjecna_tez);
            vozila.push_back(Vozilo(ikarus)); 
         }
        else{
            std::cout<<"Izuzetak: NEPOSTOJECE VOZILO!";
            return 0;
        }
    }
        dat.close();

        std::sort(vozila.begin(),vozila.end(),[](const Vozilo &a, const Vozilo &b){
            return a.DajUkupnuTezinu()<b.DajUkupnuTezinu();
        });

        for(const auto &vozilo : vozila){
            std::cout<<vozilo.DajUkupnuTezinu()<<std::endl;
        }

	return 0;
}