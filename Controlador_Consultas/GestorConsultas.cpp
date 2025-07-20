#include "GestorConsultas.h"

#include "ModeloDAO_Interfaces/DAO.h"
#include "ModeloDAO_Interfaces/ConcreteDAOFactory.h"

#include "ModeloDAO_Objetos/AlbumDAOImpl.h"
#include "ModeloDAO_Objetos/CancionDAOImpl.h"
#include "ModeloDAO_Objetos/ArtistaDAOImpl.h"
#include "ModeloDAO_LinkArb/LinkDAO.h"
#include "ModeloDAO_LinkArb/ArbolDAOBusquedas.h"
#include "ModeloDAO_LinkArb/ArbolDAOID.h"

#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"

#include "Modelo_Estatico/Segmentar.h"
#include "Modelo_Estatico/Ordenamiento.h"

#include "Modelo_Estructuras/ListaOrdenada.h"
#include "Modelo_Estructuras/Pila.h"
#include "Modelo_Estructuras/Cola.h"

GestorConsultas::GestorConsultas() {
	vista = VistaConsola(); 
	fabrica = new ConcreteDAOFactory();
	
	arbolBusq = SingletonArbolBusq<string>::obtenerInstanciaArbolBusqueda();
	
	AlbumDAO = fabrica->createAlbumDAO();	   				//Requerimos para traer datos de album
	CancionDAO = fabrica->createCancionDAO(); 				//Requerimos para traer datos de cancion
	ArtistaDAO = fabrica->createArtistaDAO(); 				//Requerimos para traer datos de artista
	LinkDAO = fabrica->createLinkDAO();		   				//Requerimos para traer links
	ArbolDAOID = fabrica->createArbolDAOID();				//Tal vez xD
	ArbolDAOBusquedas = fabrica->createArbolDAOBusquedas();	//Requerimos para traer las consultas
	
}

bool GestorConsultas::gestionar(){
	int opcion; 
    do {
    	vista.menuConsultas(); 
    	opcion = vista.leerDatoInt("Eleccion: ");
    	
        switch (opcion) {
            case 1: conEditora(); break;
            case 2: conEstudioGrabacion(); break;
            case 3: conDuracion(); break;
            case 4: conGenIns(); break; 
            case 5: conNumVer(); break;
            case 6: conVersion(); break;
            case 7: conNombreCancion(); break;
            case 8: conCoverArt(); break;
            case 9: conFotografiayEstudio(); break;
            case 10: conCompositorLetra(); break;
			case 0: vista.mostrarInformacion("Volviendo..."); break;
            default: vista.mostrarInformacion("Opcion no valida");
        }
    } while (opcion != 0);
    return false; 
}

//Consulta 1
void GestorConsultas::conEditora() {
    
	NodoArbolBusquedas<string> *nodoAux;
	
	vista.mostrarInformacion("Ingrese el nombre de la editora");
	
	string nomEditora = vista.leerDato("[+] Nombre: ");
	
	nodoAux = arbolBusq->obtenerArbol(1)->buscar(nomEditora);
	
	if(nodoAux!=nullptr){	//Si existe la editora
	
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		string registro, titulo_Alb, nomArt_Alb, anioPub_Alb; 
		
		vista.mostrarInformacion("Numero de albumes: "+to_string(tamNodo));
		
		for(int i = 0; i<tamNodo; i++){
			registro = AlbumDAO->leerDato(arreglo[i]);
			titulo_Alb = Segmentar<string>::dividirCadenaPosicion(registro,2);
			anioPub_Alb = Segmentar<string>::dividirCadenaPosicion(registro, 5);
			nomArt_Alb = Segmentar<string>::dividirCadenaPosicion(registro, 4);
			vista.mostrarInformacion("["+to_string(i+1)+"] Titulo: " + titulo_Alb + " Anio Publicacion: " + anioPub_Alb + " Nombre Artistico: " + nomArt_Alb); 
		}
		
	} else{
		vista.mostrarInformacion("Esa editora no existe.");
	}
	
}

