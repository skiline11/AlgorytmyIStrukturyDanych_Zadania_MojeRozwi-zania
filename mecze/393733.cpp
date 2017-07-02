#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);

    int ilu_uczestnikow, ile_meczy;
    cin >> ilu_uczestnikow;
    cin >> ile_meczy;
    int max_uczestnikow = 1, licznik = 0;
    while(licznik < ile_meczy && max_uczestnikow < ilu_uczestnikow)
    {
        licznik++;
        max_uczestnikow *= 2;
    }
    if(max_uczestnikow < ilu_uczestnikow)
    {
        for(int i = 1; i <= ile_meczy; i++)
        {
            for(int j = 1; j <= ilu_uczestnikow; j++)
            {
                cin >> licznik; // wczytuje je ale nic z nimi nie robie
            }
        }
        cout << "NIE\n";
    }
    else
    {
    	long long tablica[ilu_uczestnikow + 1];
    	for(int i = 1; i <= ilu_uczestnikow; i++)
    	{
    		tablica[i] = 0;
    	}
    	int osoba;
    	long long potega_dwojki = 1;
    	for(int i = 1; i <= ile_meczy; i++)
    	{
    		for(int j = 1; j <= ilu_uczestnikow/2; j++)
    		{
    			cin >> osoba;
    			tablica[osoba] += potega_dwojki;
    		}
    		for(int j = ilu_uczestnikow/2 + 1; j <= ilu_uczestnikow; j++)
    		{
    			cin >> osoba;
    		}
    		potega_dwojki *= 2;
    	}
    	sort(tablica + 1, tablica + ilu_uczestnikow + 1);
    	bool nie = false;
    	for(int i = 1; i < ilu_uczestnikow && nie == false; i++)
    	{
    		if(tablica[i] == tablica[i + 1]) nie = true;
    	}
    	if(nie == false) cout << "TAK\n";
    	else cout << "NIE\n";
    }
    return 0;
}
