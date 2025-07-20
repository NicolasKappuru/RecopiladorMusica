#ifndef MEDIATOR_INTERFACE_H
#define MEDIATOR_INTERFACE_H
#include <string>
#include <iostream>

using namespace std; 

class MediatorInterface { //Se encargara de desacoplar el codigo
public:
    virtual bool insercion() = 0;
    virtual bool eliminacion() = 0;
    virtual bool actualizacion() = 0;
    virtual bool verificacion(string) = 0;
    virtual int definirPosicion() = 0; 
    virtual string formulario(string, int) = 0; 
	virtual void setCadena(string, string, string) = 0; 
    virtual ~MediatorInterface() {}
};

#endif // MEDIATOR_INTERFACE_H

