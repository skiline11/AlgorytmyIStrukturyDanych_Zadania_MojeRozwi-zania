#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX_PROJEKTOW = 100000;

int ile_wymaganych_programistow[MAX_PROJEKTOW + 2];
int ile_wymaganych_projektow_do_ukonczenia[MAX_PROJEKTOW + 2];
vector<int> projekty_ktore_mnie_wymagaja[MAX_PROJEKTOW + 2];

struct mojComparator {
    bool operator()(const int& a, const int& b) const {
        if(ile_wymaganych_programistow[a] < ile_wymaganych_programistow[b]) return true;
        else if(ile_wymaganych_programistow[a] == ile_wymaganych_programistow[b] && a > b) return true;
        else return false;
    }
};

typedef set< int, mojComparator > mojSet;
mojSet mozliwe_do_wykonania_projekty;

void pobierz_ile_wymaganych_programistow(int ile_projektow)
{
    for(int x = 1; x <= ile_projektow; x++)
    {
        cin >> ile_wymaganych_programistow[x];
    }
}

void dodaj_wszystkie_projekty_do_seta(int ile_projektow)
{
    for(int licznik = 1; licznik <= ile_projektow; licznik++)
    {
        int x = licznik;
        mozliwe_do_wykonania_projekty.insert(x);
    }
}

void pobierz_zaleznosci(int ile_zaleznosci)
{
    int nr_projektu, nr_wymaganego_projektu;
    for(int licznik = 1; licznik <= ile_zaleznosci; licznik++)
    {
        cin >> nr_projektu >> nr_wymaganego_projektu;
        projekty_ktore_mnie_wymagaja[nr_wymaganego_projektu].push_back(nr_projektu);
        ile_wymaganych_projektow_do_ukonczenia[nr_projektu]++;
        mozliwe_do_wykonania_projekty.erase(nr_projektu);
    }
}

void oblicz_i_wypisz_wymagana_liczbe_programistow(int min_liczba_projektow, int ile_projektow)
{
    int min_liczba_programistow = -1;
    int nr_projektu, numer;
    mojSet::iterator iterator1;
    for(int licznik = 1; licznik <= min_liczba_projektow; licznik++)
    {
        iterator1 = mozliwe_do_wykonania_projekty.begin();
        mozliwe_do_wykonania_projekty.erase(iterator1);
        if(min_liczba_programistow < ile_wymaganych_programistow[*iterator1])
        {
            min_liczba_programistow = ile_wymaganych_programistow[*iterator1];
        }
        numer = *iterator1;
        while(projekty_ktore_mnie_wymagaja[numer].empty() == false)
        {
            nr_projektu = projekty_ktore_mnie_wymagaja[numer].back();
            projekty_ktore_mnie_wymagaja[numer].pop_back();
            ile_wymaganych_projektow_do_ukonczenia[nr_projektu]--;
            if(ile_wymaganych_projektow_do_ukonczenia[nr_projektu] == 0)
            {
                mozliwe_do_wykonania_projekty.insert(nr_projektu);
            }
        }
    }
    cout << min_liczba_programistow << endl;
}

int main()
{
    ios_base::sync_with_stdio(0);
    int ile_projektow, ile_zaleznosci, min_liczba_projektow;
    cin >> ile_projektow >> ile_zaleznosci >> min_liczba_projektow;
    pobierz_ile_wymaganych_programistow(ile_projektow);
    dodaj_wszystkie_projekty_do_seta(ile_projektow);
    pobierz_zaleznosci(ile_zaleznosci);
    oblicz_i_wypisz_wymagana_liczbe_programistow(min_liczba_projektow, ile_projektow);
    return 0;
}