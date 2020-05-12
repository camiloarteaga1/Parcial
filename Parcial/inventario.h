#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

class inventario
{
public:
    inventario();
    ~inventario();
    void imprimir(); //Imprime el inventario para el admin
    void descript(); //Guarda la descripcion del combo a ofrecer

private:
    const string dirInventario = "../Archivos/Inventario.txt";
    string leer(string dir);
};

#endif // INVENTARIO_H
