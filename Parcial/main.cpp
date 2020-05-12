#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <cstring>
using namespace std;

const string psAdmin = "../Archivos/ClaveAdmin.txt";

//Funciones
template <typename T>
string leer(T dir);

template <typename U>
bool validacion(U ps);

int adm();
int user();

int main()
{
    int opt = 0;
    bool conta = false;

    while (conta == false){
        cout << "BIENVENIDO A CINE KAKARIKO" << endl;
        cout << "\nComo desea ingresar? Escriba 1, 2 o 3." << endl;
        cout << "1. Administrador." << endl;
        cout << "2. Usuario." << endl;
        cout << "3. Salir." << endl;
        cout << "\nOpcion: ";
        cin >> opt;

        if (opt == 1) adm();

        else if (opt == 2) user();

        else if (opt == 3) conta = true;

        else{
            cout << "No me parece que este chico sea muy listo." << endl;
            conta = true;
       }
    }
}

//Despliega el menu del adm y ejecuta sus procesos
int adm()
{
    int opt = 0;
    string pr = "", psusu = "", saldo= "", data = "", codi = "", ps, txt, help = "Si";
    bool aux = false;

    cout << "\nBienvenido administrador" << endl;
    cout << "Por favor escriba su clave:";
    cin >> ps;

    while (validacion(ps) == false){ //Verifica si la clave es correcta

        cout << "\nContrasena incorrecta,intente nuevamente" << endl;
        cout << "Ingrese de nuevo: ";
        cin >> ps;
    }

    cout << "\nOperacion a realizar: " << endl;
    cout << "1.Crear combos" << "\n2.Salir" << endl;
    cout << "Opcion: ";
    cin >> opt;

    if (opt == 1){

        while (help == "Si"){
            cout << "\nIngrese un producto del combo: ";
            cin >> pr;

            cout << "Desea ingresar otro producto?\nSi o No" << endl;
            cin >> help;
        }

        cout << "\nCombo creado" << endl;

        cout << "El valor es de: " << endl;

        }

    else if (opt == 2) return 0;

    else cout << "Reinicie.";

    return 0;
}

//Despliega el menu del usuario
int user()
{

    return 0;
}

//Valida la clave del admin
template <typename T>
bool validacion(T ps)
{
    string enps = leer(psAdmin); //String que contiene la contraseña del txt

    for(unsigned int i = 0; i < enps.length() ; ++i){ //Compara termino a termino la clave
        if (ps.at(i) != enps.at(i)) return false;
    }

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
