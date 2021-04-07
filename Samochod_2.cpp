#include <iostream>
#include <conio.h> //biblioteka dla getch()
#include <stdlib.h>//biblioteka dla system("cls")
#include <windows.h>//biblioteka dla Sleep()
#include <iomanip>//biblioteka dla fixed, setprecision()
#include <cstdlib>//biblioteka do zmiany wielkosci liter
		

using namespace std;										                                //STEROWANIE:  W-PRZYSPIESZENIE, S- HAMOWANIE, E- BIEG DO GORY,S-BIEG W DOL, P-WYLACZANIE SILNIKA
															                                // Zakres obrot?w: 1300-6000rpm, 

char klawisz,b,c;	
double predkosc=0,  obroty=1300,  x=1,  przelicznik[6]={0,100,66.66,44.44,34.24,30},  przelicznik_1=150; 			//przelicznik zale?ny od biegu
int bieg=0,strzal;																									//strza? ze sprz?g?a

short zwieksz_obroty[5]={100,2000,1950,1690,1485};                                          //short do sygnalizacji zwiekszenia obrotow
short zwieksz_bieg[5]={4000,5000,5000,5000,5000};                                           //short do sygnalizacji zwiekszenia biegu
double przelicznik_predkosci[6]={0,1,0.8,0.6,0.4,0.2};                                      //double podajacy sekwencja() przeliczniki predkosci na konkretnych biegach

bool odpalenie=true,   wlaczony=true, szansa;                                                                        //bool sterujacy odpalanie()

void odpalanie();   void wyswietlacz();   void menu();    void sekwencja();    void komunikaty();

int main()
{   
    
    while(wlaczony==true)
    {
        szansa=true;    odpalenie=true;

        odpalanie();
        
        switch(bieg)
            {	
            case -1:
                {
                    sekwencja();
                }
            case 0:
                {
                    sekwencja();
                }
            case 1:
                {
                    sekwencja();
                }
            case 2:
                {
                    sekwencja();
                }
            case 3:
                {
                    sekwencja();
                }
            case 4:
                {
                    sekwencja();
                }
            case 5:
                {
                    sekwencja();
                }
            }
        
        komunikaty();

        cout<<"\n\n1.SPROBUJ JESZCZE RAZ\n2.OPOSC PROGRAM";
        while(szansa==true)
        {
            c=getch();
            if(c>95)                                                                      //rozwiazanie gdy uzytkownik uzywa CAPS LOCK
                {
                    c-=32;
                }
                switch(c)
                {
                    case '1': 
                        {
                            bieg=0;   predkosc=0;  obroty=1300; system("cls");  szansa=false; break;
                        }
                    case 'W':break;
                    case 'S':break;
                    case 'Q':break;
                    case 'E':break;
                    case 'P':break;

                    case '2': 
                        {   
                            
                            wlaczony=false; szansa=false;    break;
                        }
                    default:break;
                }
        }
    }
        return 0;
}

void komunikaty()                                                                               //Komunikaty przypadkow krancowych
{
	if(bieg==7)
		{
			Sleep(500);		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SILNIK ZOSTAL WYLACZONY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";		Sleep(4000);
		}
	if(bieg==10)
		{
			Sleep(500);		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SILNIK WYBUCHL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";		Sleep(4000);
		}
	if(bieg==6)
		{
			Sleep(500);		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!WRZUCILES WSTECZNY. SKRZYNIA SIE ROZPADLA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";	Sleep(4000);
		}
	if(bieg==-5)
		{
			Sleep(500);		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SAMOCHOD ZGASL!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";	Sleep(4000);
		}
}

