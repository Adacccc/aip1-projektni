#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define ID_TOCKA1 1
#define ID_SIJENA1 2
#define ID_TOCKA2 3
#define ID_SIJENA2 4
#define SLOVA "ABCDEF"
#define BOJA1 "\033[1;36m"
#define BOJA2 "\033[1;31m"
#define DEF_BOJA "\033[1;0m"

void ispis(int polje[8][8])
{
    printf(" ");
    for (int i = 0; i <= 12; i++)
    {
        for (int j = 0; j <= 12; j++)
        {
            if (i % 2 == 0 && j % 2 == 0 && i > 0 && j > 0)
            {
                int x = polje[i / 2][j / 2];
                switch (x)
                {
                case ID_TOCKA1:
                    printf("%sX%s", BOJA1, DEF_BOJA);
                    break;
                case ID_SIJENA1:
                    printf("%s|%s", BOJA1, DEF_BOJA);
                    break;
                case ID_SIJENA2:
                    printf("%s|%s", BOJA2, DEF_BOJA);
                    break;
                case ID_TOCKA2:
                    printf("%sY%s", BOJA2, DEF_BOJA);
                    break;
                default:
                    printf("%sO", DEF_BOJA);
                }
            }
            else if (i == 0 && j % 2 == 0 && j > 0)
            {
                printf("%d", j / 2);
            }
            else if (j == 0 && i % 2 == 0 && i > 0)
            {
                printf("%c", SLOVA[(i - 1) / 2]);
            }
            printf("  ");
        }
        printf("\n");
    }
}

