#ifndef MEDIATOR_CANCION_H
#define MEDIATOR_CANCION_H
#include "MediatorInterface.h"

#include "../ModeloDAO_Interfaces/DAO.h"
#include "../Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "../Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "../Modelo_Singleton_Arboles/SingletonArbolBusq.h"

#include "../Modelo_EstructuraNodos/NodoArbolBusquedas.h"

#include "../VistaConsola/VistaConsola.h" 

#include <string>

class MediatorCancion : public MediatorInterface {
private:
	SingletonPosLibres<int>* posLibres;
	SingletonArbolID<string>* arbolID;  
	SingletonArbolBusq<string>* arbolBusq;  
	VistaConsola vista; //Tiene un atributo Vista
	DAO* CancionDAO;
	string cadena;  
	NodoArbolBusquedas<string>* nodoAux; 
	DAO* ArtistaDAO;  
	
public:
    MediatorCancion(DAO* concreto);
    bool insercion() override;
    bool eliminacion() override;
    bool actualizacion() override;
    bool verificacion(string) override;
	int definirPosicion() override; 
    void actualizarArbCon(int numArb, string parametro, string ord1, string ord2);
	void actualizarArbCon5(string nombre, string ord1, string ord2, bool inserta, int posEliminar);	
	string formulario(string, int) override; //Especial para Cancion y Album 
	void setCadena(string, string, string) override; 

    ~MediatorCancion();
};

#endif 

