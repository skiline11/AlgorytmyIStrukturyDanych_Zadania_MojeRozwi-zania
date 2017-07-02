#include<cstdio>
#include<iostream>

using namespace std;

struct typ_drzewa
{
    long long wartosc;
    int pocz_przedzialu;
    int koniec_przedzialu;
};

void ustaw_przedzialy_drzewa(typ_drzewa drzewo_przedzialowe[], int pozycja, int poczatek, int koniec)
{
    drzewo_przedzialowe[pozycja].pocz_przedzialu = poczatek;
    drzewo_przedzialowe[pozycja].koniec_przedzialu = koniec;
    drzewo_przedzialowe[pozycja].wartosc = 0;
    if(poczatek != koniec)
    {
        ustaw_przedzialy_drzewa(drzewo_przedzialowe, pozycja * 2, poczatek, (poczatek + koniec) / 2);
        ustaw_przedzialy_drzewa(drzewo_przedzialowe, pozycja * 2 + 1, (poczatek + koniec) / 2 + 1, koniec);
    }
}

void ustaw_wartosci_tab_kinwersji_i_drzewa(int ile_liczb, int potega_dwojki, long long tab_kinwersji[], typ_drzewa drzewo_przedzialowe[] )
{
    for(int i = 1; i <= ile_liczb; i++)
    {
        tab_kinwersji[i] = 1;
    }
    ustaw_przedzialy_drzewa(drzewo_przedzialowe, 1, 1, potega_dwojki);
}

long long ile_ma_po_prawej_w_drzewie(int liczba, typ_drzewa drzewo_przedzialowe[], int pozycja)
{
    if(liczba == drzewo_przedzialowe[pozycja].pocz_przedzialu) return drzewo_przedzialowe[pozycja].wartosc;
    else if(liczba < drzewo_przedzialowe[2*pozycja + 1].pocz_przedzialu)
    {
        return (ile_ma_po_prawej_w_drzewie(liczba, drzewo_przedzialowe, 2*pozycja) + drzewo_przedzialowe[2*pozycja + 1].wartosc) % 1000000000;
    }
    else return ile_ma_po_prawej_w_drzewie(liczba, drzewo_przedzialowe, 2*pozycja + 1);
}

void wstaw(long long co, int gdzie, typ_drzewa drzewo_przedzialowe[], int pozycja)
{
    drzewo_przedzialowe[pozycja].wartosc += co;
    if(drzewo_przedzialowe[pozycja].pocz_przedzialu != drzewo_przedzialowe[pozycja].koniec_przedzialu)
    {
        if(gdzie < drzewo_przedzialowe[2*pozycja + 1].pocz_przedzialu)
        {
            wstaw(co, gdzie, drzewo_przedzialowe, pozycja * 2);
        }
        else wstaw(co, gdzie, drzewo_przedzialowe, pozycja * 2 + 1);
    }
}

long long sumuj_tablice(int ile_liczb, long long tab_kinwersji[])
{
    long long suma = 0;
    for(int i = 1; i <= ile_liczb; i++)
    {
        suma += tab_kinwersji[i];
        suma = suma % 1000000000;
    }
    return suma;
}

long long ile_kinwersji(int ile_liczb, int tab_input[], long long tab_kinwersji[], typ_drzewa drzewo_przedzialowe[], int parametr_k)
{
    int potega_dwojki = 1;
    while(potega_dwojki < 2 * ile_liczb) potega_dwojki *= 2;
    ustaw_wartosci_tab_kinwersji_i_drzewa(ile_liczb, potega_dwojki/2, tab_kinwersji, drzewo_przedzialowe);
    for(int licznik = 2; licznik <= parametr_k; licznik++)
    {
        for(int i = 1; i <= potega_dwojki - 1; i++) drzewo_przedzialowe[i].wartosc = 0;
        for(int i = 1; i <= ile_liczb; i++)
        {
            long long ile = ile_ma_po_prawej_w_drzewie(tab_input[i], drzewo_przedzialowe, 1);
            wstaw(tab_kinwersji[i], tab_input[i], drzewo_przedzialowe, 1);
            tab_kinwersji[i] = ile;
        }
    }
    return sumuj_tablice(ile_liczb, tab_kinwersji);
}

int main()
{
    ios_base::sync_with_stdio(0);
    int ile_liczb, parametr_k;
    cin >> ile_liczb;
    cin >> parametr_k;
    if(parametr_k > ile_liczb)
    {
        int x;
        for(int i = 0; i < ile_liczb; i++) cin >> x;
        cout << 0 << endl;
    }
    else
    {
        int tab_input[ile_liczb + 1];
        long long tab_kinwersji[ile_liczb + 2];
        typ_drzewa drzewo_przedzialowe[ile_liczb * 4];
        for(int i = 1; i <= ile_liczb; i++) cin >> tab_input[i];
        cout << ile_kinwersji(ile_liczb, tab_input, tab_kinwersji, drzewo_przedzialowe, parametr_k) << endl;
    }
    return 0;
}