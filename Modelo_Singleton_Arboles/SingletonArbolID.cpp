#include "SingletonArbolID.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm> 
#include "Modelo_Estructuras/Cola.h"
#include "ModeloDAO_LinkArb/ArbolDAOID.h"
#include "Modelo_Estructuras/ArbolRojiNegro.h"
#include "Modelo_Estructuras/ArbolRojiNegroID.h"
#include "Modelo_EstructuraNodos/NodoArbolRojiNegro.h"
#include "Modelo_Estatico/Segmentar.h"

using namespace std;


template<class T>
SingletonArbolID<T>* SingletonArbolID<T>::obtenerInstanciaArbolID() {
    if (instancia == nullptr) {
        instancia = new SingletonArbolID<T>();
    }
    return instancia;
}

template<class T>
ArbolRojiNegroID<T>* SingletonArbolID<T>::obtenerArbol(int indice) { // recibe un entero y retorna el string seg�n las posici�n dada (1 alb, 2 can o 3art) seg�n el �rbol que se quiera
    if (indice >= 1 && indice <= 3) {
        return arboles[indice-1];
    }
    return nullptr;
}

template<class T>
void SingletonArbolID<T>::establecerArboles() { // mete el apountador a arbol al arreglo
	
	arbolDAO->crearArchivo();
	
	arboles[0] = crearArbol(1);
	arboles[1] = crearArbol(2);
	arboles[2] = crearArbol(3);
	auxID = ""; 	
}

template<class T>
ArbolRojiNegroID<T>* SingletonArbolID<T>::crearArbol(int tipo) { // crea el arbol del tipo que se quiera (seg�n el entero 1 alb, 2 can o 3art) desde el archivo
	
	string arbolArch = arbolDAO->leerDato(tipo);
	
    Cola<NodoArbolRojiNegro<T>*>* colaLinea = Segmentar<T>::dividirCadenaNodoID(arbolArch);
	
	ArbolRojiNegroID<T>* arbol = new ArbolRojiNegroID<T>();
    arbol->fabricar(colaLinea);  //fabrica el arbol desde la cola de nodos con strings del archivo que tiene colaLinea
    
	return arbol; 
}

template <class T>
void SingletonArbolID<T>::setAuxID(string id){
	auxID = id; 
}

template <class T>
string SingletonArbolID<T>::getAuxID(){
	return auxID; 
}

template <class T>
void SingletonArbolID<T>::actualizarArchivo(){
	
	ArbolRojiNegroID<T> *arb1 = obtenerArbol(1);
	ArbolRojiNegroID<T> *arb2 = obtenerArbol(2);
	ArbolRojiNegroID<T> *arb3 = obtenerArbol(3);
	
	string arbol1 = arb1->niveles(arb1->getRaiz());
	string arbol2 = arb2->niveles(arb2->getRaiz());
	string arbol3 = arb3->niveles(arb3->getRaiz());
	
	arbolDAO->actualizarArch(arbol1, arbol2, arbol3); //se supoje que esto accede al archivo y le mete el arbol dado
	
}


//  definiciones de las plantillas
template class SingletonArbolID<string>;
template class ArbolRojiNegroID<string>;
template class ArbolRojiNegro<string, NodoArbolRojiNegro<string>>;
template class NodoArbolRojiNegro<string>;
template class Segmentar<string>;

