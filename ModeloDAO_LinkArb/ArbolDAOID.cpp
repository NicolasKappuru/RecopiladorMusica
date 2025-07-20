#include "ArbolDAOID.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm> 
 //
using namespace std;

ArbolDAOID::ArbolDAOID(){
}

bool ArbolDAOID::archivoExiste(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good();
}

bool ArbolDAOID::crearArchivo(){
	
    if (archivoExiste("./ArchivosArboles/ArbolID.txt")) { //Poner . es una forma de referirse al directorio en el que te encuentras actualmente.
        return false; 							  	
    }else{
        ofstream archivo("./ArchivosArboles/ArbolID.txt"); //output para escritura
        if (archivo.fail()){
            return false; 
    	}
    	
    	archivo << "0-0\n" ;
    	archivo << "0-0\n" ;
    	archivo << "0-0\n" ;
    	
    	archivo.close();
    	return true;
    }
    
}

string ArbolDAOID::leerDato(int eleccion) {   // recibe un entero y retorna el string según las posición dada (1 alb, 2 can o 3art) según el árbol que se quiera
	
	ifstream archivo("./ArchivosArboles/ArbolID.txt");
	string linea ="";
	
	switch(eleccion) {
        case 1:
        	
        	getline(archivo, linea);
			archivo.close();
			return linea;

            break;
        case 2:
      	
        	if(getline(archivo, linea)){
				if(getline(archivo, linea)){
					archivo.close();
					return linea;
				}
			}
			
            break;
        case 3:

            if(getline(archivo, linea)){
				if(getline(archivo, linea)){
					if(getline(archivo, linea)){
						archivo.close();
						return linea;
					}
				}
			}
		
            break;
        default:
	       break;
    
	}
	archivo.close();
}

void ArbolDAOID::actualizarArch(string albumArbol, string cancionArbol, string artistaArbol) { //accede al archivo y lo modifica
	ofstream archivoEscritura("./ArchivosArboles/ArbolID.txt", ios::out | ios::trunc);  //para sobreeescribir
	
	archivoEscritura << albumArbol <<"\n"<<cancionArbol<<"\n"<<artistaArbol<<"\n";
	
	archivoEscritura.close();
	
}

void ArbolDAOID::eliminarNposLibre(int eleccion) {//Eliminara y pondra pos libre
  	//cout << "ArbolDAO eliminar"<<endl;
}

void ArbolDAOID::modificarDato(int a, string aa){} 

int ArbolDAOID::tamRegistros() {
    return 0; 
}


