// TP 2022/2023: Zadaća 3, Zadatak 3
#include <iomanip>
#include <iostream>
#include <new>
#include <stdexcept>

template <typename TipElemenata> struct Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipElemenata **elementi = nullptr;
};

template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.br_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}

template <typename TipElemenata> 
void UnistiSve(Matrica<TipElemenata>mat1,Matrica<TipElemenata>mat2,Matrica<TipElemenata>mat3,Matrica<TipElemenata>mat4,Matrica<TipElemenata>mat5){
    UnistiMatricu(mat1); UnistiMatricu(mat2); UnistiMatricu(mat3); UnistiMatricu(mat4); UnistiMatricu(mat5);
}

template <typename TipElemenata> 
void NemaCurenja(Matrica<TipElemenata>mat1,Matrica<TipElemenata>mat2,Matrica<TipElemenata>mat3){
    UnistiMatricu(mat1); UnistiMatricu(mat2); UnistiMatricu(mat3);
}

template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.br_redova = br_redova;
  mat.br_kolona = br_kolona;
  mat.ime_matrice = ime;
  mat.elementi = new TipElemenata *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      mat.elementi[i] = new TipElemenata[br_kolona];
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  return mat;
}

template <typename TipElemenata> void UnesiMatricu(Matrica<TipElemenata> &mat) {
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = ";
      std::cin >> mat.elementi[i][j];
      std::cout<<std::endl;
    }
}

template <typename TipElemenata>
void IspisiMatricu(const Matrica<TipElemenata> &mat, int sirina_ispisa,
                   int preciznost = 6, bool treba_brisati = false) {
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++)
      std::cout << std::setw(sirina_ispisa) << std::right
                << std::setprecision(preciznost) << mat.elementi[i][j];
    std::cout << std::endl;
  }
  if(treba_brisati){
      for(int i=0;i<mat.br_redova;i++){
          delete[] mat.elementi[i];
      }
      delete[] mat.elementi;
  }
}

template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}

template <typename TipElemenata>
Matrica<TipElemenata> ProduktMatrica(const Matrica<TipElemenata> &mat1, const Matrica<TipElemenata> &mat2) {
  if (mat1.br_kolona != mat2.br_redova) throw std::domain_error("Matrice nisu saglasne za mnozenje");
  auto produkt = StvoriMatricu<TipElemenata>(mat1.br_redova, mat2.br_kolona);
  for (int i = 0; i < mat1.br_redova; i++) {
    for (int j = 0; j < mat2.br_kolona; j++) {
      produkt.elementi[i][j] = 0;
    }
  }
  for (int i = 0; i < mat1.br_redova; i++) {
    for (int j = 0; j < mat2.br_kolona; j++) {
      for (int k = 0; k < mat1.br_kolona; k++) {
        produkt.elementi[i][j] += mat1.elementi[i][k] * mat2.elementi[k][j];
      }
    }
  }
  return produkt;
}

template <typename TipElemenata>
Matrica<TipElemenata> PomnoziSaBrojem(const Matrica<TipElemenata> &mat, double n) {
  auto rezultat = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++) {
      rezultat.elementi[i][j] = n * mat.elementi[i][j];
    }
  }
  return rezultat;
}

template <typename TipElemenata>
Matrica<TipElemenata> MatricniHarmonijskiPolinom(const Matrica<TipElemenata> mat, int n) {
  if (mat.br_kolona != mat.br_redova) throw std::domain_error("Matrica nije kvadratna");
  if (n <= 0)   throw std::domain_error("Pogresan parametar n");
  Matrica<TipElemenata> harm_polinom{}, prethodna{}, novi{}, produkt{}, pamti{};
try{
  novi = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
  harm_polinom = StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++) {
    if(i==j) novi.elementi[i][j]=1;
    else novi.elementi[i][j]=0;
      harm_polinom.elementi[i][j] = 0;
    }
  }
  int k=1;
  while(k<=n) {
    pamti = ProduktMatrica(mat, novi);
    produkt = PomnoziSaBrojem(pamti, 1. / k);
    prethodna = ZbirMatrica(harm_polinom, produkt);
    NemaCurenja(produkt, harm_polinom, novi);
    novi = pamti;
    harm_polinom = prethodna;
    k++;
  }
  UnistiMatricu(novi);
  return harm_polinom;
}
catch(std::bad_alloc){
    UnistiSve(harm_polinom,prethodna,pamti,produkt,novi);
    throw;
}
  /*
  *******************************************************************************************************
  problem je sto u ovom kodu nikako ne mogu da unistim, a da mi rezultat bude dobar, mada vidim gdje curi
  zbog toga sam se odlucio da sve razlozim na krace dijelove, 
  zao mi je izbrisati ovaj dio jer se moze upotrijebiti lijepo bez dinamicke alokacije
  *******************************************************************************************************
  Matrica<TipElemenata> harm_mat =
      StvoriMatricu<TipElemenata>(mat.br_redova, mat.br_kolona);
  for (int i = 0; i < mat.br_redova; i++) {
    for (int j = 0; j < mat.br_kolona; j++) {
      harm_mat.elementi[i][j] = 0;
    }
  }
  Matrica<TipElemenata> rez = StvoriMatricu<TipElemenata>(mat.br_redova,
  mat.br_kolona); for (int k = 1; k <= n; k++) { rez = mat; if (k > 1) { for
  (int l = 1; l < k; l++) { Matrica<TipElemenata> pom = ProduktMatrica(rez,
  mat); rez = pom;
      }
    }
    for (int i = 0; i < mat.br_redova; i++) {
      for (int j = 0; j < mat.br_kolona; j++) {
        harm_mat.elementi[i][j] += (1. / k) * rez.elementi[i][j];
      }
    }
  }
  return harm_mat;*/
}

int main() {
  Matrica<double> a, c;
  int n, red;
  std::cout << "Unesite dimenziju kvadratne matrice:\n";
  std::cin >> n;
  try {
    a = StvoriMatricu<double>(n, n, 'A');
    std::cout << "Unesite elemente matrice A:\n";
    UnesiMatricu(a);
    std::cout<<std::endl;
    std::cout << "Unesite red polinoma:\n";
    std::cin >> red;
    std::cout << "Matricni harmonijski polinom: ";
    std::cout << std::endl;
    IspisiMatricu(c = MatricniHarmonijskiPolinom(a, red),10);
  } catch (std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
  }
  UnistiMatricu(a);
  UnistiMatricu(c);
  return 0;
}
