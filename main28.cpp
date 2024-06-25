//TP 2022/2023: LV 5, Zadatak 5
#include <iostream>
#include <cmath>
#include <iomanip>

double TrapeznoPravilo (double f(double), double a, double b ,int n){
    double suma=0;
    for(int i=1;i<=n-1;i++){
        suma+=f(a+((b-a)/(double)n)*i);
    }
    return (b-a)/double(n)*(f(a)/2 + f(b)/2 + suma);
}

int main ()
{
    int n;
    std::cout<<"Unesite broj podintervala: ";
    std::cin>>n;
    std::cout<<"Za taj broj podintervala priblizne vrijednosti integrala iznose: "<<std::endl;
    std::cout<<"- Za funkciju sin x na intervalu (0,pi): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo([](double x){return std::sin(x);}, 0, 4*atan(1) , n)<<std::endl;
    std::cout<<"- Za funkciju x^3 na intervalu (0,10): "<<std::fixed<<std::setprecision(2)<<TrapeznoPravilo([](double x){return x*x*x;}, 0, 10, n)<<std::endl;
    std::cout<<"- Za funkciju 1/x na intervalu (1,2): "<<std::fixed<<std::setprecision(5)<<TrapeznoPravilo([](double x){return 1/x;}, 1, 2, n)<<std::endl;
	return 0;
}
