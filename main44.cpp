//TP 2022/2023: LV 7, Zadatak 8
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>

std::string IzvrniBezRazmaka(std::string parametar){
    std::string pomocni;
    std::remove_copy(parametar.rbegin(),parametar.rend(),std::back_inserter(pomocni),' ');
    return pomocni;
}

int main ()
{
    std::string pom={"Evo mene opet"};
    std::cout<<IzvrniBezRazmaka(pom);

	return 0;
}
