#include <iostream>
#include <fstream>
#define INFINITY 9999

struct Wezel
{
    int nr_wzl;
    int suma_wag;
    Wezel *next;
};


class Krawedz
{
public:
    void inicjuj_krawedz(int pocz, int koniec, int waga);
    int poczatek_krawedzi;
    int koniec_krawedzi;
    int waga_krawedzi;
    void odczyt_z_pliku(int &ilosc_krawedzi, int &ilosc_wierzcholkow, int &wierzcholek_startowy);
    void zwykly_odczyt(int &ilosc_krawedzi, int &ilosc_wierzcholkow, int &wierzcholek_startowy);
};

class Graf
{
    Wezel* dodaj_wezel(int numer_wezla, int waga, Wezel* head)
    {
        Wezel* nowy_wezel = new Wezel;
        nowy_wezel->nr_wzl = numer_wezla;
        nowy_wezel->suma_wag = waga;
        nowy_wezel->next = head;
        return nowy_wezel;
    }

    int ilosc_wezlow;
    int ilosc_krawedzi;
    int pierwszy_element;

public:
     int tablica_suma_wag[251];
     int tablica_poprzedni[251];
    Wezel **head;
    Graf (Krawedz krawedzie[],int n, int N);
    ~Graf();
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
};
