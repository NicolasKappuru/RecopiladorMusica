#include "PosLibCanDAO.h"
#include <iostream>
#include <fstream>
#include "Modelo_Estructuras/Cola.h"

using namespace std;

PosLibCanDAO::PosLibCanDAO() {
}

bool PosLibCanDAO::archivoExiste() {
    ifstream archivo("./ArchivosPosLibres/posLibCan.txt");
    return archivo.good();  
}

bool PosLibCanDAO::crearArchivo() {
    if (archivoExiste()) { //Poner . es una forma de referirse al directorio en el que te encuentras actualmente.
        return false; 							  	
    }else{
        ofstream archivo("./ArchivosPosLibres/posLibCan.txt"); //output para escritura
        if (archivo.fail()){
            return false; 
    	}
    	archivo << "1\n"; // Escribimos "1" en la primera l�nea
        archivo.close(); 
        return true; 
    }
}

void PosLibCanDAO::guardarCola(Cola<int> * cola) {
    ofstream archivo("./ArchivosPosLibres/posLibCan.txt", ios::out);
    if (!archivo) {
        return;
    }

    while (!cola->colaVacia()) {
        archivo << cola->atenderCola() << endl;  // Extrae y guarda
    }
    archivo.close();
}

int PosLibCanDAO::tamRegistros() {
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

Cola<int> * PosLibCanDAO::cargarCola() {
    Cola<int>* cola = new Cola<int>();  // Crear la cola din�micamente en el heap
    ifstream archivo("./ArchivosPosLibres/posLibCan.txt");
    if (!archivo) {
        return nullptr;
    }

    int num;
    while (archivo >> num) {
        cola->insCola(num);  // Inserta los n�meros le�dos
    }
    archivo.close();
    return cola;
}



