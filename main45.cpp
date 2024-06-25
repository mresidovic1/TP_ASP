//TP 2022/2023: LV 7, Zadatak 9
#include <iostream>
#include <cmath>

auto plus2(double x){
    auto f=[x](double y){return x+y;};
    return f;
}

auto plus3(double x){
    auto g=[x](double y){
        auto f=[x,y](double z){return x+y+z;};
        return f;
    };
    return g;
}

int main ()
{
    auto f=plus2(5);
    std::cout<<f(2)<<std::endl;

    auto g=plus3(5);
    std::cout<<g(2)(5)<<std::endl;

	return 0;
}