void sekwencja()                                                                                //Funkcja sterujaca calym programem
{
    while(bieg>=-1 && bieg<=5)
	{
        if(bieg>0)                                                                               //sposoby liczenia obrotow w zaleznosci od biegu
        {   
            obroty=predkosc*przelicznik[bieg];
        }
        else if(bieg==-1)
        {
            obroty=predkosc*(-1)*przelicznik_1;
        }
        else if(bieg==0)
        {}

        
        if(obroty<1300)                                                                         // okreslanie akcji w przypadkach krancowych oraz w przypadku prawidlowych parametrow
        {
            bieg=-5;
        }
        if(obroty>6000)
        {	
            bieg=10;
        }
        if(obroty>=1300&&obroty<=6000)
        {  
            wyswietlacz();

            if(bieg==-1 || bieg==5)
            {
                if(obroty>5000&&obroty<5500){cout<<"    Wysokie obroty";}
                if(obroty>5500){cout<<"    OBROTY KRYTYCZNE";}
            }
            else if(bieg>=0 && bieg<5)
            {
                if(obroty<zwieksz_obroty[bieg])
                {
                    cout<<"    Zwieksz obroty";
                }	
                if(obroty>zwieksz_bieg[bieg])
                {
                    cout<<"    Zwieksz bieg";
                }
            }
                    
            menu();
            klawisz=getch();                                                                    //pobieranie klawisza do sterowania sekwencja
            if(klawisz>95)                                                                      //rozwiazanie gdy uzytkownik uzywa CAPS LOCK
            {
                klawisz-=32;
            }
            else{}
            system("cls");

            switch(klawisz)
                {
                    case 'W': //Przyspieszenie
                        {                                                                       //deklarowania przyspieszenia w zaleznosci od biegu
                            if(bieg==-1)
                            { 
                                predkosc=predkosc-x; break;
                            }	
                            else if(bieg==0)
                            {
                                obroty=obroty+200;break;
                            }
                            else if(bieg>0 && bieg<=5)
                            {
                                predkosc+=(przelicznik_predkosci[bieg]*x); break;
                            }
                        }
                    case 'S': //Hamowanie
                        {                                                                      //deklarowanie hamowania w zaleznosci od biegu
                            if(bieg==-1)
                            {
                                predkosc=predkosc+x; break;
                            }

                            else if(bieg==0)
                            {
                                if(predkosc<0)
                                {
                                    predkosc=predkosc+1;
                                }
                                if(predkosc>0)
                                {
                                    predkosc=predkosc-1;
                                }
                                else
                                {
                                    if(obroty>=1500)
                                    {
                                        obroty=obroty-200;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                }
                                break;
                            }

                            else if(bieg>0 && bieg<=5)
                            {
                                predkosc=predkosc-x; break; 
                            }
                        }
                    case 'E': //Bieg w gore
                        {                                                                        //deklarowanie zwiekszania biegu w zaleznosci od biegu i obrotow
                            if(bieg==0)
                            {
                                        
                                if(obroty>=1300&&obroty<2200)
                                {
                                    strzal=obroty/przelicznik[1];
                                    for(int i=0;i<strzal;i++)
                                    {
                                        predkosc++; 	obroty=obroty-10;
                                        wyswietlacz();
                                        menu();
                                        system("cls");
                                    }
                                }
                                if(obroty>=2200&&obroty<3000)
                                {
                                    strzal=obroty/przelicznik[1];
                                    for(int i=0;i<strzal;i++)
                                    {
                                        predkosc++;     obroty=obroty-30;
                                        wyswietlacz();
                                        menu();
                                        system("cls");
                                    }
                                }		
                                if(obroty>=3000&&obroty<=6000)
                                {
                                    strzal=(obroty/przelicznik[1])/2;
                                    for(int i=0;i<strzal;i++)
                                    {
                                        predkosc=predkosc+2;	obroty=obroty-80;
                                        wyswietlacz();
                                        menu();
                                        system("cls");
                                    }
                                }
                                bieg++; 	break;
                                        
                            }

                            else if(bieg==-1 ||  (bieg>0 && bieg<=4))
                            {
                                if(bieg==-1)
                                {
                                    obroty=1300;
                                }
                                else{}
                                bieg++; break;
                            }
                            else if(bieg==5)
                            {
                                bieg=6; break;
                            }
                        }
                    case 'Q': //Bieg w dol
                        {                                                                          //deklarowanie redukcji biegu w zaleznosci od biegu i obrotow
                            if(bieg==-1)
                            {
                                break;
                            }
                            else if(bieg==0)
                            {
                                if(obroty>=1300&&obroty<2200)
                                {
                                    strzal=obroty/przelicznik_1;
                                    for(int i=0;i<strzal;i++)
                                    {
                                        predkosc--;		obroty=obroty-10;
                                        wyswietlacz();
                                        menu();
                                        system("cls");
                                    }
                                }
                                else if(obroty>=2200&&obroty<3000)
                                {
                                    strzal=obroty/przelicznik_1;
                                    for(int i=0;i<strzal;i++)
                                    {
                                        predkosc--;		obroty=obroty-30;
                                        wyswietlacz();
                                        menu();
                                        system("cls");
                                    }
                                }
                                else if(obroty>=3000&&obroty<=6000)
                                {
                                    strzal=(obroty/przelicznik_1)/2;
                                    for(int i=0;i<strzal;i++)
                                    {
                                        predkosc=predkosc-2;	obroty=obroty-80;
                                        wyswietlacz();
                                        menu();
                                        system("cls");
                                    }
                                }
                                    bieg--;		break;
                                    }
                            else if(bieg>0 && bieg<=5)
                            {
                                if(bieg==1)
                                {
                                    obroty=1300;
                                }
                                else{}
                                bieg--; break;
                            }
                        }
                        
                    case 'P':   //Wylaczanie silnika
                        {
                            bieg=7; break;
                        }
                    
                    default: break;
                
                }
        }
    }
}

void menu()                                                                                    //Menu prezentujace sterowanie
{
	cout<<"\n\n\n";
										cout<<	"                              gaz\n";
										cout<<	"                             /\n";
										cout<<	"                            W\n";
										cout<<	"         bieg w dol------ Q   E -------bieg w gore                         P---wylacz silnik\n";
										cout<<	"                            S\n";
										cout<<	"                           /\n";
										cout<<	"                    hamulec\n";
										
}

void wyswietlacz()                                                                             //Wyswietlacz predkosci, biegow, obrotow
{ 
    cout<<"            "<<fixed;		cout<<"Predkosc: "<<setprecision(0)<<predkosc<< "   "<< "Bieg: "<<bieg<< "    Obroty: "<<obroty;
}

void odpalanie()                                                                               //Sekwencja odpalania silnika
{
    while(odpalenie==true)
    {
	cout <<"NACISNIJ 'O' ABY ODPALIC SAMOCHOD";      b=getch(); 
    if(b>95)
    {
        b-=32;
    }
    else{}
	Sleep(2000);     system("cls");
	
    
	switch(b)
		{
			
			case 'O':
				{
					cout << "Silnik zostal wlaczony\n";  Sleep(2500);     system("cls");    odpalenie=false;   break;
				}
			case '0':
				{
					cout << "Silnik zostal wlaczony\n";  Sleep(2500);     system("cls");    odpalenie=false;    break;
				}
            default: break;	
		}
    }
}