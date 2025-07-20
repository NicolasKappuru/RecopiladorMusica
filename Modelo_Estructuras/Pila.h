#ifndef PILA_H
#define PILA_H

template <class T>
struct nodoPila{
	T clave; 
	struct nodoPila *sig;
};

template <class T>
	class Pila{

		public:
    		Pila();

			~Pila();
    		void meter(T v);
    		T sacar();
    		bool vacia();
    		bool existeElemento(T valor); 
    		
		private:
			nodoPila<T> *cabeza, *z;
};

template <class T>
Pila<T>::Pila(){
    cabeza = new nodoPila<T>;
	z = new nodoPila<T>;
	cabeza->sig=z; 
	z->sig =z;
}

template <class T>
void Pila<T>::meter(T v){
	struct nodoPila<T> *t=new nodoPila<T>;
	t->clave = v;
	t->sig=cabeza->sig;
	cabeza->sig=t;
}

template <class T>
T Pila<T>::sacar(){
	T x;
	struct nodoPila<T> *t = cabeza->sig;
	cabeza->sig = t->sig; 
	x=t->clave;
	delete t;
	return x;
}

template <class T>
	bool Pila<T>::vacia(){
	return cabeza->sig == z;
}

template <class T>
bool Pila<T>::existeElemento(T valor) {
    nodoPila<T>* aux = cabeza->sig; // Primer nodo real (después de cabeza)

    while (aux != z) { // Recorrer hasta el nodo centinela 'z'
        if (aux->clave == valor) {
            return true; // Se encontró el valor en la pila
        }
        aux = aux->sig;
    }

    return false; // No se encontró el valor
}


template <class T>
Pila<T>::~Pila(){
	struct nodoPila<T> *t=cabeza;
	while (t!=z){
		cabeza=t;
		t=t->sig;
		delete cabeza;
	}
	delete z;
	cabeza=nullptr;
	z=nullptr;
}

#endif

