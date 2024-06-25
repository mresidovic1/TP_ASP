//TP 2022/2023: LV 6, Zadatak 1
#include <exception>
#include <iostream>
#include <cmath>
#include <limits>
#include <new>
#include <stdexcept>

template <typename tip>
tip* GenerirajStepeneDvojke (int n){
    if(n<=0) throw std::domain_error("Broj elemenata mora biti pozitivan");
    tip* p=nullptr;
    try{
        p=new tip[n];
    }
    catch(std::bad_alloc){
        throw std::logic_error("Alokacija nije uspjela");
    }
    tip stepen=1;
    for(int i=0;i<n;i++){
    if(stepen<=0 || stepen>std::numeric_limits<tip>::max()){
        delete[] p;
        throw std::overflow_error("Prekoracen dozvoljeni opseg");
    }
        p[i]=stepen;
       stepen*=2;
    }
    return p;
}

int main ()
{
    int n;
    std::cout<<"Koliko zelite elemenata: ";
    std::cin>>n;
    std::cout<<std::endl;
    try{
    unsigned long int *p=GenerirajStepeneDvojke<unsigned long int>(n);
    for(int i=0;i<n;i++){
        std::cout<<p[i]<<" ";
    }
    delete []p;
    }
    catch(std::exception& e){
        std::cout<<"Izuzetak: "<<e.what();
    }


	return 0;
}