int jeLegalno(int polje[8][8], int i, int j, int prevR, int prevS)
{
    if (polje[i][j] != 0)
    {
        return 0;
    }
    if (prevR && prevS)
    {
        if (abs(j - prevS) <= 1 && abs(i - prevR) <= 1)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        int zauzeto = 0, limit = 8;
        if (polje[i + 1][j])
        {
            zauzeto++;
        }
        if (polje[i - 1][j])
        {
            zauzeto++;
        }
        if (polje[i][j + 1])
        {
            zauzeto++;
        }
        if (polje[i][j - 1])
        {
            zauzeto++;
        }
        if (polje[i + 1][j + 1])
        {
            zauzeto++;
        }
        if (polje[i + 1][j - 1])
        {
            zauzeto++;
        }
        if (polje[i - 1][j + 1])
        {
            zauzeto++;
        }
        if (polje[i - 1][j - 1])
        {
            zauzeto++;
        }
        if (i == 1 || i == 6)
        {
            if (j == 1 || j == 6)
            {
                limit = 3;
            }
            else
            {
                limit = 5;
            }
        }
        else
        {
            if (j == 1 || j == 6)
            {
                limit = 5;
            }
        }
        if (zauzeto < limit)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
}

int upisPolja(int polje[8][8], const char kontekst[31], int prevR, int prevS)
{
    int tocanUpis = 0, stupac, redak;
    while (!tocanUpis)
    {
        char upis[3];
        printf("%s", kontekst);
        scanf("%s", upis);
        if (strlen(upis) == 2)
        {
            stupac = upis[1] - '0';
            char slovo = toupper(upis[0]);
            for (int i = 0; i < strlen(SLOVA); i++)
            {
                if (slovo == SLOVA[i])
                {
                    redak = i + 1;
                }
            }
            if (stupac && redak && stupac <= 6 && stupac >= 1 && jeLegalno(polje, redak, stupac, prevR, prevS))
            {
                tocanUpis = 1;
            }
            else
            {
                printf("Nije legalan potez.\n");
            }
        }
        else
        {
            if (upis[0] == '0')
            {
                return 100;
            }
            else
            {
                printf("Netočan upis.\n");
            }
        }
    }
    printf("\n");
    return redak * 10 + stupac;
}

void igra()
{
    int polje[8][8] = {0};
    int potez = 1, predaja = 0;

    while (1)
    {
        int legalniPotezi = 0;
        for (int i = 1; i < 7; i++)
        {
            for (int j = 1; j < 7; j++)
            {
                if (jeLegalno(polje, i, j, 0, 0))
                {
                    legalniPotezi++;
                }
            }
        }

        if (!legalniPotezi)
        {
            break;
        }

        ispis(polje);
        if (potez == 1)
        {
            printf("\nNa potezu: %sIgrač 1%s\n\n", BOJA1, DEF_BOJA);
        }
        else
        {
            printf("\nNa potezu: %sIgrač 2%s\n\n", BOJA2, DEF_BOJA);
        }

        int br = upisPolja(polje, "Upišite polje (postavljanje točkice): ", 0, 0);
        int redak = br / 10;
        int stupac = br - redak * 10;

        if (br < 100)
        {
            if (potez == 1)
            {
                polje[redak][stupac] = ID_TOCKA1;
            }
            else
            {
                polje[redak][stupac] = ID_TOCKA2;
            }
        }
        else
        {
            predaja = potez;
            break;
        }

        ispis(polje);
        printf("\n");

        br = upisPolja(polje, "Upišite polje (sijenčanje polja): ", redak, stupac);
        int redak2 = br / 10;
        int stupac2 = br - redak2 * 10;

        if (br < 100)
        {
            if (potez == 1)
            {
                polje[redak2][stupac2] = ID_SIJENA1;
            }
            else
            {
                polje[redak2][stupac2] = ID_SIJENA2;
            }
        }
        else
        {
            predaja = potez;
            break;
        }

        if (potez == 1)
        {
            potez = 2;
        }
        else
        {
            potez = 1;
        }
    }

    int veze1[8][8] = {0}, veze2[8][8] = {0}, bodovi1 = 0, bodovi2 = 0, t1 = 0, r1 = 1, t2 = 0, r2 = 1;
    for (int i = 1; i < 7; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            if (polje[i][j] == ID_TOCKA1)
            {
                int tPrije = t1;
                if (polje[i + 1][j] == ID_TOCKA1 && veze1[i + 1][j] == 0)
                {
                    veze1[i + 1][j] = r1;
                    t1++;
                }
                if (polje[i - 1][j] == ID_TOCKA1 && veze1[i - 1][j] == 0)
                {
                    veze1[i - 1][j] = r1;
                    t1++;
                }
                if (polje[i][j + 1] == ID_TOCKA1 && veze1[i][j + 1] == 0)
                {
                    veze1[i][j + 1] = r1;
                    t1++;
                }
                if (polje[i][j - 1] == ID_TOCKA1 && veze1[i][j - 1] == 0)
                {
                    veze1[i][j - 1] = r1;
                    t1++;
                }
                if (polje[i + 1][j + 1] == ID_TOCKA1 && veze1[i + 1][j + 1] == 0)
                {
                    veze1[i + 1][j + 1] = r1;
                    t1++;
                }
                if (polje[i + 1][j - 1] == ID_TOCKA1 && veze1[i + 1][j - 1] == 0)
                {
                    veze1[i + 1][j - 1] = r1;
                    t1++;
                }
                if (polje[i - 1][j + 1] == ID_TOCKA1 && veze1[i - 1][j + 1] == 0)
                {
                    veze1[i - 1][j + 1] = r1;
                    t1++;
                }
                if (polje[i - 1][j - 1] == ID_TOCKA1 && veze1[i - 1][j - 1] == 0)
                {
                    veze1[i - 1][j - 1] = r1;
                    t1++;
                }
                if (t1 == tPrije)
                {
                    t1 = 0;
                    r1++;
                }
            }
            else if (polje[i][j] == ID_TOCKA2)
            {
                int tPrije = t2;
                if (polje[i + 1][j] == ID_TOCKA2 && veze2[i + 1][j] == 0)
                {
                    veze2[i + 1][j] = r2;
                    t2++;
                }
                if (polje[i - 1][j] == ID_TOCKA2 && veze2[i - 1][j] == 0)
                {
                    veze2[i - 1][j] = r2;
                    t2++;
                }
                if (polje[i][j + 1] == ID_TOCKA2 && veze2[i][j + 1] == 0)
                {
                    veze2[i][j + 1] = r2;
                    t2++;
                }
                if (polje[i][j - 1] == ID_TOCKA2 && veze2[i][j - 1] == 0)
                {
                    veze2[i][j - 1] = r2;
                    t2++;
                }
                if (polje[i + 1][j + 1] == ID_TOCKA2 && veze2[i + 1][j + 1] == 0)
                {
                    veze2[i + 1][j + 1] = r2;
                    t2++;
                }
                if (polje[i + 1][j - 1] == ID_TOCKA2 && veze2[i + 1][j - 1] == 0)
                {
                    veze2[i + 1][j - 1] = r2;
                    t2++;
                }
                if (polje[i - 1][j + 1] == ID_TOCKA2 && veze2[i - 1][j + 1] == 0)
                {
                    veze2[i - 1][j + 1] = r2;
                    t2++;
                }
                if (polje[i - 1][j - 1] == ID_TOCKA2 && veze2[i - 1][j - 1] == 0)
                {
                    veze2[i - 1][j - 1] = r2;
                    t2++;
                }
                if (t2 == tPrije)
                {
                    t2 = 0;
                    r2++;
                }
            }
        }
    }
    for (int x = 1; x <= 2; x++)
    {
        for (int i = 1; i < 7; i++)
        {
            for (int j = 1; j < 7; j++)
            {
                if (polje[i][j] == ID_TOCKA1)
                {
                    if (polje[i + 1][j] == ID_TOCKA1 && veze1[i + 1][j] != veze1[i][j])
                    {
                        veze1[i + 1][j] = veze1[i][j];
                    }
                    if (polje[i - 1][j] == ID_TOCKA1 && veze1[i - 1][j] != veze1[i][j])
                    {
                        veze1[i - 1][j] = veze1[i][j];
                    }
                    if (polje[i][j + 1] == ID_TOCKA1 && veze1[i][j + 1] != veze1[i][j])
                    {
                        veze1[i][j + 1] = veze1[i][j];
                    }
                    if (polje[i][j - 1] == ID_TOCKA1 && veze1[i][j - 1] != veze1[i][j])
                    {
                        veze1[i][j - 1] = veze1[i][j];
                    }
                    if (polje[i + 1][j + 1] == ID_TOCKA1 && veze1[i + 1][j + 1] != veze1[i][j])
                    {
                        veze1[i + 1][j + 1] = veze1[i][j];
                    }
                    if (polje[i + 1][j - 1] == ID_TOCKA1 && veze1[i + 1][j - 1] != veze1[i][j])
                    {
                        veze1[i + 1][j - 1] = veze1[i][j];
                    }
                    if (polje[i - 1][j + 1] == ID_TOCKA1 && veze1[i - 1][j + 1] != veze1[i][j])
                    {
                        veze1[i - 1][j + 1] = veze1[i][j];
                    }
                    if (polje[i - 1][j - 1] == ID_TOCKA1 && veze1[i - 1][j - 1] != veze1[i][j])
                    {
                        veze1[i - 1][j - 1] = veze1[i][j];
                    }
                }
                else if (polje[i][j] == ID_TOCKA2)
                {
                    if (polje[i + 1][j] == ID_TOCKA2 && veze2[i + 1][j] != veze2[i][j])
                    {
                        veze2[i + 1][j] = veze2[i][j];
                    }
                    if (polje[i - 1][j] == ID_TOCKA2 && veze2[i - 1][j] != veze2[i][j])
                    {
                        veze2[i - 1][j] = veze2[i][j];
                    }
                    if (polje[i][j + 1] == ID_TOCKA2 && veze2[i][j + 1] != veze2[i][j])
                    {
                        veze2[i][j + 1] = veze2[i][j];
                    }
                    if (polje[i][j - 1] == ID_TOCKA2 && veze2[i][j - 1] != veze2[i][j])
                    {
                        veze2[i][j - 1] = veze2[i][j];
                    }
                    if (polje[i + 1][j + 1] == ID_TOCKA2 && veze2[i + 1][j + 1] != veze2[i][j])
                    {
                        veze2[i + 1][j + 1] = veze2[i][j];
                    }
                    if (polje[i + 1][j - 1] == ID_TOCKA2 && veze2[i + 1][j - 1] != veze2[i][j])
                    {
                        veze2[i + 1][j - 1] = veze2[i][j];
                    }
                    if (polje[i - 1][j + 1] == ID_TOCKA2 && veze2[i - 1][j + 1] != veze2[i][j])
                    {
                        veze2[i - 1][j + 1] = veze2[i][j];
                    }
                    if (polje[i - 1][j - 1] == ID_TOCKA2 && veze2[i - 1][j - 1] != veze2[i][j])
                    {
                        veze2[i - 1][j - 1] = veze2[i][j];
                    }
                }
            }
        }
    }
    for (int r = 1; r <= fmax(r1, r2); r++)
    {
        t1 = 0;
        t2 = 0;
        for (int i = 1; i < 7; i++)
        {
            for (int j = 1; j < 7; j++)
            {
                if (veze1[i][j] == r)
                {
                    t1++;
                }
                else if (veze2[i][j] == r)
                {
                    t2++;
                }
            }
        }
        if (t1 > bodovi1)
        {
            bodovi1 = t1;
        }
        if (t2 > bodovi2)
        {
            bodovi2 = t2;
        }
    }
    if (!predaja)
    {
        printf("X: %s%d%s\nY: %s%d%s\n\n", BOJA1, bodovi1, DEF_BOJA, BOJA2, bodovi2, DEF_BOJA);
        if (bodovi1 > bodovi2)
        {
            printf("Pobjednik/ca: %sIgrač 1%s\n", BOJA1, DEF_BOJA);
        }
        else if (bodovi2 > bodovi1)
        {
            printf("Pobjednik/ca: %sIgrač 2%s\n", BOJA2, DEF_BOJA);
        }
        else
        {
            printf("Izjednačeno!\n");
        }
    }
    else
    {
        if (predaja == 2)
        {
            printf("Pobjednik/ca: %sIgrač 1%s\n", BOJA1, DEF_BOJA);
        }
        else
        {
            printf("Pobjednik/ca: %sIgrač 2%s\n", BOJA2, DEF_BOJA);
        }
    }
}

