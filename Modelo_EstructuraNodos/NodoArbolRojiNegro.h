#ifndef NODOARBOLROJINEGRO_H
#define NODOARBOLROJINEGRO_H

template <class T>
struct NodoArbolRojiNegro {
    T clave;
    NodoArbolRojiNegro<T>* izq;
    NodoArbolRojiNegro<T>* der;
    bool color; // 0 negro, 1 rojo
    int pos;
};

#endif



