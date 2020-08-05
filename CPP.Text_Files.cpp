//POP 2018-01-19 projekt 2 Górska Aleksandra IBM 2 171816 (środowisko programistyczne: Codeblocks 16.01; kompilator: GNU GCC Complier)
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

void odczyt(fstream &plik_odczyt) //sprawdzenie obecnosci pliku
{
    if(plik_odczyt.good() == false){
        cout << "Jeden (lub wiecej) z potrzebnych plikow nie zostal otwarty" << endl;
        exit(0);
    }
}

void poczatek (fstream &plik_odczyt, int &licznik) //powrot na poczatek pliku
{
    licznik = 1; //"zerowanie" licznika
    plik_odczyt.clear();
	plik_odczyt.seekg(0, ios::beg);
}

void plik_version(fstream &plik_zapis)
{
    fstream plik_odczyt;
    string tekst1, tekst2, tekst3;
    plik_odczyt.open ("version.txt", ios::in); //otwarcie do odczytu pliku version.txt
    odczyt(plik_odczyt);

    plik_odczyt.seekg(14) >> tekst1; //pobranie danych
    plik_zapis << "Wersja jadra systemu Linux: " << tekst1 << endl; // zapisanie danych
    plik_odczyt.seekg(65) >> tekst1 >> tekst2 >> tekst3;
    plik_zapis << "Wersja kompilatora gcc: " << tekst1 << " " << tekst2 << " " << tekst3 << endl;
    plik_odczyt.close(); //zamkniecie pliku
}

void plik_cpuinfo(fstream &plik_zapis)
{
    fstream plik_odczyt;
    string linia, szukane1, szukane2, dwukropek, tekst1, tekst2, tekst3, tekst4, tekst5, tekst6;
    int liczba_procesorow = 0, licznik = 1, liczba;
    plik_odczyt.open ("cpuinfo.txt", ios::in);
    odczyt(plik_odczyt);

    while(!plik_odczyt.eof())
    {
        plik_odczyt >> szukane1;
        if(szukane1 == "processor")
        liczba_procesorow++; //zliczanie ilosci procesorow
    }
    plik_zapis << "Liczba procesorow: " << liczba_procesorow << endl;
    poczatek(plik_odczyt, licznik);

    while(!plik_odczyt.eof())
    {
        getline(plik_odczyt, linia); //szukanie od poczatku linijek
        plik_odczyt >> szukane1 >> szukane2 >> dwukropek;
        if(szukane1 == "model" && szukane2 == "name"){
            plik_odczyt >> tekst1 >> tekst2 >> tekst3 >> tekst4 >> tekst5 >> tekst6;
            plik_zapis << "Nazwa procesora " << licznik << dwukropek << " " << tekst1 << " "
            << tekst2 << " " << tekst3 << " " << tekst4 << " " << tekst5 << " " << tekst6 << endl;
            licznik++;
        }
    }
    poczatek(plik_odczyt, licznik);

    while(!plik_odczyt.eof())
    {
        getline(plik_odczyt, linia);
        plik_odczyt >> szukane1 >> szukane2 >> dwukropek;
        if(szukane1 == "cpu" && szukane2 == "MHz"){
            plik_odczyt >> liczba;
            plik_zapis << "Szybkosc taktowania procesora " << licznik << dwukropek << " " << liczba << " " << szukane2 << endl;
            licznik++;
        }
    }
    poczatek(plik_odczyt, licznik);

    while(!plik_odczyt.eof())
    {
        getline(plik_odczyt, linia);
        plik_odczyt >> szukane1 >> szukane2;
        if(szukane1 == "cache" && szukane2 == "size"){
            plik_odczyt >> dwukropek >> tekst1 >> tekst2;
            plik_zapis << "Ilosc pamieci cache procesora " << licznik << dwukropek << " " << tekst1 << " " << tekst2 << endl;
            licznik++;
        }
    }
    plik_odczyt.close();
}

void plik_meminfo(fstream &plik_zapis)
{
    fstream plik_odczyt;
    string szukane, tekst1, tekst2;
    plik_odczyt.open ("meminfo.txt", ios::in);
    odczyt(plik_odczyt);

    while(!plik_odczyt.eof())
    {
        plik_odczyt >> szukane;
        if(szukane == "MemTotal:"){ //szukanie w tekscie sformulowania, po ktorym wystepuja intereujace nas dane
            plik_odczyt >> tekst1 >> tekst2;
            plik_zapis << "Ilosc pamieci fizycznej RAM: " << tekst1 << " " << tekst2 << endl;
        }
        if(szukane == "MemFree:"){
            plik_odczyt >> tekst1 >> tekst2;
            plik_zapis << "Ilosc wolnej pamieci fizycznej RAM: " << tekst1 << " " << tekst2 << endl;
        }
        if(szukane == "LowTotal:"){
            plik_odczyt >> tekst1 >> tekst2;
            plik_zapis << "Ilosc pamieci bezposrenio mapowanej na przestrzeni jadra: " << tekst1 << " " << tekst2 << endl;
        }
        if(szukane == "SwapTotal:"){
            plik_odczyt >> tekst1 >> tekst2;
            plik_zapis << "Wielkosc partycji wymiany: " << tekst1 << " " << tekst2 << endl;
        }
        if(szukane == "VmallocTotal:"){
            plik_odczyt >> tekst1 >> tekst2;
            plik_zapis << "Ilosc pamieci wirtualnej: " << tekst1 << " " << tekst2 << endl;
        }
        if(szukane == "VmallocUsed:"){
            plik_odczyt >> tekst1 >> tekst2;
            plik_zapis << "Ilosc zajetej pamieci wirtualnej: " << tekst1 << " " << tekst2 << endl;
        }
    }
    plik_odczyt.close();
}

int main()
{
    fstream plik_zapis;
    plik_zapis.open ("systeminfo.txt", ios::out); //utworzenie do zapisu pliku systeminfo.txt
    plik_version(plik_zapis); //pobranie i zapisanie informacji z konkretnych plikow
    plik_cpuinfo(plik_zapis);
    plik_meminfo(plik_zapis);
    plik_zapis.close();
	return 0;
}
