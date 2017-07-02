#include <iostream>

using namespace std;

struct typ_drzewa
{
    int kolor; // 0-mieszane. 1-biale, 2-czarne
    int pocz, kon;
    int ileBialych;
};

typ_drzewa drzewo[2097152 + 10]; // ustawione na 0

void ustaw_drzewo(int index, int pocz, int kon)
{
   drzewo[index].pocz = pocz;
   drzewo[index].kon = kon;
   drzewo[index].kolor = 2;
   drzewo[index].ileBialych = 0;
   if(pocz != kon)
   {
      ustaw_drzewo(index * 2, pocz, (pocz + kon) / 2);
      ustaw_drzewo(index * 2 + 1, (pocz + kon) / 2 + 1, kon);
   }
}

void maluj(int index, int pocz, int kon, int kolor)
{
   if (drzewo[index].pocz == pocz && drzewo[index].kon == kon)
   {
      drzewo[index].kolor = kolor;
      if(kolor == 1) drzewo[index].ileBialych = kon - pocz + 1;
      else drzewo[index].ileBialych = 0;
   }
   else if (drzewo[index].kolor != kolor) // tylko wtedy cos robimy
   {
      if (drzewo[index].kolor != 0) // czyli tu drzewo miało jakiś konkretny kolor
      {
         drzewo[index * 2].kolor = drzewo[index * 2 + 1].kolor = drzewo[index].kolor;
         drzewo[index * 2].ileBialych = drzewo[index * 2 + 1].ileBialych = (drzewo[index].ileBialych)/2;
         drzewo[index].kolor = 0;
      }
      if (pocz <= drzewo[index * 2].kon && kon >= drzewo[index * 2 + 1].pocz)
      {
         maluj(index * 2, pocz, drzewo[index * 2].kon, kolor);
         maluj(index * 2 + 1, drzewo[index * 2 + 1].pocz, kon, kolor);
      }
      else if (kon <= drzewo[index * 2].kon)
      {
         maluj(index * 2, pocz, kon, kolor);
      }
      else // pocz >= drzewo[index * 2 + 1].pocz
      {
         maluj(index * 2 + 1, pocz, kon, kolor);
      }
      drzewo[index].ileBialych = drzewo[index * 2].ileBialych + drzewo[index * 2 + 1].ileBialych;
   }
}

int main()
{
   ios_base::sync_with_stdio(0);
   int dl_autostrady;
   cin >> dl_autostrady;
   int potega2 = 1;
   while(potega2 < dl_autostrady) potega2 *= 2;

   ustaw_drzewo(1, 1, potega2);

   int ile_wydarzen;
   cin >> ile_wydarzen;
   int pocz, kon;
   char kolor;
   for(int i = 1; i <= ile_wydarzen; i++)
   {
      cin >> pocz >> kon >> kolor;
      if(kolor == 'B') maluj(1, pocz, kon, 1);
      else maluj(1, pocz, kon, 2);
      cout << drzewo[1].ileBialych << endl;
   }
   return 0;
}