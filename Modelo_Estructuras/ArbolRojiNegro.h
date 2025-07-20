#ifndef ARBOLROJINEGRO_H
#define ARBOLROJINEGRO_H
#include <iostream>

#include <string>
#include "Cola.h"
#include "Pila.h"
#include "Modelo_EstructuraNodos/NodoArbolRojiNegro.h"

using namespace std;

template <class T, class Nodo>
class ArbolRojiNegro{
	protected:  //esto garantiza que las clases hijas lo use directamente
	    Nodo* raiz;
	    string listNiveles; //Lista que guardara el arbol
	    		
		void ajuste(Nodo *nodo);		//Ajusta los colores de la eliminacion
		void trasplantar(Nodo* viejo, Nodo* nuevo);
		Nodo *buscarPadre(Nodo *nodo);	//Busca el padre de un nodo
		
		void leftRotate(Nodo* padre);	//Rota a la izquierda
		void rightRotate(Nodo* padre);	//Rota a la derecha
		
		void coloresIzq(Nodo *nodo, Nodo *padre, Nodo *abuelo);		//Casos para ajuste de colores por izquierda (insercion)
		void coloresDer(Nodo *nodo, Nodo *padre, Nodo *abuelo);		//Casos para ajuste de colores por derecha (insercion)
		
		void eliminarNodos(Nodo* nodo) {					//Funcion para el destructor
        	if (nodo != nullptr) {
            	// Llamar recursivamente a la izquierda y derecha
            	eliminarNodos(nodo->izq);
            	eliminarNodos(nodo->der);
            
            	// Eliminar el nodo actual
            	delete nodo;
	        }
    	}
    	
	public: 
		ArbolRojiNegro();		//Constructor
		virtual ~ArbolRojiNegro();	//Destructor
										
		void fabricar(Cola<Nodo*>* cola);	//Recibe una cola de Segmentar y fabrica el arbol desde el archivo
		bool eliminar(T clave);					//1 si lo elimina, 0 si no (no existe)
		Nodo * buscar(T clave);		//Busca una clave en el arbol
		
		Cola<Nodo*>* inorden(string comparar);		//Hace el recorrido inorden segun comparar (clave>=comparar)
		Cola<Nodo*>* inordenFull();					//Hace el recorrido inorden completo
		virtual string niveles(Nodo* raiz) = 0;	//Hace el recorrido por niveles para guardar el arbol
		
		Cola<Nodo*>* listInorden;
		
	
};
template<class T, class Nodo>
ArbolRojiNegro<T, Nodo>::ArbolRojiNegro(){
	this -> raiz = nullptr;
	this->listInorden = new Cola<Nodo*>();
};

template <class T, class Nodo>
Nodo* ArbolRojiNegro<T, Nodo>::buscarPadre(Nodo* nodo){
	
	Nodo *aux = raiz;
	
	if(raiz==nullptr || raiz==nodo){ //Si el arbol esta vacio o si se busca la raiz
		return nullptr;
	}
	
	while(aux!=nullptr){ //Mientras no sea nulo hara el ciclo por todo el arbol
	
		if((aux->izq == nodo) || (aux->der == nodo)){ //Si es alguno de los hijos retorna el nodo
			return aux;
		}
		
		if(nodo->clave < aux->clave){ //Si es menor se mueve a la izquierda
			aux = aux->izq;
		} else{
			aux = aux->der;	 //Si es mayor se mueve a la derecha
		}
		
	}
	
	return nullptr;
}

template <class T, class Nodo>
void ArbolRojiNegro<T, Nodo>::coloresIzq(Nodo *nodo, Nodo *padre, Nodo *abuelo){		//El padre esta a la izquierda del abuelo
	
	Nodo *tio = abuelo->der;
	
	if(tio!=nullptr && tio->color == 1){	//Si el padre y el tio son rojos (caso 1)
		padre->color = 0;
		tio->color = 0;
		abuelo->color = 1;
		nodo = abuelo;
	
	}else{
		if(nodo == padre->der){	//Caso 2
			nodo = padre;
			leftRotate(nodo);
		}
		padre->color = 0;	//Caso 3
		abuelo->color = 1;
		rightRotate(abuelo);
	
	}
	
}

template <class T, class Nodo>
void ArbolRojiNegro<T, Nodo>::coloresDer(Nodo *nodo, Nodo *padre, Nodo *abuelo){		//El padre esta a la derecha del abuelo
	
	Nodo *tio = abuelo->izq;
	
	if(tio != nullptr && tio->color == 1){	//Si el padre y el tio son rojos (Caso 1)
		padre->color = 0;
		tio->color = 0;
		abuelo->color = 1;
		nodo = abuelo;
	
	}else{
	
		if(nodo == padre->izq){	//Caso 2
			nodo = padre;
			rightRotate(nodo);
		}
		padre->color = 0;
		abuelo->color = 1;
		leftRotate(abuelo);
	}
	
}

