//TP 2022/2023: LV 5, Zadatak 3

#include <iostream>
#include <cmath>
#include <algorithm>

void ISPIS (int a){
    std::cout<< a <<" ";
}

void UNOS(int &a){
    std::cin>>a;
}

bool PotpuniKvadrat(int a){
    return int(std::sqrt(a))*int(std::sqrt(a))==a;
}

bool BrojCifara(int a, int b){
    return (std::floor(std::log10(std::abs(a)))+1)<(std::floor(std::log10(std::abs(b)))+1);
}

bool  Trocifren(int a){
    return (std::abs(a)>=100 && std::abs(a)<=999);
}

int main ()
{
    int niz[1000],br_el;
    std::cout<<"Unesite broj elemenata (max. 1000): ";
    std::cin>>br_el;
    std::cout<<"Unesite elemente: ";
    std::for_each(niz,niz+br_el,UNOS);
    std::cout<<"Najveci element niza je "<<*std::max_element(niz,niz+br_el)<<std::endl;
    std::cout<<"Najmanji element niza se pojavljuje "<<std::count(niz,niz+br_el,*std::min_element(niz,niz+br_el))<<" puta u nizu"<<std::endl;
    std::cout<<"U nizu ima "<<std::count_if(niz, niz+br_el, PotpuniKvadrat)<<" brojeva koji su potpuni kvadrati"<<std::endl;
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(niz, niz+br_el, BrojCifara)<<std::endl;
    int novi[1000];
    int *zadnji=std::remove_copy_if(niz, niz+br_el, novi, Trocifren);
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(novi,zadnji,ISPIS);

	return 0;
}
