#include "PosLibLinkDAO.h"
#include <iostream>
#include <fstream>
#include "Modelo_Estructuras/Cola.h"

using namespace std;

PosLibLinkDAO::PosLibLinkDAO() {
}

bool PosLibLinkDAO::archivoExiste() {
    ifstream archivo("./ArchivosPosLibres/posLibLink.txt");
    return archivo.good();  
}

bool PosLibLinkDAO::crearArchivo() {
    if (archivoExiste()) { //Poner . es una forma de referirse al directorio en el que te encuentras actualmente.
        return false; 							  	
    }else{
        ofstream archivo("./ArchivosPosLibres/posLibLink.txt"); //output para escritura
        if (archivo.fail()){
            return false; 
    	}
    	archivo << "1\n"; // Escribimos "1" en la primera l�nea
        archivo.close(); 
        return true; 
    }
}

void PosLibLinkDAO::guardarCola(Cola<int> * cola) {
    ofstream archivo("./ArchivosPosLibres/posLibLink.txt", ios::out);
    if (!archivo) {
        return;
    }

    while (!cola->colaVacia()) {
        archivo << cola->atenderCola() << endl;  // Extrae y guarda
    }
    archivo.close();
}

int PosLibLinkDAO::tamRegistros() {
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

Cola<int> * PosLibLinkDAO::cargarCola() {
    Cola<int>* cola = new Cola<int>();  // Crear la cola din�micamente en el heap
    ifstream archivo("./ArchivosPosLibres/posLibLink.txt");
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



