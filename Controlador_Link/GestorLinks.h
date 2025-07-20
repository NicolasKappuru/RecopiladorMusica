#ifndef GESTORLINKS_H
#define GESTORLINKS_H

#include "ModeloDAO_Interfaces/DAO.h"
#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "VistaConsola/VistaConsola.h" 
#include <string>


class GestorLinks{
private:
	SingletonPosLibres<int>* posLibres;
	VistaConsola vista; //Tiene un atributo Vista
	DAO* LinkDAO; 
	string arregloPos; 
	
public:
    GestorLinks(DAO* concreto);
    string insercion();
    bool eliminacion();
    int definirPosicion();   
	void creacionRegistro(string); 
	string getArregloPos();  
	void setArregloPos(string); 
    ~GestorLinks();
};

#endif // Gestor de links

