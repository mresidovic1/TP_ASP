//TP 2022/2023: LV 3, Zadatak 8
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>

std::string IzdvojiRijec(std::string a,int b){
    int br_rijeci=0;
    for(int i=0;i<a.length();i++){
        if(a[i]==' ') continue;
        br_rijeci++;
        while(a[i]!=' ' && i<a.length()) i++;
    }
    if(b<1 || b>br_rijeci) throw std::domain_error("IZUZETAK: Pogresan redni broj rijeci!");
    std::string rijec;
    int brojac=0;
    for(int i=0;i<a.length();i++){
        while(a[i]==' ') i++;
        brojac++;
        if(brojac==b){
            while(a[i]!=' '){
                rijec.push_back(a[i]);
                i++;
            }
            break;
        }
        else{
            while(a[i]!=' ') i++;
        }
    }
    return rijec;
}



int main ()
{   
    int b;
    std::string recenica;
    std::cout<<"Unesite redni broj rijeci: ";
    std::cin>>b;
    std::cin.clear();
    std::cin.ignore(10000,'\n');
    std::cout<<"Unesite recenicu: ";
    std::getline(std::cin, recenica);
    try{
    IzdvojiRijec(recenica, b);
    std::cout<<"Rijec na poziciji "<<b<<" je "<<IzdvojiRijec(recenica, b);
    }
    catch(std::domain_error greska){
        std::cout<<greska.what();
    }
	return 0;
}
