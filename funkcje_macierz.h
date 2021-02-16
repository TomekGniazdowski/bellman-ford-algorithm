#include <iostream>
#include <fstream>
#define INFINITY 9999

struct Wezel_macierz
{
    int nr_wzl;
    int suma_wag;
};


class Krawedz_macierz
{
public:
    void inicjuj_macierz();
    int poczatek_krawedzi;
    int koniec_krawedzi;
    int waga_krawedzi;
};

class Graf_macierz
{
    int ilosc_wezlow;
    int ilosc_krawedzi;
    int pierwszy_element;

public:
    void inicjuj_macierz();
    int tablica_suma_wag[250];
    int tablica_poprzedni[250];
    int macierz_grafu[250][250];
    void wyswietl_graf();
    void inicjuj_tablice(int krawedzie,int wierzcholki,int pierwszy_element);
    void wyswietl_element();
    void BellmanFord();
    void BellmanFord_2_pkt(int cel, int il_wzl_do_cel);
    void wazne_elementy();
    void zapis_do_pliku(int poczatek);
    int liczbe_wzl_cel(int cel);
    void zapis_do_pliku_2_pkt(int poczatek, int cel);
    void wyswietl_trase(int j);
    ~Graf_macierz();
    void zapis_do_pliku_macierz(int poczatek);
    void zapis_do_pliku_2_pkt_macierz(int poczatek, int cel);
};
