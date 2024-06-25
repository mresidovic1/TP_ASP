//TP 2022/2023: LV 7, Zadatak 7
#include <iostream>
#include <cmath>
#include <iterator>
#include <set>
#include <algorithm>

template<typename tip1>
std::set<tip1> Unija(std::set<tip1> skup1, std::set<tip1>skup2){
    std::set<tip1>skup;
    for(auto x : skup1) skup.insert(x);
    for(auto x : skup2) skup.insert(x);
    return skup;
}

template<typename tip1>
std::set<tip1> Presjek(std::set<tip1> skup1, std::set<tip1>skup2){
    std::set<tip1>skup;
    for(auto x : skup1){
        auto temp=x;
        for(auto y : skup2){
            if(temp==y) skup.insert(temp);
        }
    }
    return skup;
}

int main ()
{
    std::set<std::string>kec={"Mujo","Bego","Haso"};
    std::set<std::string>dvica={"Rahman","Bego","Suljo"};
    for(std::string x : Unija(kec, dvica)) std::cout<<x;
    for(std::string x : Unija(kec, dvica)) std::cout<<x;
	return 0;
}
