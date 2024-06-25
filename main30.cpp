//TP 2022/2023: LV 5, Zadatak 7
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <deque>

template <typename tip1>
auto SumaBloka(tip1 pok1, tip1 pok2) -> decltype(*pok1 + *pok2){
    if(pok1==pok2)  throw std::range_error("Blok je prazan");
    auto suma=*pok1;
    pok1++;
    while(pok1!=pok2){
        suma+=*pok1++;
    }
    return suma;
}


int main ()
{
    std::deque<double> test;
    for(int i=0;i<5;i++){
        double broj;
        std::cin>>broj;
        test.push_back(broj);
    }
    std::cout<<"Suma bloka je: "<<SumaBloka(test.begin(),test.end());


	return 0;
}
