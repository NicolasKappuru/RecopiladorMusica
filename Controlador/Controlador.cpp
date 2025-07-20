#include "Controlador.h"

#include "ModeloDAO_Interfaces/DAO.h"
#include "ModeloDAO_Interfaces/ConcreteDAOFactory.h"
#include "ModeloDAO_Interfaces/DaoFactory.h"
#include "ModeloDAO_Objetos/AlbumDAOImpl.h"
#include "ModeloDAO_Objetos/ArtistaDAOImpl.h"
#include "ModeloDAO_Objetos/CancionDAOImpl.h"

#include "Modelo_Estructuras/Pila.h"

#include "Controlador_Mediator/MediatorInterface.h"
#include "Controlador_Mediator/MediatorArtista.h"
#include "Controlador_Mediator/MediatorAlbum.h"
#include "Controlador_Mediator/MediatorCancion.h"

#include "Controlador_Link/GestorLinks.h"
#include "Controlador_Consultas/GestorConsultas.h"

#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"

#include "Modelo_Estatico/CompletarCadena.h"


#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>


using namespace std; 

Controlador::Controlador(){ //Constructor
	posLibres = SingletonPosLibres<int>::obtenerInstanciaPosLibres();
	arbolID = SingletonArbolID<string>::obtenerInstanciaArbolID();	
	arbolBusq = SingletonArbolBusq<string>::obtenerInstanciaArbolBusqueda(); 
	nodoAux = nullptr; 
	vista = VistaConsola(); 
	posCan = 0; 
	auxStr = "Null"; 
	auxInt = 0; 
	auxAlb = "Null"; 
}

void Controlador::run() { //Metodo que lleva el orden del codigo
	vista.mostrarEtiqueta("Bienvenido usuario \n"); 
	posLibres->establecerColas(); //Esto lo hace el controlador al iniciar el programa
	arbolID->establecerArboles(); //Esto al inicio
	arbolBusq->establecerArbol(); //Inicializar los arboles
	
	bool continuar = true; 
	do{
		vista.menuCRUD();
		continuar =	CRUD(vista.leerDatoInt("Eleccion: "));
	}while(continuar);
	
	posLibres->guardarColas(); //Esto lo hace el controlador siempre al finalizar el codigo 
	arbolID->actualizarArchivo(); //Nos guarda los arboles de IDs
	arbolBusq->actualizarArchivo(); //Nos guarda los arboles de busquedas
	
}

bool Controlador::CRUD(int eleccion){
	GestorConsultas gestor;
	bool continuar = true; 
	switch(eleccion){
		case 1:
		vista.mostrarEtiqueta("AGREGAR"); //temporal

		do{
		vista.subMenu(); 
		continuar = mediadorAdicionar(vista.leerDatoInt("Eleccion: ")); 
		}while(continuar); 
		
		return true;
		break; 
		
		case 2: 
		vista.mostrarEtiqueta("ELIMINAR"); //temporal
		do{
		vista.subMenu();
		continuar = mediadorEliminar(vista.leerDatoInt("Eleccion: ")); 
		}while(continuar);
		return true;
		break; 
		
		case 3: 
		vista.mostrarEtiqueta("ACTUALIZAR"); //temporal
		do{
		vista.subMenu();
		continuar = mediadorActualizar(vista.leerDatoInt("Eleccion: ")); 
		}while(continuar);
		return true;
		break; 
		
		case 4: 
		vista.mostrarEtiqueta("CONSULTAR"); //temporal
		do{
		continuar =	gestor.gestionar(); 
 		}while(continuar); 
		return true;
		break; 

		case 5: 
		vista.mostrarEtiqueta("Finalizando operacion"); //temporal
		return false; 
		break; 

		default:
		vista.mostrarInformacion("Valor no valido"); 
		return true; 
		break; 
	}
}

