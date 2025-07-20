#ifndef ArtistaCanDAOimpl_H
#define ArtistaCanDAOimpl_H
#include "ModeloDAO_Interfaces/DAO.h"
#include <string>
using namespace std; 

class ArtistaDAOImpl : public DAO {
	public:
		bool archivoExiste(string) override;
		bool crearArchivo() override;
		string leerDato(int) override; 
		void modificarDato(int , string) override; 
		void eliminarNposLibre(int) override; 
		int tamRegistros() override; 

};

#endif 