//Consulta 2
void GestorConsultas::conEstudioGrabacion() {
	
    NodoArbolBusquedas<string> *nodoAux;
	
	vista.mostrarInformacion("Ingrese el nombre del estudio de grabacion");
	
	string estGrabacion = vista.leerDato("[+] Nombre: ");
	
	nodoAux = arbolBusq->obtenerArbol(2)->buscar(estGrabacion);
	
	if(nodoAux!=nullptr){	//Si existe la editora
	
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arregloAlbum = nodoAux->lista.retornarArreglo();
		string registro, titulo_Alb, anioPub_Alb, pais_Alb, listaCan_Alb, registroCan, nombre_Can;
		int tamPosicionCan;
		int *posicionesCan;
		string *arregloCancion;

		for(int i = 0; i<tamNodo; i++){
			registro = AlbumDAO->leerDato(arregloAlbum[i]);
			titulo_Alb = Segmentar<string>::dividirCadenaPosicion(registro,2);
			anioPub_Alb = Segmentar<string>::dividirCadenaPosicion(registro, 5);
			pais_Alb = Segmentar<string>::dividirCadenaPosicion(registro, 3);
			listaCan_Alb = Segmentar<string>::dividirCadenaPosicion(registro, 10);
			vista.mostrarInformacion("["+to_string(i+1)+" Album] Titulo: " + titulo_Alb + " Anio Publicacion: " + anioPub_Alb + " Pais Grabacion: " + pais_Alb);
			
			tamPosicionCan = Segmentar<string>::dividirCadenaGuionInt(listaCan_Alb);
			posicionesCan = Segmentar<string>::dividirCadenaGuion(listaCan_Alb, tamPosicionCan);
			
			arregloCancion = new string[tamPosicionCan];
			
			for(int j = 0; j<tamPosicionCan; j++){					//Llenar el arreglo de los nombres de las canciones
				registroCan = CancionDAO->leerDato(posicionesCan[j]);
				nombre_Can = Segmentar<string>::dividirCadenaPosicion(registroCan,2);
				arregloCancion[j] = nombre_Can;
			}
			Ordenamiento::ordenar(arregloCancion, tamPosicionCan);
			for(int j = 0; j<tamPosicionCan;j++){
				nombre_Can = arregloCancion[j];
				vista.mostrarInformacion("["+to_string(j+1)+" Cancion] Nombre: " + nombre_Can);
			}
		}
		
	} else{
		vista.mostrarInformacion("Ese estudio de grabacion no existe.");
	}
    
}

//Consulta 3
void GestorConsultas::conDuracion() {
	Cola<NodoArbolBusquedas<string>*> *colaAux;
	NodoArbolBusquedas<string> *nodoAux;
	ListaOrdenada lista;
	int cont = 1;
	
	vista.mostrarInformacion("Ingrese el tiempo de la cancion (MM:SS)");
	
	string tiempo = vista.leerDato("[+] Tiempo: ");
	
	colaAux = arbolBusq->obtenerArbol(3)->inorden(tiempo);
	
	if(colaAux->colaVacia()) vista.mostrarInformacion("No hay canciones que cumplan con el requisito.");
	
	string registro, nombre_Can, ciudadGra_Can, duracion_Can, arrMusicales_Can, comLetra_Can, comMus_Can; 
	int posicion_Can;
	
	while(!colaAux->colaVacia()){
		
		nodoAux = colaAux->atenderCola();
				
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		
		
		for(int i = 0; i<tamNodo; i++){
			registro = CancionDAO->leerDato(arreglo[i]);
			ciudadGra_Can = Segmentar<string>::dividirCadenaPosicion(registro, 10);
			lista.insertar(arreglo[i], ciudadGra_Can);
		}
	}
	
	
	while(!lista.listaVacia()){
		posicion_Can = lista.getPos(lista.getCab()->sig);
		ciudadGra_Can = lista.getInfo(lista.getCab()->sig);
		
		registro = CancionDAO->leerDato(posicion_Can);
		nombre_Can = Segmentar<string>::dividirCadenaPosicion(registro,2);
		duracion_Can = Segmentar<string>::dividirCadenaPosicion(registro, 6);
		arrMusicales_Can = Segmentar<string>::dividirCadenaPosicion(registro, 9);
		comLetra_Can = Segmentar<string>::dividirCadenaPosicion(registro, 7);
		comMus_Can = Segmentar<string>::dividirCadenaPosicion(registro, 8);
		vista.mostrarInformacion("["+to_string(cont)+"] Nombre: " + nombre_Can + " Ciudad Grabacion: " + ciudadGra_Can + " Duracion: " + duracion_Can + " Arreglista Musical: " + arrMusicales_Can + " Compositor Letra: " + comLetra_Can + " Compositor Musical: " + comMus_Can); 
		
		lista.eliminar(posicion_Can);
		cont++;
	}
			
}