bool Controlador::mediadorAdicionar(int eleccion) {
    MediatorInterface* mediador = nullptr; // Usar puntero a la interfaz base
    DaoFactory* fabrica = new ConcreteDAOFactory();
	GestorLinks* gestorLinks = new GestorLinks(fabrica->createLinkDAO());
    Pila<int> * pilaAux = new Pila<int>();
	int numCan = 0; 
    int numArt = 0; 
    int forAlb = 0; 
    string arreglo = ""; 
    string name = "";
    
	switch (eleccion) {
        case 1: {
            vista.mostrarEtiqueta("ADICIONAR ALBUM"); // temporal
            mediador = new MediatorAlbum(fabrica->createAlbumDAO());
		
			vista.mostrarInformacion("Digitar el titulo del album: ");
			name = ""; 
			auxStr = vista.leerDato("[+] Eleccion: "); 
			auxAlb = auxStr;  

			do{
				vista.mostrarInformacion("Digitar el numero de canciones del album [Min 1, Max 12]");
				auxInt = vista.leerDatoInt("[+] Eleccion: ");            
            }while(auxInt>12 || auxInt<1);
		
			string cadena = mediador->formulario(auxStr, 0); 
         
         	if(cadena == "Repetido"){
         		vista.mostrarInformacion("Este album ya esta en la base de datos");
         		auxStr = "Null"; 
				auxAlb = "Null"; 
				auxInt = 0;
				return false; 
			}
			
		 	numCan = auxInt; 
			forAlb = auxInt; 
			
			for(int i = 1; i<=numCan; i++){
				vista.mostrarEtiqueta("Cancion de este album"); 
				name = to_string(posLibres->obtenerCola(1)->retornarValor()); //busca
   				pilaAux->meter(posLibres->obtenerCola(1)->retornarValor());
				arreglo = CompletarCadena::crearLista(arreglo,name,forAlb);
				
					
				if(mediadorAdicionar(2)==false){
					if(forAlb == 1){
							arreglo.pop_back();	
						} else{
							arreglo.pop_back(); 
							arreglo.pop_back(); 	
						} 
					
					pilaAux->sacar(); 
					
					if(true==pilaAux->existeElemento(arbolID->obtenerArbol(2)->buscar(arbolID->getAuxID())->pos)){
						i--;
						forAlb++;
						
						}else{
							pilaAux->meter(arbolID->obtenerArbol(2)->buscar(arbolID->getAuxID())->pos);
							name = to_string(arbolID->obtenerArbol(2)->buscar(arbolID->getAuxID())->pos);
							arreglo = CompletarCadena::crearLista(arreglo,name,forAlb);		
					}	
					
				} 
				
            	forAlb--; 
			}
			
			string listado_Canciones = arreglo;
					
			vista.mostrarEtiqueta("Links Album");
			string listado_Links = gestorLinks->insercion(); //Vamos a probar este 
			gestorLinks->setArregloPos(""); //Limpiados el arreglo de posiciones del link
			
			mediador->setCadena(cadena, listado_Canciones, listado_Links);
			mediador->insercion();
			
			auxStr = "Null"; 
			auxAlb = "Null"; 
			auxInt = 0; 
			vista.mostrarEtiqueta("Operacion exitosa"); 
    		return true; 
	        break;
        }

        case 2: {
            vista.mostrarEtiqueta("ADICIONAR CANCION"); // temporal
            mediador = new MediatorCancion(fabrica->createCancionDAO());
			
			do{
				vista.mostrarInformacion("Digitar el numero de artistas de la cancion [Min 1, Max 12]");
				auxInt = vista.leerDatoInt("[+] Eleccion: ");            
            }while(auxInt>12 || auxInt<1);
            			
			string cadena = mediador->formulario(auxAlb, auxInt);
			
			///Por si se REPITE una cancion
			if(cadena == "Repetido"){
         		vista.mostrarInformacion("Esta cancion ya esta en la base de datos");
				return false; 
			}
			
			
			posCan = posLibres->obtenerCola(1)->retornarValor(); 
			numArt = auxInt; 
			forAlb = auxInt;
			
			for(int i = 1; i<=numArt; i++){
				vista.mostrarEtiqueta("Artista de esta cancion"); 
				name = to_string(posLibres->obtenerCola(2)->retornarValor()); //busca
   				pilaAux->meter(posLibres->obtenerCola(2)->retornarValor());
				arreglo = CompletarCadena::crearLista(arreglo,name,forAlb);
				
				if(mediadorAdicionar(3)==false){
					if(forAlb == 1){
						arreglo.pop_back();	
					}else{
						arreglo.pop_back(); 
						arreglo.pop_back(); 	
					} 
					pilaAux->sacar(); 
					
					if(true==pilaAux->existeElemento(arbolID->obtenerArbol(3)->buscar(arbolID->getAuxID())->pos)){
						i--;
						forAlb++;
						
					}else{
						pilaAux->meter(arbolID->obtenerArbol(3)->buscar(arbolID->getAuxID())->pos);
						name = to_string(arbolID->obtenerArbol(3)->buscar(arbolID->getAuxID())->pos);
						arreglo = CompletarCadena::crearLista(arreglo,name,forAlb);		
						
						arbolBusq->obtenerArbol(14)->insertar(arbolBusq->getNomArt()); 
						nodoAux = arbolBusq->obtenerArbol(14)->buscar(arbolBusq->getNomArt()); 
						nodoAux->lista.insertar(posCan,"a"); 
					}		
				}else{
					arbolBusq->obtenerArbol(14)->insertar(arbolBusq->getNomArt()); 
					nodoAux = arbolBusq->obtenerArbol(14)->buscar(arbolBusq->getNomArt()); 
					nodoAux->lista.insertar(posCan,"a"); 
				}
				
            	forAlb--; 
			}
			
			string listado_Artistas = arreglo;
						
			vista.mostrarEtiqueta("Links de Cancion");
			string listado_Links = gestorLinks->insercion(); //Vamos a probar este
			gestorLinks->setArregloPos(""); //Limpiados el arreglo de posiciones del link
						
			mediador->setCadena(cadena,listado_Artistas,listado_Links);
			mediador->insercion();
			
			name = "";
			arreglo = "";
			numArt = 0;
			auxStr = "Null"; 
			posCan = 0; 
			vista.mostrarEtiqueta("Operacion exitosa");
			return true;  
            break;
        }

        case 3: {
            vista.mostrarEtiqueta("ADICIONAR ARTISTA"); // temporal
            mediador = new MediatorArtista(fabrica->createArtistaDAO());
            bool repetido = mediador->insercion();
    	
		    if(repetido == false){
            	vista.mostrarInformacion("Esta repetido"); 
            	return false; 
			}
			if(posCan==0){
				arbolBusq->obtenerArbol(14)->insertar(arbolBusq->getNomArt()); 
			}

			
			vista.mostrarEtiqueta("Operacion exitosa");
			return true; 
			break;
        }

        case 4:
            vista.mostrarEtiqueta("Cerrar"); // temporal
            break;

        default:
        	vista.mostrarInformacion("Valor no valido"); 
        	return true; 
            break;
    }

    delete mediador;   // Liberar memoria
    delete fabrica;    // Liberar memoria
    delete gestorLinks;
	return false; 
}


