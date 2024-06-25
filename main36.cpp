//TP 2022/2023: LV 6, Zadatak 6
#include <iostream>
#include <cmath>
#include <new>
#include <vector>
#include <deque>

template<typename T>
T** KreirajDinamickuKopiju2D(T** mat){
    int m=mat.size();
    int br_el=mat[0].size();
    T** nova= new T*[m];
    for(int i=0;i<m;i++){
        nova[i]=new T[br_el[i]];
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<br_el[i];j++){
            nova[i][j]=mat[i][j];
        }
    }
    return nova;
}

int main ()
{
    int n;
    std::cout<<"Unesite broj redova kvadratne matrice: ";
    std::cin>>n;

    std::vector<std::vector<int>> mat(n,std::vector<int>(n));
    std::cout<<"Unesite elemente matrice: "<<std::endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            std::cin>>mat[i][j];
        }
    }

    try{
        int *br_el= new int[n];
        for(int i=0;i<n;i++){
            br_el[i]=n;
        }
        int **nova=KreirajDinamickuKopiju2D(mat);
        std::cout<<"Kreirana dinamicka matrica: "<<std::endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                std::cout<<nova[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        for(int i=0;i<n;i++){
            delete[] nova[i];
        }
        delete[] nova;
        delete[] br_el;
    }
    catch(std::bad_alloc& e){
        std::cout<<"Nedovoljno memorije"<<std::endl;
    }
    

	return 0;
}
