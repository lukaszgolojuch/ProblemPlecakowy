/*
 Jezyk programowania: C/C++
 Środowisko programistyczne: Visual Studio
 Algorytm: Rozbudowany Problem Plecakowy
 Opis: w pliku readme
 Autor: Lukasz Golojuch
 */

#include<stdio.h>

// deklaracja zmiennych globalnych
int ladownosc; // przechowuje maksymalna ladownosc danej ciezarowki
int n;
int ilosc_aut; // przechowuje ilosc aut - ilosc testow do wykonania
int przychod; // przechowuje przychod podczas obliczen, a na koncu maksymalny przychod jaki jestesmy w stanie wygenerowac

/*
 Funkcja void knapSack():
 
 Funkcja zawierajaca algorytm dla problemu plecakowego, obejmujaca rozszerzenia i wyjatki dzialanie programu opisane w pliku readme.
 
 Funkcja wypisuje na ekranie wartosc '0' jesli transport jest dla nas nieoplacalny, lub maksymalny mozliwy przychod jesli jest on wiekszy od 0.
*/
void knapSack(int* wartosci, int* wagi)
{
    int w,i,j;
    
    int** K = new int*[n+1];
    for(i = 0; i <= n; ++i)
    {
        K[i] = new int[ladownosc+1];
        for (j = 0; j <=ladownosc ; ++j)
        {
            K[i][j]=0;
        }
    }
    
    for (i = 1; i <= n; i++)
    {
        for (w = 1; w <= ladownosc; w++)
        {
            //if - sprawdzamy czy nastepny produkt zmieści się do samochodu
            if (wagi[i-1] <= w){
                //sprawdzamy czy opłaca nam sie wrzucic kolejna rzecz do samochodu jesli tak to ja wrzucamy, jesli nie to przenosimy wartość poprzedniej
                //komorki w tablicy K i zapisujemy ja na kolejnym polu
                K[i][w] = (wartosci[i-1] + K[i-1][w-wagi[i-1]] > K[i-1][w]) ? wartosci[i-1] + K[i-1][w-wagi[i-1]] : K[i-1][w];
            }
            else{
                //jeśli sie nie mieści to zapisujemy wartość z poprzedniej tabeli
                K[i][w] = K[i-1][w];
            }
        }
    }
    //przychod z automatu pomniejszamy o 20
    przychod = K[n][ladownosc] - 20;
    
    if(przychod>0)
    {
        // jesli przychod >0 wypisujemy makszymalny przychod
        printf ("%d \n", przychod);
    }
    else
    {
        // jesli przychod jest mniejszy lub rowny 0 zwracamy 0, co oznacza ze taki transport jest dla nas nieoplacalny
        printf("%d \n", 0);
    }
    
    for(i = 0; i <= n; ++i )
    {
        delete [] K[ i ];
    }
    
    delete [] K;
    
}

int main()
{
    int i, j; // zmienne pomocnicze
    
    // pobieramy ilosc aut - ilosc prob ktore bedzie trzeba wykonac
    scanf ("%d",&ilosc_aut);
    
    for(i=0; i<ilosc_aut; i++)
    {
        scanf ("%d",&n);
        
        int* wartosci = new int [n];
        int* wagi = new int [n];
        
        for(j=0; j<n; j++)
        {
            // pobieramy wartosci kolejnych przesylek do zaladowania
            scanf ("%d",&wartosci[j]);
        }
        for(j=0; j<n; j++)
        {
            //pobieramy wagi poszczegolnych przesylek do zaladowania
            scanf ("%d",&wagi[j]);
        }
        for(j=0; j<n; j++)
        {
            if(wagi[j]>100)
            {
                //pomniejszamy wartosc przesylki o 5 jesli jej waga jest wieksza niz 100
                wartosci[j]=wartosci[j]-5;
            }
        }
        // pobieramy maksymalna ladownosc pojazdu
        scanf ("%d",&ladownosc);
        
        // uruchamiamy glowna funkcje programu
        knapSack(wartosci, wagi);
        
        // zwalanianie pamieci - usuwanie tablic dynamicznych
        delete [] wartosci;
        delete [] wagi;
    }
    return 0;
}
