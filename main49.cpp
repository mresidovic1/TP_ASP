//TP 2022/2023: LV 8, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>

struct Vrijeme{
    int sati,minute,sekunde;
};

void TestirajVrijeme(Vrijeme vr){
    if(vr.sati==24 && vr.sati!=0 && vr.sekunde!=0) throw std::domain_error("Neispravno vrijeme"); 
    if(vr.sati>23 || vr.sati<0 || vr.minute>60 || vr.minute<0 || vr.sekunde>60 || vr.sekunde<0) throw std::domain_error("Neispravno vrijeme"); 
}

void IspisiVrijeme(Vrijeme &ispis){
    TestirajVrijeme(ispis);
    if(ispis.sati<10)
    std::cout<<"0"<<ispis.sati;
    else std::cout<<ispis.sati;
    std::cout<<":";
    if(ispis.minute<10)
    std::cout<<"0"<<ispis.minute;
    else std::cout<<ispis.minute;
    std::cout<<":";
    if(ispis.sekunde<10)
    std::cout<<"0"<<ispis.sekunde;
    else std::cout<<ispis.sekunde;
}

Vrijeme SaberiVrijeme(const Vrijeme vr1, const Vrijeme vr2){
    TestirajVrijeme(vr1);
    TestirajVrijeme(vr2);
    int sekunde_ukupno=(vr1.sati+vr2.sati)*3600+(vr1.minute+vr2.minute)*60+(vr1.sekunde+vr2.sekunde);
    sekunde_ukupno%=86400;
    int ukupno_sati=sekunde_ukupno/3600;
    sekunde_ukupno%=3600;
    int ukupno_minuteute=sekunde_ukupno/60;
    sekunde_ukupno%=60;
    return {ukupno_sati,ukupno_minuteute,sekunde_ukupno};
}

int main ()
{
    int sati1,m1,s1;
    int sati2,m2,s2;
    try{
    std::cout<<"Unesite prvo vrijeme (h m s): ";
    std::cin>>sati1>>m1>>s1;
    Vrijeme v1={sati1,m1,s1};
    TestirajVrijeme(v1);
    std::cout<<"Unesite drugo vrijeme (h m s): ";
    std::cin>>sati2>>m2>>s2;
    Vrijeme v2={sati2,m2,s2};
    TestirajVrijeme(v2);
    std::cout<<"Prvo vrijeme: ";
    IspisiVrijeme(v1);
    std::cout<<std::endl;
    std::cout<<"Drugo vrijeme: ";
    IspisiVrijeme(v2);
    std::cout<<std::endl;
    std::cout<<"Zbir vremena: ";
    Vrijeme v_suma=SaberiVrijeme(v1, v2);
    IspisiVrijeme(v_suma);
    }
    catch(std::domain_error e){
        std::cout<<e.what();
    }

	return 0;
}
