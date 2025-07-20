#ifndef POSALBDAO_H
#define POSALBDAO_H
#include "Modelo_Estructuras/Cola.h"

using namespace std; 

class PosLibAlbDAO{
	private:
	public:
		PosLibAlbDAO();
		bool archivoExiste();
		bool crearArchivo();
		void guardarCola(Cola<int> *cola);
		int tamRegistros(); 
		Cola<int> *cargarCola(); 
};

#endif 