bool Controlador::mediadorEliminar(int eleccion) {
    MediatorInterface* mediador = nullptr; // Usar puntero a la interfaz base
    DaoFactory* fabrica = new ConcreteDAOFactory();
	GestorLinks* gestorLinks = new GestorLinks(fabrica->createLinkDAO());
	
    switch (eleccion) {
        case 1: {
            vista.mostrarEtiqueta("ELIMINAR ALBUM"); // temporal
            mediador = new MediatorAlbum(fabrica->createAlbumDAO());
			vista.mostrarEtiqueta("Operacion exitosa");
			return true;  
            break;
        }

        case 2: {
            vista.mostrarEtiqueta("ELIMINAR CANCION"); // temporal
            mediador = new MediatorCancion(fabrica->createCancionDAO());
			mediador->eliminacion(); 
			vista.mostrarEtiqueta("Operacion exitosa"); 
			return true; 
            break;
        }

        case 3: {
            vista.mostrarEtiqueta("ELIMINAR ARTISTA"); // temporal
			mediador = new MediatorArtista(fabrica->createArtistaDAO());
			mediador->eliminacion();
			vista.mostrarEtiqueta("Operacion exitosa");
			return true; 
			break;
        }

        case 4:
            vista.mostrarEtiqueta("Volver"); // temporal
			break;

        default:
        	vista.mostrarInformacion("Valor no valido");
            return true;
			break;
    }

    delete mediador;   // Liberar memoria
    delete fabrica;    // Liberar memoria
    delete gestorLinks; 
    return false; 
}


bool Controlador::mediadorActualizar(int eleccion) {
    MediatorInterface* mediador = nullptr; // Usar puntero a la interfaz base
    DaoFactory* fabrica = new ConcreteDAOFactory();
	GestorLinks* gestorLinks = new GestorLinks(fabrica->createLinkDAO());
	
    switch (eleccion) {
        case 1: {
            vista.mostrarEtiqueta("ACTUALIZAR ALBUM"); // temporal
            mediador = new MediatorAlbum(fabrica->createAlbumDAO());
			vista.mostrarEtiqueta("Operacion exitosa"); 
            return true; 
			break;
        }

        case 2: {
            vista.mostrarEtiqueta("ACTUALIZAR CANCION"); // temporal
            mediador = new MediatorCancion(fabrica->createCancionDAO());
           	vista.mostrarEtiqueta("Operacion exitosa"); 
		    return true; 
			break;
        }

        case 3: {
            vista.mostrarEtiqueta("ACTUALIZAR ARTISTA"); // temporal
            mediador = new MediatorArtista(fabrica->createArtistaDAO()); 
			vista.mostrarEtiqueta("Operacion exitosa"); 
			return true; 
			break;
        }

        case 4:
            vista.mostrarEtiqueta("Volver"); // temporal
			break;

        default:
        	vista.mostrarInformacion("Valor no valido"); 
        	return true; 
            break;
    }

    delete mediador;   // Liberar memoria
    delete fabrica;    // Liberar memoria
    delete gestorLinks; 
    return false; 
}


