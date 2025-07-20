#ifndef POSLINKDAO_H
#define POSLINKDAO_H
#include "Modelo_Estructuras/Cola.h"

using namespace std; 

class PosLibLinkDAO{
	private:
	public:
		PosLibLinkDAO();
		bool archivoExiste();
		bool crearArchivo();
		void guardarCola(Cola<int> *cola);
		int tamRegistros(); 
		Cola<int> *cargarCola(); 
};

#endif 

