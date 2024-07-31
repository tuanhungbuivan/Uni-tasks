#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

/*
1. Create a pointer of inserted data from a file which file name is provided by the user.
Create a function which insert a movie with "some" data in the end of the list(pointer) starting
at a "certain" address (the parameter of inserted data are title, year and score).

2. Create a function that:
     a. Add a new element to the list(pointer) before every movie staring with leter 'P' and
     with a score higher than a number given by an user, also before the title starting with
     letter 'G' and a score higher than an avarage score of all movies. New element is completed
     by the data second from the end.
     b. Delete every second element from a list(pointer) with an even year.
3. Print a list before and after running a functions from point 2.
4. Delete list.
*/

using namespace std;


struct Movie{
	string title;
	int rok;
	double ocena;
	Movie *nast;
};

void dodaj(Movie *&adres,string title, int rok, double ocena){
	Movie *aktualny = new Movie;
	aktualny->title = title;
	aktualny->rok = rok;
	aktualny->ocena = ocena;

	if(adres == NULL){
		adres=aktualny;
		aktualny->nast=NULL;
	}else if(adres->nast == NULL){
		adres->nast = aktualny;
		aktualny->nast = NULL;
	}else{
		dodaj(adres->nast,title,rok,ocena);
	}
}

void drukuj(Movie *adres){
	if(adres==NULL)
		return;
	cout<<adres->title<<" "<<adres->rok<<" "<<adres->ocena<<endl;
	drukuj(adres->nast);
}

void zad2i3(Movie *&adres,int liczba,double srednia,int ile,string title,int rok,double ocena){
	Movie *nowy,*poprzedni,*aktualny, *temp;
	poprzedni = NULL;
	aktualny=adres;
	// a dodawanie elementow;
	while(aktualny!=NULL){
		//cout<<adres->title[0]<<endl;
		if(aktualny->ocena > liczba && aktualny->title[0] == 'P'){
			//insert(&adres,title,rok,ocena);
			nowy = new Movie();

			nowy->title=title;
			nowy->rok=rok;
			nowy->ocena=ocena;

			if(poprzedni == NULL){
				adres = nowy;
				adres->nast = aktualny;
			} else {
				poprzedni->nast = nowy;
				nowy->nast = aktualny;
			}
		}else if(aktualny->ocena > srednia && aktualny->title[0] == 'G'){
			nowy = new Movie();

			nowy->title=title;
			nowy->rok=rok;
			nowy->ocena=ocena;

			if(poprzedni == NULL){
				adres = nowy;
				adres->nast = aktualny;
			} else {
				poprzedni->nast = nowy;
				nowy->nast = aktualny;
			}
		}
		poprzedni=aktualny;
		aktualny=aktualny->nast;
	}
	cout<<"Lista po dopisaniu nowych elementow danymi drugiego od konca filmu na liscie: "<<endl;
	drukuj(adres);
	cout<<endl;

	//b usuwanie elementow;
	Movie *tmp;
	aktualny=adres;
	poprzedni=NULL;
	int i=0;
	while(aktualny!=NULL){
		if(aktualny->rok%2==0){
			if(i%2==1){
				if(aktualny==adres){
					adres=adres->nast;
				}else{
					poprzedni->nast=aktualny->nast;
				}
				tmp=aktualny;
				aktualny=aktualny->nast;
				delete tmp;
				i++;
			}else{
				i++;
				poprzedni=aktualny;
				aktualny=aktualny->nast;
			}
		}else{
			i+=2;
			poprzedni=aktualny;
			aktualny=aktualny->nast;
		}
	}
	cout<<"Lista po usunieci co drugiego elementu o parzystym roku: "<<endl;
	drukuj(adres);
}

int main()
{
	//1
	ifstream plik("movies.txt");

	if(!plik) { cout<<"blad podanej nazwy pliku"<<endl; return -1;}

	Movie *poprzedni, *aktualny, *glowa;
	aktualny = NULL;
	glowa = NULL;

	string title;
	int rok;
	double ocena;
	double suma=0;
	int ile=0;
	//elements second from the end
	string dktitle;
	int dkrok;
	double dkocena;
	//last elements
	string otitle;
	int orok;
	double oocena;

	while(plik.peek() != EOF){
		plik>>title>>rok>>ocena;
		suma+=ocena;
		ile++;
		dktitle=otitle;
		dkrok=orok;
		dkocena=oocena;
		otitle=title;
		orok=rok;
		oocena=ocena;
		dodaj(glowa,title,rok,ocena);
	}
	double srednia=suma/ile;
	cout<<"Lista przed zadaniem 2: "<<endl;
	drukuj(glowa);
	cout<<endl;
	cout<<"Srednia ocen: "<<srednia<<endl;
	cout<<endl;
	cout<<"Element przed ostatni z listy: "<<dktitle<<" "<<dkrok<<" "<<dkocena<<endl;
	cout<<endl;
	//2 i 3
	int liczba;
	cout<<"Podaj liczbe od 1 do 10 : "<<endl;
	do{
		cin>>liczba;
	}while(liczba<1 || liczba>10);
	cout<<endl;
	zad2i3(glowa,liczba,srednia,ile,dktitle,dkrok,dkocena);

	//4
	while(glowa != NULL){
		poprzedni = glowa;
		glowa=glowa->nast;
		delete poprzedni;
	}
	return 0;
}
