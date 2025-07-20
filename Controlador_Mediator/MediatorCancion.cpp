#include "MediatorCancion.h"

#include "ModeloDAO_Interfaces/DAO.h"
#include "ModeloDAO_Objetos/CancionDAOImpl.h"
#include "ModeloDAO_Objetos/ArtistaDAOImpl.h"

#include "Modelo_Estatico/CompletarCadena.h"
#include "Modelo_Estatico/CreacionID.h"

#include "Modelo_PosicionesLibres/SingletonPosLibres.h"
#include "Modelo_Singleton_Arboles/SingletonArbolID.h"
#include "Modelo_Singleton_Arboles/SingletonArbolBusq.h"


#include <iostream> // Para mensajes de consola, si es necesario
#include <string>

MediatorCancion::MediatorCancion(DAO* concreto) {
	posLibres = SingletonPosLibres<int>::obtenerInstanciaPosLibres();
	arbolID = SingletonArbolID<string>::obtenerInstanciaArbolID(); 
	arbolBusq = SingletonArbolBusq<string>::obtenerInstanciaArbolBusqueda(); 
	nodoAux = nullptr; 
	vista = VistaConsola();
	ArtistaDAO = new ArtistaDAOImpl();  
	CancionDAO = concreto;
	cadena = ""; 
}

string MediatorCancion::formulario(string album, int numArt){	
	//Requerimos de un formulario el cual pida los atributos. 
	//Utilizaremos al objeto vista para ello
	
	string nombre_Can = vista.leerDato("[1] Inserte el nombre de la cancion: ");
	string nombreArt_Can = vista.leerDato("[2] Inserte nombre artistico de la cancion: ");
	string version_Can = vista.leerDato("[3] Inserte version de la cancion: ");
	string duracion_Can = vista.leerDato("[4] Inserte la duracion (MM:SS): ");
	string comLetra_Can = vista.leerDato("[5] Inserte el compositor de la letra: ");
	string comMus_Can = vista.leerDato("[6] Inserte el compositor de la musica: ");
	string arrMusicales_Can = vista.leerDato("[7] Inserte el arreglista musical: ");
	string ciudadGra_Can = vista.leerDato("[8] Inserte ciudad de grabacion: ");
	string paisGra_Can = vista.leerDato("[9] Inserte pais de grabacion: ");
	string anioPub_Can = vista.leerDato("[10] Inserte anio de publicacion: ");
	string genero_Can = vista.leerDato("[11] Inserte el genero de la cancion: ");
	string album_Can = album; // Recibe un parametro
	string id_Can = CreacionID::crearID_Can(nombre_Can, nombreArt_Can, version_Can, "1", duracion_Can, "0", comLetra_Can, comMus_Can, arrMusicales_Can, ciudadGra_Can, paisGra_Can, anioPub_Can, genero_Can, album_Can);
	string numArtPri_Can = to_string(numArt);

	if(verificacion(id_Can)) return "Repetido";
	arbolID->obtenerArbol(2)->insertar(id_Can, posLibres->obtenerCola(1)->retornarValor());
  	arbolID->setAuxID(id_Can); 
  	
  	arbolBusq->setGeneroAux(genero_Can);
  	
	arbolBusq->obtenerArbol(12)->insertar(nombre_Can);
	nodoAux = arbolBusq->obtenerArbol(12)->buscar(nombre_Can); 
	nodoAux->lista.insertar(posLibres->obtenerCola(1)->retornarValor(),nombreArt_Can);
	
	//Actualiza arbol consulta 3
	actualizarArbCon(3, duracion_Can, ciudadGra_Can, nombre_Can);      
    
    //Actualiza arbol consulta 5
	actualizarArbCon5(nombre_Can, genero_Can, anioPub_Can, true, 0); //Consulta 5
	
	//Actualizar arbol consulta 6
    actualizarArbCon(6, version_Can, nombre_Can, anioPub_Can);      
    
    //Actualizar arbol consulta 7
    actualizarArbCon(7, nombre_Can, version_Can, nombreArt_Can); 
    
    //Aqui actualiza el arbol de la consulta 8
	actualizarArbCon(8, arbolBusq->getCoverArtAux(), genero_Can,anioPub_Can);
	
	//Actualiza arbol consulta 10
    actualizarArbCon(10, comLetra_Can, nombre_Can, anioPub_Can);   
  	
  	//Se crea la Cadena
	cadena = CreacionID::combinarCadenasCan(id_Can,nombre_Can, nombreArt_Can, version_Can, "1" ,duracion_Can, comLetra_Can, comMus_Can, arrMusicales_Can, ciudadGra_Can, paisGra_Can, anioPub_Can, genero_Can, album_Can, numArtPri_Can);
	return cadena; 
}

bool MediatorCancion::insercion() {
	string cadenaDef = CompletarCadena::rellenarConCeros(cadena,302); //Poner tama�o original de la cadena
	int pos = definirPosicion(); 
	CancionDAO->modificarDato(pos,cadenaDef); 

	//actualizamos el aux de busqueda 4
	arbolBusq->setGeneroAux("Null");
    return true;
}

