#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
/*
Autor: Petr Dosedel, xdosed07
Soubor: proj1.c
Datum: 8.11.2015*/


int cislo (char *retezec) // funkce rozezanvajici prvocislo
{
int i;
long cislo = strtol(retezec,NULL,10);

    if (cislo > INT_MAX)  // pokud je vetsi nez INT_MAX neprovadi se detekce na prvocislo
        {
        printf("number: %s\n",retezec);
        return 0;
        }
    if((cislo==1)|| (cislo==0))  // vyjimka u cisel 1 a 0
        {
        printf("number: %li\n", cislo);
        return 0;
        }
    else
        for(i=2;i<=cislo/2;i++) // cyklus ktery deli cislo az do jeho poloviny a hleda zbytky deleni
            {
            if((cislo%i)==0)
            {
            printf("number: %li\n", cislo);
            return 0;
            }
            }
printf("number: %li (prime)\n", cislo);
return 0;
}

int palindrom (char *retezec) // funkce urcujici zda neni slovo palindrom
{
int pocetpismen=0;
int zacatek;
int konec;

    while (retezec[pocetpismen]!='\0')   // porovnava psotupne pismenka od koncu az do sredu
      pocetpismen++;
      konec = pocetpismen-1;

    for( zacatek = 0 ; zacatek < konec  ; zacatek++ )
        {
        if ( retezec[zacatek] != retezec[konec] )
        {
        return 1;
        }
      konec--;
        }
   if(retezec[zacatek] == retezec[konec] )
    return 5;
return 0;
}

int datum(char *retezec) // funkce vypisuje den pripadajici urcitemu datu
{
char rok[11];
char den[11];
char mesic[11];

rok[0] = retezec[0]; // rozdeleni retezce na rok mesic a den
rok[1] = retezec[1];
rok[2] = retezec[2];
rok[3] = retezec[3];
den[0] = retezec[8];
den[1] = retezec[9];
mesic[0] = retezec[5];
mesic[1] = retezec[6];

int den2 = atoi(den);    // prevedeni na int
int mesic2 = atoi(mesic);
int rok2 = atoi(rok);

    if (((den2<32)&&(den2>0)) && ((mesic2<13)&&(mesic2>0))&&(rok2>0)) // kontrola zda neni den vetsi nez 31 nebo mesic vetsi nez 12
    {
    time_t rawtime;
    struct tm * informace;
    const char * weekday[] = { "Sun", "Mon",
                             "Tue", "Wed",
                             "Thu", "Fri", "Sat"};

    time ( &rawtime );                        // nacteni informaci
    informace = localtime ( &rawtime );
    informace->tm_year = rok2 - 1900;
    informace->tm_mon = mesic2 - 1;
    informace->tm_mday = den2;

    mktime ( informace );

    printf ("date: %s %s\n", weekday[informace->tm_wday],retezec); // tisknuti vysledneho datumu
    return 0;
    }
    else
        return palindrom(retezec); // pokud neni datum vola se funkce na palindrom
}


int rozrazeni (char *retezec) // funkce ktera rozhodne jestli se jedno o datum, slovo nebo datum
{
int i=0;

    if((retezec[4]== '-') && (retezec[7]== '-') && (retezec[10]=='\0') ) //detekce datumu
        {
            while(retezec[i]!='\0')// kontrola jestli datum neobsahuje jiny znak nez cislo nebo pomlcku
            {
                char b = retezec[i];

                if(((b<58) && (b > 47)) || (b==45))
                    {i++;}

                else
                    return palindrom(retezec);// pokud neni datum vola se funkce na palindrom
            }
            return datum(retezec); // pokud splnuje podmiky vola se funkce datum
                i=0;
        }


    while (retezec[i] !='\0') // detekc netisknutelnych znaku
        {
        char zadani = retezec[i];

            if(zadani < 32)
            return 7;
            else
                i++;
        }
        i=0;

    while ( retezec[i] !='\0') // rozdeleni na slovo a cislo
        {
        char zadani = retezec[i];

        if(zadani > 47 && zadani< 58)
            {
            i++;
            }
        else
            {
            return palindrom(retezec);// pokud je slovo jde do funkce palindrom
            }
        }
return cislo(retezec); // pokud splnuje podmiky jde do funkce cislo
}







int main(int argc, char *argv[])
{
    if (argv[1] != NULL)// pokud se zada argument vypise informace o programu
    {
        printf("Program slouzi k spracovani textu. Rozpozna datum, cislo, prvocislo, slovo, palindrom.\n");
        return 0;
    }

    char zadani[101];
    (void)argc;

    while(scanf("%100s", zadani) == 1) // nacitani dat ze vstupu dokut tam nejake jsou
    {
        switch(rozrazeni(zadani)) // volani funkce na zakladni rozdeleni
            {
            case 1:
                printf("word: %s \n", zadani);
                break;
            case 2:
                printf("number: %s\n", zadani);
                break;
            case 3:
                printf("number: %s (prime)\n ", zadani);
                break;
            case 4:
                printf("%s\n",zadani);
                break;
            case 5:
                printf("word: %s (palindrome)\n", zadani);
                break;
            case 6:
                printf("date: %s\n", zadani);
                break;
            case 7:
                printf("Chybny vstup\n");
                return  EXIT_FAILURE;
            default:
                {}
}
}
}
