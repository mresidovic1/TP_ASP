//TP 2022/2023: LV 2, Zadatak 2
#include <iostream>
#include <cmath>
#include<vector>

// 1 9 1 3 1 9 1 3 0
//size 

bool TestPerioda(std::vector<double>a, int p){
  if(p<=0 || p>=a.size()) return false;

  for(int i=0;i<a.size()-p;i++){
      if(a[i]!=a[i+p]) return false;
  }
  return true;
}

int OdrediOsnovniPeriod(std::vector<double>a){
    
    for(int i=1;i<=a.size();i++){
        
        if(TestPerioda(a, i)){
            return i;
        }
    }

   return 0;

}

int main ()
{
    std::vector<double>a;
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    double broj;
    while(std::cin>>broj){
        if(broj==0) break;
        a.push_back(broj);
    }
    if(OdrediOsnovniPeriod(a)==0){
        std::cout<<"Slijed nije periodican!";
        return 0;
    }
    else{
        std::cout<<"Slijed je periodican sa osnovnim periodom "<<OdrediOsnovniPeriod(a)<<".";
    }


	return 0;
}