//Consulta 4 
void GestorConsultas::conGenIns() {
	
	NodoArbolBusquedas<string> *nodoAux; 

	vista.mostrarInformacion("Ingrese el genero de la cancion");
	string estGenero = vista.leerDato("[+] Genero: ");
	
	vista.mostrarInformacion("Ingrese el Instrumetno del artista");
	string estInstrumento = vista.leerDato("[+] Instrumento: ");
	
	string busqueda = estGenero + estInstrumento; 
	
	nodoAux = arbolBusq->obtenerArbol(4)->buscar(busqueda);


	if(nodoAux!=nullptr){	//Si existe esta combinacion
		vista.mostrarEtiqueta("Lista de Canciones");
		vista.mostrarEtiqueta(estGenero);
		vista.mostrarEtiqueta(estInstrumento);
		
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		string registro, nombre_Can, nombreArt_Can; 
				
		for(int i = 0; i<tamNodo; i++){
			registro = CancionDAO->leerDato(arreglo[i]);
			nombre_Can = Segmentar<string>::dividirCadenaPosicion(registro,2);
			nombreArt_Can = Segmentar<string>::dividirCadenaPosicion(registro, 3);
			vista.mostrarInformacion("["+to_string(i+1)+"]  Nombre artistico: " + nombreArt_Can + " Nombre de la cancion: " + nombre_Can); 
		}
		
	} else{
		vista.mostrarInformacion("Esta combinacion de cancion no existe.");
	}
	
	nodoAux = arbolBusq->obtenerArbol(15)->buscar(busqueda);

	if(nodoAux!=nullptr){	//Si existe esta combinacion
		vista.mostrarEtiqueta("Lista de Artistas");
		vista.mostrarEtiqueta(estGenero);
		vista.mostrarEtiqueta(estInstrumento);

		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		string registro, nombre_Art, nombreArt_Art; 
				
		for(int i = 0; i<tamNodo; i++){
			registro = ArtistaDAO->leerDato(arreglo[i]);
			nombre_Art = Segmentar<string>::dividirCadenaPosicion(registro,2);
			nombreArt_Art = Segmentar<string>::dividirCadenaPosicion(registro, 3);
			vista.mostrarInformacion("["+to_string(i+1)+"]  Nombre artistico: " + nombreArt_Art + " Nombre del artista: " + nombre_Art); 
		}
		
	} else{
		vista.mostrarInformacion("Esta combinacion no la toca ningun artista.");
	}
	
}

