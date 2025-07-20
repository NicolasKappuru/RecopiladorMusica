#include "SingletonPosLibres.h"
#include "Modelo_Estructuras/Cola.h"
#include "PosLibAlbDAO.h"
#include "PosLibCanDAO.h"
#include "PosLibArtDAO.h"
#include "PosLibLinkDAO.h"

using namespace std;

template<class T>
SingletonPosLibres<T>* SingletonPosLibres<T>::obtenerInstanciaPosLibres() {
    if (instancia == nullptr) {
        instancia = new SingletonPosLibres<T>();
    }
    return instancia;
}

template<class T>
Cola<T>* SingletonPosLibres<T>::obtenerCola(int indice) {
    if (indice >= 0 && indice < 4) {
        return colas[indice];
    }
    return nullptr;
}

template<class T>
void SingletonPosLibres<T>::establecerColas() {
    albDAO->crearArchivo(); 
	canDAO->crearArchivo(); 
	artDAO->crearArchivo();
	linkDAO->crearArchivo(); 
    
    colas[0] = albDAO->cargarCola(); 
    colas[1] = canDAO->cargarCola(); 
    colas[2] = artDAO->cargarCola(); 
    colas[3] = linkDAO->cargarCola(); 
    
    tamAlbum = albDAO->tamRegistros();
    tamCancion = canDAO->tamRegistros();
    tamArtista = artDAO->tamRegistros(); 
	tamLink = linkDAO->tamRegistros(); 
}

template<class T>
void SingletonPosLibres<T>::guardarColas() {
	albDAO->guardarCola(colas[0]);
	canDAO->guardarCola(colas[1]);
	artDAO->guardarCola(colas[2]);
	linkDAO->guardarCola(colas[3]); 
}

template<class T>
PosLibAlbDAO * SingletonPosLibres<T>::getterAlbDAO(){
	return albDAO; 
}

template<class T>
PosLibCanDAO * SingletonPosLibres<T>::getterCanDAO(){
	return canDAO; 
}

template<class T>
PosLibArtDAO * SingletonPosLibres<T>::getterArtDAO(){
	return artDAO; 
}

template<class T>
PosLibLinkDAO * SingletonPosLibres<T>::getterLinkDAO(){
	return linkDAO; 
}

template<class T>
int SingletonPosLibres<T>::getTamAlbum(){ //Ira al archivo de albunes
	return tamAlbum; 
}

template<class T>
int SingletonPosLibres<T>::getTamCancion(){ //Ira al archivo de canciones
	return tamCancion; 
}

template<class T>
int SingletonPosLibres<T>::getTamArtista(){ //Ira al archivo de artistas
	return tamArtista; 
}

template<class T>
int SingletonPosLibres<T>::getTamLink(){ //Ira al archivo de artistas
	return tamLink; 
}

template<class T>
void SingletonPosLibres<T>::sumTamAlbum(){
	tamAlbum++; 
}

template<class T>
void SingletonPosLibres<T>::sumTamCancion(){
	tamCancion++; 
}

template<class T>
void SingletonPosLibres<T>::sumTamArtista(){
	tamArtista++; 
}

template<class T>
void SingletonPosLibres<T>::sumTamLink(){
	tamLink++; 
}

// Aseg�rate de incluir las definiciones de las plantillas
template class SingletonPosLibres<int>;