bool MediatorCancion::eliminacion() {
	vista.mostrarInformacion("Digite el nombre de la cancion que desea eliminar");
	
	string porEliminar = vista.leerDato("[+] Eliminar a: ");
	
	nodoAux = arbolBusq->obtenerArbol(12)->buscar(porEliminar);

	if(nodoAux == nullptr){
		vista.mostrarInformacion("La cancion no existe");
		return false; 
	} 

	int tamNodo = nodoAux->lista.tamanoLista();
	int *arreglo = nodoAux->lista.retornarArreglo();
	string registro, nomArtCan, version, anio; 
	
	vista.mostrarInformacion("Digita el numero de la opcion que eliminaras");
	
	for(int i = 0; i<tamNodo; i++){
		registro = CancionDAO->leerDato(arreglo[i]);
		nomArtCan = Segmentar<string>::dividirCadenaPosicion(registro,3);
		version = Segmentar<string>::dividirCadenaPosicion(registro, 4);
		anio = Segmentar<string>::dividirCadenaPosicion(registro, 12);
		vista.mostrarInformacion("["+to_string(arreglo[i])+"] " + nomArtCan + " " + version + " " + anio); 
	}
	
	int eliminar = vista.leerDatoInt("Eleccion: "); 
	    	
	registro = CancionDAO->leerDato(eliminar);
	string albumCan = Segmentar<string>::dividirCadenaPosicion(registro, 14);

	if(albumCan != "Null"){
		vista.mostrarInformacion("La cancion pertenece a un album, no se puede eliminar");
		return false; 
	}
	
	string lista = Segmentar<string>::dividirCadenaPosicion(registro, 16);
	int tamArr = stoi(Segmentar<string>::dividirCadenaPosicion(registro, 15));
	
	string idEliminar = Segmentar<string>::dividirCadenaPosicion(registro, 1); //Actualizar arbol ID
	string tiempoEliminar = Segmentar<string>::dividirCadenaPosicion(registro, 6); //Actualizar arbol consulta 3
	string versionEliminar = Segmentar<string>::dividirCadenaPosicion(registro, 4); //Actualizar arbol consulta 3
	string compLetraEliminar = Segmentar<string>::dividirCadenaPosicion(registro, 7); //Actualizar arbol consulta 10
	
	//Para actualizar arbol consulta 4
	string generoEliminar = Segmentar<string>::dividirCadenaPosicion(registro, 13);
	string inst_Art;

	// Para actualizar arbol consulta 4, 14
	int * arr = Segmentar<string>::dividirCadenaGuion(lista, tamArr);
	
	string registroArt = ""; 
	string nombreArtista = "";
	
	//Actualiza arbol consulta 4, 14
	for(int i = 0; i<tamArr;i++){
		registroArt = ArtistaDAO->leerDato(arr[i]);

		nombreArtista = Segmentar<string>::dividirCadenaPosicion(registroArt,2);
		nodoAux = arbolBusq->obtenerArbol(14)->buscar(nombreArtista);
		nodoAux->lista.eliminar(eliminar);	

		inst_Art = Segmentar<string>::dividirCadenaPosicion(registroArt,5);
		nodoAux = arbolBusq->obtenerArbol(4)->buscar(generoEliminar+inst_Art);
		nodoAux->lista.eliminar(eliminar);
	}

	arbolID->obtenerArbol(2)->eliminar(idEliminar); //Arbol de IDs
	arbolBusq->obtenerArbol(12)->eliminar(porEliminar); // Arbol de nombres

	CancionDAO->eliminarNposLibre(eliminar); //
	posLibres->obtenerCola(1)->insCola(eliminar); //Pasamos la posicion como libre
	
	nodoAux = arbolBusq->obtenerArbol(3)->buscar(tiempoEliminar);	//Actualiza arbol consulta 3
	nodoAux->lista.eliminar(eliminar);
	
	nodoAux = arbolBusq->obtenerArbol(6)->buscar(versionEliminar);	//Actualiza arbol consulta 6
	nodoAux->lista.eliminar(eliminar);
	
	nodoAux = arbolBusq->obtenerArbol(7)->buscar(porEliminar);	//Actualiza arbol consulta 7
	nodoAux->lista.eliminar(eliminar);
	
	nodoAux = arbolBusq->obtenerArbol(10)->buscar(compLetraEliminar);	//Actualiza arbol consulta 10
	nodoAux->lista.eliminar(eliminar);
	
	actualizarArbCon5(porEliminar, "", "", false, eliminar);
	
		

	return true; 
}

bool MediatorCancion::actualizacion() {
    eliminacion();
    insercion();
    return true; 

}

