#include "LinkDAO.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <algorithm> 

using namespace std;

bool LinkDAO::archivoExiste(string nombreArchivo) {
	ifstream archivo(nombreArchivo);
    return archivo.good();  
}

bool LinkDAO::crearArchivo() {
   	if (archivoExiste("./Archivos/Links.txt")) { //Poner . es una forma de referirse al directorio en el que te encuentras actualmente.
        return false; 							  	
    }else{
        ofstream archivo("./Archivos/Links.txt"); //output para escritura
        if (archivo.fail()){
            return false; 
    	}
        archivo.close(); 
        return true; 
	}
}

string LinkDAO::leerDato(int eleccion) {
	ifstream archivo("./Archivos/Links.txt");  // Abrir el archivo en modo lectura
    string dato;

    if (archivo.is_open()) {
        archivo.seekg((eleccion-1) * 118, ios::beg);  // Tamaño de la cadena +2
        getline(archivo, dato);  
        archivo.close();  // Cerrar el archivo
    } else {
        return "No se pudo abrir el archivo.";
    }

    return dato;  // Retornar la linea leida
}

void LinkDAO::modificarDato(int eleccion, string nuevoDato) {
	fstream archivo("./Archivos/Links.txt", ios::in | ios::out);  // Abrir el archivo en modo lectura y escritura
    if (archivo.is_open()) {
        string datoModificado = nuevoDato+"\n";
        archivo.seekp((eleccion - 1) * 118, ios::beg);  // Posicionarse al inicio de la línea (+2 incluye salto de línea)
        archivo.write(datoModificado.c_str(), 117);  // Escribir exactamente +1 caracteres
        archivo.close();  
    } else {
        return;
    }
	
}

void LinkDAO::eliminarNposLibre(int eleccion) {//Eliminara y pondra pos libre
  	string posLibre;
	for (int i = 0; i < 116; ++i) { //Tamaño de la cadena
        posLibre += '0';  
    }
	modificarDato(eleccion, posLibre); 
}

int LinkDAO::tamRegistros() {
    ifstream archivo("./Archivos/Links.txt");
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

