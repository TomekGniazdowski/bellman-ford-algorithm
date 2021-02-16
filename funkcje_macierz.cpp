#include <iostream>
#include <fstream>
#include "funkcje_macierz.h"

using namespace std;

void Graf_macierz :: inicjuj_macierz()
{
    //inicjalizacja elelementow grafu - wszytskie krawedzie zerowe na poczatku
    for(int i = 0; i<ilosc_wezlow; ++i)
    {
        for(int j = 0; j<ilosc_wezlow; ++j)
        {
            macierz_grafu[i][j] = 0;
        }
    }


    macierz_grafu[0][1] = 5;
    macierz_grafu[0][2] = 1;
    macierz_grafu[1][3] = 3;
    macierz_grafu[1][2] = 2;
    macierz_grafu[1][4] = 20;
    macierz_grafu[2][1] = 3;
    macierz_grafu[2][4] = 12;
    macierz_grafu[3][2] = 3;
    macierz_grafu[3][4] = 2;
    macierz_grafu[3][5] = 6;
    macierz_grafu[4][5] = 1;


//int k,j;

////petla wykorzystana do testow - tworzenia grafow "losowych"
//    for(int i = 0; i<ilosc_krawedzi; ++i)
//    {
//        if(i == 0)
//            macierz_grafu[0][rand()%ilosc_wezlow] = rand()%10;
//        else
//        {
//            do
//            {
//                k = rand()%ilosc_wezlow;
//                j = rand()%ilosc_wezlow;
//            }
//            while(macierz_grafu[k][j] != 0);
//
//            if(macierz_grafu[k][j] == 0)
//                macierz_grafu[k][j] = rand()%10;
//        }
//
//    }
}


void Graf_macierz :: inicjuj_tablice(int krawedzie,int wierzcholki,int pierwszy_element)
{
    //na poczatku odleglosci punktow od punku starowego sa rowne nieskonczonosc
    for(int i = 0; i < wierzcholki ; ++i)
    {
        this->tablica_suma_wag[i] = INFINITY;
    }

    this -> ilosc_wezlow = wierzcholki;
    this -> ilosc_krawedzi = krawedzie;

    //odleglosc od punku poczatkowego rowna zero
    tablica_suma_wag[pierwszy_element] = 0;
    tablica_poprzedni[pierwszy_element] = 0;
    this->pierwszy_element = pierwszy_element;
}

Graf_macierz :: ~Graf_macierz()
{
    for(int i = 0; i < ilosc_wezlow ; ++i)
    {
        this->tablica_suma_wag[i] = INFINITY;
    }

    for(int i = 0; i<ilosc_wezlow; ++i)
    {
        for(int j = 0; j<ilosc_wezlow; ++j)
        {
            macierz_grafu[i][j] = 0;
        }
    }
}


void Graf_macierz :: wyswietl_element()
{
    //wyseitlanie grafu
    for(int i = 0; i < ilosc_wezlow; ++i)
    {
        for(int j = 0; j< ilosc_wezlow; ++j)
        {
            if(macierz_grafu[i][j] != 0)
                std::cout << "(" << i << " -> " << j <<  " waga: " << macierz_grafu[i][j] << ") " ;

            if(j == ilosc_wezlow - 1)
                std::cout << std::endl;
        }
    }
}

void Graf_macierz:: BellmanFord()
{
    int suma = 0;

    //algorytm ma dzilac N-1 razy
    for(int k=0; k < ilosc_wezlow - 1; ++k)
    {
        //ma dojsc do kazdego elementu

        for (int i = 0; i < ilosc_wezlow; ++i)
        {

            for(int j = 0; j < ilosc_wezlow ; ++j )

            {
                //aktualizacja odleglosci punktu od celu

                if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + macierz_grafu[i][j] < tablica_suma_wag[j] && macierz_grafu[i][j] != 0)
                {
                    tablica_suma_wag[j] = tablica_suma_wag[i] + macierz_grafu[i][j];
                    tablica_poprzedni[j] = i;
                }

            }
        }
    }


    //detekcja ujemnych cykli
    for (int i = 0; i < ilosc_wezlow; ++i)
    {

        for(int j = 0; j < ilosc_wezlow ; ++j )

        {

            if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + macierz_grafu[i][j] < tablica_suma_wag[j] && macierz_grafu[i][j] != 0)
            {
                std::cout << "Graf posiada ujemny cykl \n";
                break;
            }
        }
    }

    std::cout << std::endl;

    //wyswietlanie odleglosci
    for(int i = 0; i<ilosc_wezlow; ++i)
        std::cout << tablica_suma_wag[i] << " ";

    std::cout << std::endl;

    //wyswietlanie trasy do elementow
    for(int j = ilosc_wezlow - 1; j>=0; --j )
    {
        if(j != pierwszy_element)
        {
            wyswietl_trase(j);
        }
    }

    std::cout << std::endl;
}

