//TP 2022/2023: LV 3, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> IzdvojiElemente(std::vector<int>a,bool provjera){
    std::vector<int>izdvojeni;
    if(provjera){
        for(int x : a) {
            int suma=0;
            int paran=x;
            while(x!=0){
                suma+=x%10;
                x/=10;
            }
            if(suma%2==0) izdvojeni.push_back(paran);
        }
        return izdvojeni;
    }
    else{
        for(int x : a) {
            int suma=0;
            int neparan=x;
            while(x!=0){
                suma+=x%10;
                x/=10;
            }
            if(suma%2!=0) izdvojeni.push_back(neparan);
        }
        return izdvojeni;
    }
}

int main ()
{   
    int br_el;
    std::vector<int>a;
    std::cout<<"Koliko zelite unijeti elemenata: ";
    std::cin>>br_el;
    if(br_el<=0){ 
        std::cout<<"Broj elemenata mora biti veci od 0!";
        return 0; }
                
    std::cout<<"Unesite elemente: ";
    int broj;
    for(int i=0;i<br_el;i++){
       std::cin>>broj;
       a.push_back(broj);
    }
    std::vector<int>b{IzdvojiElemente(a, true)};
    for(int x : b) std::cout<<x<<" ";
    std::cout<<std::endl;
    std::vector<int>c{IzdvojiElemente(a, false)};
    for(int x : c) std::cout<<x<<" ";


	return 0;
}
