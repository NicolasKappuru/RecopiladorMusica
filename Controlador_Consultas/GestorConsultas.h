#ifndef GESTORCONSULTAS_H
#define GESTORCONSULTAS_H

#include "VistaConsola/VistaConsola.h" 

#include "ModeloDAO_Interfaces/DaoFactory.h"
#include "ModeloDAO_Interfaces/DAO.h"

#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"

#include <string>


class GestorConsultas{
private:
	VistaConsola vista; //Tiene un atributo Vista
	DaoFactory* fabrica;
	
	DAO* AlbumDAO; //Requerimos para traer los datos de album
	DAO* CancionDAO; //Requerimos para traer datos de cancion
	DAO* ArtistaDAO; //Requerimos para traer datos de artista
	DAO* LinkDAO;
	DAO* ArbolDAOID;
	DAO* ArbolDAOBusquedas;
	
	SingletonArbolBusq<string> *arbolBusq;
	
public:
    GestorConsultas();  
	bool gestionar(); 
	void conEditora(); 
	void conEstudioGrabacion(); 
	void conDuracion(); 
	void conGenIns(); 
	void conNumVer(); 
	void conVersion(); 
	void conNombreCancion(); 
	void conCoverArt(); 
	void conFotografiayEstudio();
	void conCompositorLetra(); 
    ~GestorConsultas();
};

#endif

