//TP 2022/2023: LV 2, Zadatak 4
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
        double R;
        double X;
        std::cout<<"R"<<i+1<<" = ";
        std::cin>>R;
        std::cout<<"X"<<i+1<<" = ";
        std::cin>>X;
        std::cout<<std::endl;
        z=std::complex<double>(R,X);
        suma+=1./z;
    }
    std::complex<double> konacna_suma;
    konacna_suma=1./suma;
    std::cout<<"Paralelna veza ovih elemenata ima R = "<<real(konacna_suma)<<" i X = "<<imag(konacna_suma)<<".";
    

	return 0;
}