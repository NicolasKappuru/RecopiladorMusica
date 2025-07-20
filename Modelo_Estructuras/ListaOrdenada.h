#ifndef LISTAORD_H
#define LISTAORD_H

#include <string>
using namespace std;

struct nodo {
    nodo *sig;
    int pos;
    string info;
};

class ListaOrdenada {
    nodo *cab, *fin;
    int tam;
    
public:
	
	nodo* getCab();
	int getPos(nodo* n);
	string getInfo(nodo* n);
	
    ListaOrdenada();
    bool listaVacia();
    nodo *buscarNodo(int pos);
    int tamanoLista();
    void setTamano(int tamano);
    void insertar(int posicion, string comparar);
    void insertarFinal(int posicion, string info);
    void eliminar(int pos);
    string recorrerLista();
    int * retornarArreglo(); 
    ~ListaOrdenada();
};

#endif // LISTAORD_H


