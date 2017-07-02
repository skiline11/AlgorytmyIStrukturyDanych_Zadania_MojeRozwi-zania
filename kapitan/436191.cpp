#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAX_ILOSC_WYSP = 200000;

struct parametry_wyspy
{
    int x, y;
    int ile_krokow_min;
    bool czy_odwiedzona;
    bool czy_jestem_w_secie;
};

parametry_wyspy wyspy[MAX_ILOSC_WYSP + 1];

int ile_wysp;

struct comparatorPoXach {
    bool operator()(const int& a, const int& b)
    {
        if(wyspy[a].x < wyspy[b].x) return true;
        else if(wyspy[a].x > wyspy[b].x) return false;
        else
        {
            if(wyspy[a].y < wyspy[b].y) return true;
            else return false;
        }
    }
};

struct comparatorPoYach {
    bool operator()(const int& a, const int& b)
    {
        if(wyspy[a].y < wyspy[b].y) return true;
        else if(wyspy[a].y > wyspy[b].y) return false;
        else
        {
            if(wyspy[a].x < wyspy[b].x) return true;
            else return false;
        }
    }
};

set<int, comparatorPoXach> setPoXach;
set<int, comparatorPoYach> setPoYach;

void pobierz_wyspy()
{
    //Pobieram wyspy
    parametry_wyspy p;
    p.x = p.y = p.ile_krokow_min = 1000000001;
    p.czy_odwiedzona = false;
    wyspy[0] = p;
    for(int licznik = 1; licznik <= ile_wysp; licznik++)
    {
        cin >> p.x >> p.y;
        p.ile_krokow_min = -1;
        p.czy_odwiedzona = false;
        p.czy_jestem_w_secie = false;
        wyspy[licznik] = p;
        setPoXach.insert(licznik);
        setPoYach.insert(licznik);
    }
    wyspy[1].ile_krokow_min = 0;
    wyspy[1].czy_odwiedzona = true;
    wyspy[1].czy_jestem_w_secie = true;
}

struct comparatorKolejki {
    bool operator()(const int& a, const int& b)
    {
        if(a == b) return false;
        if(wyspy[a].ile_krokow_min < wyspy[b].ile_krokow_min) return true;
        else if(wyspy[a].ile_krokow_min > wyspy[b].ile_krokow_min) return false;
        else
        {
            if(wyspy[a].x < wyspy[b].x) return true;
            else if(wyspy[a].x > wyspy[b].x) return false;
            else
            {
                if(wyspy[a].y < wyspy[b].y) return true;
                else if(wyspy[a].y > wyspy[b].y) return false;
            }
        }
        return true;
    }
};

set<int, comparatorKolejki> kolejka;
set<int, comparatorPoXach>::iterator iteratorPoXach;
set<int, comparatorPoYach>::iterator iteratorPoYach;
set<int, comparatorKolejki>::iterator iteratorKolejki;

void wypisz_kolejke()
{
    for(iteratorKolejki = kolejka.begin(); iteratorKolejki != kolejka.end(); iteratorKolejki++)
    {
        cout << *iteratorKolejki << "(" << wyspy[*iteratorKolejki].x << ", " << wyspy[*iteratorKolejki].y << ")->ruchow:" << wyspy[*iteratorKolejki].ile_krokow_min<< ",   ";
    }
    cout << endl;
}

void wykonuj_ruchy();

void wykonaj_ruch_w_poziomie(int nrWyspy)
{
    iteratorPoXach = setPoXach.find(nrWyspy);
    int poprzedniaWyspa, nastepnaWyspa;
    int ile_krokow;
    if(iteratorPoXach != setPoXach.begin())
    {
        iteratorPoXach--;
        poprzedniaWyspa = *iteratorPoXach;
        iteratorPoXach++;
        if(wyspy[poprzedniaWyspa].czy_odwiedzona == false)
        {
            ile_krokow = wyspy[nrWyspy].ile_krokow_min + min(abs(wyspy[nrWyspy].x - wyspy[poprzedniaWyspa].x), abs(wyspy[nrWyspy].y - wyspy[poprzedniaWyspa].y));
            if(wyspy[poprzedniaWyspa].ile_krokow_min == -1 || wyspy[poprzedniaWyspa].ile_krokow_min > ile_krokow)
            {
                if(wyspy[poprzedniaWyspa].czy_jestem_w_secie == true)
                {
//                    cout << poprzedniaWyspa << " jest w secie" << endl;
                    iteratorKolejki = kolejka.find(poprzedniaWyspa);
                    kolejka.erase(iteratorKolejki);
                }
                wyspy[poprzedniaWyspa].ile_krokow_min = ile_krokow;
                wyspy[poprzedniaWyspa].czy_jestem_w_secie = true;
                kolejka.insert(poprzedniaWyspa);
            }
        }
    }
//    if(setPoXach.find(nrWyspy) != iteratorPoXach) cout << "ERRRRRRROOOOOOOOOORRRRRRR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
    iteratorPoXach++;
    if(iteratorPoXach != setPoXach.end())
    {
        nastepnaWyspa = *iteratorPoXach;
        if(wyspy[nastepnaWyspa].czy_odwiedzona == false)
        {
            ile_krokow = wyspy[nrWyspy].ile_krokow_min + min(abs(wyspy[nrWyspy].x - wyspy[nastepnaWyspa].x), abs(wyspy[nrWyspy].y - wyspy[nastepnaWyspa].y));
            if(wyspy[nastepnaWyspa].ile_krokow_min == -1 || wyspy[nastepnaWyspa].ile_krokow_min > ile_krokow)
            {
                if(wyspy[nastepnaWyspa].czy_jestem_w_secie == true)
                {
//                    cout << nastepnaWyspa << " jest w secie" << endl;
                    iteratorKolejki = kolejka.find(nastepnaWyspa);
                    kolejka.erase(iteratorKolejki);
                }
                wyspy[nastepnaWyspa].ile_krokow_min = ile_krokow;
                wyspy[nastepnaWyspa].czy_jestem_w_secie = true;
                kolejka.insert(nastepnaWyspa);
            }
        }
    }
//    cout << "Kolejka po ruchu w poziomie: ";
//    wypisz_kolejke();
}

