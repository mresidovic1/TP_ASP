//TP 2022/2023: LV 5, Zadatak 4

#include <iostream>
#include <cmath>
#include <algorithm>
#include <deque>



int main ()
{
    int br_el;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>br_el;
    std::deque<int>dek(br_el);
    std::cout<<"Unesite elemente: ";
    std::for_each(dek.begin(),dek.end(),[](int &a){std::cin>>a;});
    std::cout<<"Najveci element deka je "<<*std::max_element(dek.begin(),dek.end())<<std::endl;
    std::cout<<"Najmanji element deka se pojavljuje "<<std::count(dek.begin(),dek.end(),*std::min_element(dek.begin(),dek.end()))<<" puta u deku"<<std::endl;
    std::cout<<"U deku ima "<<std::count_if(dek.begin(),dek.end(), [](int a){return int(std::sqrt(a))*int(std::sqrt(a))==a;})<<" brojeva koji su potpuni kvadrati"<<std::endl;
    std::cout<<"Prvi element sa najmanjim brojem cifara je "<<*std::min_element(dek.begin(),dek.end(), [](int a,int b){return std::floor(std::log10(std::abs(a)))+1<std::floor(std::log10(std::abs(b)))+1;})<<std::endl;
    std::deque<int>novi(dek.size());
    auto zadnji=std::remove_copy_if(dek.begin(),dek.end(), novi.begin(), [](int a){return (std::abs(a)>=100 && std::abs(a)<=999);});
    std::cout<<"Elementi koji nisu trocifreni su: ";
    std::for_each(std::begin(novi),zadnji,[](int a){std::cout<< a <<" ";});

	return 0;
}

