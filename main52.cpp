//TP 2022/2023: LV 8, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <map>

auto ZamijeniPremaRjecniku(const std::string &ulaz, const std::map<std::string,std::string>&Rjecnik)->std::string{
    std::string zamjena{};
    int pocetak=0;
    for(auto it=ulaz.begin();it!=ulaz.end();it++){
        if(*it==' '){
            std::string rijec=ulaz.substr(pocetak,std::distance(ulaz.begin(),it)-pocetak);
            if(Rjecnik.count(rijec)==1){
                zamjena+=Rjecnik.find(rijec)->second+' ';
            }
            else{
                zamjena+=rijec+' ';
            }
            pocetak=std::distance(ulaz.begin(),it)+1;
        }
    }
    std::string rijec=ulaz.substr(pocetak,ulaz.size()-pocetak);
    if(Rjecnik.count(rijec)==1){
        zamjena+=Rjecnik.find(rijec)->second;
    }
    else{
        zamjena+=rijec;
    }
    return zamjena;
}


int main ()
{
     std::map<std::string, std::string> rjecnik 
    { 
        {"jabuka", "apple"}, 
        {"da", "yes"}, 
        {"kako", "how"}, 
        {"ne", "no"}, 
        {"majmun", "monkey"}, 
        {"mart", "ozujak"},
        {"maj", "svibanj"}, 
        {"jul", "srpanj"}
    };
    
  std::cout << ZamijeniPremaRjecniku("  kako   da   ne   ", rjecnik) << std::endl;

	return 0;
}
