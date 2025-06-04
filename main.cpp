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
                    printf("%s●%s", BOJA1, DEF_BOJA);
                    break;
                case ID_SIJENA1:
                    printf("%s|%s", BOJA1, DEF_BOJA);
                    break;
                case ID_SIJENA2:
                    printf("%s|%s", BOJA2, DEF_BOJA);
                    break;
                case ID_TOCKA2:
                    printf("%s●%s", BOJA2, DEF_BOJA);
                    break;
                default:
                    printf("%s○", DEF_BOJA);
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

int zbrojiBodove(int polje[8][8], int provjera)
{
    int max = 0, posijeceno[8][8] = {0};
    for (int i = 1; i < 7; i++)
    {
        for (int j = 1; j < 7; j++)
        {
            if (polje[i][j] == provjera)
            {
                int slijedeceX[64] = {};
                int slijedeceY[64] = {};
                slijedeceX[0] = i;
                slijedeceY[0] = j;
                int brSlijedecih = 1;
                int brPovezanih = 0;
                while (brSlijedecih)
                {
                    int x = slijedeceX[brSlijedecih - 1], y = slijedeceY[brSlijedecih - 1];
                    brSlijedecih--;
                    if (posijeceno[x][y] || x < 0 || x > 7 || y < 0 || y > 7)
                    {
                        continue;
                    }
                    posijeceno[x][y] = 1;
                    if (polje[x][y] == provjera)
                    {
                        brPovezanih++;
                        slijedeceX[brSlijedecih] = x + 1;
                        slijedeceY[brSlijedecih] = y;
                        brSlijedecih++;
                        slijedeceX[brSlijedecih] = x - 1;
                        slijedeceY[brSlijedecih] = y;
                        brSlijedecih++;
                        slijedeceX[brSlijedecih] = x;
                        slijedeceY[brSlijedecih] = y + 1;
                        brSlijedecih++;
                        slijedeceX[brSlijedecih] = x;
                        slijedeceY[brSlijedecih] = y - 1;
                        brSlijedecih++;
                        slijedeceX[brSlijedecih] = x + 1;
                        slijedeceY[brSlijedecih] = y + 1;
                        brSlijedecih++;
                        slijedeceX[brSlijedecih] = x - 1;
                        slijedeceY[brSlijedecih] = y + 1;
                        brSlijedecih++;
                        slijedeceX[brSlijedecih] = x + 1;
                        slijedeceY[brSlijedecih] = y - 1;
                        brSlijedecih++;
                        slijedeceX[brSlijedecih] = x - 1;
                        slijedeceY[brSlijedecih] = y - 1;
                        brSlijedecih++;
                    }
                }
                if (brPovezanih > max)
                {
                    max = brPovezanih;
                }
            }
        }
    }
    return max;
}

void igra(char ime1[69], char ime2[69])
{
    int polje[8][8] = {0};
    int potez = 1, predaja = 0, bodovi1 = 0, bodovi2 = 0;

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
            printf("\nNa potezu: %s%s%s\n\n", BOJA1, ime1, DEF_BOJA);
        }
        else
        {
            printf("\nNa potezu: %s%s%s\n\n", BOJA2, ime2, DEF_BOJA);
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
        }

        bodovi1 = zbrojiBodove(polje, ID_TOCKA1);
        bodovi2 = zbrojiBodove(polje, ID_TOCKA2);

        printf("%s: %s%d%s\n%s: %s%d%s\n\n", ime1, BOJA1, bodovi1, DEF_BOJA, ime2, BOJA2, bodovi2, DEF_BOJA);

        if (predaja)
        {
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

    if (!predaja)
    {
        ispis(polje);
        if (bodovi1 > bodovi2)
        {
            printf("Pobjednik/ca: %s%s%s\n", BOJA1, ime1, DEF_BOJA);
        }
        else if (bodovi2 > bodovi1)
        {
            printf("Pobjednik/ca: %s%s%s\n", BOJA2, ime2, DEF_BOJA);
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
            printf("Pobjednik/ca: %s%s%s\n", BOJA1, ime1, DEF_BOJA);
        }
        else
        {
            printf("Pobjednik/ca: %s%s%s\n", BOJA2, ime2, DEF_BOJA);
        }
    }
}

int main()
{
    int lastCmd;
    char ime1[69] = "Igrač 1", ime2[69] = "Igrač 2";
    printf("Projektni rad - \"Sakupljivač\"\n");
    printf("Škola: Srednja Strukovna Škola, Samobor, Andrije Hebrenga 26\n");
    printf("Školska godina: 2024./2025.\n");
    printf("Autor: Adrian Horvat\n");
    printf("Razred: 1.G\n");
    while (1)
    {
        printf("\n");
        printf("Unesite radnju:\n0 - Izađi iz programa\n1 - Nova igra\n2 - Upute\n3 - Postavke\n");
        scanf("%d", &lastCmd);
        printf("\n");
        if (lastCmd == 1)
        {
            printf("Nova igra:\n\n");
            igra(ime1, ime2);
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
        else if (lastCmd == 3)
        {
            printf("Postavke:\n\n");
            printf("Ime 1. igrača: %s%s%s\n", BOJA1, ime1, DEF_BOJA);
            printf("Ime 2. igrača: %s%s%s\n\n", BOJA2, ime2, DEF_BOJA);
            printf("Naredbe:\n0 - Izlaz iz postavka\n1 - Promijeni ime 1. igrača\n2 - Promijeni ime 2. igrača\n\n");
            int cmd = 3;
            while (cmd != 0 && cmd != 1 && cmd != 2)
            {
                printf("Upišite naredbu: ");
                scanf("%d", &cmd);
            }
            printf("\n");
            if (cmd == 1)
            {
                printf("Promijena 1. imena: ");
                getchar();
                fgets(ime1, 68, stdin);
                for (int i = 0; i < strlen(ime1); i++)
                {
                    if (ime1[i] == '\n')
                    {
                        ime1[i] = '\0';
                    }
                }
                printf("\nIme 1. igrača: %s%s%s\n", BOJA1, ime1, DEF_BOJA);
            }
            else if (cmd == 2)
            {
                printf("Promijena 2. imena: ");
                getchar();
                fgets(ime2, 68, stdin);
                for (int i = 0; i < strlen(ime2); i++)
                {
                    if (ime2[i] == '\n')
                    {
                        ime2[i] = '\0';
                    }
                }
                printf("\nIme 2. igrača: %s%s%s\n", BOJA2, ime2, DEF_BOJA);
            }
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