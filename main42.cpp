//TP 2022/2023: LV 7, Zadatak 6
#include <iostream>
#include <cmath>
#include <list>

template<typename tip1>
std::list<tip1>SortirajListu(std::list<tip1>&parametar){
    for(auto i=parametar.begin();i!=parametar.end();i++){
        for(auto j=i;j!=parametar.end();j++){
            if(*i>*j){
                auto temp=*j;
                *j=*i;
                *i=temp;
            }
        }
    }
    return parametar;
}

int main ()
{
    int n;
    std::cout<<"Koliko ima elemenata: ";
    std::cin>>n;
    std::list<int>parametar;
    std::cout<<std::endl;
    std::cout<<"Unesite elemente: ";
    for(int i=0;i<n;i++){
        int broj;
        std::cin>>broj;
        parametar.push_back(broj);
    }
    std::cout<<"Sortirana lista: ";
    for(auto x : SortirajListu(parametar)) std::cout<<x<<" ";

	return 0;
}
