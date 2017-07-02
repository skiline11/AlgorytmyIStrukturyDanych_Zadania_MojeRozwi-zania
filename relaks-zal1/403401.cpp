/*
 * Michał Radecki
 * mr371591
 * przedmiot : Algorytmy i Struktury danych
 * Zadanie Zaliczeniowe 1 : "Releax"
 */

#include<cstdio>
#include<iostream>

using namespace std;

/*
 * Obserwacja :
 *      Zauważamy że wchodzenie pod górę jest równoważne schodzieniu w dół na warunkach wchodzenia pod górę
 *      (Czyli ruch o 1 pole w dół i conajwyżej 2 pola w prawo bądź lewo),
 *      pod warunkiem że Tomek schodzący na warunkach wchodzenia pod górę, jest w tej samej linii co Tomek schodzący normalnie, bądź niższej.
 */


/*
 Funkcja "wczytaj_mape"
 ->   Pobiera liczby z zakresu 0 do 100000 oznaczające ile punktów zdobędzie Tomek jesli stanie na dane pole
*/
void wczytaj_mape(int mapa[41][501], int ile_kolumn, int ile_wierszy)
{
    for(int y = 1; y <= ile_wierszy; y++)
    {
        for(int x = 1; x <= ile_kolumn; x++)
        {
            cin >> mapa[x][y];
        }
    }
}


/*
 * Liczba w tablicy pamiec[x1][x2][y] przechowuje informację ile maksymalnie punktów zdobył Tomek
 */

/*
 * Funkcja "wyczysc_pamiec"
 * ->   Ustawia wszystkie pary pól w każdej linii pamięci na wartość -1.
 *      Jest to informacja że tomek nie pojawił się nigdy na tych dwóch polach w czasie jedej wędrówki
 */
void wyczysc_pamiec(int pamiec[41][41][501], int ile_kolumn, int ile_wierszy)
{
    for(int a = 1; a <= ile_kolumn; a++)
    {
        for(int b = 1; b <= ile_kolumn; b++)
        {
            for(int c = 1; c <= ile_wierszy; c++)
            {
                pamiec[a][b][c] = -1;
            }
        }
    }
}

/*
 * Funkcja "licz_max_wedrowki"
 * ->   Zwraca największą liczbę punktów jaką może zdobyć Tomek podczas wędrówki
 */