int main()
{
    int lastCmd;
    printf("Projektni rad - \"Točke i sijene\"\n");
    printf("Škola: Srednja Strukovna Škola, Samobor, Andrije Hebrenga 26\n");
    printf("Školska godina: 2024./2025.\n");
    printf("Radio: Adrian Horvat\n");
    printf("Razred: 1.G\n");
    while (1)
    {
        printf("\n");
        printf("Unesite radnju:\n0 - Izađi iz programa\n1 - Nova igra\n2 - Upute\n");
        scanf("%d", &lastCmd);
        printf("\n");
        if (lastCmd == 1)
        {
            printf("Nova igra:\n\n");
            igra();
            printf("\n");
        }
        else if (lastCmd == 2)
        {
            printf("Upute:\n\n");
            printf("Igra se odvija u 6x6 igračem polju.\nIgrači igraju naizmjenično.\n\n");
            printf("Jedan potez se sastoji od postavljanja točkice na bilo koje slobodno polje\n");
            printf("te zatim sijenčanje jednog susjednog slobodnog polja.\n\n");
            printf("Kada je vaš potez, kako biste unijeli vaše odabrano polje, u jedan red morate utipkati:\n");
            printf("-> 1.) Slovo (redak)\n");
            printf("-> 2.) Broj (stupac)\n");
            printf("Time ćete dobiti koordinate polja u kojem želite izvesti radnju! (primjer: A5)\n\n");
            printf("Slobodna polja su samo ona koja nemaju točkicu i nisu osijenčana.\n\n");
            printf("Vaše točkice se spajaju sa susjednim točkicama (koje su također vaše).\n");
            printf("Cilj igre je imati više spojenih točkica od vašeg protivnika.\n");
            printf("Ako se želite predati, dok ste na potezu upišite nulu.\n");
        }
        else if (lastCmd == 0)
        {
            printf("Izlaz...");
            break;
        }
        else
        {
            printf("Pogrešan unos, pokušajte ponovno.\n");
        }
    }
}