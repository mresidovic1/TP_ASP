//TP 2016/2017: LV 1, Zadatak 3
#include <iostream>
#include <cmath>
#include <iomanip>

int main ()
{
    int a,b;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;
    std::cout<<std::endl;
    std::cout<<"+"<<std::setw(10)<<std::setfill('-')<<"+"<<std::setw(11)<<std::setfill('-')<<"+"<<std::setw(11)<<std::setfill('-')<<"+"<<std::setw(12)<<std::setfill('-')<<"+"<<std::endl;
    std::cout<<"|"<<" Brojevi "<<"|"<<" Kvadrati "<<"|"<<" Korijeni "<<"|"<<" Logaritmi "<<"|"<<std::endl;
    std::cout<<"+"<<std::setw(10)<<std::setfill('-')<<"+"<<std::setw(11)<<std::setfill('-')<<"+"<<std::setw(11)<<std::setfill('-')<<"+"<<std::setw(12)<<std::setfill('-')<<"+"<<std::endl;
    int brojac=b-a;
    for(int i=0;i<=brojac;i++){
        std::cout<<"| "<<std::setw(8)<<std::setfill(' ')<<std::left<<a<<"|"<<std::setw(9)<<std::right<<a*a<<" |"<<std::setw(9)<<std::setprecision(3)<<std::fixed<<std::right<<std::right<<std::sqrt(a)<<" |"<<std::setw(10)<<std::setprecision(5)<<std::right<<std::log(a)<<" |"<<std::endl;
        a++;
    }
    std::cout<<"+"<<std::setw(10)<<std::setfill('-')<<"+"<<std::setw(11)<<std::setfill('-')<<"+"<<std::setw(11)<<std::setfill('-')<<"+"<<std::setw(12)<<std::setfill('-')<<"+"<<std::endl;
	return 0;
}