int licz_max_wedrowki(int mapa[41][501], int pamiec[41][41][501], int ile_kolumn, int ile_wierszy)
{
    int max_wedrowki = 0;
    int x1, x2, x1_1, x1_2, x1_3, x2_2, x2_3, wartosc_ruchu_x1, wartosc_ruchu_x2, wartosc_ruchu;
    for(x1 = 1; x1 <= ile_kolumn; x1++)
    {
        for(x2 = x1 + 1; x2 <= ile_kolumn; x2++)
        {
            pamiec[x1][x2][1] = pamiec[x2][x1][1] = mapa[x1][1] + mapa[x2][1];
        }
    }
    for(int nr_wiersza = 1; nr_wiersza <= ile_wierszy; nr_wiersza++) // Dla każdego wiersza
    {
        for(x1 = 1; x1 <= ile_kolumn; x1++) // Wybieram pierwszą liczbę
        {
            for(x2 = 1; x2 <= ile_kolumn; x2++) // Wybieram drugą liczbę
            {
                if(x1 != x2 && pamiec[x1][x2][nr_wiersza] >= 0) // Sprawdzam czy można było tu dojsc
                {
                    if(nr_wiersza == ile_wierszy) // Jeśli jestem drugą liczbą w ostatniej linii
                    {
                        if(max_wedrowki < pamiec[x1][x2][nr_wiersza]) // i dało się dojść zbierając więcej punktów
                        {
                            max_wedrowki = pamiec[x1][x2][nr_wiersza]; // to ustawiam max_wedrówki na tą liczbę punktów
                        }
                    }
                    else // Jeśli nie jestem drugą liczbą w ostatniej linii
                    {
                        for(x1_1 = -2; x1_1 <= 2; x1_1++) // 1 liczba -> 1 ruch
                        {
                            if(1 <= (x1 + x1_1) && (x1 + x1_1) <= ile_kolumn) // Sprawdzam czy w 1 ruchu nie wyszliśmy pierwszą liczbą poza mapę
                            {
                                wartosc_ruchu_x1 = mapa[x1 + x1_1][nr_wiersza + 1];
                                if(nr_wiersza + 2 <= ile_wierszy) // Jeśli nie jestem drugą liczbą w żadnej z 2 linii od końca
                                {
                                    for(x1_2 = -2; x1_2 <= 2; x1_2++) // 1 liczba -> 2 ruch
                                    {
                                        if(1 <= (x1 + x1_1 + x1_2) && (x1 + x1_1 + x1_2) <= ile_kolumn) // Sprawdzam czy w 2 ruchu nie wyszliśmy x1 poza mapę
                                        {
                                            wartosc_ruchu_x1 += mapa[x1 + x1_1 + x1_2][nr_wiersza + 2];
                                            for(x2_2 = -1; x2_2 <= 1; x2_2++) // 2 liczba -> 1 ruch
                                            {
                                                if(1 <= (x2 + x2_2) && (x2 + x2_2) <= ile_kolumn) // Sprawdzam czy w 1 ruchu nie wyszlismy x2 poza mape
                                                {
                                                    wartosc_ruchu_x2 = mapa[x2 + x2_2][nr_wiersza + 2];
                                                    wartosc_ruchu = wartosc_ruchu_x1 + wartosc_ruchu_x2;
                                                    if(pamiec[x1 + x1_1 + x1_2][x2 + x2_2][nr_wiersza + 2] < pamiec[x1][x2][nr_wiersza] + wartosc_ruchu)
                                                    {
                                                        pamiec[x1 + x1_1 + x1_2][x2 + x2_2][nr_wiersza + 2] = pamiec[x1][x2][nr_wiersza] + wartosc_ruchu;
                                                    }
                                                }
                                            }
                                            if(nr_wiersza + 3 <= ile_wierszy) // Jeśli nie jestem drugą liczbą w żadnej z 3 linii od końca
                                            {
                                                for(x1_3 = -2; x1_3 <= 2; x1_3++) // 1 liczba -> 3 ruch
                                                {
                                                    if(1 <= (x1 + x1_1 + x1_2 + x1_3) && (x1 + x1_1 + x1_2 + x1_3) <= ile_kolumn) // Sprawdzam czy w 3 ruchu nie wyszlismy x1 poza mape
                                                    {
                                                        wartosc_ruchu_x1 += mapa[x1 + x1_1 + x1_2 + x1_3][nr_wiersza + 3];
                                                        for(x2_3 = -1; x2_3 <= 1; x2_3++) // 2 liczba -> 1 ruch
                                                        {
                                                            if(1 <= (x2 + x2_3) && (x2 + x2_3) <= ile_kolumn) // Sprawdzam czy w 1 ruchu nie wyszlismy x2 poza mape
                                                            {
                                                                wartosc_ruchu_x2 = mapa[x2 + x2_3][nr_wiersza + 3];
                                                                wartosc_ruchu = wartosc_ruchu_x1 + wartosc_ruchu_x2;
                                                                if(pamiec[x1 + x1_1 + x1_2 + x1_3][x2 + x2_3][nr_wiersza + 3] < pamiec[x1][x2][nr_wiersza] + wartosc_ruchu)
                                                                {
                                                                    pamiec[x1 + x1_1 + x1_2 + x1_3][x2 + x2_3][nr_wiersza + 3] = pamiec[x1][x2][nr_wiersza] + wartosc_ruchu;
                                                                }
                                                            }
                                                        }
                                                        wartosc_ruchu_x1 -= mapa[x1 + x1_1 + x1_2 + x1_3][nr_wiersza + 3];
                                                    }
                                                }
                                            }
                                            wartosc_ruchu_x1 -= mapa[x1 + x1_1 + x1_2][nr_wiersza + 2];
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return max_wedrowki;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int ile_wierszy, ile_kolumn;
    cin >> ile_wierszy;
    cin >> ile_kolumn;
    int mapa[41][501];
    int pamiec[41][41][501];
    wczytaj_mape(mapa, ile_kolumn, ile_wierszy);
    wyczysc_pamiec(pamiec, ile_kolumn, ile_wierszy);

    cout << licz_max_wedrowki(mapa, pamiec, ile_kolumn, ile_wierszy);
    return 0;
}