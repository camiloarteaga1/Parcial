#ifndef PLANTILLAS_H
#define PLANTILLAS_H

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;


//Borra un archivo
template <typename T>
void borrar(T dir)
{
    if(remove(dir.c_str()) != 0) //Elimina un archivo
       perror("Error al borrar archivo!.");
}

//Lee lo de un archivo y lo asigna a una variable
template <typename T>
string leer(T dir)
{
    ifstream archivo;
    string txt;

    archivo.open(dir.c_str(),ios::in);

    if(!archivo.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    while(!archivo.eof()) { //Lee linea a linea mientras no sea el final del archivo
        getline(archivo, txt);
    }

    archivo.close(); //Cierra el archivo

    return txt;
}


//Valida la clave del admin
template <typename T>
bool validacion(T psAdmin, T code)
{
    string enps = leer(psAdmin); //String que contiene la contraseña encriptada del sudo

    for(unsigned int i = 0; i < enps.length() ; ++i){ //Compara termino a termino la clave
        if (code.at(i) != enps.at(i)) return false;
    }

    return true;
}

//Verifica si los caracteres ingrsados son numeros
template <typename T>
bool valnum (T num){

    for(unsigned int i = 0; i < num.length(); ++i){ //Verifica si el string tiene caracteres no validos
        //Rango caracteres numericos en el codigo ASCII
        if (num.at(i) <= 47) return false;
        if (num.at(i) >= 58) return false;
    }
    return true;
}

#endif // PLANTILLAS_H
