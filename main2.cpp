//TP 2016/2017: Tutorijal 1, Zadatak 2
#include <iostream>
#include <cmath>
int main ()
{
    double str1,str2,str3;
    for(;;){
        std::cout<<"Unesite tri broja: ";
        if(std::cin>>str1>>str2>>str3 && str1>0 && str2>0 && str3>0 && str1+str2>str3 && str1+str3>str2 && str2+str3>str1) break;
        std::cout<<"Ne postoji trougao cije su duzine stranica "<<str1<<", "<<str2<<" i "<<str3<<"!";
        return 0;
    }
        std::cout<<"Obim trougla sa duzinama stranica "<<str1<<", "<<str2<<" i "<<str3<<" iznosi "<<str1+str2+str3<<"."<<std::endl;
        double s=(str1+str2+str3)/2;
        std::cout<<"Njegova povrsina iznosi "<<std::sqrt(s*(s-str1)*(s-str2)*(s-str3))<<"."<<std::endl;
        if(str1<=str2 && str1<=str3){
            double alfa;
            alfa=(std::acos((str2*str2+str3*str3-str1*str1)/(2*str2*str3)))*(180/(4*std::atan(1)));
            std::cout<<"Njegov najmanji ugao ima "<<int(alfa)<<" stepeni, "<<int((alfa-int(alfa))*60)<<" minuta i "<<int((((alfa-int(alfa))*60)-int(((alfa-int(alfa))*60)))*60)<<" sekundi.";
        }
        else if(str2<str1 && str2<str3){
            double beta;
            beta=(std::acos((str1*str1+str3*str3-str2*str2)/(2*str1*str3)))*(180/(4*std::atan(1)));
            std::cout<<"Njegov najmanji ugao ima "<<int(beta)<<" stepeni, "<<int((beta-int(beta))*60)<<" minuta i "<<int((((beta-int(beta))*60)-int(((beta-int(beta))*60)))*60)<<" sekundi.";
        }
        else if(str3<str1 && str3<str2){
            double gama;
            gama=(std::acos((str1*str1+str2*str2-str3*str3)/(2*str1*str2)))*(180/(4*std::atan(1)));
            std::cout<<"Njegov najmanji ugao ima "<<int(gama)<<" stepeni, "<<int((gama-int(gama))*60)<<" minuta i "<<int((((gama-int(gama))*60)-int(((gama-int(gama))*60)))*60)<<" sekundi.";
        }

	return 0;
}