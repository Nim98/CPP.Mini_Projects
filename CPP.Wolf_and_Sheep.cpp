//POP 2017-12-15 projekt 1 Górska Aleksandra IBM 2 171816 (środowisko programistyczne: Codeblocks 16.01; kompilator: GNU GCC Complier)
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const string litery[8] = {"H","G","F","E","D","C","B","A"}; //współrzędne wierszy planszy

void PolozenieWilka(string pola[][8], int pierwszy_wiersz, int *pierwsza_kolumna)
{
    int losowa;
    srand(time(NULL));
    losowa = rand() % 4; //losowanie liczby do określenia początkowego położenia WILKA
    //wybór początkowego położenia WILKA
    if(losowa == 0){
        *pierwsza_kolumna = 1;
        pola[pierwszy_wiersz][*pierwsza_kolumna] = "W";
    }

    else if(losowa == 1){
        *pierwsza_kolumna = 3;
        pola[pierwszy_wiersz][*pierwsza_kolumna] = "W";
    }

    else if(losowa == 2){
        *pierwsza_kolumna = 5;
        pola[pierwszy_wiersz][*pierwsza_kolumna] = "W";
    }

    else if(losowa == 3){
        *pierwsza_kolumna = 7;
        pola[pierwszy_wiersz][*pierwsza_kolumna] = "W";
    }
}

void WyswietlaniePlanszy(string pola[][8])
{
    system("cls");
    for(int i = 0; i < 8; i++){ //wyświetlanie planszy
            cout << litery[i] << " |";
            for(int j = 0; j < 8; j++)
                cout << pola[i][j] << "|";
            cout << endl;
	}
	cout << "   0 1 2 3 4 5 6 7 " << endl; //współrzędne kolumn planszy
}

void Konwersja(int *wiersz, int *kolumna)
{
	char litera;
	int cyfra;

	do{ //sprawdzanie poprawności wprowadzonych współrzędnych
        cin >> litera >> cyfra;
        if (litera != 'A' && litera != 'B' && litera != 'C' && litera != 'D' &&
            litera != 'E' && litera != 'F' && litera != 'G' && litera != 'H' && (cyfra < 0 || cyfra > 7))
            cout << "Niepoprawny adres wiersza i kolumny, wpisz ponownie: ";
        else if (litera != 'A' && litera != 'B' && litera != 'C' && litera != 'D' &&
            litera != 'E' && litera != 'F' && litera != 'G' && litera != 'H')
            cout << "Niepoprawny adres wiersza, wpisz ponownie: ";
        else if (cyfra < 0 || cyfra > 7)
            cout << "Niepoprawny adres kolumny, wpisz ponownie: ";
    }while((litera != 'A' && litera != 'B' && litera != 'C' && litera != 'D' &&
            litera != 'E' && litera != 'F' && litera != 'G' && litera != 'H') || (cyfra < 0 || cyfra > 7)); //pętla działająca do czasu wprowadzenia poprawnych danych

	*kolumna = cyfra;
	switch(litera){ //zamiana współrzędnych wiersza na dane odpowiednie do wykorzystania w tabeli
        case 'H': *wiersz = 0; break;
        case 'G': *wiersz = 1; break;
        case 'F': *wiersz = 2; break;
        case 'E': *wiersz = 3; break;
        case 'D': *wiersz = 4; break;
        case 'C': *wiersz = 5; break;
        case 'B': *wiersz = 6; break;
        case 'A': *wiersz = 7; break;
	}
}

void ktoraOwca(string pola[][8], int *wierszPrzed, int *kolumnaPrzed)
{
	cout << endl << "(OWCE)";

	do{
        cout << endl << "Podaj ktora owca rusza: "; //wybór OWCY
        Konwersja(wierszPrzed, kolumnaPrzed);
        if (pola[*wierszPrzed][*kolumnaPrzed] != "O") //sprawdzanie obecności OWCY na wpisanym polu
            cout << "Na tym polu nie ma owcy, wpisz ponownie";
    }while(pola[*wierszPrzed][*kolumnaPrzed] != "O"); //pętla działająca do czasu wprowadzenia poprawnych danych
}

