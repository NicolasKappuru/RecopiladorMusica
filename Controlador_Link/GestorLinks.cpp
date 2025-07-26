#include "GestorLinks.h"

#include "ModeloDAO_Interfaces/DAO.h"
#include "ModeloDAO_LinkArb/LinkDAO.h"

#include "Modelo_Estatico/CreacionID.h"
#include "Modelo_Estatico/CompletarCadena.h"

#include "Modelo_PosicionesLibres/SingletonPosLibres.h"


#include <iostream> // Para mensajes de consola, si es necesario
#include <string>

GestorLinks::GestorLinks(DAO* concreto) {
	posLibres = SingletonPosLibres<int>::obtenerInstanciaPosLibres();
	vista = VistaConsola(); 
	LinkDAO = concreto;	
	LinkDAO->crearArchivo(); // Asegurarse de que el archivo se crea al iniciar el gestor
	arregloPos = "";
}

string GestorLinks::insercion(){
	vista.mostrarEtiqueta("Gestor de links");
		
	creacionRegistro("Spotify");
	creacionRegistro("Amazon");
	creacionRegistro("Youtube Music");
	creacionRegistro("Deezer");
	creacionRegistro("Itunes");
	
	return arregloPos; 
}

bool GestorLinks::eliminacion() {
    vista.mostrarInformacion("Mediador links va a eleminiar");
   	return true; 
}

int GestorLinks::definirPosicion(){
	int pos = posLibres->obtenerCola(3)->atenderCola(); //La cola de album 
	int tam = posLibres->getTamLink(); 
	if(pos>tam){
		posLibres->obtenerCola(3)->insCola(pos+1);
		posLibres->sumTamLink(); 
		return pos; 
	}else{
		return pos; 
	}
}

void GestorLinks::creacionRegistro(string platform){

	int eleccion; 
	string link; 
	string plataforma; 
	
	vista.mostrarInformacion("\nIngrese el numero para saber si tiene el link de la plataforma: [1]SI  [0]NO");
	eleccion = vista.leerDatoInt("Tiene link para la plataforma [" + platform + "] ?: "); 
	if(eleccion==1){
		plataforma = platform; 
		link = vista.leerDato("Ingrese el link: ");
		string cadena = CreacionID::combinarCadenasLink(plataforma,link); 
		string cadenaDef = CompletarCadena::rellenarConCeros(cadena,116); //Poner tama�o original de la cadena
		int pos = definirPosicion();
		arregloPos += to_string(pos) + "-";
		if(platform == "Itunes") arregloPos.pop_back();
		LinkDAO->modificarDato(pos,cadenaDef); 
	}else{
		arregloPos += "0-";
		if(platform == "Itunes") arregloPos.pop_back();
	}  
}

string GestorLinks::getArregloPos(){
	return arregloPos; 
}

void GestorLinks::setArregloPos(string cadena){
	arregloPos = cadena;
}

GestorLinks::~GestorLinks() {
}