void Graf_macierz :: wyswietl_trase(int j)
{
    //wysweitlanie trasy do elementow - na tej samej zasadzie co w grafie w formie listy
    int cel = j;
    std::cout << tablica_suma_wag[cel] << ": ";
    std::cout << cel << " <- ";
    std::cout  << tablica_poprzedni[cel] << " ";

    if(tablica_suma_wag[cel] != INFINITY)
    {
        while(tablica_poprzedni[cel] != pierwszy_element)
        {

            std::cout << " <- " << tablica_poprzedni[tablica_poprzedni[cel]];
            cel = tablica_poprzedni[cel];
        }
    }
    std::cout << std::endl;

}



void Graf_macierz :: wazne_elementy()
{
    std::cout << "ilosc wezlow: " << ilosc_wezlow << std::endl;
    std::cout << "ilosc krawedzi: " << ilosc_krawedzi << std::endl;
    std::cout << "pierwszy element: " << pierwszy_element << std::endl;
    for(int i = 0; i< this->ilosc_wezlow; ++i)
        std::cout << this->tablica_suma_wag[i] << " ";
}




int Graf_macierz :: liczbe_wzl_cel(int cel)
{
    //okreslenie liczby wezlow bezposrednich do celu
    int licznik = 0;
    for ( int i = 0; i < ilosc_wezlow; ++i)
    {
        for(int j = 0; j< ilosc_wezlow; ++j)
        {
            if(macierz_grafu[i][j] != 0 && j == cel)
            {
                licznik = licznik + 1;
            }
        }
    }
    std::cout << "ilsc wezlow do celu: " << licznik << std::endl;
    return licznik;
}



void Graf_macierz:: BellmanFord_2_pkt(int cel, int il_wzl_do_cel)
{
    //dziala tak samo jak zwykly, ale konczy prace, gdy wszytskie wezly do celu zostana sprawdzone
    int licznik = 0;

    std :: cout << std:: endl;

    for(int k=1; k< ilosc_wezlow; ++k)
    {
        for (int i = 0; i < ilosc_wezlow; ++i)
        {

            for(int j = 0; j < ilosc_wezlow ; ++j )

            {

                if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + macierz_grafu[i][j] < tablica_suma_wag[j] && macierz_grafu[i][j] != 0)
                {
                    tablica_suma_wag[j] = tablica_suma_wag[i] + macierz_grafu[i][j];
                    tablica_poprzedni[j] = i;
                    if(j == cel)
                        licznik = licznik + 1;
                    if(licznik == il_wzl_do_cel)
                        break;
                }

            }
        }
    }

    std::cout << std::endl;

    for (int i = 0; i < ilosc_wezlow; ++i)
    {

        for(int j = 0; j < ilosc_wezlow ; ++j )

        {

            if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + macierz_grafu[i][j] < tablica_suma_wag[j] && macierz_grafu[i][j] != 0)
            {
                std::cout << "Graf posiada ujemny cykl \n";
                break;
            }
        }
    }

    std::cout << tablica_suma_wag[cel] << " ";

    std::cout << std::endl;

    this->wyswietl_trase(cel);

    std::cout << std::endl;
}

void Graf_macierz :: zapis_do_pliku_2_pkt_macierz(int poczatek, int cel)
{
    //zapis do pliku
    fstream plik;
    plik.open("Wyniki_macierz.txt",ios::out);
    plik << "odleglosci miedzy dwoma punktami: " << endl;

    plik << poczatek << "-> " << cel << ": " << tablica_suma_wag[cel];

    plik.close();
}

void Graf_macierz :: zapis_do_pliku_macierz(int poczatek)
{
    //zapis wynikow do pliku
    fstream plik;
    plik.open("Wyniki_macierz.txt",ios::out);
    plik << "odleglosci miedzy kolejnymi punktami: " << endl;

    for(int i = 0; i< this->ilosc_wezlow; ++i)
    {
        plik << poczatek << "->" << i << ": " << this->tablica_suma_wag[i] << endl;
    }

    plik.close();
}
