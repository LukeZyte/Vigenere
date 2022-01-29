#include "Logika.h"

#include <iostream>
#include <string>
#include <fstream>
#include <cctype> // tolower()

using namespace std;

// Wyswietla instrukcje poprawnego uzycia programu
void komunikatBledu()
{
	system("cls");
	cout << "\t Zle wywolano program!" << endl;
	cout << "Wprowadz komende w nastepujacy sposob:" << endl;
	cout << "nazwa_programu -i plik wejsciowy -o plik wyjsciowy" << endl;
	cout << "\t lub" << endl;
	cout << "nazwa_programu -o plik wyjsciowy -i plik wejsciowy" << endl;
	exit(0);
}

// Zwraca wartosc wyboru do wykonania
int pobierzWybor()
{
	int wybor = 0; // cyfra wybrana przez uzytkownika odpowiadajaca danej czynnosci
	system("cls");
	while (wybor == 0)
	{
		cout << "\t [ 1 ] Szyfrowanie" << endl;
		cout << "\t [ 2 ] Deszyfrowanie" << endl;
		cout << "Wybierz czynnosc do wykonania: ";
		cin >> wybor;
		if (wybor == 1 or wybor == 2)
		{
			return wybor;
		}
		else
		{
			wybor = 0;
			return wybor;
		}
	}
	cout << endl;
}

// Sprawdza czy podany znak nalezy do sekwencji lub jest spacja
bool poprawnyZnak(char znak)
{
	string sekwencja = "abcdefghijklmnopqrstuvwxyz0123456789"; // Ciag wszystkich mozliwych poprawnych znakow bez spacji
	for (int i = 0; i < sekwencja.length(); i++)
	{
		if (znak == sekwencja[i] or znak == ' ')
		{
			return true;
		}
	}
	return false;
}

// Zwraca zawartosc pliku wejsciowego jako string bez blednych znakow - zlicza ile ich bylo edytujac zmienne "ileBledne", "bledne"
string pobierzCiagZnakow(string plik, int &iloscBlednychZnakow, string &bledne)
{
	fstream odczyt(plik);	// wczytanie pliku wejsciowego
	string ciagZnakow = ""; // Zawartosc pliku wejsciowego
	string wiersz;			// rozpatrywany wiersz pliku wejsciowego

	if (odczyt)
	{
		while (!odczyt.eof())
		{
			getline(odczyt, wiersz);
			ciagZnakow += wiersz;
			if (!odczyt.eof())
			{
				ciagZnakow += ' '; // Spacja zamiast zalamanego wiersza
			}
		}
	}
	else
	{
		cout << "NIE ZNALEZIONO PLIKU!" << endl;
		exit(0);
	}

	// Zamiana ciagu o roznych wielkosciach znaku na same male litery, pomijanie niepoprawnych i ich zliczanie
	string malyCiagZnakow = ""; // ciagZnakow o samych malych znakach

	for (int i = 0; i < ciagZnakow.length(); i++)
	{
		if (poprawnyZnak(tolower(ciagZnakow[i])))
		{
			malyCiagZnakow += tolower(ciagZnakow[i]);
		}
		else
		{
			iloscBlednychZnakow += 1;
			bledne += ciagZnakow[i];
		}
	}
	odczyt.close();
	return malyCiagZnakow;
}

void blednyKlucz()
{
	cout << "Wprowadzony klucz posiada nielegalne znaki!" << endl;
	cout << "Wprowadz klucz korzystajac z [a-z], [A-Z], [0-9]" << endl;
	exit(0);
}

// Zwraca klucz o dlugosci ciaguZnakow, bez spacji, jako string
string pobierzKlucz(int dlugosc)
{
	string klucz; // zmienna przechowujaca wprowadzony przez uzytkownika klucz
	string kluczZeSpacja;
	cout << "Wprowadz klucz: ";
	cin >> klucz;									 // pobieranie ciagu znakow przed pierwsza spacja
	getline(cin, kluczZeSpacja);					 // pobieranie klucza reszty klucza gdy pojawila sie spacja
	for (int i = 0; i < kluczZeSpacja.length(); i++) // usuwanie spacji
	{
		if (kluczZeSpacja[i] != ' ')
			klucz += kluczZeSpacja[i]; // polaczenie zmiennych klucz i kluczZeSpacja
	}

	int dlugoscKlucza = klucz.length();
	int index = 0;			// indeks znaku klucza
	string dlugiKlucz = ""; // zmienna przechowywujaca klucz o dlugosci ciagu znakow pliku wejsciowego
	for (int i = 0; i < dlugosc; i++)
	{
		if (i % dlugoscKlucza == 0)
		{
			index = 0; // wartosc indeksu klucza, ktory jest mniejszy od dlugiegoKlucza
		}
		klucz[index] = tolower(klucz[index]); // zamieniam kazdy znak klucza na male litery
		if (poprawnyZnak(klucz[index]))
		{
			dlugiKlucz += klucz[index];
			index++;
		}
		else
		{
			blednyKlucz();
		}
	}
	return dlugiKlucz;
}

