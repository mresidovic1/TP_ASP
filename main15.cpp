//TP 2022/2023: LV 3, Zadatak 6
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

typedef std::vector<std::vector<int>> Matrica;

int NajvecaSirina(Matrica a){
    if(a.size()==0) return 0;
    int najveci=0;
    for(auto red : a){
        for(auto broj : red){
            int brojac=0;
            if(broj<0) brojac=1;
            while(broj!=0){
                brojac++;
                broj/=10;
            }
            if(brojac>=najveci) {
                najveci=brojac;
        }
    }
    }
    return najveci;
}

Matrica KroneckerovProizvod(std::vector<int>a,std::vector<int>b){
    Matrica kroneker(a.size(),std::vector<int>(b.size()));
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b.size();j++){
            kroneker[i][j]=a[i]*b[j];
        }
    }
    return kroneker;
}

int main ()
{
    int vel1,vel2;
    std::vector<int>a;
    std::vector<int>b;
    std::cout<<"Unesite broj elemenata prvog vektora: ";
    std::cin>>vel1;
    std::cout<<"Unesite elemente prvog vektora: ";
    for(int i=0;i<vel1;i++){
        int broj;
        std::cin>>broj;
        a.push_back(broj);
    }
    std::cout<<"Unesite broj elemenata drugog vektora: ";
    std::cin>>vel2;
    std::cout<<"Unesite elemente drugog vektora: ";
    for(int i=0;i<vel2;i++){
        int broj;
        std::cin>>broj;
        b.push_back(broj);
    }
    std::cout<<std::endl;
    for(std::vector<int>red : KroneckerovProizvod(a, b)){
        for(int x : red) std::cout<<std::fixed<< std::setw(NajvecaSirina(KroneckerovProizvod(a,b))+1)<<std::right<<x;
        std::cout<<std::endl;
    }



	return 0;
}
