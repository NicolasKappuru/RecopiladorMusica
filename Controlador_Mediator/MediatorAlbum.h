#ifndef MEDIATOR_ALBUM_H
#define MEDIATOR_ALBUM_H
#include "MediatorInterface.h"

#include "ModeloDAO_Interfaces/DAO.h"

#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"

#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"

#include "VistaConsola/VistaConsola.h"

#include <string>


class MediatorAlbum : public MediatorInterface {
private:
	SingletonPosLibres<int>* posLibres;
	SingletonArbolID<string>* arbolID;  
	SingletonArbolBusq<string>* arbolBusq;  
	VistaConsola vista; //Tiene un atributo Vista
	NodoArbolBusquedas<string>* nodoAux; 
	DAO* AlbumDAO; 
	string cadena; 

public:
    MediatorAlbum(DAO* concreto);
    bool insercion() override;
    bool eliminacion() override;
    bool actualizacion() override;
    bool verificacion(string) override;
    int definirPosicion() override; 
    
    //Para arbol 1 y 2
    void actualizarArbCon1(int numArb, string parametro, string ord1, string ord2);
    
    string formulario(string, int) override; //Especial para Cancion y Album 
	void setCadena(string, string, string) override; 
    ~MediatorAlbum();
};

#endif // MEDIATOR_ALBUM_H

