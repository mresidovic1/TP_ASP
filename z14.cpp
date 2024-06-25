// TP 2022/2023: Zadaća 3, Zadatak 5
#include <cmath>
#include <iostream>

struct Cvor {
  int redni_broj;
  Cvor *sljedeci;
};

int Poglavica(int N, int M, bool ispisi = false) {
  if (N <= 0 || M <= 0)
    return 0;
  Cvor *prvi = new Cvor;
  Cvor *bas_taj = prvi;
  for (int i = 1; i <= N; i++) {
    bas_taj->redni_broj = i;
    if (i < N) {
      bas_taj->sljedeci = new Cvor;
      bas_taj = bas_taj->sljedeci;
    }
  }
  bas_taj->sljedeci = prvi;

  Cvor *iza = nullptr;
  bas_taj = prvi;
  while (N != 1) {
    for (int i = 0; i < M - 1; i++) {
      iza = bas_taj;
      bas_taj = bas_taj->sljedeci;
    }
    if (ispisi)
      std::cout << bas_taj->redni_broj << ", ";
    if(iza!=nullptr)
    iza->sljedeci = bas_taj->sljedeci;
    else prvi=bas_taj->sljedeci;
    Cvor *pamti = bas_taj;
    bas_taj = bas_taj->sljedeci;
    delete pamti;
    N--;
  }
  int rezultat = bas_taj->redni_broj;
  delete bas_taj;
  return rezultat;
}

int SigurnoMjesto(int M, int N1, int N2) {
  if (M <= 0 || N1 <= 0 || N2 <= 0 || N2 < N1)
    return 0;
  int broj;
  for (int i = N1;; i++) {
    for (int k = N1; k <= N2; k++) {
      int p = Poglavica(k, M);
      if (i == p)
        break;
      else if (i != p && k == N2)
        return i;
      else
        continue;
    }
    if (i == N2)
      break;
  }
  return 0;
}

int main() {
  int N, M, N1, N2;
  std::cout << "Unesite broj punoljetnih clanova za odabir poglavice plemena Wabambe: ";
  std::cin >> N;
  std::cout << "Unesite korak razbrajanja: ";
  std::cin >> M;
  std::cout << "Unesite raspon za odabir (N1 i N2): ";
  std::cin >> N1 >> N2;
  std::cout << "Redni broj osobe koja postaje poglavica: " << Poglavica(N, M) << std::endl;
  if (!SigurnoMjesto(M, N1, N2)) {
    std::cout << "Zao mi je Mbebe Mgogo, ali nema sigurnog mjesta.";
    return 0;
  }

  std::cout << "Mbebe Mgogo, stani na sigurno mjesto "<< SigurnoMjesto(M, N1, N2) << " da ne bi bio poglavica!";

  return 0;
}
