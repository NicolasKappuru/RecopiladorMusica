#ifndef ARBOLDAOBUSQUEDAS_H
#define ARBOLDAOBUSQUEDAS_H
#include "ModeloDAO_Interfaces/DAO.h"

#include <string>

using namespace std; 

class ArbolDAOBusquedas : public DAO {
	public:
		ArbolDAOBusquedas();
		bool archivoExiste(string) override;
		bool crearArchivo() override;
		string leerDato(int) override;
		void leerArchivo();
		void modificarDato(int , string);
		void actualizarArch(string, string, string, string, string, string, string, string, string, string, string, string, string, string, string); 
		void eliminarNposLibre(int) override; 
		int tamRegistros() override;
		
		string* getLineas();
	private:
		string *lineas;
};

#endif 