// Szyfruje ciagZnakow i zwraca zaszyfrowana tekst
string szyfrowanie(string ciagZnakow, string klucz)
{
	string sekwencja = "abcdefghijklmnopqrstuvwxyz0123456789"; // kolejne znaki szyfru
	string szyfrZnakow = "";								   // zaszyfrowany ciag znakow
	char szyfrZnak = '@';									   // zaszyfrowany znak ciagu znakow
	int wartoscZnakuKlucza;									   // wartosc znaku klucza w sekwencji, np. 'a' = 0, 'c' = 2, '2' = 28
	int wartoscZnaku = -100;								   // wartosc znaku ciaguZnakow w sekwencji
	int wartoscSzyfrZnak;									   // wartosc szyfrZnak w sekwencji

	for (int i = 0; i < ciagZnakow.length(); i++)
	{
		for (int j = 0; j < sekwencja.length(); j++)
		{
			if (klucz[i] == sekwencja[j])
				wartoscZnakuKlucza = j;

			if (ciagZnakow[i] == sekwencja[j])
				wartoscZnaku = j;
			else if (ciagZnakow[i] == ' ')
				wartoscZnaku = -1; // jest spacja
		}

		if (wartoscZnaku != -1)
			wartoscSzyfrZnak = wartoscZnaku + wartoscZnakuKlucza;
		else if (wartoscZnaku == -1)
			wartoscSzyfrZnak = -1;

		if (wartoscSzyfrZnak > 35) // operacja wymagana zeby po np. '9' przypisywac 'a'
			wartoscSzyfrZnak = wartoscSzyfrZnak - 36;

		for (int j = 0; j < sekwencja.length(); j++) // przypisanie kazdej wartosci odpowiadajacy jej znak z sekwencji
		{
			if (wartoscSzyfrZnak == j)
				szyfrZnak = sekwencja[j];
			else if (wartoscSzyfrZnak == -1)
				szyfrZnak = ' ';
		}
		szyfrZnakow += szyfrZnak;
	}
	return szyfrZnakow;
}

// Deszyfruje podany ciagZnakow i zwraca zdeszyfrowany tekst
string deszyfrowanie(string ciagZnakow, string klucz)
{
	string sekwencja = "abcdefghijklmnopqrstuvwxyz0123456789"; // kolejne znaki szyfru
	string szyfrZnakow = "";								   // zaszyfrowany ciag znakow
	char szyfrZnak = '@';									   // zaszyfrowany znak ciagu znakow
	int wartoscZnakuKlucza;									   // wartosc znaku klucza w sekwencji, np. 'a' = 0, 'c' = 2, '2' = 28
	int wartoscZnaku = -100;								   // wartosc znaku ciaguZnakow w sekwencji
	int wartoscSzyfrZnak;									   // wartosc szyfrZnak w sekwencji

	for (int i = 0; i < ciagZnakow.length(); i++)
	{
		for (int j = 0; j < sekwencja.length(); j++)
		{
			if (klucz[i] == sekwencja[j])
				wartoscZnakuKlucza = j;
			if (ciagZnakow[i] == sekwencja[j])
				wartoscZnaku = j;
			else if (ciagZnakow[i] == ' ')
				wartoscZnaku = 37; // jest spacja
		}

		if (wartoscZnaku != 37)
			wartoscSzyfrZnak = wartoscZnaku - wartoscZnakuKlucza;
		else if (wartoscZnaku == 37)
			wartoscSzyfrZnak = 37;

		if (wartoscSzyfrZnak < 0) // operacja wymagana zeby po np. '9' przypisywac 'a'
			wartoscSzyfrZnak = wartoscSzyfrZnak + 36;

		for (int j = 0; j < sekwencja.length(); j++) // przypisanie kazdej wartosci odpowiadajacy jej znak z sekwencji
		{
			if (wartoscSzyfrZnak == j)
				szyfrZnak = sekwencja[j];
			else if (wartoscSzyfrZnak == 37)
				szyfrZnak = ' ';
		}
		szyfrZnakow += szyfrZnak;
	}
	return szyfrZnakow;
}

// Zapisuje podany tekst do podanego pliku
void zapisDoPliku(string tekst, string plik)
{
	ofstream zapis(plik);
	zapis << tekst;
	zapis.close();
}

// Wypisuje ile blednych znakow zawieral plik wejsciowy oraz podaje jakie to znaki
void komunikatKoncowy(int ilosc, string bledne)
{
	char *bledneZnaki = new char[ilosc]; // dynamiczna tablica zawierajaca bledne znaki

	for (int i = 0; i < ilosc; i++)
	{
		bledneZnaki[i] = bledne[i];
	}

	if (ilosc)
	{
		cout << endl;
		cout << "\t \t UWAGA!" << endl;
		cout << "W pliku zrodlowym wystapila nastepujaca ilosc blednych znakow: " << ilosc << endl;
		cout << "Bledne znaki to: ";
		for (int i = 0; i < ilosc; i++)
		{
			cout << bledneZnaki[i] << ", ";
		}
		cout << endl;
	}
}
