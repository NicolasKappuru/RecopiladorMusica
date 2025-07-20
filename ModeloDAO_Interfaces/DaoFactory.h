#ifndef DAOFactory_H
#define DAOFactory_H
#include "DAO.h"
#include <string>

class DaoFactory {  //interfaz
public:
    virtual DAO* createAlbumDAO() = 0;
    virtual DAO* createArtistaDAO() = 0;
    virtual DAO* createCancionDAO() = 0;
    
    virtual DAO* createLinkDAO() = 0;
    virtual DAO* createArbolDAOID() = 0;
    virtual DAO* createArbolDAOBusquedas() = 0; 
};

#endif 
