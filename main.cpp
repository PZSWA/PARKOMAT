#include <iostream>
#include <string>
#include <windows.h>
#include <winbase.h>
#include <time.h>
#include <conio.h>
#include <limits>

using namespace std;

string rejestracja;
int oplataDodatkowa = 1;

int iloscGodzinParkowania = 0;
class Parkomat{
public:

    void start(){
        cout << "Nacisnij dowolny przycisk\nPress some button\nParkomat czynny\n" << this->dataIczas();
        getch();
        this->wprowadzRejestracje();
    }

    void wprowadzRejestracje(){
        system("cls");
        cout << "Wprowadz rejestracje [ENTER - akceptuj]:";
        cin >> rejestracja;
        cout << "Oplata dodatkowa - " << oplataDodatkowa << " PLN";
        Sleep(5000);
        this->wplata();
    }

    void wplata(){
        system("cls");
        cout << "Chcesz wplacic karta czy gotowka?: 1. Karta, 2.Gotowka" << endl;
        int wybor;
        cin >> wybor;
        switch (wybor){
            case 1:
                wplataKarta();
                break;
            case 2:
                wplataMonety();
                break;
            default:
                cin.clear();
                cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
                cout << "Brak takiego wyboru ;c";
                Sleep(1000);
                this->wplata();
                break;
        }
    }

    void wplataKarta(){
        system("cls");
        do{
            cout << "Wprowadz czas postoju: (MAX 50 godzin, 1 PLN za godzine)";
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cin >> iloscGodzinParkowania;
        }while (cin.fail() || iloscGodzinParkowania < 1 || iloscGodzinParkowania > 50);
        cout << "Ilosc monet: " << iloscGodzinParkowania+1 << " jest to: " << iloscGodzinParkowania << " godzin parkowania\n";
        cout << "* Uzytkownik przyklada karte\n* Parkomatr laczy sie z internetem i oplaca..." << endl;
        Sleep(5000);
        this->odbiorBiletu();
    }

    void wplataMonety(){
        system("cls");
        cout << "Wplacono 0.0 PLN\nCzas postoju 0:00\nDo: " << this->dataIczas() << endl << "Akcpetuj - dowolny przycisk";
        getch();
        system("cls");
        cout << "Aby oplacic wrzuc monete sposrod:\n1. 1zl\n2. 2zl\n3. 5zl\nKazda wrzucona zlotowka to 1 godzina parkowania (limit 50 zl)\n9. Akceptuj oplacenie";
        int pomoc;
        do{
            cin.clear();
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n');
            cout << "* Rzuc monete (numer monety lub 9 dalej): ";
            cin >> pomoc;

            switch (pomoc){
                case 1:
                    if(iloscGodzinParkowania + 1 > 51){
                        cout << "Nie mozna miec wiecej niz 50 godzin";
                        this->odbiorBiletu();
                        break;
                    }
                    iloscGodzinParkowania += 1;
                    break;
                case 2:
                    if(iloscGodzinParkowania + 2 > 51){
                        cout << "Nie mozna miec wiecej niz 50 godzin";
                        this->odbiorBiletu();
                        break;
                    }
                    iloscGodzinParkowania += 2;
                    break;
                case 3:
                    if(iloscGodzinParkowania + 5 > 51){
                        cout << "Nie mozna miec wiecej niz 50 godzin";
                        this->odbiorBiletu();
                        break;
                    }
                    iloscGodzinParkowania +=5;
                    break;
                case 9:
                    if(iloscGodzinParkowania > 1)
                    this->odbiorBiletu();
                    break;
                default:
                    break;
            }
            if(!cin.fail() && (pomoc == 1 || pomoc == 2 || pomoc == 3)) cout << "Ilosc monet: " << iloscGodzinParkowania << " jest to: " << iloscGodzinParkowania-1 << " godzin parkowania\n";
            iloscGodzinParkowania--;
        }while(cin.fail() || iloscGodzinParkowania <2 || pomoc != 9);



    }

    void odbiorBiletu(){
        system("cls");
        cout << "* Drukuje bilet..." << endl;
        Sleep(2000);
        cout << "Twok bilet:\n_____P_____\nOplata za parkowanie\nSamochod rejestracja: " << rejestracja << "\nCzas parkowania: " << this->dataIczas() << " + " << iloscGodzinParkowania << " godzin\n_____Z_____\nPawel Zubek S.A.";
        getch();
    }

    string dataIczas(){
        time_t czas;
        struct tm * data;
        char godzina[ 80 ];
        time( & czas );
        data = localtime( & czas );
        strftime( godzina, 80, "%Y-%m-%d %H:%M", data );
        return godzina;
    }


};

int main() {
    Parkomat parkomat;
    parkomat.start();


    getch();
    return 0;
}
