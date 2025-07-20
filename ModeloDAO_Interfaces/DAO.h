#ifndef DAO_H
#define DAO_H
#include <string>

using namespace std; 

//Metodos como virtuales puros para que las clases derivadas tengan que implementarlos.
class DAO {    //interfaz DAO
public:
    DAO() = default;
    virtual ~DAO() = default;

    virtual bool archivoExiste(string) = 0;
	virtual bool crearArchivo() = 0;
	virtual string leerDato(int) = 0; 
	virtual void modificarDato(int , string) = 0; 
	virtual void eliminarNposLibre(int) = 0; 
	virtual int tamRegistros() = 0; 
};


//el virtual = 0 es porque DAO es una clase abstracta que no puede ser instanciada directamente

#endif 

