//TP 2022/2023: LV 8, Zadatak 6
#include <iostream>
#include <cmath>

template<typename Tip>
struct Cvor{
    Tip el;
    Cvor<Tip> *veza;
};

template <typename TipElemenata>
Cvor<TipElemenata> *KreirajPovezanuListu(TipElemenata zavrsni){
    TipElemenata unos;
    Cvor<TipElemenata> *prvi=nullptr, *prethodni=nullptr,*novi;
    while(true){
        std::cin>>unos;
        if(unos==zavrsni) break;
        novi=new Cvor<TipElemenata>{unos,nullptr};
        if(prethodni) prethodni->veza=novi;
        else prvi=novi;
        prethodni=novi;
    }
    return prvi;
}

template<typename TipElemenata>
int BrojElemenata(Cvor<TipElemenata>*pocetak){
    int broj=0;
    while(pocetak){
        broj++;
        pocetak=pocetak->veza;
    }
    return broj;
}

template <typename TipElemenata>
TipElemenata SumaElemenata(Cvor<TipElemenata>*pocetak){
    TipElemenata suma= TipElemenata();
    while(pocetak){
        suma+=pocetak->el;
        pocetak=pocetak->veza;
    }
    return suma;
}

template<typename TipElemenata>
int BrojVecihOd(Cvor<TipElemenata> *pocetak, TipElemenata prag){
    int broj=0;
    while(pocetak){
        if(pocetak->el>prag) broj++;
        pocetak=pocetak=pocetak->veza;
    }
    return broj;
}

template <typename TipElemenata>
void UnistiListu(Cvor<TipElemenata> *pocetak){
    while(pocetak){
        Cvor<TipElemenata> *pom=pocetak;
        pocetak=pocetak->veza;
        delete pom;
    }
}

int main ()
{
    std::cout<<"Unesite slijed brojeva (0 za kraj): ";
    Cvor<double> *lista=KreirajPovezanuListu(0.0);
    double suma=SumaElemenata(lista);

    int br_el=BrojElemenata(lista);
    double at_sr=0;
    if(br_el>0)
    at_sr=suma/br_el;

    std::cout<<"U slijedu ima "<<BrojVecihOd(lista, at_sr)<<" brojeva vecih od njihove aritmeticke sredine"<<std::endl;

    UnistiListu(lista);

	return 0;
}
