//TP 2016/2017: LV 1, Zadatak 4
#include <iostream>
#include <cmath>
int main ()
{
    double broj, suma=0;
    for(;;){
        std::cout<<"Unesite prirodan broj ili 0 za kraj: ";
        std::cin>>broj;
        if(!std::cin || broj!=int(broj) || broj<0){
        std::cout<<"Niste unijeli prirodan broj!"<<std::endl;
        std::cin.clear();
        std::cin.ignore(10000,'\n');
        continue;
        }
        if(broj==0){
            std::cout<<"Dovidjenja!";
            return 0;
        }
        else{
            suma=0;
            for(int j=1;j<broj;j++){
                if(int(broj)%j==0) suma+=j;
            }
        
            if(suma>broj) std::cout<<"Broj "<<broj<<" je obilan!"<<std::endl;
            if(broj==suma) std::cout<<"Broj "<<broj<<" je savrsen!"<<std::endl;
            if(suma<broj) std::cout<<"Broj "<<broj<<" je manjkav!"<<std::endl;
            continue;
        }
    }

	return 0;
}