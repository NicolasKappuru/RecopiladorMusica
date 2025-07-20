#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "VistaConsola/VistaConsola.h" //Es una forma de referirse al directorio que est� un nivel por encima del directorio actual.
#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"
#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"

class Controlador {
	private: 
		SingletonPosLibres<int>* posLibres;
		SingletonArbolID<string>* arbolID;  
		SingletonArbolBusq<string>* arbolBusq;  
		NodoArbolBusquedas<string>* nodoAux; 

		VistaConsola vista; //Tiene un atributo Vista
		string auxStr; 
		string auxAlb;
		int auxInt; 
		int posCan; 
		
	public:
		Controlador(); //Constructor
    	void run(); 
    	bool CRUD(int);//Se encarga de ver la operacion a realizar del CRUD
		bool mediadorAdicionar(int);// Se encargara de elegir el componente y mediarlo
		bool mediadorEliminar(int);// Se encargara de elegir el componente y mediarlo
		bool mediadorActualizar(int);// Se encargara de elegir el componente y mediarlo
};

#endif


