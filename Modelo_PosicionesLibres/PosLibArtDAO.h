#ifndef POSARTDAO_H
#define POSARTDAO_H
#include "Modelo_Estructuras/Cola.h"

using namespace std; 

class PosLibArtDAO{
	private:
	public:
		PosLibArtDAO();
		bool archivoExiste();
		bool crearArchivo();
		void guardarCola(Cola<int> *cola);
		int tamRegistros();
		Cola<int> *cargarCola(); 
};

#endif 


