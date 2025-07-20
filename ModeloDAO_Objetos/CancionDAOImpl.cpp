#include "CancionDAOImpl.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm> 

using namespace std;

bool CancionDAOImpl::archivoExiste(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good();  
}

bool CancionDAOImpl::crearArchivo() {
    if (archivoExiste("./Archivos/Cancion.txt")) { //Poner . es una forma de referirse al directorio en el que te encuentras actualmente.
        return false; 							  	
    }else{
        ofstream archivo("./Archivos/Cancion.txt"); //output para escritura
        if (archivo.fail()){
            return false; 
    	}
        archivo.close(); 
        return true; 
    }
}

string CancionDAOImpl::leerDato(int eleccion) {
    ifstream archivo("./Archivos/Cancion.txt");  // Abrir el archivo en modo lectura
    string dato;

    if (archivo.is_open()) {
        archivo.seekg((eleccion-1) * 304, ios::beg);  // Tama�o de la cadena +2
        getline(archivo, dato);  
        archivo.close();  // Cerrar el archivo
    } else {
        return "No se pudo abrir el archivo.";
    }

    return dato;  // Retornar la linea leida
}

void CancionDAOImpl::modificarDato(int eleccion, string nuevoDato) {
    fstream archivo("./Archivos/Cancion.txt", ios::in | ios::out);  // Abrir el archivo en modo lectura y escritura
    if (archivo.is_open()) {
        string datoModificado = nuevoDato+"\n";
        archivo.seekp((eleccion - 1) * 304, ios::beg);  // Posicionarse al inicio de la l�nea (+2 incluye salto de l�nea)
        archivo.write(datoModificado.c_str(), 303);  // Escribir exactamente +1 caracteres
        archivo.close();  
    } else {
        return;
    }
}

void CancionDAOImpl::eliminarNposLibre(int eleccion) {//Eliminara y pondra pos libre
	string posLibre;
	for (int i = 0; i < 302; ++i) { //Tama�o de la cadena
        posLibre += '0';  
    }
	modificarDato(eleccion, posLibre); 
}

int CancionDAOImpl::tamRegistros() {
    ifstream archivo("./Archivos/Cancion.txt");
    if (!archivo) {
        return -1; // Retornar -1 en caso de error
    }

    int contador = 0;
    string linea;
    while (getline(archivo, linea)) {
        contador++;
    }

    archivo.close();
    return contador;
}
