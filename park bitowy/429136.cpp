#include<cstdio>
#include<iostream>

using namespace std;

struct typGlownegoDrzewa
{
    int wysokosc_polanki_w_drzewie;
    int ojciec, lewy_syn, prawy_syn;
};

struct typNajdluzszejSciezki
{
    int wysokosc_polanki_w_drzewie;
    int ojciec;
    int nr_w_najdluzszej_sciezce; // ten z najdluzszej sciezki
};

typGlownegoDrzewa polanki_glownego_drzewa[500002];
int najdluzsza_sciezka[500002];
typNajdluzszejSciezki polanki_najdluzszej_sciezki[500002];
int dlugosc_najdluzszej_sciezki;

void pobierzPolanki(int ilePolanek)
{
    for(int licznik = 1; licznik <= ilePolanek; licznik++)
    {
        cin >> polanki_glownego_drzewa[licznik].lewy_syn >> polanki_glownego_drzewa[licznik].prawy_syn;
        polanki_glownego_drzewa[licznik].ojciec = -1;
    }
}

void polaczPolanki(int numerPolanki)
{
    if(polanki_glownego_drzewa[numerPolanki].lewy_syn != -1)
    {
        polanki_glownego_drzewa[polanki_glownego_drzewa[numerPolanki].lewy_syn].ojciec = numerPolanki;
        polanki_glownego_drzewa[polanki_glownego_drzewa[numerPolanki].lewy_syn].wysokosc_polanki_w_drzewie = polanki_glownego_drzewa[numerPolanki].wysokosc_polanki_w_drzewie + 1;
        polaczPolanki(polanki_glownego_drzewa[numerPolanki].lewy_syn);
    }
    if(polanki_glownego_drzewa[numerPolanki].prawy_syn != -1)
    {
        polanki_glownego_drzewa[polanki_glownego_drzewa[numerPolanki].prawy_syn].ojciec = numerPolanki;
        polanki_glownego_drzewa[polanki_glownego_drzewa[numerPolanki].prawy_syn].wysokosc_polanki_w_drzewie = polanki_glownego_drzewa[numerPolanki].wysokosc_polanki_w_drzewie + 1;
        polaczPolanki(polanki_glownego_drzewa[numerPolanki].prawy_syn);
    }
}

struct wynikBFS
{
    int nr_wierzcholka, odleglosc;
};

wynikBFS BFS(int nr_wierzcholka, int poprzedni, int odleglosc)
{
    wynikBFS sasiad1, sasiad2;
    wynikBFS wynik1, wynik2;
    if(polanki_glownego_drzewa[nr_wierzcholka].ojciec == poprzedni)
    {
        sasiad1.nr_wierzcholka = polanki_glownego_drzewa[nr_wierzcholka].lewy_syn;
        sasiad2.nr_wierzcholka = polanki_glownego_drzewa[nr_wierzcholka].prawy_syn;
    }
    else if(polanki_glownego_drzewa[nr_wierzcholka].lewy_syn == poprzedni)
    {
        sasiad1.nr_wierzcholka = polanki_glownego_drzewa[nr_wierzcholka].ojciec;
        sasiad2.nr_wierzcholka = polanki_glownego_drzewa[nr_wierzcholka].prawy_syn;
    }
    else if(polanki_glownego_drzewa[nr_wierzcholka].prawy_syn == poprzedni)
    {
        sasiad1.nr_wierzcholka = polanki_glownego_drzewa[nr_wierzcholka].ojciec;
        sasiad2.nr_wierzcholka = polanki_glownego_drzewa[nr_wierzcholka].lewy_syn;
    }
    if(sasiad1.nr_wierzcholka != -1)
    {
        if(sasiad2.nr_wierzcholka != -1)
        {
            wynik1 = BFS(sasiad1.nr_wierzcholka, nr_wierzcholka, odleglosc + 1);
            wynik2 = BFS(sasiad2.nr_wierzcholka, nr_wierzcholka, odleglosc + 1);
            if(wynik1.odleglosc < wynik2.odleglosc) return wynik2;
            else return wynik1;
        }
        else return BFS(sasiad1.nr_wierzcholka, nr_wierzcholka, odleglosc + 1);
    }
    else if(sasiad1.nr_wierzcholka == -1)
    {
        if(sasiad2.nr_wierzcholka != -1)
        {
            return BFS(sasiad2.nr_wierzcholka, nr_wierzcholka, odleglosc + 1);
        }
        else
        {
            wynik1.nr_wierzcholka = nr_wierzcholka;
            wynik1.odleglosc = odleglosc;
            return wynik1;
        }
    }
}

