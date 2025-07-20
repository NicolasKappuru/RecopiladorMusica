#include "SingletonArbolBusq.h"
#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm> 

using namespace std;

template <class T>
SingletonArbolBusq<T>* SingletonArbolBusq<T>::obtenerInstanciaArbolBusqueda() {
    if (instancia == nullptr) {
        instancia = new SingletonArbolBusq<T>();
    }
    return instancia;
}

template <class T>
ArbolRojiNegroBusquedas<T>* SingletonArbolBusq<T>::obtenerArbol(int indice) {
    if (indice >= 1 && indice <= 15) {
        return arboles[indice-1];
    }
    return nullptr;
}

template <class T>
void SingletonArbolBusq<T>::establecerArbol() {

    arbolDAO->crearArchivo();

    arbolDAO->leerArchivo();
	
	nomArt = ""; 
	coverArtAux = "Null";
	generoAux = "Null"; 
	
	arboles[0] = crearArbol(1);		//Consulta 1
	arboles[1] = crearArbol(2);		//Consulta 2
	arboles[2] = crearArbol(3);		//Consulta 3
	arboles[3] = crearArbol(4);		//Consulta 4 Cancion
	arboles[4] = crearArbol(5);		//Consulta 5
	arboles[5] = crearArbol(6);		//Consulta 6
	arboles[6] = crearArbol(7);		//Consulta 7
	arboles[7] = crearArbol(8);		//Consulta 8
	arboles[8] = crearArbol(9);		//Consulta 9
	arboles[9] = crearArbol(10);	//Consulta 10
	arboles[10] = crearArbol(11);	//Consulta Nombre Album
	arboles[11] = crearArbol(12);	//Consulta Nombre Cancion
	arboles[12] = crearArbol(13);	//Consulta Nombre Artista
	arboles[13] = crearArbol(14);	//Consulta Lista Canciones de Artista
	arboles[14] = crearArbol(15);	//Consulta 4 Artista

}

template <class T>
ArbolRojiNegroBusquedas<T>* SingletonArbolBusq<T>::crearArbol(int tipo){
	
	string* arrLineas = arbolDAO->getLineas();	
	
	string arbolArch = arrLineas[tipo- 1];
	
    Cola<NodoArbolBusquedas<T>*>* colaLinea = Segmentar<T>::dividirCadenaNodoBusq(arbolArch);
	
	ArbolRojiNegroBusquedas<T>* arbol = new ArbolRojiNegroBusquedas<T>();
	
    arbol->fabricar(colaLinea);  //fabrica el arbol desde la cola de nodos con strings del archivo que tiene colaLinea
	return arbol; 
}

template <class T>
void SingletonArbolBusq<T>::actualizarArchivo(){
	
	ArbolRojiNegroBusquedas<T> *arb1 = obtenerArbol(1);
	ArbolRojiNegroBusquedas<T> *arb2 = obtenerArbol(2);
	ArbolRojiNegroBusquedas<T> *arb3 = obtenerArbol(3);
	ArbolRojiNegroBusquedas<T> *arb4 = obtenerArbol(4);
	ArbolRojiNegroBusquedas<T> *arb5 = obtenerArbol(5);
	ArbolRojiNegroBusquedas<T> *arb6 = obtenerArbol(6);
	ArbolRojiNegroBusquedas<T> *arb7 = obtenerArbol(7);
	ArbolRojiNegroBusquedas<T> *arb8 = obtenerArbol(8);
	ArbolRojiNegroBusquedas<T> *arb9 = obtenerArbol(9);
	ArbolRojiNegroBusquedas<T> *arb10 = obtenerArbol(10);
	ArbolRojiNegroBusquedas<T> *arb11 = obtenerArbol(11);
	ArbolRojiNegroBusquedas<T> *arb12 = obtenerArbol(12);
	ArbolRojiNegroBusquedas<T> *arb13 = obtenerArbol(13);
	ArbolRojiNegroBusquedas<T> *arb14 = obtenerArbol(14);
	ArbolRojiNegroBusquedas<T> *arb15 = obtenerArbol(15);

	string arbol1 = arb1->niveles(arb1->getRaiz());
	string arbol2 = arb2->niveles(arb2->getRaiz());
	string arbol3 = arb3->niveles(arb3->getRaiz());
	string arbol4 = arb4->niveles(arb4->getRaiz());
	string arbol5 = arb5->niveles(arb5->getRaiz());
	string arbol6 = arb6->niveles(arb6->getRaiz());
	string arbol7 = arb7->niveles(arb7->getRaiz());
	string arbol8 = arb8->niveles(arb8->getRaiz());
	string arbol9 = arb9->niveles(arb9->getRaiz());
	string arbol10 = arb10->niveles(arb10->getRaiz());
	string arbol11 = arb11->niveles(arb11->getRaiz());
	string arbol12 = arb12->niveles(arb12->getRaiz());
	string arbol13 = arb13->niveles(arb13->getRaiz());
	string arbol14 = arb14->niveles(arb14->getRaiz());
	string arbol15 = arb15->niveles(arb15->getRaiz());

	arbolDAO->actualizarArch(arbol1, arbol2, arbol3, arbol4, arbol5, arbol6, arbol7, arbol8, arbol9, arbol10, arbol11, arbol12, arbol13, arbol14, arbol15); //se supoje que esto accede al archivo y le mete el arbol dado
}


template <class T>
void SingletonArbolBusq<T>::setNomArt(string nom){
	nomArt = nom; 
}
	
	template <class T>
string SingletonArbolBusq<T>::getNomArt(){
	return nomArt; 
}

template <class T>
void SingletonArbolBusq<T>::setCoverArtAux(string cover){
	coverArtAux = cover; 
}
	
	template <class T>
string SingletonArbolBusq<T>::getCoverArtAux(){
	return coverArtAux; 
}

template <class T>
void SingletonArbolBusq<T>::setGeneroAux(string genero){
	generoAux = genero; 
}
	
	template <class T>
string SingletonArbolBusq<T>::getGeneroAux(){
	return generoAux; 
}	

// Asegurate de incluir las definiciones de las plantillas
template class SingletonArbolBusq<string>;
template class ArbolRojiNegroBusquedas<string>;
template class ArbolRojiNegro<string, NodoArbolBusquedas<string>>;
template class NodoArbolBusquedas<string>;
template class Segmentar<string>;
