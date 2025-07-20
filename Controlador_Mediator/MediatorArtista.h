#ifndef MEDIATOR_ARTISTA_H
#define MEDIATOR_ARTISTA_H
#include "MediatorInterface.h"

#include "ModeloDAO_Interfaces/DAO.h"

#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"

#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"

#include "VistaConsola/VistaConsola.h"


#include <string>

class MediatorArtista : public MediatorInterface {
private:
	SingletonPosLibres<int>* posLibres;
	SingletonArbolID<string>* arbolID;  
	SingletonArbolBusq<string>* arbolBusq;  
	NodoArbolBusquedas<string>* nodoAux; 
		
	VistaConsola vista; //Tiene un atributo Vista
	DAO* ArtistaDAO; 
	DAO* CancionDAO; 

public:
    MediatorArtista(DAO* concreto);
    bool insercion() override;
    bool eliminacion() override;
    bool actualizacion() override;
    bool verificacion(string comparar) override;
    int definirPosicion() override; 
    void actualizarArbCon(int numArb,int numCola, string parametro, string ord1, string ord2);	
    string formulario(string, int) override; 
    void setCadena(string, string, string) override; 
	

	~MediatorArtista();
};

#endif // MEDIATOR_ARTISTA_H