void dodajDoPolanekNajdluzszejSciezki(int numerPolanki)
{
    if(numerPolanki != -1)
    {
        polanki_najdluzszej_sciezki[numerPolanki].nr_w_najdluzszej_sciezce = polanki_najdluzszej_sciezki[polanki_najdluzszej_sciezki[numerPolanki].ojciec].nr_w_najdluzszej_sciezce;
        polanki_najdluzszej_sciezki[numerPolanki].wysokosc_polanki_w_drzewie = polanki_najdluzszej_sciezki[polanki_najdluzszej_sciezki[numerPolanki].ojciec].wysokosc_polanki_w_drzewie + 1;
        if(polanki_glownego_drzewa[numerPolanki].lewy_syn != -1)
        {
            polanki_najdluzszej_sciezki[polanki_glownego_drzewa[numerPolanki].lewy_syn].ojciec = numerPolanki;
            dodajDoPolanekNajdluzszejSciezki(polanki_glownego_drzewa[numerPolanki].lewy_syn);
        }
        if(polanki_glownego_drzewa[numerPolanki].prawy_syn != -1)
        {
            polanki_najdluzszej_sciezki[polanki_glownego_drzewa[numerPolanki].prawy_syn].ojciec = numerPolanki;
            dodajDoPolanekNajdluzszejSciezki(polanki_glownego_drzewa[numerPolanki].prawy_syn);
        }
    }
}

void dodajDoNajdluzszejSciezki(int numerWNajdluzszejSciezce, wynikBFS wierzcholek, bool czyPoczatek)
{
    int przesuniecie;
    if(czyPoczatek) przesuniecie = -1;
    else przesuniecie = 1;
    najdluzsza_sciezka[numerWNajdluzszejSciezce] = wierzcholek.nr_wierzcholka;
    polanki_najdluzszej_sciezki[najdluzsza_sciezka[numerWNajdluzszejSciezce]].ojciec = -1;
    polanki_najdluzszej_sciezki[najdluzsza_sciezka[numerWNajdluzszejSciezce]].wysokosc_polanki_w_drzewie = 0;
    polanki_najdluzszej_sciezki[najdluzsza_sciezka[numerWNajdluzszejSciezce]].nr_w_najdluzszej_sciezce = numerWNajdluzszejSciezce;
    int polanka;
    if(numerWNajdluzszejSciezce != 1 && numerWNajdluzszejSciezce != dlugosc_najdluzszej_sciezki) // bo 1 nie ma na pewno żadnych synów, tak samo jak kon = dlugosc_najdluzszej_sciezki
    {
        if(polanki_glownego_drzewa[wierzcholek.nr_wierzcholka].lewy_syn != najdluzsza_sciezka[numerWNajdluzszejSciezce + przesuniecie])
        {
            polanka = polanki_glownego_drzewa[wierzcholek.nr_wierzcholka].lewy_syn;
            polanki_najdluzszej_sciezki[polanki_glownego_drzewa[wierzcholek.nr_wierzcholka].lewy_syn].ojciec = najdluzsza_sciezka[numerWNajdluzszejSciezce];
        }
        else if(polanki_glownego_drzewa[wierzcholek.nr_wierzcholka].prawy_syn != najdluzsza_sciezka[numerWNajdluzszejSciezce + przesuniecie])
        {
            polanka = polanki_glownego_drzewa[wierzcholek.nr_wierzcholka].prawy_syn;
            polanki_najdluzszej_sciezki[polanki_glownego_drzewa[wierzcholek.nr_wierzcholka].prawy_syn].ojciec = najdluzsza_sciezka[numerWNajdluzszejSciezce];
        }
        if(polanka != -1)
        {
            polanki_najdluzszej_sciezki[polanka].wysokosc_polanki_w_drzewie = 1;
            polanki_najdluzszej_sciezki[polanka].ojciec = najdluzsza_sciezka[numerWNajdluzszejSciezce];
            dodajDoPolanekNajdluzszejSciezki(polanka);
        }
    }
}

