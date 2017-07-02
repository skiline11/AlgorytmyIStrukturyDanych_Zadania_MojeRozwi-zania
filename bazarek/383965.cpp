#include<iostream>

using namespace std;

struct typ_ceny_produktow
{
    int cena;
    int nastepny_o_innej_parzystosci;
    int poprzedni_o_innej_parzystosci;
};

void uzupelnij_strukture_o_poprzednie_i_nastepne_innych_parzystosci(typ_ceny_produktow ceny_produktow[], int ile_jest_produktow_na_bazarku)
{
    int poprzedni_parzysty = -1, poprzedni_nieparzysty = -1;
    for(int i = 0; i < ile_jest_produktow_na_bazarku; i++)
    {
        if(ceny_produktow[i].cena % 2 == 1)
        {
            ceny_produktow[i].poprzedni_o_innej_parzystosci = poprzedni_parzysty;
            poprzedni_nieparzysty = ceny_produktow[i].cena;
        }
        else
        {
            ceny_produktow[i].poprzedni_o_innej_parzystosci = poprzedni_nieparzysty;
            poprzedni_parzysty = ceny_produktow[i].cena;
        }
    }
    int nastepny_parzysty = -1, nastepny_nieparzysty = -1;
    for(int i = ile_jest_produktow_na_bazarku - 1; i >= 0; i--)
    {
        if(ceny_produktow[i].cena % 2 == 1)
        {
            ceny_produktow[i].nastepny_o_innej_parzystosci = nastepny_parzysty;
            nastepny_nieparzysty = ceny_produktow[i].cena;
        }
        else
        {
            ceny_produktow[i].nastepny_o_innej_parzystosci = nastepny_nieparzysty;
            nastepny_parzysty = ceny_produktow[i].cena;
        }
    }
}

void licz_sumy_prefixowe(int ile_jest_produktow_na_bazarku, typ_ceny_produktow ceny_produktow[], long long int sumy_prefiksowe_cen_produktow[])
{
    sumy_prefiksowe_cen_produktow[0] = 0;
    for(int i = 1; i <= ile_jest_produktow_na_bazarku; i++)
    {
        sumy_prefiksowe_cen_produktow[i] = sumy_prefiksowe_cen_produktow[i - 1] + ceny_produktow[i - 1].cena;
    }
}

long long int znajdz_max_nieparzysta_cene_produktow(int ile_jest_produktow_na_bazarku, typ_ceny_produktow ceny_produktow[], long long int sumy_prefiksowe_cen_produktow[])
{
    int ile_produktow_chce_kupic;
    cin >> ile_produktow_chce_kupic;
    if(sumy_prefiksowe_cen_produktow[ile_produktow_chce_kupic] % 2 == 1) return sumy_prefiksowe_cen_produktow[ile_produktow_chce_kupic];
    else {
        if (ile_produktow_chce_kupic == ile_jest_produktow_na_bazarku) return -1;
        else {
            if ((ceny_produktow[ile_produktow_chce_kupic - 1].cena + ceny_produktow[ile_produktow_chce_kupic].cena) %
                2 == 1) {
                return sumy_prefiksowe_cen_produktow[ile_produktow_chce_kupic] -
                       ceny_produktow[ile_produktow_chce_kupic - 1].cena +
                       ceny_produktow[ile_produktow_chce_kupic].cena;
            }
            else {
//          |------------------------|
//          |    a     b||c     d    |
//          |------------------------|
                if (ceny_produktow[ile_produktow_chce_kupic - 1].poprzedni_o_innej_parzystosci != -1) //istnieje a
                {
                    if (ceny_produktow[ile_produktow_chce_kupic].nastepny_o_innej_parzystosci != -1) // istnieje d
                    {
                        int dodaj1 = ceny_produktow[ile_produktow_chce_kupic].cena -
                                     ceny_produktow[ile_produktow_chce_kupic - 1].poprzedni_o_innej_parzystosci;
                        int dodaj2 = ceny_produktow[ile_produktow_chce_kupic].nastepny_o_innej_parzystosci -
                                     ceny_produktow[ile_produktow_chce_kupic - 1].cena;
                        return sumy_prefiksowe_cen_produktow[ile_produktow_chce_kupic] + max(dodaj1, dodaj2);
                    }
                    else // nie istnieje d
                    {
                        return sumy_prefiksowe_cen_produktow[ile_produktow_chce_kupic] -
                               ceny_produktow[ile_produktow_chce_kupic - 1].poprzedni_o_innej_parzystosci +
                               ceny_produktow[ile_produktow_chce_kupic].cena;
                    }
                }
                else // nie istnieje a
                {
                    if (ceny_produktow[ile_produktow_chce_kupic].nastepny_o_innej_parzystosci != -1) // istnieje d
                    {
                        return sumy_prefiksowe_cen_produktow[ile_produktow_chce_kupic] -
                               ceny_produktow[ile_produktow_chce_kupic - 1].cena +
                               ceny_produktow[ile_produktow_chce_kupic].nastepny_o_innej_parzystosci;
                    }
                    else // nie istnieje d
                    {
                        return -1;
                    }
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);

    int ile_jest_produktow_na_bazarku;
    cin >> ile_jest_produktow_na_bazarku;

    typ_ceny_produktow ceny_produktow[ile_jest_produktow_na_bazarku];
    for(int i = 0; i < ile_jest_produktow_na_bazarku; i++)
    {
        cin >> ceny_produktow[ile_jest_produktow_na_bazarku - i - 1].cena;
    }

    uzupelnij_strukture_o_poprzednie_i_nastepne_innych_parzystosci(ceny_produktow, ile_jest_produktow_na_bazarku);

    int ile_dni_bajtek_spedzi_u_babci;
    cin >> ile_dni_bajtek_spedzi_u_babci;

    long long int sumy_prefiksowe_cen_produktow[ile_jest_produktow_na_bazarku + 1];
    licz_sumy_prefixowe(ile_jest_produktow_na_bazarku, ceny_produktow, sumy_prefiksowe_cen_produktow);

    for(int i = 0; i < ile_dni_bajtek_spedzi_u_babci; i++)
    {
        cout << znajdz_max_nieparzysta_cene_produktow(ile_jest_produktow_na_bazarku, ceny_produktow, sumy_prefiksowe_cen_produktow) << endl;
    }
    return 0;
}