//Consulta 5
void GestorConsultas::conNumVer() {
	Cola<NodoArbolBusquedas<string>*>* colaAux;
    NodoArbolBusquedas<string> *nodoAux;
	
	vista.mostrarInformacion("Ingrese el numero de versiones");
	
	string numVersiones = vista.leerDato("[+] Num. Versiones: ");
	
	colaAux = arbolBusq->obtenerArbol(5)->inorden(numVersiones);
	
	if(colaAux->colaVacia()){
		vista.mostrarInformacion("No se encontraron canciones con mas versiones de las indicadas");
		return;
	}
	int cont=1;
	
	while(!colaAux->colaVacia()){
		
		nodoAux = colaAux->atenderCola();
		
		int tamLista = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		
		string registro, nombre_Can, version_Can, genero_Can, anioPub_Can; 
			
		for(int i = 0; i<tamLista; i++){
			registro = CancionDAO->leerDato(arreglo[i]);
			nombre_Can = Segmentar<string>::dividirCadenaPosicion(registro,2);
			version_Can = Segmentar<string>::dividirCadenaPosicion(registro,4);
			genero_Can = Segmentar<string>::dividirCadenaPosicion(registro, 13);
			anioPub_Can = Segmentar<string>::dividirCadenaPosicion(registro, 12);
			vista.mostrarInformacion("["+to_string(cont)+"] Nombre: " + nombre_Can + " Version: "+ version_Can+" Genero: " + genero_Can + " Anio Publicacion: " + anioPub_Can); 
			cont++;
		}
	}
	
	
}

//Consulta 6
void GestorConsultas::conVersion() {
    
    NodoArbolBusquedas<string> *nodoAux;
	
	vista.mostrarInformacion("Ingrese el tipo de version");
	
	string version = vista.leerDato("[+] Version: ");
	
	nodoAux = arbolBusq->obtenerArbol(6)->buscar(version);
	
	if(nodoAux!=nullptr){	//Si existe la editora
	
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		
		string registro, nombre_Can, gen_Can, anioPub_Can, pais_Can; 
		string registro_Art, listaArtistas_Can, numArtPri_Can, nombre_Art;
		string registro_Link, listaLinks_Can, plataforma_Link;
		int numLinks = 0, tamArt;
		int *posicionesArt, *posicionesLinks;
		string *arregloArtistas, *arregloLinks;
		int cont=0;
		
		for(int i = 0; i<tamNodo; i++){
			registro = CancionDAO->leerDato(arreglo[i]);
			
			listaLinks_Can = Segmentar<string>::dividirCadenaPosicion(registro,17);
			numLinks = Segmentar<string>::dividirCadenaGuionInt(listaLinks_Can);
			
			if(numLinks > 1){
				nombre_Can = Segmentar<string>::dividirCadenaPosicion(registro,2);
				gen_Can = Segmentar<string>::dividirCadenaPosicion(registro, 13);
				anioPub_Can = Segmentar<string>::dividirCadenaPosicion(registro, 12);
				pais_Can = Segmentar<string>::dividirCadenaPosicion(registro, 11);
				vista.mostrarInformacion("["+to_string(i+1)+" Cancion] Titulo: " + nombre_Can + " Genero: "+ gen_Can +" Anio Publicacion: " + anioPub_Can + " Pais Publicacion: " + pais_Can); 
				
				vista.mostrarInformacion("[+ Original] Titulo:" + nombre_Can);
				
				//Impresion plataformas
				posicionesLinks = Segmentar<string>::dividirCadenaGuion(listaLinks_Can, 5);
				arregloLinks = new string[5];
				
				for(int j = 0; j<5; j++){					//Llenar el arreglo de los nombres de las canciones
					if(posicionesLinks[j]!=0){
						registro_Link = LinkDAO->leerDato(posicionesLinks[j]);
						plataforma_Link = Segmentar<string>::dividirCadenaPosicion(registro_Link,1);
						arregloLinks[j] = plataforma_Link;
					}else{
						arregloLinks[j] = "Null";
					}
				}
				cont = 1;
				for(int j = 0; j<5;j++){
					plataforma_Link = arregloLinks[j];
					if(plataforma_Link != "Null"){
						vista.mostrarInformacion("["+to_string(cont)+"Plataforma] Nombre: " + plataforma_Link);
						cont++;
					}
				}
				
				//Impresion Artista
				listaArtistas_Can = Segmentar<string>::dividirCadenaPosicion(registro, 16);
				numArtPri_Can = Segmentar<string>::dividirCadenaPosicion(registro, 15);
				
				tamArt = stoi(numArtPri_Can);
				
				posicionesArt = Segmentar<string>::dividirCadenaGuion(listaArtistas_Can, tamArt);
				arregloArtistas = new string[tamArt];
			
				for(int j = 0; j<tamArt; j++){					//Llenar el arreglo de los nombres de las canciones
					registro_Art = ArtistaDAO->leerDato(posicionesArt[j]);
					nombre_Art = Segmentar<string>::dividirCadenaPosicion(registro_Art,2);
					arregloArtistas[j] = nombre_Art;
				}
				
				Ordenamiento::ordenar(arregloArtistas, tamArt);
				
				for(int j = 0; j<tamArt;j++){
					nombre_Art = arregloArtistas[j];
					vista.mostrarInformacion("["+to_string(j+1)+" Artista] Nombre: " + nombre_Art);
				}
				
			}
		}
		
	} else{
		vista.mostrarInformacion("Esa version no existe.");
	}
    
}

