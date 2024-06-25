//TP 2022/2023: LV 3, Zadatak 4
#include <iostream>
#include <deque>
#include <cmath>

std::deque<int> IzdvojiElemente(std::deque<int>a,bool provjera){
    std::deque<int>izdvojeni;
    if(provjera){
        for(int x : a) {
            int suma=0;
            int paran=x;
            while(x!=0){
                suma+=x%10;
                x/=10;
            }
            if(suma%2==0) izdvojeni.push_front(paran);
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
            if(suma%2!=0) izdvojeni.push_front(neparan);
        }
        return izdvojeni;
    }
}

int main ()
{   
    int br_el;
    std::deque<int>a;
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
    std::deque<int>b{IzdvojiElemente(a, true)};
    for(int i=0;i<b.size();i++){ 
        if(i==b.size()-1){ 
            std::cout<<b[i];
            break;
        }
        else{
            std::cout<<b[i]<<",";
        }
    }
    std::cout<<std::endl;
    std::deque<int>c{IzdvojiElemente(a, false)};
    for(int i=0;i<c.size();i++){ 
        if(i==c.size()-1){ 
            std::cout<<c[i];
            break;
        }
        else{
            std::cout<<c[i]<<",";
        }
    }


	return 0;
}