template <class T, class Nodo>
Nodo* ArbolRojiNegro<T, Nodo>::buscar(T claveBuscar){
	
	Nodo *aux = raiz;
	
	if(raiz == nullptr) return nullptr;
	
	while(aux!=nullptr){
		if(aux->clave == claveBuscar) return aux;
		
		if(claveBuscar < aux->clave) aux = aux->izq;
		else aux = aux->der;
	}
	
	return nullptr;
	
}

template <class T, class Nodo>
void ArbolRojiNegro<T, Nodo>::leftRotate(Nodo *padre){
	
	Nodo *nodo = padre->der, *abuelo;
	
	padre->der = nodo->izq;
	nodo->izq = padre;
	
	if(padre == raiz) {
		
		raiz = nodo;
	}else{
		abuelo = buscarPadre(padre);
		if(abuelo->izq == padre) abuelo->izq = nodo;
		else abuelo->der = nodo;
	}
	
}

template <class T, class Nodo>
void ArbolRojiNegro<T, Nodo>::rightRotate(Nodo *padre){
	
	Nodo *nodo = padre->izq, *abuelo;
	
	padre->izq = nodo->der;
	nodo->der = padre;
	if(padre == raiz){
		raiz = nodo;
	}else{
		abuelo = buscarPadre(padre);
		if(abuelo->izq == padre) abuelo->izq = nodo;
		else abuelo->der = nodo;
	}
	
}

template <class T, class Nodo>
void ArbolRojiNegro<T, Nodo>::trasplantar(Nodo* viejo, Nodo* nuevo) {
    Nodo* padre = buscarPadre(viejo); // Obtener el padre del nodo viejo

    if (padre == nullptr) {
        raiz = nuevo;
    } else if (padre->izq == viejo) {
        padre->izq = nuevo;
    } else {
        padre->der = nuevo;
    }

}

template <class T, class Nodo>
void ArbolRojiNegro<T, Nodo>::ajuste(Nodo *nodo) {
    Nodo *padre = buscarPadre(nodo);
    Nodo *hermano;

    while (nodo != raiz && nodo->color == 0) {
        if (nodo == padre->izq) { // Si nodo es el hijo izquierdo
            hermano = padre->der;

            if (hermano != nullptr) { 
                // Caso 1: Hermano rojo
                if (hermano->color == 1) {
                    hermano->color = 0;
                    padre->color = 1;
                    leftRotate(padre);
                    hermano = padre->der;
                }

                // Caso 2: Ambos hijos del hermano son negros
                if ((hermano->izq == nullptr || hermano->izq->color == 0) &&
                    (hermano->der == nullptr || hermano->der->color == 0)) {
                    hermano->color = 1;
                    nodo = padre;
                } else {
                    // Caso 3: El hijo derecho del hermano es negro
                    if (hermano->der == nullptr || hermano->der->color == 0) {
                        if (hermano->izq != nullptr) { // Evitar acceso inv�lido
                            hermano->izq->color = 0;
                        }
                        hermano->color = 1;
                        rightRotate(hermano);
                        hermano = padre->der;
                    }

                    // Caso 4
                    hermano->color = padre->color;
                    padre->color = 0;
                    if (hermano->der != nullptr) {
                        hermano->der->color = 0;
                    }
                    leftRotate(padre);
                    nodo = raiz;
                }
            } else {
                nodo = padre; // Si no hay hermano, simplemente subir en el �rbol
            }

        } else { // Si nodo es el hijo derecho
            hermano = padre->izq;

            if (hermano != nullptr) {
                // Caso 1: Hermano rojo
                if (hermano->color == 1) {
                    hermano->color = 0;
                    padre->color = 1;
                    rightRotate(padre);
                    hermano = padre->izq;
                }

                // Caso 2: Ambos hijos del hermano son negros
                if ((hermano->izq == nullptr || hermano->izq->color == 0) &&
                    (hermano->der == nullptr || hermano->der->color == 0)) {
                    hermano->color = 1;
                    nodo = padre;
                } else {
                    // Caso 3: El hijo izquierdo del hermano es negro
                    if (hermano->izq == nullptr || hermano->izq->color == 0) {
                        if (hermano->der != nullptr) { // Evitar acceso inv�lido
                            hermano->der->color = 0;
                        }
                        hermano->color = 1;
                        leftRotate(hermano);
                        hermano = padre->izq;
                    }

                    // Caso 4
                    hermano->color = padre->color;
                    padre->color = 0;
                    if (hermano->izq != nullptr) {
                        hermano->izq->color = 0;
                    }
                    rightRotate(padre);
                    nodo = raiz;
                }
            } else {
                nodo = padre; // Si no hay hermano, simplemente subir en el �rbol
            }
        }

        padre = buscarPadre(nodo); // Actualizar el padre del nodo
    }

    if (nodo != nullptr) {
        nodo->color = 0; // Asegurar que la ra�z sea negra
    }
}