//Consulta 7 
void GestorConsultas::conNombreCancion() {
	NodoArbolBusquedas<string> *nodoAux;
	
	vista.mostrarInformacion("Ingrese el nombre de la cancion");
	
	string nomCan = vista.leerDato("[+] Nombre: ");
	
	nodoAux = arbolBusq->obtenerArbol(12)->buscar(nomCan);
	
	string links;

	if(nodoAux!=nullptr){	//Si existe la cancion
	
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		string registro, version, link, plataforma, links; 
		int verOriginal = 0; //Este nos distinguira el valor original 
		Pila<int> pilaAux; 
	
		for(int i = 0; i<tamNodo; i++){
			registro = CancionDAO->leerDato(arreglo[i]); 
			string ver =  Segmentar<string>::dividirCadenaPosicion(registro,4);
			
			
			if(ver=="Original"){
				verOriginal = arreglo[i]; 
				links = Segmentar<string>::dividirCadenaPosicion(registro, 17);
			} else{
				pilaAux.meter(arreglo[i]);
			}
			
			if(i==1) {
				pilaAux.meter(verOriginal);
			}
		}
		
				
		vista.mostrarInformacion("Versiones de " + nomCan);
		for(int i = 0; i<tamNodo; i++){
			registro = CancionDAO->leerDato(pilaAux.sacar());
			version = Segmentar<string>::dividirCadenaPosicion(registro, 4);
			
			cout << version << endl; 
			vista.mostrarInformacion("["+to_string(i+1)+"] Version: " + version); 

			if("Original" == version){			
				Cola<int> * colaAux = Ordenamiento::procesarCadena(links);
				while(!colaAux->colaVacia()){
					links = LinkDAO->leerDato(colaAux->atenderCola()); 
					plataforma = Segmentar<string>::dividirCadenaPosicion(links,1);					
					link = Segmentar<string>::dividirCadenaPosicion(links,2);
					vista.mostrarInformacion("Plataforma: " + plataforma + "   Link: " + link); 
				}
			}
		}
	} else{
		vista.mostrarInformacion("Esta cancion no�existe.");
	}
}

// Consulta 8
void GestorConsultas::conCoverArt() {
    NodoArbolBusquedas<string> *nodoAux;
    
    vista.mostrarInformacion("Ingrese el nombre del encargado del Cover Art");
    string nomCoverArt = vista.leerDato("[+] Nombre: ");

    nodoAux = arbolBusq->obtenerArbol(8)->buscar(nomCoverArt);
    int tamNodo = 0;

    if (nodoAux != nullptr) {
        tamNodo = nodoAux->lista.tamanoLista();
    }

    string *versiones = new string[tamNodo];  

    if (nodoAux != nullptr) { // Si existe esta persona
        int *arreglo = nodoAux->lista.retornarArreglo();
        string registro, nombreCan, version, anio, genero; 
        
        vista.mostrarInformacion(nomCoverArt + " tiene: " + to_string(tamNodo) + " canciones");
        
        for (int i = 0; i < tamNodo; i++) {
            registro = CancionDAO->leerDato(arreglo[i]);
            nombreCan = Segmentar<string>::dividirCadenaPosicion(registro, 2);
            version = Segmentar<string>::dividirCadenaPosicion(registro, 4);
            anio = Segmentar<string>::dividirCadenaPosicion(registro, 12);
            genero = Segmentar<string>::dividirCadenaPosicion(registro, 13);
            vista.mostrarInformacion("[" + to_string(i+1) + "] Nombre: " + nombreCan);
            vista.mostrarInformacion("    Version: " + version); 
            vista.mostrarInformacion("    A�o: " + anio);
            vista.mostrarInformacion("    G�nero: " + genero);
            versiones[i] = version; 
        }

        delete[] arreglo; // Libera el arreglo din�mico
    } else {
        vista.mostrarInformacion("Ese encargado no existe.");
    }

    vista.mostrarInformacion(nomCoverArt + " tiene: " + to_string(Ordenamiento::contarPalabrasUnicas(versiones, tamNodo)) + " versiones");
    
    delete[] versiones; // Aseg�rate de escribir esta l�nea manualmente
}


