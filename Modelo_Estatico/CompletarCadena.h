#include <string>
#include <sstream>
#ifndef COMPLETARCADENA_H
#define COMPLETARCADENA_H

using namespace std;

class CompletarCadena{
	public:
		
		static string rellenarConCeros(string str, size_t tamanoDeseado) {
    		if (str.length() >= tamanoDeseado) {
        		return str; // Si ya cumple o excede el tamaño, no se modifica.
    		}
    	return str + string(tamanoDeseado - str.length(), '0');
		}
		
		static string crearLista(string original, string agregado, int value){
			original = original+agregado+"-";
			
			if(value == 1){
				original.pop_back(); 
				return original; 
			} 		
			return original; 
		}
		
};


#endif
