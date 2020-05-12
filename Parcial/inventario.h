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
    void imprimir();

private:
    const string dirInventario = "../Archivos/Inventario.txt";
    string leer(string dir);
};

#endif // INVENTARIO_H