//Consulta 9
void GestorConsultas::conFotografiayEstudio() {
    NodoArbolBusquedas<string> *nodoAux;
	
	vista.mostrarInformacion("Ingrese el nombre del encargado de fotografia");
	
	string fotografia = vista.leerDato("[+] Nombre: ");
	
	vista.mostrarInformacion("Ingrese el estudio de grabacion");
	
	string estudio = vista.leerDato("[+] Estudio: ");
	
	nodoAux = arbolBusq->obtenerArbol(1)->buscar(fotografia+estudio);
	
	if(nodoAux!=nullptr){	//Si existe la editora
	
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		string registro, titulo_Alb, pais_Alb; 
		
		for(int i = 0; i<tamNodo; i++){
			registro = AlbumDAO->leerDato(arreglo[i]);
			titulo_Alb = Segmentar<string>::dividirCadenaPosicion(registro,2);
			pais_Alb = Segmentar<string>::dividirCadenaPosicion(registro, 3);
			vista.mostrarInformacion("["+to_string(i+1)+"] Titulo: " + titulo_Alb + " Pais Grabacion: " + pais_Alb); 
		}
		
	} else{
		vista.mostrarInformacion("No se encontro informacion con ese encargado de fotografia en el estudio de grabacion.");
	}
    
}

//Consulta 10
void GestorConsultas::conCompositorLetra() {
    
    NodoArbolBusquedas<string> *nodoAux;
	
	vista.mostrarInformacion("Ingrese el nombre del compositor de la letra");
	
	string compositor = vista.leerDato("[+] Nombre: ");
	
	nodoAux = arbolBusq->obtenerArbol(2)->buscar(compositor);
	
	if(nodoAux!=nullptr){	//Si existe la editora
	
		int tamNodo = nodoAux->lista.tamanoLista();
		int *arreglo = nodoAux->lista.retornarArreglo();
		string registro, nombre_Can, gen_Can, anioPub_Can, album_Can;
		string listaLinks;
		int numLinks;
		
		for(int i = 0; i<tamNodo; i++){
			registro = CancionDAO->leerDato(arreglo[i]);
			nombre_Can = Segmentar<string>::dividirCadenaPosicion(registro,2);
			gen_Can = Segmentar<string>::dividirCadenaPosicion(registro, 13);
			anioPub_Can = Segmentar<string>::dividirCadenaPosicion(registro,12);
			album_Can = Segmentar<string>::dividirCadenaPosicion(registro,14);
			
			if(album_Can == "Null"){
				album_Can = "Ninguno";
			}
			
			listaLinks = Segmentar<string>::dividirCadenaPosicion(registro,17);
			numLinks = Segmentar<string>::dividirCadenaGuionInt(listaLinks);
			
			vista.mostrarInformacion("["+to_string(i+1)+"] Nombre: " + nombre_Can + " Genero: " + gen_Can+ " Anio Publicacion: " + anioPub_Can + " Album al que pertenece: " + album_Can +" Num. Plataformas: " + to_string(numLinks)); 
		}
		
	} else{
		vista.mostrarInformacion("No se encontro informacion con el compositor de la letra.");
	}
}



GestorConsultas::~GestorConsultas() {
}

