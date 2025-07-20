// ConcreteDAOFactory.h
#ifndef CONCRETEDAO_H
#define CONCRETEDAO_H
#include "DAOFactory.h"
#include "ModeloDAO_Objetos/AlbumDAOImpl.h"
#include "ModeloDAO_Objetos/ArtistaDAOImpl.h"
#include "ModeloDAO_Objetos/CancionDAOImpl.h"
#include "ModeloDAO_LinkArb/LinkDAO.h"
#include "ModeloDAO_LinkArb/ArbolDAOID.h"
#include "ModeloDAO_LinkArb/ArbolDAOBusquedas.h"



class ConcreteDAOFactory : public DaoFactory {
public:
    DAO* createAlbumDAO() override {
        return new AlbumDAOImpl();
    };
    DAO* createArtistaDAO() override {
        return new ArtistaDAOImpl();
    };
    DAO* createCancionDAO() override {
        return new CancionDAOImpl();
    };
    DAO* createLinkDAO() override {
    	return new LinkDAO();
	}
    DAO* createArbolDAOID() override {
    	return new ArbolDAOID();
	}
	DAO* createArbolDAOBusquedas() override {
		return new ArbolDAOBusquedas(); 
	}
};

#endif 