void wykonaj_ruch_w_pionie(int nrWyspy)
{
    iteratorPoYach = setPoYach.find(nrWyspy);
    int poprzedniaWyspa, nastepnaWyspa;
    int ile_krokow;
    if(iteratorPoYach != setPoYach.begin())
    {
        iteratorPoYach--;
        poprzedniaWyspa = *iteratorPoYach;
        iteratorPoYach++;
        if(wyspy[poprzedniaWyspa].czy_odwiedzona == false)
        {
            ile_krokow = wyspy[nrWyspy].ile_krokow_min + min(abs(wyspy[nrWyspy].x - wyspy[poprzedniaWyspa].x), abs(wyspy[nrWyspy].y - wyspy[poprzedniaWyspa].y));
            if(wyspy[poprzedniaWyspa].ile_krokow_min == -1 || wyspy[poprzedniaWyspa].ile_krokow_min > ile_krokow)
            {
                if(wyspy[poprzedniaWyspa].czy_jestem_w_secie == true)
                {
//                    cout << poprzedniaWyspa << " jest w secie" << endl;
                    iteratorKolejki = kolejka.find(poprzedniaWyspa);
                    kolejka.erase(iteratorKolejki);
                }
                wyspy[poprzedniaWyspa].ile_krokow_min = ile_krokow;
                wyspy[poprzedniaWyspa].czy_jestem_w_secie = true;
                kolejka.insert(poprzedniaWyspa);
            }
        }
    }
    iteratorPoYach++;
    if(iteratorPoYach != setPoYach.end())
    {
        nastepnaWyspa = *iteratorPoYach;
        if(wyspy[nastepnaWyspa].czy_odwiedzona == false)
        {
            ile_krokow = wyspy[nrWyspy].ile_krokow_min + min(abs(wyspy[nrWyspy].x - wyspy[nastepnaWyspa].x), abs(wyspy[nrWyspy].y - wyspy[nastepnaWyspa].y));
            if(wyspy[nastepnaWyspa].ile_krokow_min == -1 || wyspy[nastepnaWyspa].ile_krokow_min > ile_krokow)
            {
                if(wyspy[nastepnaWyspa].czy_jestem_w_secie == true)
                {
//                    cout << nastepnaWyspa << " jest w secie" << endl;
                    iteratorKolejki = kolejka.find(nastepnaWyspa);
                    kolejka.erase(iteratorKolejki);
                }
                wyspy[nastepnaWyspa].ile_krokow_min = ile_krokow;
                wyspy[nastepnaWyspa].czy_jestem_w_secie = true;
                kolejka.insert(nastepnaWyspa);
            }
        }
    }
//    cout << "Kolejka po ruchu w pionie: ";
//    wypisz_kolejke();

}

void wykonuj_ruchy()
{
    bool koniec = false;
    while(koniec == false)
    {
//        cout << "Kolejka: ";
//        wypisz_kolejke();
        iteratorKolejki = kolejka.begin();
//        cout << "Jestem na wyspie nr " << *iteratorKolejki << " (" << wyspy[*iteratorKolejki].x << ", " << wyspy[*iteratorKolejki].y << ")->ruchow:" << wyspy[*iteratorKolejki].ile_krokow_min << endl;
        if(*iteratorKolejki == ile_wysp)
        {
            cout << wyspy[*iteratorKolejki].ile_krokow_min << endl;
            koniec = true;
        }
        else
        {
            int nrWyspy = *iteratorKolejki;
            kolejka.erase(iteratorKolejki);
//            cout << "Kolejka po usunieciu: ";
//            wypisz_kolejke();

            wyspy[nrWyspy].czy_odwiedzona = true;
            wykonaj_ruch_w_poziomie(nrWyspy);
            wykonaj_ruch_w_pionie(nrWyspy);
//            cout << endl;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin >> ile_wysp;
    pobierz_wyspy();
    kolejka.insert(0); // Dodaję to bo jest jakiś problem gdy w secie nie ma elementu największego
    kolejka.insert(1);
    wykonuj_ruchy();
    return 0;
}