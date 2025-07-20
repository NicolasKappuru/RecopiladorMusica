#ifndef SINGLETONARBOLBUSQ_H
#define SINGLETONARBOLBUSQ_H
#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"
#include "Modelo_Estructuras/ArbolRojiNegroBusquedas.h"
#include "ModeloDAO_LinkArb/ArbolDAOBusquedas.h"
#include <string>

using namespace std;

template<class T>
class SingletonArbolBusq {
private:
    static SingletonArbolBusq* instancia;
    
	ArbolRojiNegroBusquedas<T>* arboles[15]; // Arreglo de tama�o 13 para los �rboles
    
    ArbolDAOBusquedas *arbolDAO;
    string nomArt; 
    string coverArtAux; 
    string generoAux; 

    SingletonArbolBusq() {		//contructor que inciializa el arreglo vac�o
        for (int i = 0; i < 15; ++i) {
            arboles[i] = nullptr;
        }
        arbolDAO = new ArbolDAOBusquedas();
    }

public:
    static SingletonArbolBusq* obtenerInstanciaArbolBusqueda();  //m�todo est�tico que crea una �nica instancia de la clase

    ArbolRojiNegroBusquedas<T>* obtenerArbol(int indice);	// M�todo que retorna el nodo del arbol en l�a posici�n deseada

    void establecerArbol(); // M�todo que guarda el nodo del arbol en la posici�n deseada
    
    ArbolRojiNegroBusquedas<T> *crearArbol(int tipo);  // crear� el arbol desde el archivo (abrir programa)
    
    void actualizarArchivo();  // actualiza el archivo con el arbol seleccionado (cerrar programa)

	string getNomArt(); 
	void setNomArt(string); 
	
	string getCoverArtAux(); 
	void setCoverArtAux(string); 

	string getGeneroAux();
	void setGeneroAux(string);
};

// Inicializar el puntero est�tico a nullptr
template<class T>
SingletonArbolBusq<T>* SingletonArbolBusq<T>::instancia = nullptr;

#endif
