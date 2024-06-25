#include <iostream>
using namespace std;

int fib_petlja(int n) {
  if (n <= 1)
    return n; 
  int pretprosli(0), prosli(1), rezultat;
  for (int i(2); i <= n; i++) {
    rezultat = pretprosli + prosli;
    pretprosli = prosli;
    prosli = rezultat;
  }
  return rezultat;
}

int fib2_0(int n, int pretprosli = 0, int prosli = 1) {
  if (n == 0)
    return pretprosli;
  else if (n == 1)
    return prosli;
  return fib2_0(n - 1, prosli, pretprosli + prosli);
}

int nzd(int x, int y){
    if(y==0) return x;
    return nzd(y, x%y);
}

void testirajFibonacci(){
    std::cout<<"10. Fibonaccijev broj koristeci >>fib_petlja<< je: "<<fib_petlja(10)<<std::endl;
    std::cout<<"10. Fibonaccijev broj koristeci >>fib2_0<< je: "<<fib2_0(10)<<std::endl<<std::endl;
    std::cout<<"Prvih 20 Fibonaccijevih brojeva koristeci oba metoda su: "<<std::endl<<std::endl;
    for(int i=0;i<20;i++){
        std::cout<<" && "<< fib_petlja(i) <<" && ";
        std::cout<<" ** "<< fib2_0(i) <<" ** ";
    }
    std::cout<<std::endl;
}

void testirajNZD(){
    std::cout<<std::endl<<"NZD brojeva 1024 i 4096 je: "<<nzd(1024, 4096); 
}

int main() {
  testirajFibonacci();
  testirajNZD();
  return 0;
}