#include <iostream>
#include <fstream>
#include "funkcje_lista.h"

using namespace std;

Graf ::Graf(Krawedz krawedzie[], int n, int N)
{
    // alokacja pamieci
    head = new Wezel*[N]();
    this->ilosc_wezlow = N;

    // inicjalizacja wskaznika do wszystkich wezlow
    for (int i = 0; i < N; ++i)
        head[i] = nullptr;


    // dodawanie wezla do grafu wazonego
    for (int i = 0; i < n; i++)
    {
        int poczatek = krawedzie[i].poczatek_krawedzi;
        int koniec = krawedzie[i].koniec_krawedzi;
        int waga = krawedzie[i].waga_krawedzi;

        // dodanie do poacztku krawedzi
        Wezel* nowy_wezel = dodaj_wezel(koniec, waga, head[poczatek]);

        //wskaznik "head" ma wskazywac na nastepny element
        head[poczatek] = nowy_wezel;
    }
}

Graf::~Graf()
{
    //usuniecie tablicy
    for (int i = 0; i < ilosc_wezlow; i++)
        delete[] head[i];

    delete[] head;
}

void Graf::inicjuj_tablice(int krawedzie,int wierzcholki,int pierwszy_element)
{
    //inicjalizacja suma wag - na poczatku maja wynosic nieskonczonosc
    for(int i = 0; i< wierzcholki ; ++i)
    {
        this->tablica_suma_wag[i] = INFINITY;
    }

    //inicjalizacja wartosci ilosc wierzcholkow i krawedzi
    this -> ilosc_wezlow = wierzcholki;
    this -> ilosc_krawedzi = krawedzie;

    //odleglosc od punktu poczatkowego = 0
    tablica_suma_wag[pierwszy_element] = 0;
    //tablica do wyznaczania trasy
    tablica_poprzedni[pierwszy_element] = 0;
    this->pierwszy_element = pierwszy_element;
}

void Graf :: wyswietl_element()
{
    //wyswietlanie wszytstkich elementow grafu
    for ( int i = 0; i < this->ilosc_wezlow; ++i)
    {
        Wezel* tmp = this -> head[i];
        while (tmp != nullptr)
        {
            std::cout << "(";
            std::cout << i << " ";
            std::cout<<"-> "<< tmp->nr_wzl;
            std::cout << " waga: ";
            std::cout << tmp->suma_wag;
            std::cout << ")";
            tmp = tmp->next;
            std::cout << " ";
        }
        std::cout<< std::endl;
    }
}

void Graf:: BellmanFord()
{
    int i,j, suma = 0;
    Wezel* tmp;

    //algorytm dziala N - 1 razy
    for(j=1; j<this->ilosc_wezlow; ++j)
    {
        //"dojscie" do kazdego elementu grafu
        for (int i = 0; i < this->ilosc_wezlow; ++i)
        {
            tmp = this -> head[i];

            while (tmp != nullptr)

            {

                //aktualizacja odleglosci punktu od wezla poczatkowego
                if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + tmp->suma_wag < tablica_suma_wag[tmp->nr_wzl])
                {
                    tablica_suma_wag[tmp->nr_wzl] = tablica_suma_wag[i]+tmp->suma_wag;
                    tablica_poprzedni[tmp->nr_wzl] = i;
                }
                //"przeskoczenie" do nastepnego elementu
                tmp = tmp->next;
            }
        }
    }


    //petla do detkecji ujmenych cykli
    for (int i = 0; i < this->ilosc_wezlow; ++i)
    {
        tmp = this -> head[i];

        while (tmp != nullptr)

        {

            if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + tmp->suma_wag < tablica_suma_wag[tmp->nr_wzl])
            {
                std::cout << "Graf posiada ujemny cykl!" << std::endl;
                break;
            }
            tmp = tmp->next;
        }
    }

    //wyswietlanie odleglosci od punktu poczatkowego

    std::cout << std::endl;

    for(int i = 0; i<ilosc_wezlow; ++i)
        std::cout << this->tablica_suma_wag[i] << " ";

    std::cout << std::endl;

    //wyswietlanie trasy do punktu
    for(int j = ilosc_wezlow - 1; j>=0; --j )
    {
        if(j != pierwszy_element)
        {
            this->wyswietl_trase(j);
        }
    }

    std::cout << std::endl;
}

