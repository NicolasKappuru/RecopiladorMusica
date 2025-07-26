#include "MediatorArtista.h"

#include "Modelo_Estructuras/Cola.h"
#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"

#include "ModeloDAO_Interfaces/DAO.h"
#include "ModeloDAO_Objetos/CancionDAOImpl.h"
#include "ModeloDAO_Objetos/ArtistaDAOImpl.h"

#include "Modelo_Estatico/CompletarCadena.h"
#include "Modelo_Estatico/CreacionID.h"
#include "Modelo_Estatico/Segmentar.h"

#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"


#include <iostream> // Para mensajes de consola, si es necesario
#include <string>
#include <sstream>

MediatorArtista::MediatorArtista(DAO* concreto) {
	posLibres = SingletonPosLibres<int>::obtenerInstanciaPosLibres();
	arbolID = SingletonArbolID<string>::obtenerInstanciaArbolID(); 
	arbolBusq = SingletonArbolBusq<string>::obtenerInstanciaArbolBusqueda(); 
	nodoAux = nullptr; 
	vista = VistaConsola(); 
	ArtistaDAO = concreto;
	cout << "Ey, mediator si tiene contructro " << endl;
	ArtistaDAO->crearArchivo(); //Aseguramos que el archivo exista
	cout << "Entramos a crear el archivo " << endl;

}

bool MediatorArtista::insercion() {
	
	int pos;
	
	string nombre_Art = vista.leerDato("[1] Inserte nombre: ");
	string nombreArtis_Art = vista.leerDato("[2] Inserte nombre artistico: ");
	string pais_Art = vista.leerDato("[3] Inserte pais: ");
	string instrumento_Art = vista.leerDato("[4] Inserte instrumento: ");
	string id_Art = CreacionID::crearID_Art(nombre_Art, nombreArtis_Art, pais_Art, instrumento_Art);
	
	arbolBusq->setNomArt(nombre_Art); //Ese lo guardamos en el auxiliar para el arbol canciones de un artista 
	
	if(verificacion(id_Art)) return false;  //Se debe verificar primero
	
	//Actualizar arbol de ID de artista
	arbolID->obtenerArbol(3)->insertar(id_Art,posLibres->obtenerCola(2)->retornarValor()); //Insertamos valor a arbol id
	arbolID->setAuxID(id_Art); 
	
	//Actualizar arbol de nombre
	arbolBusq->obtenerArbol(13)->insertar(nombre_Art);
	nodoAux = arbolBusq->obtenerArbol(13)->buscar(nombre_Art); 
	nodoAux->lista.insertar(posLibres->obtenerCola(2)->retornarValor(),nombreArtis_Art);
	
	//Actualizar arbol de consulta 4, y su mitad 14
	string parametro = arbolBusq->getGeneroAux() + instrumento_Art;
	
	
	actualizarArbCon(4,1,parametro,nombreArtis_Art,instrumento_Art); //Este guarda las canciones
	
	actualizarArbCon(14,2,parametro,nombreArtis_Art,instrumento_Art); //Este guarda los artistas
	
	//Completar el registro
	string cadena = CreacionID::combinarCadenasArt(id_Art,nombre_Art, nombreArtis_Art, pais_Art, instrumento_Art);
	string cadenaDef = CompletarCadena::rellenarConCeros(cadena,97);
	
	//Definir la posicion libre y subir el registro
	pos = definirPosicion(); 
	ArtistaDAO->modificarDato(pos,cadenaDef); 
	
	return true; 
}

bool MediatorArtista::eliminacion() {
	vista.mostrarInformacion("Digite el nombre del artista que desea eliminar");
	string porEliminar = vista.leerDato("[+] Eliminar a: ");
	
	nodoAux = arbolBusq->obtenerArbol(13)->buscar(porEliminar);

	if(nodoAux == nullptr){
		vista.mostrarInformacion("El artista no existe");
		return false; 
	} 

	int tamNodo = nodoAux->lista.tamanoLista();
	int *arreglo = nodoAux->lista.retornarArreglo();
	string registro, nomArt, inst, pais; 
	
	vista.mostrarInformacion("Digita el numero de la opcion que eliminaras");
	
	for(int i = 0; i<tamNodo; i++){
		registro = ArtistaDAO->leerDato(arreglo[i]);
		nomArt = Segmentar<string>::dividirCadenaPosicion(registro, 3);
		pais = Segmentar<string>::dividirCadenaPosicion(registro, 4);
		inst = Segmentar<string>::dividirCadenaPosicion(registro, 5);
		vista.mostrarInformacion("["+to_string(arreglo[i])+"] " + nomArt + " " + pais + " " + inst); 
	}
	
	int eliminar = vista.leerDatoInt("Eleccion: ");  
	
	////
	
	string clave = ArtistaDAO->leerDato(eliminar);
	arbolBusq->setNomArt(Segmentar<string>::dividirCadenaPosicion(clave,2));
	string idEliminar = Segmentar<string>::dividirCadenaPosicion(clave,1);
	nodoAux = arbolBusq->obtenerArbol(14)->buscar(arbolBusq->getNomArt());
	
	if(nodoAux->lista.listaVacia()!=true){
		vista.mostrarInformacion("Este artista pertenece a una cancion, no puedes eliminarlo");
	return false; 
	
	}
	
	ArtistaDAO->eliminarNposLibre(eliminar); //
	posLibres->obtenerCola(2)->insCola(eliminar); //Pasamos la posicion como libre
	
	//Actualizar
	arbolID->obtenerArbol(3)->eliminar(idEliminar); 
	
	
	arbolBusq->obtenerArbol(13)->eliminar(arbolBusq->getNomArt()); 
	
	Cola<NodoArbolBusquedas<string>*>* colaAux = arbolBusq->obtenerArbol(15)->inordenFull();
	NodoArbolBusquedas<string>* nodoAux;
	
	while(!colaAux->colaVacia()){
		nodoAux = colaAux->atenderCola();
		nodoAux->lista.eliminar(eliminar);
	}
	
	return true; 
}

bool MediatorArtista::actualizacion() {
	eliminacion();
	insercion(); 
	return true; 
}

bool MediatorArtista::verificacion(string comparar) {
    vista.mostrarInformacion("\nVerificando que no se repita el registro..." + comparar);
	if(arbolID->obtenerArbol(3)->buscar(comparar)==nullptr) return false; 
	arbolID->setAuxID(comparar); 
	return true; //Si se repite
}

int MediatorArtista::definirPosicion(){
	int pos = posLibres->obtenerCola(2)->atenderCola(); //La cola de artista 
	int tam = posLibres->getTamArtista(); 
	//pos 1       tam 0
	if(pos>tam){
		posLibres->obtenerCola(2)->insCola(pos+1); //2
		posLibres->sumTamArtista(); // tam 1
		return pos; 
	}else{
		return pos; 
	}
}

string MediatorArtista::formulario(string cop, int num){
	return "Not neccesary"; 
}

void MediatorArtista::setCadena(string a, string b, string c){
	vista.mostrarInformacion("Not neccesary"); 
}

void MediatorArtista::actualizarArbCon(int numArb,int numCola, string parametro, string ord1, string ord2){
	arbolBusq->obtenerArbol(numArb)->insertar(parametro);
	nodoAux = arbolBusq->obtenerArbol(numArb)->buscar(parametro); 
	string ordenamiento = ord1 + ord2; 
	nodoAux->lista.insertar(posLibres->obtenerCola(numCola)->retornarValor(), ordenamiento);
}
//Las colas estan de 0 a 2,
//Los arboles estan de 1 a 14 

MediatorArtista::~MediatorArtista() {
}

