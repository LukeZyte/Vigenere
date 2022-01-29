// Lukasz Jarzab, INF, (AEI), stacjonarne, Gliwice 2021 - grupa 4

#include "Logika.h"

#include <iostream>
#include <string>

using namespace std;
/** Funkcja glowna
* \param argc ilosc parametrow podanych podczas wywolania funkcji.
* \param argv[] wartosci podanych parametrow
*/
int main(int argc, char *argv[])
{
    string nazwaPliku;   // nazwa pliku wejsciowego
    string plikWynikowy; // nazwa pliku wyjsciowego
    string arg;          // zmienna przechowujaca rozpatrywany argument

    if (argc != 5)
    {
        komunikatBledu();
        return 0;
    }
    for (int i = 1; i < argc; i += 2)
    {
        arg = argv[i];
        if (arg == "-i")
        {
            nazwaPliku = argv[i + 1];
        }
        else if (arg == "-o")
        {
            plikWynikowy = argv[i + 1];
        }
        else
        {
            komunikatBledu();
            return 0;
        }
    }

    int wybor;              // cyfra wybranej czynnosci
    int ileBlednych = 0;    // ilosc blednych znakow w pliku wejsciowym
    string bledne = "";     // zawiera wszystkie bledne znaki
    wybor = pobierzWybor(); // 1 szyfrowanie, 2 deszyfrowanie

    string ciagZnakow = pobierzCiagZnakow(nazwaPliku, ileBlednych, bledne); // zawartosc pliku wejsciowego bez blednych znakow

    string klucz = pobierzKlucz(ciagZnakow.length()); // klucz
    string wynik;                                     // zaszyfrowany lub zdeszyfrowany ciag znakow

    if (wybor == 1)
    {
        wynik = szyfrowanie(ciagZnakow, klucz);
    }
    else
    {
        wynik = deszyfrowanie(ciagZnakow, klucz);
    }

    komunikatKoncowy(ileBlednych, bledne);

    zapisDoPliku(wynik, plikWynikowy);
}