void Graf :: wyswietl_trase(int j)
{
    //funkcja do wyswetlania trasy
    int cel = j;
    std::cout << tablica_suma_wag[cel] << ": ";
    std::cout << cel << " <- ";
    std::cout  << tablica_poprzedni[cel] << " ";

    //dziala dopoki nie "dojdziemy" do elementu poczatkowego

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

void Graf :: wazne_elementy()
{
    //wazna elementy - wyswietlanie
    std::cout << "ilosc wezlow: " << this->ilosc_wezlow << std::endl;
    std::cout << "ilosc krawedzi: " << this->ilosc_krawedzi << std::endl;
    for(int i = 0; i< this->ilosc_wezlow; ++i)
        std::cout << this->tablica_suma_wag[i] << " ";
}

void Krawedz:: inicjuj_krawedz(int pocz, int koniec, int waga)
{
    //inicjalizacja krawedzi
    this->poczatek_krawedzi = pocz;
    this->koniec_krawedzi = koniec;
    this->waga_krawedzi = waga;
}

void Krawedz :: odczyt_z_pliku(int &ilosc_krawedzi, int &ilosc_wierzcholkow, int &wierzcholek_startowy)
{
    //odczyt wartosci krawedzi z pliku
    fstream plik;
    int poczatek, koniec, waga;
    int licznik = -1;

    plik.open( "dane.txt", ios::in | ios::out );
    if( plik.good() == true )
    {
        while (!(plik.eof()))
        {
            plik >> poczatek >> koniec >> waga;

            if(licznik == -1)
            {
                ilosc_krawedzi = poczatek;
                ilosc_wierzcholkow = koniec;
                wierzcholek_startowy = waga;
            }

            else
            {
                this[licznik].poczatek_krawedzi = poczatek;
                this[licznik].koniec_krawedzi = koniec;
                this[licznik].waga_krawedzi = waga;
            }

            licznik = licznik + 1;

        }
        plik.close();
    }
}

void Graf :: zapis_do_pliku(int poczatek)
{
    //zapis wynikow do pliku
    fstream plik;
    plik.open("Wyniki_lista.txt",ios::out);
    plik << "odleglosci miedzy kolejnymi punktami: " << endl;

    for(int i = 0; i< this->ilosc_wezlow; ++i)
    {
        plik << poczatek << "->" << i << ": " << this->tablica_suma_wag[i] << endl;
    }

    plik.close();
}

void Graf:: BellmanFord_2_pkt(int cel, int il_wzl_do_cel)
{
    //dziala tak samo jak zwykly, ale konczy prace, gdy wszytskie wezly do celu zostana sprawdzone
    int i,j;
    Wezel* tmp;
    int licznik = 0;

    for(j=1; j<this->ilosc_wezlow; ++j)
    {
        //for each edge
        for (int i = 0; i < this->ilosc_wezlow; ++i)
        {
            tmp = this -> head[i];

            while (tmp != nullptr)

            {

                if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + tmp->suma_wag < tablica_suma_wag[tmp->nr_wzl])
                {
                    tablica_suma_wag[tmp->nr_wzl] = tablica_suma_wag[i]+tmp->suma_wag;
                    tablica_poprzedni[tmp->nr_wzl] = i;
                    if(tmp->nr_wzl == cel)
                        licznik = licznik + 1;
                    if(licznik == il_wzl_do_cel)
                        break;

                }
                tmp = tmp->next;
            }
        }
    }

    std::cout << std::endl;

    //petla do detekcji ujemnych cykli
    for (int i = 0; i < this->ilosc_wezlow; ++i)
    {
        tmp = this -> head[i];

        while (tmp != nullptr)

        {

            if(tablica_suma_wag[i]!=INFINITY && tablica_suma_wag[i] + tmp->suma_wag < tablica_suma_wag[tmp->nr_wzl])
            {
                std::cout << "Graf posiada ujemny cykl!" << std::endl;
                break;
            }
            tmp = tmp->next;
        }
    }


    std::cout << this->tablica_suma_wag[cel] << " ";

    std::cout << std::endl;

    this->wyswietl_trase(cel);
}

int Graf :: liczbe_wzl_cel(int cel)
{
    //okreslenie liczby bezposrednich krawedzi do wezla - celu
    int licznik = 0;
    for ( int i = 0; i < this->ilosc_wezlow; ++i)
    {
        Wezel* tmp = this -> head[i];
        while (tmp != nullptr)
        {
            if(tmp->nr_wzl == cel)
            {
                licznik = licznik + 1;
            }
            tmp = tmp->next;
        }
    }
    std::cout << "ilosc wezlow do celu: " << licznik << std::endl;
    return licznik;
}

void Graf :: zapis_do_pliku_2_pkt(int poczatek, int cel)
{
    //zapis do pliku
    fstream plik;
    plik.open("Wyniki_lista.txt",ios::out);
    plik << "odleglosci miedzy dwoma punktami: " << endl;

    plik << poczatek << "-> " << cel << ": " << tablica_suma_wag[cel];

    plik.close();
}

void Krawedz :: zwykly_odczyt(int &ilosc_krawedzi, int &ilosc_wierzcholkow, int &wierzcholek_startowy)
{
    //odczyt zwykly - wykorzystany przy testach algorytmu

    for(int i = 0; i< ilosc_krawedzi ; ++i)
    {
        this[i].poczatek_krawedzi = rand()%ilosc_wierzcholkow;
        this[i].koniec_krawedzi = rand()%ilosc_wierzcholkow;
        this[i].waga_krawedzi = rand()%10 + 1;
    }
}
