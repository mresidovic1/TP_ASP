//TP 2022/2023: LV 7, Zadatak 10
#include <iostream>
#include <cmath>
#include <functional>

std::function<int(int)> IteriranaFunkcija(std::function<int(int)>f, int n){
    if(n<=0){
        return [](int x){return x;};
    }
    else{
        return [f,n](int x){
            int rez=x;
            for(int i=0;i<n;i++){
                rez=f(rez);
            }
            return rez;
        };
    }
}

int f(int n){
    return n*2;
}

int main ()
{
    std::cout<<IteriranaFunkcija(f,10)(5);
    std::cout<<f(f(f(f(f(f(f(f(f(f(5))))))))));

	return 0;
}