template <class T, class Nodo>
bool ArbolRojiNegro<T, Nodo>::eliminar(T clave) {
    Nodo *viejo, *nodoReemplazo;
    viejo = buscar(clave);

    if (viejo == nullptr) {
        return false; // Si no se encuentra el nodo, no hay nada que eliminar
    }

    // Determinar el nodo a eliminar f�sicamente
    bool colorOriginal = viejo->color;
    if (viejo->izq == nullptr) {
        nodoReemplazo = viejo->der;
        trasplantar(viejo, nodoReemplazo);
    } else if (viejo->der == nullptr) {
        nodoReemplazo = viejo->izq;
        trasplantar(viejo, nodoReemplazo);
    } else {
        // Encontrar el sucesor en orden (m�nimo del sub�rbol derecho)
        Nodo* sucesor = viejo->der;
        while (sucesor->izq != nullptr) {
            sucesor = sucesor->izq;
        }
        colorOriginal = sucesor->color;
        nodoReemplazo = sucesor->der;

        Nodo* padreSucesor = buscarPadre(sucesor);
        if (padreSucesor != viejo) {
            trasplantar(sucesor, sucesor->der);
            sucesor->der = viejo->der;
            if (sucesor->der) {
                Nodo* padreDer = buscarPadre(sucesor->der);
                if (padreDer) padreDer = sucesor; // Establecer el nuevo padre
            }
        }
        trasplantar(viejo, sucesor);
        sucesor->izq = viejo->izq;
        Nodo* padreIzq = buscarPadre(sucesor->izq);
        if (padreIzq) padreIzq = sucesor; // Establecer el nuevo padre
        sucesor->color = viejo->color;
    }

    delete viejo;

    // Si el nodo eliminado era negro, aplicamos la correcci�n de colores
    if (colorOriginal == 0) {
        ajuste(nodoReemplazo);
    }

    return true;
}


template <class T, class Nodo>
void ArbolRojiNegro<T, Nodo>::fabricar(Cola<Nodo*> *cola){
	if(cola->colaVacia()) return;
	
	Nodo *nodoCola = cola->atenderCola();
	if(nodoCola->clave=="0") return;
	this->raiz = nodoCola;								//Se establece la raiz
	
	int cont = 0;
	Nodo *aux = nullptr;
	Cola<Nodo*> *colaAux = new Cola<Nodo*>();
	
	colaAux->insCola(raiz);

	while(!cola->colaVacia()){

		nodoCola = cola->atenderCola();	//Obtenemos el nodo de la cola
		if(cont == 0) aux = colaAux->atenderCola();	//Se saca el nodo de la cola de los auxiliares que actuara de padre
		
		if(cont == 0){ //Asigna hijo izquierdo
			if(nodoCola->clave != "0"){
				aux->izq = nodoCola;	//Si el hijo no es nulo, se asigna
			}
		}else{		//Asigna el hijo derecho
			if(nodoCola->clave != "0"){
				aux->der = nodoCola; //Si el hijo no es nulo, se asigna
			}
		}
		colaAux->insCola(nodoCola);	//Se inserta en la cola auxiliar el nodo al que se le asignaran los hijos posteriormente
		
		cont = 1 - cont;	//Varia entre hijo izq y der
	}

	return;
}

template <class T, class Nodo>
Cola<Nodo*>* ArbolRojiNegro<T, Nodo>::inorden(string comparar){
	
	if(raiz!=nullptr){	//Mientras el arbol no este vacio
		
		
		Nodo *temp = raiz;			//Inicia en la raiz		
		Pila<Nodo*> pila;
		
		do{
			while(temp!=nullptr){				//Mientras no se vaya a la posicion 0
				pila.meter(temp);		//Guardamos su posicion en la pila
				temp = temp->izq;		//Avanzamos por su izquierda
			}
			
			temp = pila.sacar();		//Si se volvio nulo entonces toma el ultimo valor de la pila
			
			if(temp->clave>=comparar){
				listInorden->insCola(temp);	//Guardamos el nodo que indicaba la pila
			}
			
			
			temp = temp->der;		//Se mueve a la derecha por si tiene hijos derechos
			
		}while(!pila.vacia() || temp!=nullptr);
	}
	
	return listInorden;
}

template <class T, class Nodo>
Cola<Nodo*>* ArbolRojiNegro<T, Nodo>::inordenFull(){
	
	if(raiz!=nullptr){	//Mientras el arbol no este vacio
		
		
		Nodo *temp = raiz;			//Inicia en la raiz		
		Pila<Nodo*> pila;
		
		do{
			while(temp!=nullptr){				//Mientras no se vaya a la posicion 0
				pila.meter(temp);		//Guardamos su posicion en la pila
				temp = temp->izq;		//Avanzamos por su izquierda
			}
			
			temp = pila.sacar();		//Si se volvio nulo entonces toma el ultimo valor de la pila
			
			listInorden->insCola(temp);	//Guardamos el nodo que indicaba la pila			
			
			temp = temp->der;		//Se mueve a la derecha por si tiene hijos derechos
			
		}while(!pila.vacia() || temp!=nullptr);
	}
	
	return listInorden;
}

template <class T, class Nodo>
ArbolRojiNegro<T, Nodo>::~ArbolRojiNegro(){
	eliminarNodos(raiz);
	raiz=nullptr;
}

#endif
