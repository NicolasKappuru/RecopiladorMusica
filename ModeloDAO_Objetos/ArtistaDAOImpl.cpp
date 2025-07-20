#include "ArtistaDAOImpl.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm> 

using namespace std;

bool ArtistaDAOImpl::archivoExiste(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good();  
}

bool ArtistaDAOImpl::crearArchivo() {
    if (archivoExiste("./Archivos/Artista.txt")) { //Poner . es una forma de referirse al directorio en el que te encuentras actualmente.
        return false; 							  	
    }else{
        ofstream archivo("./Archivos/Artista.txt"); //output para escritura
        if (archivo.fail()){
            return false; 
    	}
        archivo.close(); 
        return true; 
    }
}

string ArtistaDAOImpl::leerDato(int eleccion) {
    ifstream archivo("./Archivos/Artista.txt");  // Abrir el archivo en modo lectura
    string dato;

    if (archivo.is_open()) {
        archivo.seekg((eleccion-1) * 99, ios::beg);  // Tamaño de la cadena +2
        getline(archivo, dato);  
        archivo.close();  // Cerrar el archivo
    } else {
        return "No se pudo abrir el archivo.";
    }

    return dato;  // Retornar la linea leida
}

void ArtistaDAOImpl::modificarDato(int eleccion, string nuevoDato) {
    fstream archivo("./Archivos/Artista.txt", ios::in | ios::out);  // Abrir el archivo en modo lectura y escritura
    if (archivo.is_open()) {
        string datoModificado = nuevoDato+"\n";
        archivo.seekp((eleccion - 1) * 99, ios::beg);  // Posicionarse al inicio de la línea (+2 incluye salto de línea)
        archivo.write(datoModificado.c_str(), 98);  // Escribir exactamente +1 caracteres
        archivo.close();  
    } else {
        return;
    }
}

void ArtistaDAOImpl::eliminarNposLibre(int eleccion) {//Eliminara y pondra pos libre
	string posLibre;
	for (int i = 0; i < 97; ++i) { //Tamaño de la cadena
        posLibre += '0';  
    }
	modificarDato(eleccion, posLibre); 
}

int ArtistaDAOImpl::tamRegistros() {
    ifstream archivo("./Archivos/Artista.txt");
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
