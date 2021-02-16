#include <iostream>
#include <fstream>
#include <time.h>
#include <windows.h>
#include "funkcje_lista.h"
#include "funkcje_macierz.h"

using namespace std;

double czas_sr(double czas, double &suma)
{
    suma = suma + czas;
    return suma;
}

int licznik_linii_plik()
{
    int licznik = 0;
    fstream plik;
    string linia;

    plik.open( "dane.txt", ios::in);
    if( plik.good() == true )
    {
        while (!(plik.eof()))
        {
            getline(plik, linia);
            licznik = licznik + 1;
        }
        plik.close();
    }

    return licznik;
}


int main()
{
    cin.clear();
    cout.clear();

    int n = licznik_linii_plik();
    int N;
    int pierwszy_element;
    int rodzaj_szukania;
    Krawedz krawedzie[n];
    n = sizeof(krawedzie)/sizeof(krawedzie[0]);

    krawedzie[0].odczyt_z_pliku(n, N, pierwszy_element);
    Graf graf(krawedzie, n, N);

    graf.inicjuj_tablice(n,N,pierwszy_element);

    graf.wyswietl_element();

    graf.wazne_elementy();

    cout << "\nWybierz rodzaj szukania (1 lub 2): ";
    cin >> rodzaj_szukania;

    if(rodzaj_szukania == 1)
    {
        graf.BellmanFord();
        graf.zapis_do_pliku(pierwszy_element);
    }

    if(rodzaj_szukania == 2)
    {
        cout << "Podaj cel: ";
        int cel;
        cin >> cel;
        int il_wzl_do_cel = graf.liczbe_wzl_cel(cel);
        graf.BellmanFord_2_pkt(cel,il_wzl_do_cel);
        graf.zapis_do_pliku_2_pkt(pierwszy_element, cel);
    }

    cout << "\nWybierz rodzaj szukania (3 lub 4): ";
    cin >> rodzaj_szukania;
    cout << "\podaj pierwszy element: ";
    cin >> pierwszy_element;



    N = 6;
    n = 11;
    Graf_macierz graf_macierz;
    graf_macierz.inicjuj_tablice(n,N,pierwszy_element);
    graf_macierz.inicjuj_macierz();
    graf_macierz.wyswietl_element();
    graf_macierz.wazne_elementy();

    if(rodzaj_szukania == 3)
    {
        graf_macierz.BellmanFord();
        graf_macierz.zapis_do_pliku_macierz(pierwszy_element);
    }



    if(rodzaj_szukania == 4)
    {
        cout << "Podaj cel: ";
        int cel;
        cin >> cel;
        int il_wzl_do_cel = graf_macierz.liczbe_wzl_cel(cel);
        graf_macierz.BellmanFord_2_pkt(cel,il_wzl_do_cel);
        graf_macierz.zapis_do_pliku_2_pkt_macierz(pierwszy_element, cel);
    }

    return 0;
}
