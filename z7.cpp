// TP 2022/2023: Zadaća 2, Zadatak 3
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

template <typename T> int najduzi(std::vector<std::vector<T>> &test) {
  int vel = test.at(0).size();
  for (auto &red : test) {
    for (auto &el : red) {
      if (el.length() > vel) {
        vel = el.length();
      }
    }
  }
  return vel;
}

template <typename T1, typename T2, typename G, typename F>
auto GeneraliziraniMatricniProizvod(std::vector<std::vector<T1>> &A, std::vector<std::vector<T2>> &B, F f, G g)-> std::vector<std::vector<decltype(g(A.at(0).at(0), B.at(0).at(0)))>> {
if(A.size()==0 || B.size()==0){
    return {};
}

  std::vector<std::vector<decltype(g(A.at(0).at(0),B.at(0).at(0)))>> C(A.size(), std::vector<decltype(g(A.at(0).at(0),B.at(0).at(0)))>(B.at(0).size()));
    for (int i = 0; i < A.size(); i++) {
      if(A.at(i).size()!=B.size()){
          throw std::domain_error("Matrice nisu saglasne za mnozenje");
      }
    
    for (int j = 0; j < B.at(0).size(); j++) {
      for (int k = 0; k < A.at(0).size(); k++) {
        try{
        if(k!=0)
        C.at(i).at(j) = f(C.at(i).at(j),g(A.at(i).at(k), B.at(k).at(j)));
        else{
            C.at(i).at(j)=g(A.at(i).at(k),B.at(k).at(j));
        }
        }
        catch(...){
            throw std::runtime_error("Neocekivani problemi pri racunanju");
        }
      }
    }
  }
  return C;
}

int main() {
  int m, n, p;
  std::cout << "Unesite broj redova prve matrice: ";
  std::cin >> m;
  std::cout
      << "Unesite broj kolona prve matrice, ujedno broj redova druge matrice: ";
  std::cin >> n;
  std::cout << "Unesite broj kolona druge matrice: ";
  std::cin >> p;

  std::vector<std::vector<std::string>> A(m, std::vector<std::string>(n));
  std::vector<std::vector<std::string>> B(n, std::vector<std::string>(p));
  std::cout << std::endl;
  std::cout << "Unesite elemente prve matrice: " << std::endl;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cin >> A.at(i).at(j);
    }
  }
  std::cout << "Unesite elemente druge matrice: " << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      std::cin >> B.at(i).at(j);
    }
  }
  std::cout << std::endl;
  try {
    std::vector<std::vector<std::string>> MojaMatrica =
        GeneraliziraniMatricniProizvod(
            A, B, [](std::string x, std::string y) { return x + "+" + y; },
            [](std::string x, std::string y) { return x + "*" + y; });
    std::cout << "Matricni proizvod: " << std::endl;
    for (auto red : MojaMatrica) {
      for (auto el : red) {
        std::cout << std::left << std::setw(najduzi(MojaMatrica) + 1)<<el;
      }
      std::cout << std::endl;
    }
  }
   
  catch (std::domain_error greska) {
    std::cout << greska.what();
  }
  catch(std::runtime_error greska){
      std::cout<< greska.what();
  }
  return 0;
}
