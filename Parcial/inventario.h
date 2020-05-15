#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <iostream>
#include <conio.h>
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <map>
#include <vector>
#include <plantillas.h>
using namespace std;

class inventario
{
public:
    inventario();
    ~inventario();
    void imprimir(string dir); //Imprime el inventario para el admin
    void descript(int cont, string dirDescripCombos); //Recibe y guarda la descripcion del combo a ofrecer
    void combos(map <int, vector<string>>, string dircombo); //Crea los combos
    void leer(string dir); //Lee un archivo linea a linea mientras no sea el final e imprime la linea
    bool compra(vector <string> datos); //Realiza la compra del combo actualiza los datos del inventario y devuelve el dinero total a pagar
    void printfact(string fecha); //Imprime las ventas
    void Copy(); //Rellena el inventario

private:
    const string dirInventario = "../Archivos/Inventario.txt";
    const string dirInventarioActu = "../Archivos/InventarioActu.txt";
    const string dirfact = "../Archivos/dirfact.txt";
    const string dirtemp = "../Archivos/dirtemp.txt";

    void escribir(string dir, string txt); //Escribe en un archivo un string
    int pago(int costo, int A); //Problema 1 practica 2 devuelve el sobrante al usuario
    void genfact(vector <string> fact); //Lee un vector y genera la factura
    bool modinv(vector <string> mod); //Lee un vector que permite actualizar el inventario

};

#endif // INVENTARIO_H
