#ifndef ARBOLDAOID_H
#define ARBOLDAOID_H
#include "ModeloDAO_Interfaces/DAO.h"
#include <string>

using namespace std; 

class ArbolDAOID : public DAO {
	public:
		ArbolDAOID();
		bool archivoExiste(string) override;
		bool crearArchivo() override;
		string leerDato(int) override;
		void modificarDato(int , string); 
		void actualizarArch(string , string, string); 
		void eliminarNposLibre(int) override; 
		int tamRegistros() override; 	 
};

#endif 

