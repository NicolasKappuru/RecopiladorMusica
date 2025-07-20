#ifndef SINGLETONPOSLIBRES_H
#define SINGLETONPOSLIBRES_H
#include "Modelo_Estructuras/Cola.h"

#include "PosLibAlbDAO.h"
#include "PosLibCanDAO.h"
#include "PosLibArtDAO.h"
#include "PosLibLinkDAO.h"

using namespace std; 

//Este arreglo de colas, es para cada una de las colas de posLibres
//[0] para Albunes  [1] para Canciones  [2] para Artistas
template<class T>
class SingletonPosLibres {
private:
    static SingletonPosLibres* instancia;
    Cola<T>* colas[4]; // Arreglo de tama�o 3 para apuntadores a las colas

    SingletonPosLibres() { // Constructor privado que inicializa el arreglo vac�o
        for (int i = 0; i < 4; ++i) {
            colas[i] = nullptr;
        }
    }
    
    PosLibAlbDAO *albDAO; //Este sera el dao para las poslibres de album
    PosLibCanDAO *canDAO; //Este sera el dao para las poslibres de cancion
    PosLibArtDAO *artDAO; //Este para las de artista
	PosLibLinkDAO *linkDAO; //Este es para los links
	int tamAlbum; 
	int tamArtista; 
	int tamCancion; 
	int tamLink; 
	
public:
    static SingletonPosLibres* obtenerInstanciaPosLibres(); // Metodo estatico que crea una instancia de la clase una �nica vez
    Cola<T>* obtenerCola(int indice); // Metodo que retorna la cola de la posici�n deseada
    void establecerColas(); // Metodo que ingresa una cola en la posici�n deseada
	void guardarColas(); //Metodo que guardara las colas al finalizar el programa
	PosLibAlbDAO * getterAlbDAO(); //Devuelve el archivo.
	PosLibCanDAO * getterCanDAO(); //Devuelve el archivo.
	PosLibArtDAO * getterArtDAO(); //Devuelve el archivo.
	PosLibLinkDAO * getterLinkDAO(); //Devuelve el archivo.

	int getTamAlbum();//Siempre tendremos un valor del tama�o del archivo.
	void sumTamAlbum();//Siempre tendremos que sumar en uno cuando se agrege al programa info  
	int getTamCancion();//Siempre tendremos un valor del tama�o del archivo.
	void sumTamCancion();//Siempre tendremos que sumar en uno cuando se agrege al programa info  
	int getTamArtista();//Siempre tendremos un valor del tama�o del archivo.
	void sumTamArtista();//Siempre tendremos que sumar en uno cuando se agrege al programa info  
	int getTamLink();//Siempre tendremos un valor del tama�o del archivo.
	void sumTamLink();//Siempre tendremos que sumar en uno cuando se agrege al programa info  

};

// Inicializar el puntero est�tico a nullptr
template<class T>
SingletonPosLibres<T>* SingletonPosLibres<T>::instancia = nullptr;

#endif

