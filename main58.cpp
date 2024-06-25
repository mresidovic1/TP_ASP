//TP 2022/2023: LV 9, Zadatak 4
#include <iostream>
#include <cmath>
#include <iomanip>

class Sat{
    int sati,minute,sekunde;

    public:
    static bool DaLiJeIspravno(int sati, int minute, int sekunde){
        return sati>=0 && sati<24 && minute >=0 && minute<60 && sekunde>=0 && sekunde<60;
    }
    void Postavi(int sati, int minute, int sekunde){
        if(!DaLiJeIspravno(sati, minute, sekunde)){
            throw std::domain_error("Neispravno vrijeme");
        }
        this->sati=sati;
        this->minute=minute;
        this->sekunde=sekunde;
    }
    void PostaviNormalizirano(int sati, int minute, int sekunde){
        while(sekunde<0){ sekunde+=60; minute--; }
        while(minute<0) {minute+=60; sati--;}
        while(sati<0){sati+=24;}
        while(sekunde>59){sekunde-=60; minute++;}
        while(minute>59){minute-=60; sati++;}
        while(sati>23){sati-=24;}
        this->sati=sati;
        this->minute=minute;
        this->sekunde=sekunde;
    }
    Sat Sljedeci(){sekunde++; PostaviNormalizirano(sati, minute, sekunde); return *this;}
    Sat Prethodni(){sekunde--; PostaviNormalizirano(sati, minute, sekunde); return *this;}
    Sat PomjeriZa(int pomak){sekunde+=pomak; PostaviNormalizirano(sati, minute, sekunde); return *this;}
    void Ispisi() const { std::cout<<std::setw(2)<<std::setfill('0')<<sati<<":"<<std::setw(2)<<std::setfill('0')<<minute<<":"<<std::setw(2)<<std::setfill('0')<<sekunde;}
    int DajSate() const {return sati;}
    int DajMinute() const {return minute;}
    int DajSekunde() const {return sekunde;}
    friend int BrojSekundiIzmedju(const Sat& s1, const Sat& s2);
    static int Razmak(const Sat& s1, const Sat& s2);
};

    int BrojSekundiIzmedju(const Sat& s1, const Sat& s2){
        int razlikaH= s1.sati-s2.sati;
        int razlikaM=s1.minute-s2.minute;
        int razlikaS=s1.sekunde-s2.sekunde;
        return razlikaH*3600+razlikaM*60+razlikaS;
    }

    int Sat::Razmak(const Sat &s1, const Sat &s2){
        return BrojSekundiIzmedju(s1, s2);
    }


int main ()
{
    Sat s1,s2;

    s1.Postavi(10,30,0);
    s2.Postavi(20,40,32);
    s1.Ispisi(); std::cout<<std::endl;
    s2.Ispisi(); std::cout<<std::endl;

    s1.Sljedeci().Ispisi(); std::cout<<std::endl;
    s2.Sljedeci().Ispisi(); std::cout<<std::endl;

    s1.PomjeriZa(30).Ispisi(); std::cout<<std::endl;
    s2.PomjeriZa(-12).Ispisi(); std::cout<<std::endl;

    std::cout<<BrojSekundiIzmedju(s1, s2)<<" "<<Sat::Razmak(s1, s2)<<std::endl;
    std::cout<<s1.DajSate()<<":"<<s1.DajMinute()<<":"<<s1.DajSekunde();

   s1.PostaviNormalizirano(23, 120, -22);
   s1.Ispisi();

	return 0;
}