void ruchOwca(string pola[][8])
{
	int wierszPrzed, kolumnaPrzed, wierszPo, kolumnaPo;
	ktoraOwca(pola, &wierszPrzed, &kolumnaPrzed);

	do{
        cout << "Podaj gdzie: "; //wybór pola, na które ma przejść owca
        Konwersja(&wierszPo, &kolumnaPo);
		if((kolumnaPo == (kolumnaPrzed-1) || kolumnaPo == (kolumnaPrzed+1)) //sprawdzenie możliwości przejścia na wpisane pole
            && (wierszPo == (wierszPrzed+1))
			&& (pola[wierszPo][kolumnaPo] == " ")){

			pola[wierszPo][kolumnaPo] = pola[wierszPrzed][kolumnaPrzed]; //aktualizacja danych
        	pola[wierszPrzed][kolumnaPrzed] = " ";
		}
        else
        	cout << "Owca nie moze przejsc na to pole, wpisz ponownie" << endl;
    }while(pola[wierszPrzed][kolumnaPrzed] == "O"); //pętla działająca do czasu wprowadzenia poprawnych danych
}

bool droga(string pola[][8], int wiersz, int kolumna, int suma) //szukanie luki w położeniu OWIEC
{
    if(wiersz == 0) //możliwość dotarcia do wiersza H
		return true;

	else{
		if(kolumna-1 > -1) //obecność luki z lewej strony
			if(pola[wiersz-1][kolumna-1] == " "){
				suma = suma + droga(pola, wiersz-1, kolumna-1, suma);
			}

        if(kolumna+1 < 8) //obecność luki z prawej strony
            if(pola[wiersz-1][kolumna+1] == " "){
				suma = suma + droga(pola, wiersz-1, kolumna+1, suma);
			}
    }
	return suma;
}

