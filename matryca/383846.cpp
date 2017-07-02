#include<iostream>

using namespace std;

int znajdz_matryce()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    int aktualna_pozycja = 0, pozycja_poprzedniego_znaku = -1;
    int minimalna_odleglosc_pomiedzy_roznymi_znakami = -1;
    char poprzedni_znak;
    string input;
    cin >> input;
    // Chcemy znaleźć minimalną odległość pomiędzy różnymi literami, przy założeniu że odleglosc pomiędzy A i B w ciągu A*B wynosi 1
    for(int i = 0; i < input.length(); i++)
    {
        aktualna_pozycja++;
        if(input[i] != '*')
        {
            if(pozycja_poprzedniego_znaku == -1)
            {
                pozycja_poprzedniego_znaku = aktualna_pozycja;
                poprzedni_znak = input[i];
            }
            else if(poprzedni_znak == input[i])
            {
                pozycja_poprzedniego_znaku = aktualna_pozycja;
            }
            else
            {
                if(minimalna_odleglosc_pomiedzy_roznymi_znakami == -1 || minimalna_odleglosc_pomiedzy_roznymi_znakami > aktualna_pozycja - pozycja_poprzedniego_znaku - 1)
                {
                    minimalna_odleglosc_pomiedzy_roznymi_znakami = aktualna_pozycja - pozycja_poprzedniego_znaku - 1;
                }
                pozycja_poprzedniego_znaku = aktualna_pozycja;
                poprzedni_znak = input[i];
            }
        }
    }
    if(minimalna_odleglosc_pomiedzy_roznymi_znakami == -1) minimalna_odleglosc_pomiedzy_roznymi_znakami = input.length() - 1;
    // Minimalna dlugosc matrycy to różnica pomiędzy długością wczytanego ciągu i minimalną odległością pomiędzy różnymi literami
    int min_dlugosc_matrycy = input.length() - minimalna_odleglosc_pomiedzy_roznymi_znakami;
    return min_dlugosc_matrycy;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout << znajdz_matryce();
    return 0;
}