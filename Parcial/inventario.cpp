#include "inventario.h"

inventario::inventario()
{

}
inventario::~inventario()
{

}
void inventario::imprimir()
{
    ifstream invent;

    invent.open(dirInventario, ios::in);

    if(!invent.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    for (string line; getline (invent, line); ){

        string product = "", uni = "", id = "", costo = "";


        for (unsigned int i = 0; i < line.find(","); ++i){ //Hasta que encuentre la primera ","
            id += line.at(i); //String con el ID del producto
        }

        for (unsigned int i = line.find(",") + 1; i < line.find(";"); ++i){
            product += line.at(i);
        }

        for (unsigned int i = line.find(";") + 1; i < line.find(":"); ++i){
            uni += line.at(i);
        }

        for (unsigned int i = line.find(":") + 1; i < line.length(); ++i){
            costo += line.at(i);
        }

        if (id != "ID") cout << "ID: " << id << " Producto: " << product << " Unidades: " << uni << " Costo: " << costo << endl;
    }
    invent.close();
}

string inventario::leer(string dir)
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
