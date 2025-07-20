#ifndef SEGMENTAR_H
#define SEGMENTAR_H
#include <iostream>
#include <string>
#include <sstream>

#include "Modelo_EstructuraNodos/NodoArbolRojiNegro.h"
#include "Modelo_EstructuraNodos/NodoArbolBusquedas.h"
#include "Modelo_Estructuras/Cola.h"
#include "Modelo_Estructuras/ListaOrdenada.h"

using namespace std;

template <class T>
class Segmentar{
	public:
		
		static int dividirCadenaGuionInt(const string &linea){
            istringstream ss1(linea);
            string segmento = ""; 
            int cont = 0;

            while(getline(ss1, segmento, '-')){
            	if(segmento!="0")
                	cont++;
            }

            return cont;
        }
		
		static int* dividirCadenaGuion(const string &linea, int tamArreglo){
            int *arr = new int[tamArreglo];
            istringstream ss1(linea);
            string segmento = ""; 
            int cont = 0;

            while(getline(ss1, segmento, '-') && cont<tamArreglo){
                arr[cont] = stoi(segmento);
                cont++;
            }

            return arr;
        }
        
		//nombre|apellido|
		static string dividirCadenaPosicion(const string &linea, int posicion){
			
			// Usar stringstream para dividir la l�nea
    		istringstream ss(linea);
    		string segmento;
    		int i = 1;
		    
			// Dividir la l�nea por el delimitador '|'
    		for (i = 0; i != posicion && getline(ss, segmento, '|'); i++); //Avanza i hasta la posicion deseada y retorna ese segmento
    		return segmento;
		}
		
		static Cola<NodoArbolRojiNegro<T>*>* dividirCadenaNodoID(const string &linea){	//Retorna una cola para construir el arbol ID
			// Usar stringstream para dividir la l�nea
			NodoArbolRojiNegro<T> *nodo;
			Cola<NodoArbolRojiNegro<T>*> *cola = new Cola<NodoArbolRojiNegro<T>*>;
    		istringstream ss1(linea);
    		string segmento = ""; 
			string info = "";
    		int cont = 1;
			// Dividir la l�nea por el delimitador
    		while (getline(ss1, segmento, '|')){
    			nodo = new NodoArbolRojiNegro<T>;
    			istringstream iss2(segmento);
    			
    			while(getline(iss2, info, '-')){
    				switch (cont){
    					case 1:
    						nodo->clave = info;
    						cont++;
    					break;
    					case 2:
    						nodo->pos = stoi(info);
    						cont++;
    					break;
    					case 3:
    						nodo->color = stoi(info);
    					break;
					}
				}
				cont = 1;
				nodo->izq = nullptr;
				nodo->der = nullptr;
				cola->insCola(nodo);
    		}
    		    		
    		return cola;
		}
	
		static Cola<NodoArbolBusquedas<T>*>* dividirCadenaNodoBusq(const string &linea) {	
	
	    Cola<NodoArbolBusquedas<T>*> *cola = new Cola<NodoArbolBusquedas<T>*>;
	    
	    istringstream ss1(linea);
	    string segmento, info;
	    int cont = 1, pos;
	    
	    while (getline(ss1, segmento, '|')) {
	        NodoArbolBusquedas<T> *nodo = new NodoArbolBusquedas<string>; // Crear nodo
	        
	        istringstream iss2(segmento);
	        
	        while (getline(iss2, info, '-')) {
	            switch (cont) {
	                case 1:
	                    nodo->clave = info;
	                    cont++;
	                    break;
	                case 2:
	                    nodo->color = stoi(info);
	                    cont++;
	                    break;
	                case 3:
	                    if (info == "0") {
	                        cont = 6; // No hay lista, salta al siguiente nodo
	                        getline(iss2, info, '-');
	                        getline(iss2, info, '-');
	                    } else {
	                        nodo->lista.setTamano(stoi(info)); // Usa la lista que ya est� en el nodo
	                        cont++;
	                    }
	                    break;
	                case 4:
	                    pos = stoi(info);
	                    cont++;
	                    break;
	                case 5:
	                    nodo->lista.insertarFinal(pos, info); // Usa la lista del nodo
	                    cont = 4;
	                    break;
	            }
	        }
	        cont = 1;
	        nodo->izq = nullptr;
	        nodo->der = nullptr;
	        cola->insCola(nodo);
	    }
	    
	    return cola;
	}

		
		
};

#endif


