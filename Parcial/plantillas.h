#ifndef PLANTILLAS_H
#define PLANTILLAS_H

#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const string diraux = "../Archivos/txtAux.txt"; //Direccion auxiliar, no hay que cambiarla

//Valida la clave del admin
template <typename T>
bool validacion(T ps, T psAdmin, unsigned int semi)
{
    {
        string enps = leer(psAdmin); //String que contiene la contraseña encriptada del sudo
        string code;

        convert(ps, diraux);
        code = codificacion2(diraux, semi); //Contraseña encriptada ingresada por el usuario

        for(unsigned int i = 0; i < enps.length() ; ++i){ //Compara termino a termino la clave
            if (code.at(i) != enps.at(i)) return false;
        }

        borrar(diraux);

        return true;
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

#endif // PLANTILLAS_H
