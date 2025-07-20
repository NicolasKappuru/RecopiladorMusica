#ifndef NODOARBOLBUSQUEDAS_H
#define NODOARBOLBUSQUEDAS_H

#include "Modelo_Estructuras/ListaOrdenada.h"

template <class T>
struct NodoArbolBusquedas{
	T clave;
    NodoArbolBusquedas<T>* izq;
    NodoArbolBusquedas<T>* der;
    bool color; // 0 negro, 1 rojo
    ListaOrdenada lista;
};

#endif

