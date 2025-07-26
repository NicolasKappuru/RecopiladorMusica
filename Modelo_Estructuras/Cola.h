#ifndef COLA_H     
#define COLA_H 

using namespace std;

template <class T>
struct nodoCola {
    T dato; 
    nodoCola* sig;
};

template <class T>
class Cola {
public: 
    Cola() {
        cab = fin = new nodoCola<T>;
        fin->sig = nullptr;
    }

    void insCola(T i);
    T atenderCola();
    T retornarValor(); 
    bool colaVacia();
    bool existeElemento(T valor);
    ~Cola();

private:
    nodoCola<T>* cab; // Apunta al nodo cabecera
    nodoCola<T>* fin; // Apunta al �ltimo nodo
};

template <class T>
void Cola<T>::insCola(T i) {
    nodoCola<T>* nuevo = new nodoCola<T>;
    nuevo->dato = i;
    nuevo->sig = nullptr;

    fin->sig = nuevo; //Conectar el �ltimo nodo con el nuevo
    fin = nuevo;      //Actualizar el puntero fin al nuevo nodo
}

template <class T>
T Cola<T>::atenderCola() {
    if (colaVacia()) {
        return T();
    }

    nodoCola<T>* aux = cab->sig; //Primer nodo real (despu�s del cabecera)
    T valor = aux->dato;
    cab->sig = aux->sig; //Avanzar la cabecera

    if (aux == fin) { 	//Si se atiende el �ltimo nodo
        fin = cab;     // Restablecer fin a la cabecera
    }

    delete aux; // Liberar memoria del nodo atendido
    return valor;
}

template <class T>
T Cola<T>::retornarValor() {
    if (colaVacia()) {
        return T(); // Retornar un valor por defecto si la cola est� vac�a
    }
    return cab->sig->dato; // Retornar el dato del primer nodo real
}


template <class T>
bool Cola<T>::colaVacia() {
    return cab == fin; //cab y fin apuntan al mismo nodo inicial
}

template <class T>
bool Cola<T>::existeElemento(T valor) {
    nodoCola<T>* aux = cab->sig; // Primer nodo real (despu�s del cabecera)
    
    while (aux != nullptr) {
        if (aux->dato == valor) {
            return true; // Si el valor ya est� en la cola, retornamos true
        }
        aux = aux->sig;
    }

    return false; // Si no se encuentra el valor, retornamos false
}


template <class T>
Cola<T>::~Cola() {
    while (!colaVacia()) {
        atenderCola();
    }
    delete cab; //Liberar el nodo inicial
}

#endif
