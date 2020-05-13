#include "inventario.h"

template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw(width) << setfill(' ') << t;
}

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

    printElement("ID:", 7);
    printElement("Producto:", 45);
    printElement("Unidades:", 15);
    printElement("Costo:", 15);
    cout << endl;

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


        if (id != "ID"){
            printElement(id, 7);
            printElement(product, 45);
            printElement(uni, 15);
            printElement(costo, 15);
            cout << endl;
        }
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

void inventario::descript()
{
    string descript = "";

    cout << "Oferta del combo: ";

    cin.ignore(100, '\n');
    getline (cin, descript);

    cout << "Descripcion del combo: " << descript << endl;
}
