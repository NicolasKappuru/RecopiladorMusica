#ifndef POSCANDAO_H
#define POSCANDAO_H
#include "Modelo_Estructuras/Cola.h"

using namespace std; 

class PosLibCanDAO{
	private:
	public:
		PosLibCanDAO();
		bool archivoExiste();
		bool crearArchivo();
		void guardarCola(Cola<int> *cola);
		int tamRegistros(); 
		Cola<int> *cargarCola(); 
};

#endif 


