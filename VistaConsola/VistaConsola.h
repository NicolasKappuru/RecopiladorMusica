#ifndef VISTACONSOLA_H
#define VISTACONSOLA_H
#include <string>

using namespace std; 

class VistaConsola{ //Declaracion de metodos de VistaConsola
	public:
		VistaConsola(); //Constructor de VistaConsola
		void mostrarInformacion(string); //Metodo que imprime en consola
		string leerDato(string); //Metodo para ingresar un apuntador a caracter (nuestra cadena)
		int leerDatoInt(string); //Metodo para ingresar un entero
		void mostrarEtiqueta(string); 
		void menuCRUD(); //Menu para el CRUD del programa
		void subMenu(); //Menu para ver que elemento se tratara
		void menuConsultas(); //Menu para consultas a realizar
};

#endif //VISTACONSOLA_H

