#include "ArbolDAOBusquedas.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

ArbolDAOBusquedas::ArbolDAOBusquedas(){
	
	this->lineas = new string[15];
	for(int i=0; i<15 ; i++){	//Inicializa el arreglo 
		lineas[i] = "";	
	}
}

bool ArbolDAOBusquedas::archivoExiste(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good();
}

bool ArbolDAOBusquedas::crearArchivo(){
	
    if (archivoExiste("./ArchivosArboles/ArbolBusquedas.txt")) { //Poner . es una forma de referirse al directorio en el que te encuentras actualmente.
        return false; 							  	
    }else{
        ofstream archivo("./ArchivosArboles/ArbolBusquedas.txt"); //output para escritura
        if (archivo.fail()){
            return false; 
    	}
    	
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	archivo << "0-0-0-0-0\n" ;
    	
    	
    	archivo.close();
    	return true;
    }
    
}

void ArbolDAOBusquedas::leerArchivo(){
	
	ifstream archivo("./ArchivosArboles/ArbolBusquedas.txt");
	string linea = "";
	int i=0;
	while(getline(archivo, linea) && i<15){
		this->lineas[i] = linea;
		i++;
	}
	
	archivo.close();
}

string ArbolDAOBusquedas::leerDato(int eleccion) {   // recibe un entero y retorna el string según las posición dada (1-10) según el árbol de consulta que se quiera
	return this->lineas[eleccion-1];
}

void ArbolDAOBusquedas::actualizarArch(string cons1, string cons2, string cons3, string cons4, string cons5, string cons6, string cons7, string cons8, string cons9, string cons10, string cons11, string cons12, string cons13, string cons14, string cons15) { //accede al archivo y lo modifica
	
	ofstream archivoEscritura("./ArchivosArboles/ArbolBusquedas.txt", ios::out | ios::trunc);  //para sobreeescribir
	
	archivoEscritura<<cons1<<"\n"
					<<cons2<<"\n"
					<<cons3<<"\n"
					<<cons4<<"\n"
					<<cons5<<"\n"
					<<cons6<<"\n"
					<<cons7<<"\n"
					<<cons8<<"\n"
					<<cons9<<"\n"
					<<cons10<<"\n"
					<<cons11<<"\n"
					<<cons12<<"\n"
					<<cons13<<"\n"
					<<cons14<<"\n"
					<<cons15<<"\n";
	
	archivoEscritura.close();
}

void ArbolDAOBusquedas::eliminarNposLibre(int eleccion) {//Eliminara y pondra pos libre
  	//cout << "ArbolDAO eliminar"<<endl;

}

void ArbolDAOBusquedas::modificarDato(int a, string aa){
} 

int ArbolDAOBusquedas::tamRegistros() {
    return 0; 
}

string* ArbolDAOBusquedas::getLineas(){
	return this->lineas;
}

