#pragma once
#include <string>

using namespace std;

/*! Wyswietla instrukcje poprawnego uzycia programu. */
void komunikatBledu();

/*! Wyswietla komunikat dotyczacy niepoprawnosci wprowadzonego klucza */
void blednyKlucz();

/*! Zwraca wartosc wyboru do wykonania */
int pobierzWybor();

/** Sprawdza czy podany znak nalezy do sekwencji lub jest spacja.
* \param znak Sprawdzany znak.
* \return True jesli znak jest poprawny, False jesli bledny.
*/
bool poprawnyZnak(char znak);

/** Wczytuje zawartosc podanego pliku i ja filtruje z blednych znakow.
* \param ileBlednychZnakow Ilosc blednych znakow.
* \param bledne ciag blednych znakow jako string.
* \return Zawartosc pliku wejsciowego jako string bez blednych znakow.
*/
string pobierzCiagZnakow(string plik, int& iloscBlednychZnakow, string&bledne);

/** Prosi uzytkownika o wczytanie klucza, ktorego eliminuje z ewentualnych spacji
* \param dlugosc Liczba znakow zmiennej "ciagZnakow".
* \return Klucz jako string o dlugosci zmiennej "dlugosc" eliminujac spacje.
*/
string pobierzKlucz(int dlugosc);

/** Szyfruje wprowadzony tekst
* \param ciagZnakow Tekst do zaszyfrowania
* \param klucz ciag znakow, sluzacy jako klucz w szyfrowaniu
* \return Zaszyfrowany tekst wejsciowy
*/
string szyfrowanie(string ciagZnakow, string klucz);

/** Deszyfruje wprowadzony tekst
* \param ciagZnakow Tekst do zdeszyfrowania
* \param klucz ciag znakow, sluzacy jako klucz w deszyfrowaniu
* \return Zdeszyfrowany tekst wejsciowy
*/
string deszyfrowanie(string ciagZnakow, string klucz);

/** Zapisuje podany tekst do podanego pliku.
* \param tekst Zawartosc wpisywana do pliku
* \param plik Nazwa pliku do ktorego ma zostac zapisany tekst
*/
void zapisDoPliku(string tekst, string plik);

/** Wypisuje ile blednych znakow zawieral plik wejsciowy oraz podaje jakie to znaki.
* \param ilosc Liczba blednych znakow
* \param bledne ciag blednych znakow
*/
void komunikatKoncowy(int ilosc, string bledne);
