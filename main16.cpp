//TP 2022/2023: LV 3, Zadatak 7
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <stdexcept>

typedef std::vector<std::vector<int>> Matrica;

int NajvecaSirina(Matrica a){
    int najveci=0;
    for(auto red : a){
        for(auto broj : red){
            int brojac=0;
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

Matrica PascalovTrougao(int n){
    if(n<0) throw std::domain_error("Broj redova ne smije biti negativan");
    Matrica a(n);
    for(int i=0;i<a.size();i++){
        a[i].resize(i+1);
        for(int j=0;j<a[i].size();j++){
            if(j==0 || j==a[i].size()-1) a[i][j]=1;
            else a[i][j]=a[i-1][j]+a[i-1][j-1];
        }
    }
    return a;
}

int main ()
{   
    int n;
    std::cout<<"Unesite broj redova: ";
    std::cin>>n;
    std::cout<<std::endl;
    try{
    for(std::vector<int>red : PascalovTrougao(n)){
        for(int x : red) std::cout<<std::fixed<<std::right<<std::setw(NajvecaSirina(PascalovTrougao(n))+1)<<x;
        std::cout<<std::endl;
    }
    }
    catch(std::domain_error negativan){
        std::cout<<negativan.what()<<std::endl;
    }

	return 0;
}
