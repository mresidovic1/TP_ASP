//TP 2022/2023: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <iterator>
#include <new>
#include <stdexcept>
#include <type_traits>
#include <list>
#include <array>
#include <vector>
#include <algorithm>
#include <deque>

template<typename T, typename U>
auto KreirajTablicuSabiranja(T apoc, T akraj, U bpoc){
    using Rez=decltype(*apoc+*bpoc);
    int n=std::distance(apoc,akraj);
    int vel=n*(n+1)/2;
    Rez **tab_sum=nullptr;
    Rez *temp=nullptr;
    try{
    tab_sum=new Rez*[n];
    temp= new Rez[vel];
    for(int i=0;i<n;i++){
        *(tab_sum+i)=temp+(i*(i+1))/2;
    }
    auto sum=[](const auto& a, const auto &b) -> Rez {return a+b;};
    auto i=apoc;
    for(auto k=0;k<n;k++){
        auto j=bpoc;
        for(int l=0;l<=k;l++){
          *(*(tab_sum+k)+l)=sum(*i,*j);
          if(l>0 && *(*(tab_sum+k)+l)!=sum(*j,*i)){
              throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
          }
          j++;
        }
        i++;
    }
    }
    catch(std::bad_alloc){
        delete[] temp;
        delete[] tab_sum;
        throw std::range_error("Nema dovoljno memorije!");
    }
    catch(...){
        delete[] temp;
        delete[] tab_sum;
        throw;
    }
    return tab_sum;
}


int main ()
{

    int vel;
    std::cout<<"Duzina sekvenci: ";
    std::cin>>vel;
    std::cout<<std::endl;
    std::vector<double>prvi(vel);
    std::cout<<"Elementi prve sekvence: ";
    for(int i=0;i<vel;i++){
        std::cin>>prvi.at(i);
    }
    std::cout<<std::endl;
    std::deque<double>drugi(vel);
    std::cout<<"Elementi druge sekvence: ";
    for(int i=0;i<vel;i++){
        std::cin>>drugi.at(i);
    }
    std::cout<<std::endl;
    auto tab_sab=KreirajTablicuSabiranja(prvi.begin(), prvi.end(), drugi.begin());
    try{
       std::cout<<"Tablica sabiranja: "<<std::endl;
       int br_el=0;
       for(int i=0;i<vel;i++){
           for(int j=0;j<=i;j++){
              std::cout<<*(*(tab_sab+i)+j)<<" ";
           }
           std::cout<<std::endl;
       }
    }
    catch(std::range_error greska){
        delete[] *tab_sab;
        delete[] tab_sab;
        std::cout<<greska.what();
    }
    catch(std::logic_error greska){
        delete[] *tab_sab;
        delete[] tab_sab;
        std::cout<<greska.what();
    }
    catch(...){
        delete[] *tab_sab;
        delete[] tab_sab;
        std::cout<<"Greska pri alokaciji!";
    }
    for(int i=0;i<vel;i++){
        delete[] *(tab_sab+i);
    }
    delete[] tab_sab;

	return 0;
}