void dodawaj(int aktualnyWierzcholek, int poprzedniWierzcholek)
{
    int wierzcholek1, wierzcholek2;
    if(polanki_glownego_drzewa[aktualnyWierzcholek].ojciec == poprzedniWierzcholek)
    {
        wierzcholek1 = polanki_glownego_drzewa[aktualnyWierzcholek].lewy_syn;
        wierzcholek2 = polanki_glownego_drzewa[aktualnyWierzcholek].prawy_syn;
    }
    else if(polanki_glownego_drzewa[aktualnyWierzcholek].lewy_syn == poprzedniWierzcholek)
    {
        wierzcholek1 = polanki_glownego_drzewa[aktualnyWierzcholek].ojciec;
        wierzcholek2 = polanki_glownego_drzewa[aktualnyWierzcholek].prawy_syn;
    }
    else if(polanki_glownego_drzewa[aktualnyWierzcholek].prawy_syn == poprzedniWierzcholek)
    {
        wierzcholek1 = polanki_glownego_drzewa[aktualnyWierzcholek].ojciec;
        wierzcholek2 = polanki_glownego_drzewa[aktualnyWierzcholek].lewy_syn;
    }
    if(wierzcholek1 != -1)
    {
        polanki_najdluzszej_sciezki[wierzcholek1].nr_w_najdluzszej_sciezce = polanki_najdluzszej_sciezki[aktualnyWierzcholek].nr_w_najdluzszej_sciezce;
        polanki_najdluzszej_sciezki[wierzcholek1].wysokosc_polanki_w_drzewie = polanki_najdluzszej_sciezki[aktualnyWierzcholek].wysokosc_polanki_w_drzewie + 1;

        polanki_najdluzszej_sciezki[wierzcholek1].ojciec = aktualnyWierzcholek;
        dodawaj(wierzcholek1, aktualnyWierzcholek);
        if (wierzcholek2 != -1)
        {
            polanki_najdluzszej_sciezki[wierzcholek2].nr_w_najdluzszej_sciezce = polanki_najdluzszej_sciezki[aktualnyWierzcholek].nr_w_najdluzszej_sciezce;
            polanki_najdluzszej_sciezki[wierzcholek2].wysokosc_polanki_w_drzewie = polanki_najdluzszej_sciezki[aktualnyWierzcholek].wysokosc_polanki_w_drzewie + 1;
            polanki_najdluzszej_sciezki[wierzcholek2].ojciec = aktualnyWierzcholek;
            dodawaj(wierzcholek2, aktualnyWierzcholek);
        }
    }
    else if(wierzcholek2 != -1)
    {
        polanki_najdluzszej_sciezki[wierzcholek2].nr_w_najdluzszej_sciezce = polanki_najdluzszej_sciezki[aktualnyWierzcholek].nr_w_najdluzszej_sciezce;
        polanki_najdluzszej_sciezki[wierzcholek2].wysokosc_polanki_w_drzewie = polanki_najdluzszej_sciezki[aktualnyWierzcholek].wysokosc_polanki_w_drzewie + 1;
        polanki_najdluzszej_sciezki[wierzcholek2].ojciec = aktualnyWierzcholek;
        dodawaj(wierzcholek2, aktualnyWierzcholek);
    }
}

void dodajNajwyzszyWierzcholekDoNajdluzszejSciezki(int numerWNajdluzszejSciezce, int wierzcholek)
{
    najdluzsza_sciezka[numerWNajdluzszejSciezce] = wierzcholek;
    polanki_najdluzszej_sciezki[wierzcholek].ojciec = -1;
    polanki_najdluzszej_sciezki[wierzcholek].wysokosc_polanki_w_drzewie = 0;
    polanki_najdluzszej_sciezki[wierzcholek].nr_w_najdluzszej_sciezce = numerWNajdluzszejSciezce;

    if(polanki_glownego_drzewa[wierzcholek].ojciec != -1)
    {
        polanki_najdluzszej_sciezki[polanki_glownego_drzewa[wierzcholek].ojciec].ojciec = wierzcholek;
        polanki_najdluzszej_sciezki[polanki_glownego_drzewa[wierzcholek].ojciec].wysokosc_polanki_w_drzewie = 1;
        polanki_najdluzszej_sciezki[polanki_glownego_drzewa[wierzcholek].ojciec].nr_w_najdluzszej_sciezce = numerWNajdluzszejSciezce;
        // dodaje te które są podczepione do najwyższego
        dodawaj(polanki_glownego_drzewa[wierzcholek].ojciec, wierzcholek);
    }
}