void ruchWilk(string pola[][8], int *wierszPrzed, int *kolumnaPrzed, bool *wilkUciekl)
{
    int losowa;
    srand(time(NULL));
    losowa = rand()%2; //losowość ruchów

	int wierszPo, kolumnaPo;

	int wiersz = *wierszPrzed, kolumna = *kolumnaPrzed;
    // losowość ruchów w zależności od obecności luki w położeniu OWIEC
	if(pola[wiersz-1][kolumna-1] == " " && droga(pola, wiersz-1, kolumna-1, 0))
		losowa = 0;

	if(pola[wiersz-1][kolumna+1] == " " && droga(pola, wiersz-1, kolumna+1, 0))
		losowa = 1;

	if(*kolumnaPrzed == 7 && *wierszPrzed == 7){ //ruch WILKA z prawego dolnego rogu
		wierszPo = *wierszPrzed-1;
		kolumnaPo = *kolumnaPrzed-1;
    }

	if(*kolumnaPrzed == 7 && *wierszPrzed < 7){ //ruch WILKA z kolumny 7

		if(pola[*wierszPrzed-1][*kolumnaPrzed-1] == " "){ //ruch w górę
			wierszPo = *wierszPrzed-1;
			kolumnaPo = *kolumnaPrzed-1;
		}

        else{ //ruch w dół
			wierszPo = *wierszPrzed+1;
			kolumnaPo = *kolumnaPrzed-1;
		}
	}

	if(*kolumnaPrzed == 0 && *wierszPrzed < 7){ //ruch WILKA z kolumny 0

		if(pola[*wierszPrzed-1][*kolumnaPrzed+1] == " "){ //ruch w górę
			wierszPo = *wierszPrzed-1;
			kolumnaPo = *kolumnaPrzed+1;
		}

		else{ //ruch w dół
			wierszPo = *wierszPrzed+1;
			kolumnaPo = *kolumnaPrzed+1;
		}
	}

    if(*kolumnaPrzed < 7 && *wierszPrzed == 7){ //ruch WILKA z wiersza A

		do{ //ruch w górę
            if(pola[*wierszPrzed-1][*kolumnaPrzed-1] == " " && losowa == 0){ //ruch w lewo
                wierszPo = *wierszPrzed-1;
                kolumnaPo = *kolumnaPrzed-1;
                break;
            }
            if(pola[*wierszPrzed-1][*kolumnaPrzed+1] == " " && losowa == 1){ //ruch w prawo
                wierszPo = *wierszPrzed-1;
                kolumnaPo = *kolumnaPrzed+1;
                break;
            }
            losowa = rand()%2; //większa losowość ruchów
        }while(*kolumnaPrzed < 7 && *wierszPrzed == 7);
    }

    if(*kolumnaPrzed > 0 && *kolumnaPrzed < 7 && *wierszPrzed == 1){ //ruch WILKA z wiersza G
        //pewne przejście do wiersza H, jeżeli jest taka możliwość
		if(pola[*wierszPrzed-1][*kolumnaPrzed-1] == " "){ //ruch w lewo
                wierszPo = *wierszPrzed-1;
                kolumnaPo = *kolumnaPrzed-1;
            }

            else if(pola[*wierszPrzed-1][*kolumnaPrzed+1] == " "){ //ruch w prawo
                wierszPo = *wierszPrzed-1;
                kolumnaPo = *kolumnaPrzed+1;
            }
            //przejście do wiersza F
            else{
            	do{
                    if(pola[*wierszPrzed+1][*kolumnaPrzed-1] == " " && losowa == 0){ //ruch w lewo
                        wierszPo = *wierszPrzed+1;
                        kolumnaPo = *kolumnaPrzed-1;
                        break;
		            }
		            else if(pola[*wierszPrzed+1][*kolumnaPrzed+1] == " " && losowa == 1){ //ruch w prawo
		                wierszPo = *wierszPrzed+1;
		                kolumnaPo = *kolumnaPrzed+1;
		                break;
                    }
				losowa = rand()%2; //większa losowość ruchów
		    	}while(*kolumnaPrzed > 0 && *kolumnaPrzed < 7 && *wierszPrzed == 1);
			}
	}

	if(*kolumnaPrzed > 0 && *kolumnaPrzed < 7 && *wierszPrzed > 1 && *wierszPrzed < 7){ //ruch WILKA ze środka planszy

		do{ //WILK w miarę możliwości stara się poruszyć w górę
            if(pola[*wierszPrzed-1][*kolumnaPrzed-1] == " " && losowa == 0){ //ruch w lewo
                wierszPo = *wierszPrzed-1;
                kolumnaPo = *kolumnaPrzed-1;
                break;
            }
            else if(pola[*wierszPrzed-1][*kolumnaPrzed+1] == " " && losowa == 1){ //ruch w prawo
                wierszPo = *wierszPrzed-1;
                kolumnaPo = *kolumnaPrzed+1;
                break;
            }
            else{ //jeżeli nie ma możliwości poruszenia się do góry WILK rozważa cofnięcie się
            	if(pola[*wierszPrzed+1][*kolumnaPrzed-1] == " " && losowa == 0){ //ruch w lewo
                    wierszPo = *wierszPrzed+1;
                    kolumnaPo = *kolumnaPrzed-1;
                    break;
                }
                else if(pola[*wierszPrzed+1][*kolumnaPrzed+1] == " " && losowa == 1){ //ruch w prawo
                    wierszPo = *wierszPrzed+1;
                    kolumnaPo = *kolumnaPrzed+1;
                    break;
                }
            }
            losowa = rand()%2; //większa losowość ruchów
        }while(*kolumnaPrzed > 0 && *kolumnaPrzed < 7 && *wierszPrzed > 0 && *wierszPrzed < 7);
	}

	cout << endl << "(WILK)" << endl << //wypisanie gdzie ruszył WILK
	"Z pola "<< litery[*wierszPrzed] << *kolumnaPrzed <<
	" na "<< litery[wierszPo] << kolumnaPo << " (nacisnij dowolny klawisz aby kontynuowac)" << endl;
	system("pause>null");

	pola[wierszPo][kolumnaPo] = "W"; //aktualizacja danych
	pola[*wierszPrzed][*kolumnaPrzed]=" ";
	*wierszPrzed = wierszPo;
	*kolumnaPrzed = kolumnaPo;

	if(wierszPo == 0) //sprawdzenie wygranej komputera
		*wilkUciekl = true;
}

