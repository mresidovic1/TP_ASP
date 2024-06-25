#include <cmath>
#include <iostream>
#include <ctime>
#include <vector>

std::vector <long long int> ProstiBrojevi(long long int n) {
  std::vector<long long int> pom;
  for (int i = 2; i <= std::sqrt(n); i*=i) {
    int mnozilac = i;
    while (mnozilac <= n) {
      mnozilac += i;
      pom.push_back(mnozilac);
    }
  }
  std::vector<long long int> prosti;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < pom.size(); j++) {
      if (i == pom[j])
        break;
      else if (j == pom.size() - 1)
        prosti.push_back(i);
    }
  }
  return prosti;
}

int main() {

  std::cout << "Prosti brojevi do 5000 su: ";
  clock_t vrijeme1 = clock();
  for (int a : ProstiBrojevi(1000000)){}
      clock_t vrijeme2 = clock();
int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC/1000);
  std::cout<<"Vrijeme izvrsavanja: "<<ukvrijeme<<" ms."<<std::endl;
}