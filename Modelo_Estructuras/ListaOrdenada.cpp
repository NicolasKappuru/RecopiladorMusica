#include "ListaOrdenada.h"
#include <cmath>
#include <iostream>

using namespace std;
ListaOrdenada::ListaOrdenada() {
    cab = new nodo;
    cab->info = "0";
    cab->pos = 0;
    fin = cab;
    cab->sig = nullptr;
    tam = 0;
    
}

nodo* ListaOrdenada::getCab(){
	return cab;
}

nodo* ListaOrdenada::buscarNodo(int pos) {
    nodo* actual = cab->sig; // Empezamos desde el primer nodo después de la cabecera
    while (actual != nullptr) {
        if (actual->pos == pos) {
            return actual; // Retorna el nodo si la posición coincide
        }
        actual = actual->sig; // Avanza al siguiente nodo
    }
    return nullptr; // Retorna nullptr si no se encontró el nodo
}

int ListaOrdenada::getPos(nodo* n){
	return n->pos;
}

string ListaOrdenada::getInfo(nodo* n){
	return n->info;
}

bool ListaOrdenada::listaVacia() { return tam == 0; }
int ListaOrdenada::tamanoLista() { return tam; }
void ListaOrdenada::setTamano(int tamano) { this->tam = tamano; }

void ListaOrdenada::insertar(int posicion, string comparar) {

    nodo *nuevo = new nodo;
    nuevo->pos = posicion;
    nuevo->info = comparar;
    nuevo->sig = nullptr;


    // Si la lista está vacía o el nuevo nodo debe ir al inicio
    if (cab->sig == nullptr || cab->sig->info >= comparar) {
        nuevo->sig = cab->sig;
        cab->sig = nuevo;

        if (nuevo->sig == nullptr) {
            fin = nuevo;
        }

        tam++;
        return;
    }

    // Buscar la posición correcta para insertar
    nodo *temp = cab->sig;
    nodo *prev = cab;

    while (temp != nullptr && temp->info < comparar) {
        prev = temp;
        temp = temp->sig;
    }

    // Insertar en la posición correcta
    nuevo->sig = temp;
    prev->sig = nuevo;

    if (temp == nullptr) {
        fin = nuevo;
    }

    tam++;
}


void ListaOrdenada::insertarFinal(int posicion, string info) {
    nodo *nuevo = new nodo;
    nuevo->pos = posicion;
    nuevo->info = info;
    nuevo->sig = nullptr;
    fin->sig = nuevo;
    fin = nuevo;
}

void ListaOrdenada::eliminar(int pos) {
    if (cab == fin) return;
    nodo *temp = cab;
    
    while (temp->sig != nullptr && temp->sig->pos != pos ) {
        temp = temp->sig;
    }
    
    if (temp!=nullptr) {
        nodo *auxSig = temp->sig;
        temp->sig = auxSig->sig;
        if (temp->sig == nullptr) fin = temp;
        delete auxSig;
        tam--;
    }
}

string ListaOrdenada::recorrerLista() {
    if (cab == fin) return "0-0";
    string lista = "";
    nodo *aux = cab->sig;
    while (aux != nullptr) {
        lista += to_string(aux->pos) + "-" + aux->info;
        aux = aux->sig;
        if (aux != nullptr) lista += "-";
    }
    return lista;
}

int* ListaOrdenada::retornarArreglo() {
    if (tam == 0) {
        return nullptr; // Retorna un puntero nulo si la lista está vacía
    }

    int* arreglo = new int[tam]; // Crear el arreglo dinamico
    nodo* aux = cab->sig;
    int i = 0;

    while (aux != nullptr) {
        arreglo[i++] = aux->pos; // Guardar cada posicion en el arreglo
        aux = aux->sig;
    }

    return arreglo; // Retornar el puntero al arreglo
}


ListaOrdenada::~ListaOrdenada() {
    nodo *avn;
    while (cab != nullptr) {
        avn = cab;
        cab = cab->sig;
        delete avn;
    }
    fin = nullptr;
}


