//TP 2016/2017: LV 1, Zadatak 1
#include <iostream>
#include <cmath>
int main ()
{
    int duzina,sirina,dubina;
    std::cout<<"Unesite duzinu, sirinu i dubinu bazena u metrima: ";
    std::cin>>duzina>>sirina>>dubina;
    int sirina_plocice;
    std::cout<<"Unesite sirinu plocice u centimetrima: ";
    std::cin>>sirina_plocice;
    if((sirina*100)%sirina_plocice!=0 || (duzina*100)%sirina_plocice!=0 || (dubina*100)%sirina_plocice!=0){
        std::cout<<"Poplocavanje bazena dimenzija "<<duzina<<"x"<<sirina<<"x"<<dubina<<"m sa plocicama dimenzija "<<sirina_plocice<<"x"<<sirina_plocice<<"cm nije izvodljivo bez lomljenja plocica!"<<std::endl;
        return 0;
    }
    else{
        std::cout<<"Za poplocavanje bazena dimenzija "<<duzina<<"x"<<sirina<<"x"<<dubina<<"m sa plocicama dimenzija "<<sirina_plocice<<"x"<<sirina_plocice<<"cm potrebno je "<<(((duzina*sirina)+2*(sirina*dubina)+2*(duzina*dubina))*10000)/(sirina_plocice*sirina_plocice)<<" plocica."<<std::endl;
    }
	return 0;
}