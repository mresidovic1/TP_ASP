//TP 2022/2023: LV 4, Zadatak 4
#include <iostream>
#include <cmath>

template<typename Tip>
void UnosBroja(std::string tekst, std::string poruka, Tip &broj){
    std::cout<<tekst;
    while(!(std::cin>>broj) || std::cin.peek()!='\n'){
        std::cout<<poruka<<std::endl;
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        std::cout<<tekst;
    }
}

int main ()
{

    double broj;

    UnosBroja("Unesite bazu: \n", "Neispravan unos, pokusajte ponovo...\n", broj);
    
    int eksponent;

    UnosBroja("Unesite cjelobrojni eksponent: \n", "Neispravan unos, pokusajte ponovo...\n", eksponent);
    double rez=1;
    int pozitivan=std::abs(eksponent);
    for(int i=0;i<pozitivan;i++){
        rez*=broj;
    }
    if(eksponent<0) rez=1/rez;
    std::cout<<broj<<" na "<<eksponent<<" iznosi "<<rez;

	return 0;
    
}
