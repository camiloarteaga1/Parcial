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
    void descript(int cont, string dirDescripCombos); //Recibe y guarda la descripcion del combo a ofrecer
    void combos(map <int, vector<string>>, string dircombo); //Crea los combos
    void leer(string dir); //Lee un archivo linea a linea mientras no sea el final e imprime la linea
    int compra(string comb, string cant, string dircombo); //Realiza la compra del combo actualiza los datos del inventario y devuelve el dinero total a pagar

private:
    const string dirInventario = "../Archivos/Inventario.txt";

    void escribir(string dir, string txt); //Escribe en un archivo un string
};

#endif // INVENTARIO_H
