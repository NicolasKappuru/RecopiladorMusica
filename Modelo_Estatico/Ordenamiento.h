#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <string>

using namespace std;

class Ordenamiento {
public:
    static void ordenar(string* &arr, int size) {
        for (int i = 1; i < size; i++) {
            string clave = arr[i];
            int izquierda = 0, derecha = i - 1;
            while (izquierda <= derecha) {
                int medio = izquierda + (derecha - izquierda) / 2;
                if (arr[medio] > clave) {
                    derecha = medio - 1;
                } else {
                    izquierda = medio + 1;
                }
            }
            for (int j = i - 1; j >= izquierda; j--) {
                arr[j + 1] = arr[j];
            }
            arr[izquierda] = clave;
        }
    }

    static int contarPalabrasUnicas(string* arr, int n) {
        int uniqueCount = 0;
        for (int i = 0; i < n; i++) {
            bool repetida = false;
            for (int j = 0; j < i; j++) { 
                if (arr[i] == arr[j]) {
                    repetida = true;
                    break;
                }
            }
            if (!repetida) {
                uniqueCount++;
            }
        }
        return uniqueCount;
    }
    
    static Cola<int>* procesarCadena(const std::string& cadena) {
    Cola<int>* cola = new Cola<int>();
    std::stringstream ss(cadena);
    std::string segmento;
    
    while (std::getline(ss, segmento, '-')) {
        int numero = std::stoi(segmento);
        if (numero != 0) {
            cola->insCola(numero);
        }
    }
    return cola;
}

};

#endif

