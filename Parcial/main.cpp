#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <map>
#include <inventario.h>

using namespace std;

const string psAdmin = "../Archivos/ClaveAdmin.txt";

//Funciones
template <typename T>
string leer(T dir);

template <typename >
bool validacion(T ps);

int adm();
int user();

int main()
{
    int opt = 0;
    bool conta = false;
    cout << "BIENVENIDO A CINE KAKARIKO" << endl;

    while (conta == false){
        cout << "Menu" << endl;
        cout << "Operacion a realizar. Escriba 1, 2 o 3." << endl;
        cout << "1. Administrador." << endl;
        cout << "2. Usuario." << endl;
        cout << "3. Salir." << endl;
        cout << "Opcion: ";
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
    int opt = 0, cont = 0;
    string pr = "", id = "", unidades = "", ps, help = "Si", comb="";
    bool aux = false;
    map <int, string> combos;
    inventario inv;

    cout << "\nIngresando como administrador" << endl;
    cout << "Por favor escriba su clave:";
    cin >> ps;

    while (validacion(ps) == false){ //Verifica si la clave es correcta

        cout << "\nContrasena incorrecta,intente nuevamente" << endl;
        cout << "Ingrese de nuevo: ";
        cin >> ps;
    }
    system("cls");
    cout << "Bienvenido administrador" << endl;

    while (aux == false){

        cout << "Operacion a realizar: " << endl;
        cout << "1.Crear combos" << "\n2.Salir" << endl;
        cout << "Opcion: ";
        cin >> opt;

        if (opt == 1){ //Se empieza a crear el combo de acuerdo al inventario

            while (help == "Si"){

                system("cls");
                cout << "Productos disponibles: " << endl;
                inv.imprimir(); //Imprime el inventario disponible

                cout << "\nIngrese un producto a utilizar: ";
                cin >> pr;
                comb = comb + pr;
                pr = "";

                cout << "ID del producto: ";
                cin >> id;

                cout << "Unidades a utilizar: ";
                cin >> unidades;

                cout << "Desea ingresar otro producto? Mayuscula inicial Si o No: ";
                cin >> help;


                if (help == "Si") comb += ", ";
            }

            system("cls");
            cout << "Combo creado" << endl;

            ++cont;
            combos.insert({cont, comb}); // Se agrega el combo al mapa

            cout << "El combo es: Combo " << cont << " " << combos[cont] << endl;

            cout << "El valor es de: \n" << endl;

            help = "Si";

            inv.descript(); //Descripcion del combo ingresado
        }

        else if (opt == 2){
            aux = true;
            system("cls");
        }

        else{
            cout << "Ingrese un numero valido." << endl;
            system("cls");
        }
    }
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
