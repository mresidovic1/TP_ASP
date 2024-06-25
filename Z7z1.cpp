#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

template <typename tip> void razmijeni(tip &a, tip &b) {
  tip pom = a;
  a = b;
  b = pom;
}

template <typename tip> void bubble_sort(tip *niz, int vel) {
  for (int i = 0; i < vel - 1; i++) {
    for (int j = 0; j < vel - i - 1; j++) {
      if (niz[j] > niz[j + 1]) {
        razmijeni(niz[j], niz[j + 1]);
      }
    }
  }
}

template <typename tip> void selection_sort(tip *niz, int vel) {
  for (int i = 0; i < vel - 1; i++) {
    int min = i;
    for (int j = i + 1; j < vel; j++) {
      if (niz[j] < niz[min])
        min = j;
    }
    razmijeni(niz[i], niz[min]);
  }
}

template <typename tip>
int Particija(tip *niz, const int prvi, const int zadnji) {
  tip pivot = niz[prvi];
  int p = prvi + 1;
  while (p <= zadnji) {
    if (niz[p] <= pivot)
      p++;
    else
      break;
  }
  for (int i = p + 1; i <= zadnji; i++) {
    if (niz[i] < pivot) {
      auto temp = niz[p];
      niz[p] = niz[i];
      niz[i] = temp;
      p++;
    }
  }
  auto temp = niz[p - 1];
  niz[p - 1] = niz[prvi];
  niz[prvi] = temp;

  return p - 1;
}

template <typename tip> void quick_sort(tip *niz, int vel) {
  static int prvi = 0;
  static int zadnji = vel - 1;
  if (prvi < zadnji) {
    int j = Particija(niz, prvi, zadnji);
    auto q = zadnji;
    zadnji = j - 1;
    quick_sort(niz, vel);
    prvi = j + 1;
    zadnji = q;
    quick_sort(niz, vel);
  }
}

template <typename tip>
void Merge(tip *niz, const int l, const int p, const int q, const int u) {
  int i(0), j(q - l), k(l);
  tip *B = new tip[u - l + 1];
  for (int m = 0; m <= u - l; m++)
    B[m] = niz[l + m];
  while (i <= p - l && j <= u - l) {
    if (B[i] < B[j])
      niz[k] = B[i++];
    else
      niz[k] = B[j++];
    k++;
  }
  while (i <= p - l)
    niz[k++] = B[i++];
  while (j <= u - l)
    niz[k++] = B[j++];
  delete[] B;
}

template <typename tip> void merge_sort(tip *niz, int vel) {
  static int l = 0;
  static int u = vel - 1;
  if (u > l) {
    int p = (l + u - 1) / 2;
    int q = p + 1;
    auto z = u;
    auto y = l;
    u = p;
    merge_sort(niz, vel);
    u = z;
    l = q;
    merge_sort(niz, vel);
    l = y;
    Merge(niz, l, p, q, u);
  }
}

void ucitaj(std::string ime, int *&niz, int &vel) {
  std::ifstream file(ime);

  if (!file.is_open()) {
    std::cerr << "Nemoguće otvoriti datoteku: " << ime << std::endl;
    return;
  }

  vel = 0;
  int broj;
  while (file >> broj) {
    ++vel;
  }

  file.clear();
  file.seekg(0, std::ios::beg);

  niz = new int[vel];

  for (int i = 0; i < vel; ++i) {
    file >> niz[i];
  }

  file.close();
}

void generisi(std::string ime, int vel) {
  std::ofstream file(ime);

  if (!file.is_open()) {
    std::cerr << "Nemoguće otvoriti datoteku: " << ime << std::endl;
    return;
  }

  for (int i = 0; i < vel; ++i) {
    file << rand() % 100 << " ";
  }

  file.close();
}

void ispisi_niz(int *niz, int vel) {
  for (int i = 0; i < vel; ++i) {
    std::cout << niz[i] << " ";
  }
  std::cout << std::endl;
}

bool provjeri_sortiranost(int *niz, int vel) {
  for (int i = 1; i < vel; ++i) {
    if (niz[i] < niz[i - 1]) {
      return false;
    }
  }
  return true;
}

template <typename Fun> double izmjeri_vrijeme(Fun func, int *niz, int vel) {
  auto pocetak = std::chrono::high_resolution_clock::now();
  func(niz, vel);
  auto kraj = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> vrijeme = kraj - pocetak;
  return vrijeme.count();
}

template <typename tip>
void funkcija(int *niz, int vel, tip fun_sort, const std::string &ime) {
    auto pocetak = std::chrono::high_resolution_clock::now();
    fun_sort(niz, vel);
    auto kraj = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> vrijeme = kraj - pocetak;

    std::cout << "Vrijeme izvršavanja " << ime << ": " << vrijeme.count() << " milisekunde\n";

    if (provjeri_sortiranost(niz, vel)) {
        std::cout << "Uspješno sortirano.\n";
    } else {
        std::cout << "Probajte ponovo.\n";
    }

    std::string izlaz = "sortiran.txt";
    std::ofstream izlaz_file(izlaz);
    for (int i = 0; i < vel; ++i) {
        izlaz_file << niz[i] << " ";
    }
    izlaz_file.close();
}

int main() {

  int *niz = nullptr;
    int vel = 0;

    std::string ulaz = "ulaz.txt";
    std::string izlaz = "izlaz.txt";

    generisi(ulaz, 10);

    ucitaj(ulaz, niz, vel);

    std::cout << "Prije sortiranja: ";
    ispisi_niz(niz, vel);

    using SortFunction = void (*)(int *, int);
    SortFunction fun_sort = bubble_sort; 
    std::string ime = "Bubble Sort"; 

    funkcija(niz, vel, fun_sort, ime);
    delete[] niz;

    return 0;
}