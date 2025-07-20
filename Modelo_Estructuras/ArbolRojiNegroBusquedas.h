#ifndef ARBOLROJINEGROBUSQUEDAS_H
#define ARBOLROJINEGROBUSQUEDAS_H

#include <string>

#include "ArbolRojiNegro.h"
#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"
#include "Cola.h"
#include "ListaOrdenada.h"

#include "Modelo_Estatico/Segmentar.h"

template <class T>
class ArbolRojiNegroBusquedas : public ArbolRojiNegro<T, NodoArbolBusquedas<T>>{

	public: 
		ArbolRojiNegroBusquedas();	//Constructor
		virtual ~ArbolRojiNegroBusquedas();	//Destructor
    	virtual std::string niveles(NodoArbolBusquedas<T>* raiz);
    	ListaOrdenada getLista(NodoArbolBusquedas<T>* nodo);
    	NodoArbolBusquedas<T>* getRaiz();
    	bool insertar(T claveNueva);
    	
    private:
    	void eliminarNodos(NodoArbolBusquedas<T>* nodo);
		
};
template <class T>
ListaOrdenada ArbolRojiNegroBusquedas<T>:: getLista(NodoArbolBusquedas<T>* nodo){
	return nodo -> lista;
}

template <class T>
NodoArbolBusquedas<T>* ArbolRojiNegroBusquedas<T>::getRaiz(){
	return this->raiz;
}

template <class T>
ArbolRojiNegroBusquedas<T>::ArbolRojiNegroBusquedas() : ArbolRojiNegro<T, NodoArbolBusquedas<T>>() {
	this->raiz = nullptr;
	
}
template <class T>



bool ArbolRojiNegroBusquedas<T>::insertar(T claveNueva){
	
	 NodoArbolBusquedas<T> *nuevo, *aux, *abuelo;
	
	if(claveNueva!=""){						//Clave valida
		if(this->raiz == nullptr){

			this->raiz = new  NodoArbolBusquedas<T>;
			this->raiz->clave = claveNueva;
			this->raiz->color = 0;
			this->raiz -> izq = nullptr;
			this->raiz -> der = nullptr;
			
			return 1;
		}else{
			nuevo = new NodoArbolBusquedas<T>;		//Se crea el nuevo nodo
			nuevo->clave = claveNueva;
			nuevo->color = 1;
			nuevo->izq = nullptr;
			nuevo->der = nullptr;
			
			aux = this->raiz;		//Aux para recorrer el arbol (hace de nodo padre)
			
			while(aux!=nullptr){
				if(claveNueva < aux->clave){			//Se mueve a la izq
					if(aux->izq == nullptr){
						aux->izq = nuevo;
						break;
					} 
					aux = aux->izq;
	
				}else if(claveNueva > aux->clave){	//Se mueve a la der
					if(aux->der == nullptr){
						aux->der = nuevo;
						break;
					} 
					aux = aux->der;
				}else return 0;					//Clave repetida
			}
			
			while (nuevo!=this->raiz && aux->color==1){
				
    			// Verificar si hay un conflicto entre aux y nuevo
    			aux = this->buscarPadre(nuevo);
				abuelo = this->buscarPadre(aux);
				
				if (aux == abuelo->izq) {
					this->coloresIzq(nuevo, aux, abuelo);
        		} else if (aux == abuelo->der) {
            		this->coloresDer(nuevo, aux, abuelo);
        		}
			
			}
            
            this->raiz->color = 0;
            
            return 1;
		}
	}
	return 0;
}

template <class T>
string ArbolRojiNegroBusquedas<T>::niveles(NodoArbolBusquedas<T> *raiz){
	
	
	if(raiz==nullptr) return "0-0-0-0-0"; //CLAVE- COLOR - TAMLISTA - 
	
	this->listNiveles = "";

	Cola<NodoArbolBusquedas<T>*> cola;
		
	NodoArbolBusquedas<T> *temp = nullptr, *vacio;
	vacio = new NodoArbolBusquedas<T>;	//Nodo en caso de que un hijo sea null
	
	vacio->clave = "0";
	vacio->color = 0;
	vacio->izq = nullptr;
	vacio->der = nullptr;
	cola.insCola(raiz);
	
	
	while(!cola.colaVacia()){
		
		temp = cola.atenderCola();	//Toma el valor del hijo izq
		
		this->listNiveles += temp->clave+"-"+to_string(temp->color)+"-";
		
		if(temp == vacio){
			this->listNiveles+="0-0-0";
		} 		
		else{
			this->listNiveles += to_string (temp->lista.tamanoLista())+ "-" + temp->lista.recorrerLista();
		} 
		
		
		if (temp->izq != nullptr && temp->der != nullptr) {	// Si tiene los dos hijos se agrega con normalidad
            cola.insCola(temp->izq);
            cola.insCola(temp->der);
            
            
        } else if (temp->izq != nullptr) {	// Si solo tiene el hijo izquierdo, agrega un nodo "0-0-0|" a su derecha
            cola.insCola(temp->izq);
            cola.insCola(vacio);
            
        } else if (temp->der != nullptr) {	// Si solo tiene el hijo derecho, agrega un nodo "0-0-0|" a su izquierda
            cola.insCola(vacio); 
            cola.insCola(temp->der);
        
		} else if(temp != vacio){
			cola.insCola(vacio);
			cola.insCola(vacio);
			
		}
		if(!cola.colaVacia()) this->listNiveles+="|";
	}
		
	return this->listNiveles;
}


template <class T>
void ArbolRojiNegroBusquedas<T>::eliminarNodos(NodoArbolBusquedas<T>* nodo) {					//Funcion para el destructor
	if (nodo != nullptr) {
    	// Llamar recursivamente a la izquierda y derecha
    	eliminarNodos(nodo->izq);
    	eliminarNodos(nodo->der);
    
    	// Eliminar el nodo actual
    	delete nodo;
    }
}

template <class T>
ArbolRojiNegroBusquedas<T>::~ArbolRojiNegroBusquedas(){
	eliminarNodos(this->raiz);
	this->raiz=nullptr;
}




#endif