bool MediatorCancion::verificacion(string comparar) {
    vista.mostrarInformacion("\nVerificando que no se repita el registro..." + comparar);
	if(arbolID->obtenerArbol(2)->buscar(comparar)==nullptr) return false; 
	arbolID->setAuxID(comparar); 
	return true; //Si se repite
}

int MediatorCancion::definirPosicion(){
	int pos = posLibres->obtenerCola(1)->atenderCola(); //La cola de artista 
	int tam = posLibres->getTamCancion(); 
	if(pos>tam){
		posLibres->obtenerCola(1)->insCola(pos+1);
		posLibres->sumTamCancion(); 
		return pos; 
	}else{
		return pos; 
	}
}

void MediatorCancion::setCadena(string cadena1, string cadena2, string cadena3){
	cadena = CreacionID::combinar3Cadenas(cadena1, cadena2, cadena3); 
}

void MediatorCancion::actualizarArbCon(int numArb, string parametro, string ord1, string ord2){
	arbolBusq->obtenerArbol(numArb)->insertar(parametro);
	nodoAux = arbolBusq->obtenerArbol(numArb)->buscar(parametro); 
	string ordenamiento = ord1 + ord2; 
	nodoAux->lista.insertar(posLibres->obtenerCola(1)->retornarValor(), ordenamiento);
}

void MediatorCancion::actualizarArbCon5(string nombre, string ord1, string ord2, bool inserta, int posEliminar){
	
	Cola<NodoArbolBusquedas<string>*>* colaInorden = arbolBusq->obtenerArbol(5)->inordenFull();
	NodoArbolBusquedas<string>* nodoAux, *nuevaLista;
	
	int numVersiones, tamLista;
	string registroComp, nomComp;
	int *posCan;
	
	string ordenamiento2;
	bool encontrado = false;	
	
	if(inserta == true){
		string ordenamiento = ord1+ord2;
		
		
		if(colaInorden->colaVacia()) {
			actualizarArbCon(5, "1", ord1, ord2);
			return;
		}
		while(!colaInorden->colaVacia() && encontrado==false){
			nodoAux = colaInorden->atenderCola();
			
			numVersiones = stoi(nodoAux->clave);
			tamLista = nodoAux->lista.tamanoLista();
			
			if(!nodoAux->lista.listaVacia()){
				
				posCan = nodoAux->lista.retornarArreglo();
					
				for(int i=0;i<tamLista;i++){
					
					registroComp = CancionDAO->leerDato(posCan[i]);
					nomComp = Segmentar<string>::dividirCadenaPosicion(registroComp, 2);
						
					if(nombre == nomComp){
						
						ordenamiento2 = nodoAux->lista.getInfo(nodoAux->lista.buscarNodo(posCan[i]));
						nodoAux->lista.eliminar(posCan[i]);
						
						nuevaLista = arbolBusq->obtenerArbol(5)->buscar(to_string(numVersiones+1));
						
						if(nuevaLista==nullptr){
							arbolBusq->obtenerArbol(5)->insertar(to_string(numVersiones+1));
							nuevaLista = arbolBusq->obtenerArbol(5)->buscar(to_string(numVersiones+1));
						}
						
						nuevaLista->lista.insertar(posCan[i], ordenamiento2);
						
						encontrado = true;
					}	
				}
			}
		}
		if(encontrado == true){
			actualizarArbCon(5, to_string(numVersiones+1), ord1, ord2);
		}else{
			actualizarArbCon(5, "1", ord1, ord2);
		}
	}else{	//Modificar arbol eliminacion
		if(colaInorden->colaVacia()){
			return;
		}
		
		while(!colaInorden->colaVacia() && encontrado==false){
			
			nodoAux = colaInorden->atenderCola();
			
			numVersiones = stoi(nodoAux->clave);
			tamLista = nodoAux->lista.tamanoLista();
			
			if(!nodoAux->lista.listaVacia()){
				
				posCan = nodoAux->lista.retornarArreglo();
					
				for(int i=0;i<tamLista;i++){
					
					registroComp = CancionDAO->leerDato(posCan[i]);
					nomComp = Segmentar<string>::dividirCadenaPosicion(registroComp, 2);
						
					if(nombre == nomComp){
						
						ordenamiento2 = nodoAux->lista.getInfo(nodoAux->lista.buscarNodo(posCan[i]));
						nodoAux->lista.eliminar(posCan[i]);
						
						nuevaLista = arbolBusq->obtenerArbol(5)->buscar(to_string(numVersiones-1));
						
						if(nuevaLista==nullptr){
							arbolBusq->obtenerArbol(5)->insertar(to_string(numVersiones-1));
							nuevaLista = arbolBusq->obtenerArbol(5)->buscar(to_string(numVersiones-1));
						}
						
						nuevaLista->lista.insertar(posCan[i], ordenamiento2);
						
						encontrado = true;
					}	
				}
			}
		}
		nodoAux->lista.eliminar(posEliminar);
	}
}
//Las colas estan de 0 a 2, 


MediatorCancion::~MediatorCancion() {
}

