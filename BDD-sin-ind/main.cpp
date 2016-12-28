#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>
#include <cstdlib> // para "clear"
#include "principal.h"
#include"principal.cpp"
using namespace std;

namespace functionsSupport{
	void Menu(){
		cout << "\n\n" ;
		cout << "\t\t\t\tMENU PRINCIPAL" << endl;;
		cout << "\t\t 1.- Ingresar Datos " << endl;
		cout << "\t\t 2.- Eliminacion de un jugador. " << endl;
		cout << "\t\t 3.- Consultas e Informacion del jugador. " << endl;
		cout << "\t\t 4.- Modificaciones de Datos de un jugador del club. " << endl;
		cout << "\t\t 5.- Salir" << endl;
		cout << "\t\t 6.- Mostrar Lista de Jugadores " << endl;
		cout << "\n\t\telige una opcion -->  ";
	}

	void clear(){
		system("clear");
	}
}

int main(){

	int iclave;
	int iop, ij;
	char ope = 'n', cont = 'N';

	ifstream salida_pri;
	ofstream entrada_pri;

	Principal<int> jugador1;


	do{
		functionsSupport::clear();
		functionsSupport::Menu();
		cin >> iop;
		switch(iop){
			case 1:
				functionsSupport::clear();
				entrada_pri.open("principal.txt",ios::out | ios::app);
				do{
					jugador1.pedirdatos();
					entrada_pri.write( (char*) &jugador1, sizeof(jugador1));
					cout << "\n\n\t\tDesea otro registro ?: ";
					cin >> ope;
					functionsSupport::clear();
				} while(toupper(ope) == 'S');
				entrada_pri.close();
				break;

			case 2:
				functionsSupport::clear();
				salida_pri.open("principal.txt", ios::in);
				entrada_pri.open("temp.txt", ios::out | ios::app);
				cout << "introduzca el DNI del jugador a eliminar del club: "; cin>> iclave;

				while( salida_pri.read( (char*) &jugador1, sizeof(jugador1) ) != 0 ){
					if(jugador1.getDni() != iclave)
						entrada_pri.write( (char*) &jugador1,sizeof(jugador1) );
				}
				salida_pri.close();
				entrada_pri.close();

				remove("principal.txt");
				rename("temp.txt","principal.txt");
				break;

			case 3:
				functionsSupport::clear();
				salida_pri.open("principal.txt",ios::in);
				cout << "\n\t\tIntrodusca el DNI del jugador a consultar -->  ", cin >> iclave;

				while( salida_pri.read( (char*) &jugador1, sizeof(jugador1) ) != 0 ){
					if(jugador1.getDni() == iclave){
						jugador1.consultas();
						cout << "\n\n\t\t\t\tContinuar (S) -->  "; cin >> cont;
					}
				}
				salida_pri.close();

				break;

			case 4:
				functionsSupport::clear();
				salida_pri.open("principal.txt",ios::in);
				entrada_pri.open("temp.txt" ,ios::out | ios::app );
				cout << "\n\t\tDNI del jugador a modificar -->  "; cin >> iclave;

				while(salida_pri.read( (char*) &jugador1, sizeof(jugador1) ) != 0 ){
					if(jugador1.getDni() == iclave){
						jugador1.modificar();
						entrada_pri.write( (char*)& jugador1, sizeof(jugador1) );
						cout << "modificacion exitosa " << endl;
					}
					else
						entrada_pri.write( (char*)& jugador1, sizeof(jugador1) );
				}
				salida_pri.close();
				entrada_pri.close();
				remove("principal.txt");
				rename("temp.txt","principal.txt");
				break;

			case 6:
				functionsSupport::clear();
				salida_pri.open("principal.txt", ios::in);
				while( salida_pri.read( (char*)&jugador1, sizeof(jugador1) ) != 0){
					jugador1.datos_constantes();
				}
				cout << "\n\n\t\t\t\tContinuar (S) -->  "; cin >> cont;
				salida_pri.close();
				break;

		}
	} while(iop != 5);
	functionsSupport::clear();


	return 0;
}
