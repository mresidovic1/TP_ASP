//TP 2022/2023: LV 2, Zadatak 1
#include <iostream>
#include <vector>
#include <cmath>

bool DaLiJeProst(int n){
    if(n<=1) return false;
    for(int i=2;i<=std::sqrt(n);i++){
        if(n%i==0){
            return false;
        }
    }
    return true;
}

std::vector<int> ProstiBrojeviUOpsegu(int a,int b){
    std::vector<int> ProstiNiz;
    for(int i=a;i<=b;i++){
        if(DaLiJeProst(i)){
            ProstiNiz.push_back(i);
        }
        if(i==b) break;
    }
    return ProstiNiz;
}

int main ()
{
    int a,b;
    std::cout<<"Unesite pocetnu i krajnju vrijednost: ";
    std::cin>>a>>b;
    int vel=ProstiBrojeviUOpsegu(a, b).size();
    if(vel==0){
        std::cout<<"Nema prostih brojeva u rasponu od "<<a<<" do "<<b<<"!";
        return 0;
    }
    else{
        std::cout<<"Prosti brojevi u rasponu od "<<a<<" do "<<b<<" su: ";
        for(int i=0;i<vel;i++){
            if(ProstiBrojeviUOpsegu(a, b)[i]>1){
            std::cout<<ProstiBrojeviUOpsegu(a, b)[i];
            }
            else continue;

            if(i<vel-1){
                std::cout<<", ";
            }
            else{
                std::cout<<std::endl;
            }
        }
    }

    std::ios::sync_with_stdio(false);

	return 0;
}
