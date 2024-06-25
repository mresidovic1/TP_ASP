//TP 2022/2023: LV 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <complex>


int main ()
{
    int br_el;
    std::cout<<"Unesite broj elemenata: "<<std::endl;
    std::cin>>br_el;
    std::complex<double> suma;
    std::complex<double>z;
    for(int i=0;i<br_el;i++){
        double Z;
        double fi;
        std::cout<<"Z"<<i+1<<" = ";
        std::cin>>Z;
        std::cout<<"fi"<<i+1<<" = ";
        std::cin>>fi;
        std::cout<<std::endl;
        fi=fi*((4*atan(1))/180);
        z=std::polar(Z,fi);
        suma+=1./z;
    }
    std::complex<double> konacna_suma;
    konacna_suma=1./suma;
    std::cout<<"Paralelna veza ovih elemenata ima Z = "<<abs(konacna_suma)<<" i fi = "<<arg(konacna_suma)*(180/(4*atan(1)))<<".";

	return 0;
}
