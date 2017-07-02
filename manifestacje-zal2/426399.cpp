#include<cstdio>
#include <queue>
#include <iostream>
#include <set>
using namespace std;

struct typ
{
    int numer_manifestacji, ile_osob_bierze_udzial;
};

int wartosci_set1[1000001];

struct mojComparator {
    bool operator()(const int& a, const int& b) const {
        if(wartosci_set1[a] > wartosci_set1[b]) return true;
        else if(wartosci_set1[a] < wartosci_set1[b]) return false;
        else
        {
            if(a < b) return true;
            else return false;
        }
    }
};

vector<int> poczatki[1000001];
vector<int> konce[1000001];
typedef set< int, mojComparator > mojSet;
mojSet set1;
typ wyniki[1000001];

void dodaj(int pocz, int kon, int numer_manifestacji)
{
    poczatki[pocz].push_back(numer_manifestacji);
    konce[kon].push_back(numer_manifestacji);
}

void pobierz_obywateli(int ile_obywateli)
{
    int pocz, kon, numer_manifestacji;
    for(int licznik = 1; licznik <= ile_obywateli; licznik++)
    {
        cin >> pocz >> kon >> numer_manifestacji;
        dodaj(pocz, kon, numer_manifestacji);
    }
}

void ustaw_wyniki()
{
    int nr_manifestacji;
    set<int>::iterator iterator1;
    for(int licznik = 1; licznik <= 1000000; licznik++)
    {
        while(poczatki[licznik].empty() == false)
        {
            nr_manifestacji = poczatki[licznik].back();
            poczatki[licznik].pop_back();
            if(wartosci_set1[nr_manifestacji] != 0)
            {
                set1.erase(nr_manifestacji);
            }
            wartosci_set1[nr_manifestacji]++;
            set1.insert(nr_manifestacji);
        }

        if(set1.empty() == false)
        {
            iterator1 = set1.begin();
            wyniki[licznik].numer_manifestacji = *iterator1;
            wyniki[licznik].ile_osob_bierze_udzial = wartosci_set1[*iterator1];
        }

        while(konce[licznik].empty() == false)
        {
            nr_manifestacji = konce[licznik].back();
            konce[licznik].pop_back();
            set1.erase(nr_manifestacji);
            wartosci_set1[nr_manifestacji]--;
            if(wartosci_set1[nr_manifestacji] != 0)
            {
                set1.insert(nr_manifestacji);
            }
        }
    }
}

void pobierz_momenty_i_wypisz_wyniki(int ile_momentow)
{
    int moment;
    for(int licznik = 1; licznik <= ile_momentow; licznik++)
    {
        cin >> moment;
        if(wyniki[moment].ile_osob_bierze_udzial == 0) cout << "1 0" << endl;
        else cout << wyniki[moment].numer_manifestacji << " " << wyniki[moment].ile_osob_bierze_udzial << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    int ile_obywateli, ile_momentow;
    cin >> ile_obywateli >> ile_momentow;
    pobierz_obywateli(ile_obywateli);
    ustaw_wyniki();
    pobierz_momenty_i_wypisz_wyniki(ile_momentow);
    return 0;
}