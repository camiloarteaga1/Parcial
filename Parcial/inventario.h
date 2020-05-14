#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
using namespace std;

class inventario
{
public:
    inventario();
    ~inventario();
    void imprimir(); //Imprime el inventario para el admin
    void descript(); //Guarda la descripcion del combo a ofrecer
    void combos(map <int, vector<string>>, string dircombo); //Crea los combos

private:
    const string dirInventario = "../Archivos/Inventario.txt";
    string leer(string dir);
    void escribir(string dir, string txt); //Escribe en un archivo un string
};

#endif // INVENTARIO_H
