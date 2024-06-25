//TP 2022/2023: LV 6, Zadatak 2
#include <iostream>
#include <cmath>
#include <new>
#include <stdexcept>
#include <vector>

template<typename T>
auto KreirajIzvrnutiNiz(T p1, T p2)-> typename std::remove_reference<decltype(*p1)>::type*{
    using Niz=typename std::remove_reference<decltype(*p1)>::type;
    T privremena=p1;
    int el=0;
    while(privremena!=p2){
        privremena++;
        el++;
    }
     Niz *p=new Niz[el]{};
    try{
        
        Niz *setajuci=p+el-1;
        while(p1!=p2){
            *setajuci--=*p1++;
        }
    }
    catch(...){
        throw;
    }

    return p;
    
}

int main ()
{
    int n=0;
    try{
    std::cout<<"Koliko zelite elemenata: ";
    std::cin>>n;
    std::vector<double>vektor(n);
    std::cout<<std::endl;
    std::cout<<"Unesite elemente: ";
    for(int i=0;i<n;i++){
        std::cin>>vektor[i];
    }
    std::cout<<"Kreirani niz: ";
    auto p= KreirajIzvrnutiNiz(vektor.begin(), vektor.end());
    for(int i=0;i<n;i++){
        std::cout<<p[i]<<" ";
    }
    delete[] p;
    }
    catch(std::logic_error& e){
        std::cout<<"Izuzetak: "<<e.what();
    }
    catch(...){
        std::cout<<"Nedovoljno memorije!";
    }
	return 0;
}