void CzyWilkZlapany(string pola[][8], bool *wilkZlapany, int wierszWilka, int kolumnaWilka) //sprawdzanie wygranej gracza
{
	if(kolumnaWilka == 0){
		if(pola[wierszWilka+1][kolumnaWilka+1] != " " && pola[wierszWilka-1][kolumnaWilka+1] != " ")
			*wilkZlapany = true; //WILK w kolumnie 0, w prawym górnym i prawym dolnym polu są OWCE
	}

	if(kolumnaWilka == 7 && wierszWilka < 7){
		if(pola[wierszWilka+1][kolumnaWilka-1] != " " && pola[wierszWilka-1][kolumnaWilka-1] != " ")
			*wilkZlapany = true; //WILK w kolumnie 7, w lewym górnym i lewym dolnym polu są OWCE
	}

	if(kolumnaWilka == 7 && wierszWilka == 7){
		if(pola[wierszWilka-1][kolumnaWilka-1] != " ")
			*wilkZlapany = true; //WILK w prawym dolnym rogu, w lewym górnym polu jest OWCA
	}

	if(kolumnaWilka > 0 && kolumnaWilka < 7 && wierszWilka > 0 && wierszWilka < 7){
		if(pola[wierszWilka+1][kolumnaWilka+1] != " " && pola[wierszWilka-1][kolumnaWilka+1] != " "
        && pola[wierszWilka+1][kolumnaWilka-1] != " " && pola[wierszWilka-1][kolumnaWilka-1] != " ")
			*wilkZlapany = true; //WILK na środku planszy, na wszystkich otaczających polach są OWCE
	}

	if(kolumnaWilka < 7 && wierszWilka == 7){
		if(pola[wierszWilka-1][kolumnaWilka-1]!=" " && pola[wierszWilka-1][kolumnaWilka+1]!=" ")
			*wilkZlapany = true; //WILK w wierszu 7, w prawym górnym i lewym górnym polu są OWCE
	}
}

int main()
{
	string pola[8][8] = {{"O","#","O","#","O","#","O","#"},
                         {"#"," ","#"," ","#"," ","#"," "},
                         {" ","#"," ","#"," ","#"," ","#"},
                         {"#"," ","#"," ","#"," ","#"," "},
                         {" ","#"," ","#"," ","#"," ","#"},
                         {"#"," ","#"," ","#"," ","#"," "},
                         {" ","#"," ","#"," ","#"," ","#"},
                         {"#"," ","#"," ","#"," ","#"," "},};

    bool wilkZlapany = false, wilkUciekl = false;

	int wierszWilka = 7, kolumnaWilka;

    PolozenieWilka(pola, wierszWilka, &kolumnaWilka);
	WyswietlaniePlanszy(pola);

	do{
		ruchWilk(pola, &wierszWilka, &kolumnaWilka, &wilkUciekl);
		WyswietlaniePlanszy(pola);
		if(wilkUciekl == true)
			break; //przerwanie pętli jeżeli wygrał komputer
		ruchOwca(pola);
		WyswietlaniePlanszy(pola);
		CzyWilkZlapany(pola, &wilkZlapany, wierszWilka, kolumnaWilka);
	}while(!wilkZlapany); //przerwanie pętli jeżeli wygrał gracz

	if(wilkUciekl == true) //wygrana komputera
		cout << endl << "Przegralas/es!!!";

    if(wilkZlapany == true) //wygrana gracza
		cout << endl << "Wygralas/es!!!";

	cout << endl << endl;
	system("pause");
	return 0;
}
