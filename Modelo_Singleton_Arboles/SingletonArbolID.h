#ifndef SINGLETONARBOLID_H
#define SINGLETONARBOLID_H
#include "../Modelo_Estructuras/ArbolRojiNegroID.h"
#include "../Modelo_Estructuras/ArbolRojiNegro.h"
#include <string>
#include "ModeloDAO_LinkArb/ArbolDAOID.h"
#include "ModeloDAO_Interfaces/DAO.h"
#include "Modelo_Estatico/Segmentar.h"

using namespace std; 

template<class T>
class SingletonArbolID {
	
private:
    static SingletonArbolID* instancia;
    ArbolRojiNegroID<T>* arboles[3]; // Arreglo de tama�o 3 para las ra�ces de los �rboles
    
	ArbolDAOID* arbolDAO;
	
	string auxID; 
	
    SingletonArbolID() { // Constructor privado que inicializa el arreglo vac�o
        for (int i = 0; i < 3; ++i) {
            arboles[i] = nullptr;
        }
        arbolDAO = new ArbolDAOID();
    }

	
public:
	
    static SingletonArbolID* obtenerInstanciaArbolID(); // M�todo est�tico que crea una instancia de la clase una �nica vez

    ArbolRojiNegroID<T>* obtenerArbol(int indice); // M�todo que retorna el nodo de la posici�n deseada

    void establecerArboles(); // M�todo que ingresa un apuntador a arbol en la posici�n deseada
    
    ArbolRojiNegroID<T> *crearArbol(int tipo);  // crear� el arbol desde el archivo (abrir programa)
    
    void actualizarArchivo();  // actualiza el archivo con el arbol seleccionado (cerrar programa)
    
    void setAuxID(string);
    
    string getAuxID(); 
};




// Inicializar el puntero est�tico a nullptr
template<class T>
SingletonArbolID<T>* SingletonArbolID<T>::instancia = nullptr;

#endif

