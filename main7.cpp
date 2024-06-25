//TP 2022/2023: LV 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <complex>

int main ()
{
    int br_el;
    std::cout<<"Unesite broj elemenata: ";
    std::cin>>br_el;
    std::complex<double> suma;
    for(int i=0;i<br_el;i++){
        std::cout<<"Z_"<<i+1<<" = ";
        std::complex<double>z;
        std::cin>>z;
        suma+=1./z;
    }
    std::complex<double> konacna_suma;
    konacna_suma=1./suma;
    std::cout<<"Paralelna veza ovih elemenata ima impedansu Z_ = "<<konacna_suma<<".";
    

	return 0;
}
