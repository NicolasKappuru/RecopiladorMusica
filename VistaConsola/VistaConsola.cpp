#include "VistaConsola.h"
#include <iostream>
#include <string>
#include <cstring> 
#include <limits>

using namespace std; 

//Implementacion o definicion de los metodos de la clase VistaConsola

VistaConsola::VistaConsola(){ //Constructor de la clase VistaConsola
}

void VistaConsola::mostrarInformacion(string mensaje){ 
	cout<< mensaje<<endl; 
}

string VistaConsola::leerDato(string mensaje){ //Mensaje indica que "dato" ingresar
	string dato = "";
	cout << mensaje; 
    if (cin.peek() == '\n') {
        cin.ignore(); // Ignora el salto de línea
    }
	getline(cin, dato); 
	cout <<endl; 
    return dato; 
}
	
int VistaConsola::leerDatoInt(string mensaje){ //Mensaje indica que "dato" ingresar
	int eleccion = 0;
	cout<< "\n" + mensaje; 
	cin >> eleccion;
	cout << endl;  
	return eleccion; //Retorna el numero entero que ingrese el usuario
}

void VistaConsola::mostrarEtiqueta(string cadena){ 
	cout << "===================  "+ cadena +"  ====================" << endl;
	cout << endl;  
}

void VistaConsola::menuCRUD(){ 
	cout << "====================================================" << endl; 
	cout << "===================  MENU CRUD  ====================" << endl; 
	cout <<	"====================================================" << endl;  
	cout << endl; 
	cout <<	"Ingrese el numero relacionado a la opcion que desea ejecutar" << endl << endl <<
			"[1] Agregar " << endl <<
			"[2] Eliminar " << endl <<
			"[3] Actualizar " << endl <<
			"[4] Consultar " << endl <<
			"[5] Cerrar el programa " << endl; 
}

void VistaConsola::subMenu(){ 
cout << "====================================================" << endl; 
cout << "=================  MENU OPCIONES  ==================" << endl; 
cout << "====================================================" << endl; 
cout << endl; 
cout << "Ingrese el numero relacionado a la opcion que desea ejecutar" << endl << endl;

cout << "[1] Album " << endl
     << "[2] Cancion " << endl
     << "[3] Artista " << endl
     << "[4] Volver al CRUD" << endl;

}
	
void VistaConsola::menuConsultas(){
	cout << "==================================================" << endl; 
	cout << "================  MENU CONSULTAS  ================" << endl; 
	cout <<	"==================================================" << endl;
	cout << endl; 
	cout <<	"Ingrese el numero relacionado a la opcion que desea ejecutar" << endl<<endl;

	cout <<	"[1]  Por editora " << endl <<
			"[2]  Por estudio de grabacion " << endl <<
			"[3]  Por tiempo de duracion de la cancion (>=)  " << endl <<
			"[4]  Por genero e instrumento  " << endl <<
			"[5]  Por numero de versiones" << endl <<
			"[6]  Por tipo de version " << endl <<
			"[7]  Por nombre de una cancion " << endl <<
			"[8]  Por cover art" << endl <<
			"[9]  Por fotografia y estudio de grabacion " << endl <<
			"[10] Por el compositor de la letra " << endl <<
			"[0]  Cancelar la consulta " << endl; 
}



/*
void VistaConsola::menuConsultas(){
	cout << "Por favor seleccione el numero correspondiente a la plataforma del link \n" << endl <<
			"Plataformas:" << endl <<
			"1)  Spotify " << endl <<
			"2)  Amazon " << endl <<
			"3)  Youtube Music " << endl <<
			"4)  Deezer  " << endl <<
			"5)  Itunes" << endl; 
}
*/

