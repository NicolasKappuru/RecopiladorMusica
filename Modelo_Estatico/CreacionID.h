#include <iostream>
#include <string>
#include <algorithm> 

#ifndef CREACIONID_H
#define CREACIONID_H
using namespace std;



class CreacionID{
	public:
		
		static string crearID_Art(string palabra1, string palabra2, string palabra3, string palabra4) {
    		string sub1 = palabra1.substr(0, 3);
    		string sub2 = palabra2.substr(0, 3);
    		string sub3 = palabra3.substr(0, 3);
    		string sub4 = palabra4.substr(0, 3);
    		transform(sub1.begin(), sub1.end(), sub1.begin(), ::tolower);
    		transform(sub2.begin(), sub2.end(), sub2.begin(), ::tolower);
    		transform(sub3.begin(), sub3.end(), sub3.begin(), ::tolower);
    		transform(sub4.begin(), sub4.end(), sub4.begin(), ::tolower);

    		return sub1 + sub2 + sub3 + sub4;
		}
		
		static string crearID_Alb(string palabra1, string palabra2, string palabra3, string palabra4, 
            string palabra5, string palabra6, string palabra7, string palabra8) {
    		string sub1 = palabra1.substr(0, 2);
    		string sub2 = palabra2.substr(0, 2);
    		string sub3 = palabra3.substr(0, 2);
    		string sub4 = palabra4.substr(0, 2);
   	 		string sub5 = palabra5.substr(0, 2);
    		string sub6 = palabra6.substr(0, 2);
    		string sub7 = palabra7.substr(0, 2);
    		string sub8 = palabra8.substr(0, 2);
    		transform(sub1.begin(), sub1.end(), sub1.begin(), ::tolower);
    		transform(sub2.begin(), sub2.end(), sub2.begin(), ::tolower);
    		transform(sub3.begin(), sub3.end(), sub3.begin(), ::tolower);
    		transform(sub4.begin(), sub4.end(), sub4.begin(), ::tolower);
    		transform(sub5.begin(), sub5.end(), sub5.begin(), ::tolower);
    		transform(sub6.begin(), sub6.end(), sub6.begin(), ::tolower);
    		transform(sub7.begin(), sub7.end(), sub7.begin(), ::tolower);
    		transform(sub8.begin(), sub8.end(), sub8.begin(), ::tolower);

    		return sub1 + sub2 + sub3 + sub4 + sub5 + sub6 + sub7 + sub8;
		}
		
	static string crearID_Can(string palabra1, string palabra2, string palabra3, string palabra4, 
                          string palabra5, string palabra6, string palabra7, string palabra8, 
                          string palabra9, string palabra10, string palabra11, string palabra12, 
                          string palabra13, string palabra14) {
    string id;
    
    // Tomar los tres primeros caracteres de las tres primeras palabras y convertirlos a minúscula
    id += tolower(palabra1[0]);
    if (palabra1.length() > 1) id += tolower(palabra1[1]);
    if (palabra1.length() > 2) id += tolower(palabra1[2]);
    
    id += tolower(palabra2[0]);
    if (palabra2.length() > 1) id += tolower(palabra2[1]);
    if (palabra2.length() > 2) id += tolower(palabra2[2]);
    
    id += tolower(palabra3[0]);
    if (palabra3.length() > 1) id += tolower(palabra3[1]);
    if (palabra3.length() > 2) id += tolower(palabra3[2]);
    
    id += tolower(palabra4[0]);
    id += tolower(palabra5[0]);
    id += tolower(palabra6[0]);
    id += tolower(palabra7[0]);
    id += tolower(palabra8[0]);
    id += tolower(palabra9[0]);
    id += tolower(palabra10[0]);
    id += tolower(palabra11[0]);
    id += tolower(palabra12[0]);
    id += tolower(palabra13[0]);
    id += tolower(palabra14[0]);
    
    return id;
}

		
		static string combinarCadenasAlb(string palabra1, string palabra2, string palabra3, string palabra4, string palabra5,string palabra6, string palabra7, string palabra8, string palabra9) {
    		return palabra1 + "|" + palabra2 + "|" + palabra3 + "|" + palabra4 + "|" + palabra5 + "|" +
        	   	palabra6 + "|" + palabra7 + "|" + palabra8 + "|" + palabra9 + "|";
		}
		
		static string combinarCadenasCan(string palabra1, string palabra2, string palabra3, string palabra4,string palabra5, string palabra6, string palabra7, string palabra8,string palabra9, string palabra10, string palabra11, string palabra12, string palabra13, string palabra14, string palabra15) {
	    	return palabra1 + "|" + palabra2 + "|" + palabra3 + "|" + palabra4 + "|" + palabra5 + "|" +
           		palabra6 + "|" + palabra7 + "|" + palabra8 + "|" + palabra9 + "|" + palabra10 + "|" +
           		palabra11 + "|" + palabra12 + "|" + palabra13 +"|" + palabra14 + "|" + palabra15 + "|";
		}
		
		static string combinarCadenasCanc(string palabra1, string palabra2, string palabra3, string palabra4,string palabra5, string palabra6, string palabra7, string palabra8,string palabra9, string palabra10, string palabra11, string palabra12, string palabra13, string palabra14, string palabra15, string palabra16, string palabra17) {
	    	return palabra1 + "|" + palabra2 + "|" + palabra3 + "|" + palabra4 + "|" + palabra5 + "|" +
           		palabra6 + "|" + palabra7 + "|" + palabra8 + "|" + palabra9 + "|" + palabra10 + "|" +
           		palabra11 + "|" + palabra12 + "|" + palabra13 +"|" + palabra14 + "|" + palabra15 + "|"+
				palabra16 + "|" + palabra17 +"|";
		}

		static string combinarCadenasArt(string palabra1,	string palabra2, string palabra3, string palabra4, string palabra5){
    		return palabra1 + "|" + palabra2 + "|" + palabra3 + "|" + palabra4 + "|" + palabra5 + "|";
		}
			
		static string combinarCadenasLink(string palabra1,	string palabra2){
    		return palabra1 + "|"+ palabra2 + "|";
		}
		
		//Este no lleva un |, porque ya lo trae, no cambiar
		static string combinar3Cadenas(string palabra1,	string palabra2, string palabra3){
    		return palabra1 + palabra2 + "|" + palabra3 + "|";
		}	
};

#endif
