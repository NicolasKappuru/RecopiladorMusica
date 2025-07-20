#include "MediatorAlbum.h"

#include "ModeloDAO_Interfaces/DAO.h"
#include "ModeloDAO_Objetos/AlbumDAOImpl.h"

#include "Modelo_Estatico/CompletarCadena.h"
#include "Modelo_Estatico/CreacionID.h"

#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"

#include <iostream> // Para mensajes de consola, si es necesario
#include <string>

MediatorAlbum::MediatorAlbum(DAO* concreto) {
	posLibres = SingletonPosLibres<int>::obtenerInstanciaPosLibres();
	arbolID = SingletonArbolID<string>::obtenerInstanciaArbolID(); 
	arbolBusq = SingletonArbolBusq<string>::obtenerInstanciaArbolBusqueda(); 
	nodoAux = nullptr; 
	vista = VistaConsola(); 
	AlbumDAO = concreto;
	cadena = "";
}

string MediatorAlbum::formulario(string titulo, int numCan){
 
	string titulo_Alb = titulo; 
	string pais_Alb = vista.leerDato("[1] Inserte pais de grabacion: ");
	string nombreArt_Alb = vista.leerDato("[2] Inserte nombre artistico: ");
	string anioPub_Alb = vista.leerDato("[3] Inserte anio de publicacion: ");
	string coverArt_Alb = vista.leerDato("[4] Inserte el encargado del cover art: ");
	string fotografia_Alb = vista.leerDato("[5] Inserte el encargado de fotografia: ");
	string editora_Alb = vista.leerDato("[6] Inserte la editora: ");
	string estudioGra_Alb = vista.leerDato("[7] Inserte el estudio de grabacion: ");
	
	string id_Alb = CreacionID::crearID_Alb(titulo_Alb,pais_Alb,nombreArt_Alb,anioPub_Alb,coverArt_Alb,fotografia_Alb,editora_Alb,estudioGra_Alb);	
	
	if(verificacion(id_Alb)) return "Repetido"; 
	
	//Este prepara el aux para consulta 8
	arbolBusq->setCoverArtAux(coverArt_Alb);
	
	//Actualizar arbol de IDs y crea la cadena que retornara
	arbolID->obtenerArbol(1)->insertar(id_Alb,posLibres->obtenerCola(0)->retornarValor());
	cadena = CreacionID::combinarCadenasAlb(id_Alb,titulo_Alb,pais_Alb,nombreArt_Alb,anioPub_Alb,coverArt_Alb,fotografia_Alb,editora_Alb,estudioGra_Alb); 
	
	//Actualizar primer arbol de busqueda
	arbolBusq->obtenerArbol(11)->insertar(titulo_Alb); 
	nodoAux = arbolBusq->obtenerArbol(11)->buscar(titulo_Alb); 
	nodoAux->lista.insertar(posLibres->obtenerCola(0)->retornarValor(), nombreArt_Alb);
	
	//Actualizar arbol consulta 1
	actualizarArbCon1(1, editora_Alb, anioPub_Alb, nombreArt_Alb);  
	  
	//Actualizar arbol consulta 2
    actualizarArbCon1(2, estudioGra_Alb, anioPub_Alb, pais_Alb);   

	//Actualizar arbol consulta 9
    string fotografiaEstudio_Alb = fotografia_Alb + estudioGra_Alb;
    actualizarArbCon1(9, fotografiaEstudio_Alb, pais_Alb, titulo_Alb);

	
	return cadena;
}

bool MediatorAlbum::insercion() {	 
	string cadenaDef = CompletarCadena::rellenarConCeros(cadena,249); //Poner tama�o original de la cadena
	int pos = definirPosicion(); 
	AlbumDAO->modificarDato(pos,cadenaDef); 

	//limpiar aux para proximas consultas
	arbolBusq->setCoverArtAux("Null");
    return true;

}

bool MediatorAlbum::eliminacion() {
    vista.mostrarInformacion("Eliminacion de Album en proceso");
   	return true; 
}

bool MediatorAlbum::actualizacion() {
    vista.mostrarInformacion("Actualizacion de Album en proceso");
    return true; 

}

bool MediatorAlbum::verificacion(string comparar) {
    vista.mostrarInformacion("\nVerificando que no se repita el registro..." + comparar);
	if(arbolID->obtenerArbol(1)->buscar(comparar)==nullptr) return false; 
	return true; //Si se repite
}

int MediatorAlbum::definirPosicion(){
	int pos = posLibres->obtenerCola(0)->atenderCola(); //La cola de album 
	int tam = posLibres->getTamAlbum(); 
	if(pos>tam){
		posLibres->obtenerCola(0)->insCola(pos+1);
		posLibres->sumTamAlbum(); 
		return pos; 
	}else{
		return pos; 
	}
}

void MediatorAlbum::setCadena(string cadena1, string cadena2, string cadena3){
	cadena = CreacionID::combinar3Cadenas(cadena1, cadena2, cadena3); 
}


//Esta funcion se hace antes de insertar el Album, para no atender la posLibre
void MediatorAlbum::actualizarArbCon1(int numArb, string parametro, string ord1, string ord2){
	arbolBusq->obtenerArbol(numArb)->insertar(parametro);
	nodoAux = arbolBusq->obtenerArbol(numArb)->buscar(parametro); 
	string ordenamiento = ord1 + ord2; 
	nodoAux->lista.insertar(posLibres->obtenerCola(0)->retornarValor(), ordenamiento);
}
//Las colas estan de 0 a 2, 

MediatorAlbum::~MediatorAlbum() {
}

