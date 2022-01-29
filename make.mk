a.out:Szyfr_Vigenera.o Logika.o
		g++ Szyfr_Vigenera.o Logika.o
Szyfr_Vigenera.o:Szyfr_Vigenera.cpp
		g++ -c Szyfr_Vigenera.cpp
Logika.o:Logika.cpp
		g++ -c Logika.cpp