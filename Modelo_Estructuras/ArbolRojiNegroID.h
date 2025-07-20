#ifndef ARBOLROJINEGROID_H
#define ARBOLROJINEGROID_H

#include <string>

#include "Modelo_EstructuraNodos/NodoArbolRojiNegro.h"
#include "ArbolRojiNegro.h"
#include "Cola.h"

#include "Modelo_Estatico/Segmentar.h"

using namespace std;

template <class T>
class ArbolRojiNegroID : public ArbolRojiNegro<T, NodoArbolRojiNegro<T>>{

	public: 
		ArbolRojiNegroID();	//Constructor
		virtual ~ArbolRojiNegroID();	//Destructor
		bool insertar(T claveNueva, int pos);	//Insertar al arbol
    	string niveles(NodoArbolRojiNegro<T>* raiz);	//Recorre el arbol y lo guarda en un string para ser almacenado en el archivo
    	NodoArbolRojiNegro<T> *getRaiz();
	private:	
		void eliminarNodos(NodoArbolRojiNegro<T>* nodo);
};


template <class T>
ArbolRojiNegroID<T>::ArbolRojiNegroID() : ArbolRojiNegro<T, NodoArbolRojiNegro<T>>(){
	this->raiz = nullptr;
	
}

template <class T>
bool ArbolRojiNegroID<T>::insertar(T claveNueva, int pos){
	
	NodoArbolRojiNegro<T> *nuevo, *aux, *abuelo;
	
	if(claveNueva!=""){						//Clave valida
	
		if(this->raiz == nullptr){
			this->raiz = new NodoArbolRojiNegro<T>;
			this->raiz->clave = claveNueva;
			this->raiz->pos = pos;
			this->raiz->color = 0;
			this->raiz->izq = nullptr;
			this->raiz->der = nullptr;
			return 1;
		}else{
			nuevo = new NodoArbolRojiNegro<T>;		//Se crea el nuevo nodo
			nuevo->clave = claveNueva;
			nuevo->pos = pos;
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
string ArbolRojiNegroID<T>::niveles(NodoArbolRojiNegro<T>* raiz){
	
	if(raiz==nullptr) return "0-0-0";
	this->listNiveles = "";
	Cola<NodoArbolRojiNegro<T>*> cola;
		
	NodoArbolRojiNegro<T> *temp = nullptr, *vacio;
	vacio = new NodoArbolRojiNegro<T>;	//Nodo en caso de que un hijo sea null
	
	vacio->clave = "0";
	vacio->pos = 0;
	vacio->color = 0;
	vacio->izq = nullptr;
	vacio->der = nullptr;
	
	cola.insCola(raiz);

	while(!cola.colaVacia()){
		
		temp = cola.atenderCola();	//Toma el valor del hijo izq
		
		this->listNiveles += temp->clave+"-"+to_string(temp->pos)+"-"+to_string(temp->color);
		
		
		if (temp->izq != nullptr && temp->der != nullptr) {	// Si tiene los dos hijos se agrega con normalidad
            cola.insCola(temp->izq);
            cola.insCola(temp->der);
            
        } else if (temp->izq != nullptr) {	// Si solo tiene el hijo izquierdo, agrega un nodo "0-0-0|" a su derecha
            cola.insCola(temp->izq);
            cola.insCola(vacio);
            
        } else if (temp->der != nullptr) {	// Si solo tiene el hijo derecho, agrega un nodo "0-0-0|" a su izquierda
            cola.insCola(vacio); 
            cola.insCola(temp->der);
        
		} else if (temp!=vacio){
			cola.insCola(vacio);
			cola.insCola(vacio);
		}
		
		if(!cola.colaVacia()) this->listNiveles+="|";
	}
	
	return this->listNiveles;
}

template <class T>
void ArbolRojiNegroID<T>::eliminarNodos(NodoArbolRojiNegro<T>* nodo) {					//Funcion para el destructor
	if (nodo != nullptr) {
    	// Llamar recursivamente a la izquierda y derecha
    	eliminarNodos(nodo->izq);
    	eliminarNodos(nodo->der);
    
    	// Eliminar el nodo actual
    	delete nodo;
    }
}

template <class T>
NodoArbolRojiNegro<T>* ArbolRojiNegroID<T>::getRaiz(){
	return this->raiz;
}

template <class T>
ArbolRojiNegroID<T>::~ArbolRojiNegroID(){
	eliminarNodos(this->raiz);
	this->raiz=nullptr;
}

#endif



