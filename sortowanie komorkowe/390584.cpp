#include<iostream>

using namespace std;

long long int miliard = 1000000000;

long long int funkcja(long long int rozwiazane_problemy[1002][1002][2], long long int tab[1002], int index_pocz, int index_kon, long long int ost_z_przodu, long long int ost_z_tylu)
{

	if(index_pocz > index_kon) return 1;
	else if(ost_z_przodu == 0 && ost_z_tylu == 0)
	{
		if(index_pocz == index_kon)
		{
			rozwiazane_problemy[index_pocz][index_kon][0] = rozwiazane_problemy[index_pocz][index_kon][1] = 1;
			return rozwiazane_problemy[index_pocz][index_kon][0];
		}
		else
		{
			rozwiazane_problemy[index_pocz + 1][index_kon][0] = funkcja(rozwiazane_problemy, tab, index_pocz + 1, index_kon, tab[index_pocz], 0);
			rozwiazane_problemy[index_pocz][index_kon - 1][1] = funkcja(rozwiazane_problemy, tab, index_pocz, index_kon - 1, 0, tab[index_kon]);
			return (rozwiazane_problemy[index_pocz + 1][index_kon][0] + rozwiazane_problemy[index_pocz][index_kon - 1][1])%miliard;
		}
	}
	else if(ost_z_przodu != 0)
	{
		if(rozwiazane_problemy[index_pocz][index_kon][0] != -1) return (rozwiazane_problemy[index_pocz][index_kon][0])%miliard;
		else if(tab[index_pocz] > ost_z_przodu)
		{
			if(tab[index_kon] > ost_z_przodu && index_pocz != index_kon)
			{
				rozwiazane_problemy[index_pocz + 1][index_kon][0] = funkcja(rozwiazane_problemy, tab, index_pocz + 1, index_kon, tab[index_pocz], 0);
				rozwiazane_problemy[index_pocz][index_kon - 1][1] = funkcja(rozwiazane_problemy, tab, index_pocz, index_kon - 1, 0, tab[index_kon]);
				rozwiazane_problemy[index_pocz][index_kon][0] = (rozwiazane_problemy[index_pocz + 1][index_kon][0] + rozwiazane_problemy[index_pocz][index_kon - 1][1])%miliard;
				return rozwiazane_problemy[index_pocz][index_kon][0];
			}
			else
			{
				rozwiazane_problemy[index_pocz][index_kon][0] = rozwiazane_problemy[index_pocz + 1][index_kon][0] = funkcja(rozwiazane_problemy, tab, index_pocz + 1, index_kon, tab[index_pocz], 0);
				return rozwiazane_problemy[index_pocz][index_kon][0];
			}
		}
		else
		{
			if(tab[index_kon] > ost_z_przodu)
			{
				rozwiazane_problemy[index_pocz][index_kon][0] = rozwiazane_problemy[index_pocz][index_kon - 1][1] = funkcja(rozwiazane_problemy, tab, index_pocz, index_kon - 1, 0, tab[index_kon]);
				return rozwiazane_problemy[index_pocz][index_kon][0];
			}
			else
			{
				rozwiazane_problemy[index_pocz][index_kon][0] = rozwiazane_problemy[index_pocz][index_kon][1] = 0;
				return 0;
			}
		}
	}
	else if(ost_z_tylu != 0)
	{
		if(rozwiazane_problemy[index_pocz][index_kon][1] != -1) return rozwiazane_problemy[index_pocz][index_kon][1];
		else if(tab[index_pocz] < ost_z_tylu)
		{
			if(tab[index_kon] < ost_z_tylu && index_pocz != index_kon)
			{
				rozwiazane_problemy[index_pocz + 1][index_kon][0] = funkcja(rozwiazane_problemy, tab, index_pocz + 1, index_kon, tab[index_pocz], 0);
				rozwiazane_problemy[index_pocz][index_kon - 1][1] = funkcja(rozwiazane_problemy, tab, index_pocz, index_kon - 1, 0, tab[index_kon]);
				return (rozwiazane_problemy[index_pocz + 1][index_kon][0] + rozwiazane_problemy[index_pocz][index_kon - 1][1])%miliard;
			}
			else
			{
				rozwiazane_problemy[index_pocz + 1][index_kon][0] = funkcja(rozwiazane_problemy, tab, index_pocz + 1, index_kon, tab[index_pocz], 0);
				return rozwiazane_problemy[index_pocz + 1][index_kon][0];
			}
		}
		else
		{
			if(tab[index_kon] < ost_z_tylu)
			{
				rozwiazane_problemy[index_pocz][index_kon - 1][1] = funkcja(rozwiazane_problemy, tab, index_pocz, index_kon - 1, 0, tab[index_kon]);
				return rozwiazane_problemy[index_pocz][index_kon - 1][1];
			}
			else return 0;
		}
	}
	return 0;
}

int main()
{
	ios_base::sync_with_stdio(0);
	int ile_liczb;
	cin >> ile_liczb;
	long long int tablica[1002];
	long long int rozwiazane_problemy[1002][1002][2];
	for(int i = 0; i < ile_liczb; i++)
	{
		for(int j = 0; j < ile_liczb; j++)
		{
			rozwiazane_problemy[i][j][0] = -1;
			rozwiazane_problemy[i][j][1] = -1;
		}
	}
	for(int i = 0; i < ile_liczb; i++)
	{
		cin >> tablica[i];
	}
	long long int wynik = funkcja(rozwiazane_problemy, tablica, 0, ile_liczb - 1, 0, 0);
	wynik = wynik%miliard;
	cout << wynik;
}