void oznaczNajdluzszaSciezkeWGrafie()
{
    // Znajdzmy początek i koniec najdluzszejsciezki
    wynikBFS wierzcholek_poczatkowy = BFS(1, -1, 0);
    wynikBFS wierzcholek_koncowy = BFS(wierzcholek_poczatkowy.nr_wierzcholka, -1, 0);
    dlugosc_najdluzszej_sciezki = wierzcholek_koncowy.odleglosc + 1;
    int pocz = 1;
    int kon = dlugosc_najdluzszej_sciezki;
    // Teraz wierzcholki z najdluzszej sciezki bedziemy podczepiac do najdluzsza_sciezka, i z tych wierzcholków wyprowadzać drzewa polanki_najdluzszej_sciezki
    while(pocz != kon)
    {
        if(polanki_glownego_drzewa[wierzcholek_poczatkowy.nr_wierzcholka].wysokosc_polanki_w_drzewie > polanki_glownego_drzewa[wierzcholek_koncowy.nr_wierzcholka].wysokosc_polanki_w_drzewie)
        {
            dodajDoNajdluzszejSciezki(pocz, wierzcholek_poczatkowy, true);
            pocz++;
            wierzcholek_poczatkowy.nr_wierzcholka = polanki_glownego_drzewa[wierzcholek_poczatkowy.nr_wierzcholka].ojciec;
        }
        else if(polanki_glownego_drzewa[wierzcholek_poczatkowy.nr_wierzcholka].wysokosc_polanki_w_drzewie < polanki_glownego_drzewa[wierzcholek_koncowy.nr_wierzcholka].wysokosc_polanki_w_drzewie)// jeśli są na tej samej wysykości to najpierw dodaje tego prawego (PS : to nie ma znaczenia ale inaczej musiał bym cały czas obie strony dodawać na raz
        {
            dodajDoNajdluzszejSciezki(kon, wierzcholek_koncowy, false);
            kon--;
            wierzcholek_koncowy.nr_wierzcholka = polanki_glownego_drzewa[wierzcholek_koncowy.nr_wierzcholka].ojciec;
        }
        else
        {
            dodajDoNajdluzszejSciezki(pocz, wierzcholek_poczatkowy, true);
            dodajDoNajdluzszejSciezki(kon, wierzcholek_koncowy, false);
            wierzcholek_poczatkowy.nr_wierzcholka = polanki_glownego_drzewa[wierzcholek_poczatkowy.nr_wierzcholka].ojciec;
            wierzcholek_koncowy.nr_wierzcholka = polanki_glownego_drzewa[wierzcholek_koncowy.nr_wierzcholka].ojciec;
            pocz++;
            kon--;
        }
    }
    // Teraz pocz == kon, wierzcholek_poczatkowy = wierzcholek_koncowy
    dodajNajwyzszyWierzcholekDoNajdluzszejSciezki(pocz, wierzcholek_poczatkowy.nr_wierzcholka);
}

int szukajPolanki(int aktualnaPolanka, int odleglosc)
{
    if(polanki_najdluzszej_sciezki[aktualnaPolanka].wysokosc_polanki_w_drzewie <= odleglosc)
    {
        odleglosc -= polanki_najdluzszej_sciezki[aktualnaPolanka].wysokosc_polanki_w_drzewie;
        if (odleglosc > polanki_najdluzszej_sciezki[aktualnaPolanka].nr_w_najdluzszej_sciezce - 1)
        {
            if (odleglosc > dlugosc_najdluzszej_sciezki - polanki_najdluzszej_sciezki[aktualnaPolanka].nr_w_najdluzszej_sciezce)
            {
                return -1;
            }
            else return najdluzsza_sciezka[polanki_najdluzszej_sciezki[aktualnaPolanka].nr_w_najdluzszej_sciezce + odleglosc];
        }
        else return najdluzsza_sciezka[polanki_najdluzszej_sciezki[aktualnaPolanka].nr_w_najdluzszej_sciezce - odleglosc];
    }
    else
    {
        while(odleglosc != 0)
        {
            aktualnaPolanka = polanki_najdluzszej_sciezki[aktualnaPolanka].ojciec;
            odleglosc--;
        }
        return aktualnaPolanka;
    }
}

void pobierzIWykonajPolecenia(int ilePolecen)
{
    int poczatkowaPolanka, odleglosc, wynik;
    for(int licznik = 1; licznik <= ilePolecen; licznik++)
    {
        cin >> poczatkowaPolanka >> odleglosc;
        wynik = szukajPolanki(poczatkowaPolanka, odleglosc);
        cout << wynik << endl;
    }
}

int main()
{
    int ilePolanek;
    cin >> ilePolanek;
    pobierzPolanki(ilePolanek);
    polanki_glownego_drzewa[1].wysokosc_polanki_w_drzewie = 0;
    polanki_glownego_drzewa[1].ojciec = -1;
    polaczPolanki(1);
    oznaczNajdluzszaSciezkeWGrafie();
    int ilePolecen;
    cin >> ilePolecen;
    pobierzIWykonajPolecenia(ilePolecen);
}