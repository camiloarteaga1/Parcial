#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const string dirAdmin = "../Archivos/ClaveAdmin.txt";

//Funciones
string leer(string dir);
bool validacion(string dir, string ps);
int adm();

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
    string id = "", psusu = "", saldo= "", data = "", codi = "", ps, txt;
    bool aux = false;

    cout << "\nBienvenido administrador" << endl;
    cout << "Por favor escriba su clave:";
    cin >> ps;

    while (validacion(dirAdmin, ps) == false){ //Verifica si la clave es correcta

        cout << "\nContrasena incorrecta,intente nuevamente" << endl;
        cout << "Ingrese: ";
        cin >> ps;
    }

    cout << "\nOperacion a realizar: " << endl;
    cout << "1.Ingresar usuarios" << "\n2.Salir" << endl;
    cout << "Opcion: ";
    cin >> opt;

    if (opt == 1){

        cout << "\nIngresar Usuario" << endl;
        cout << "Escriba el documento: ";
        cin >> id;

        while (valnum(id) == false){ //Verifica si los caracteres son numericos

            cout << "Ingrese solo caracteres numericos" << endl;
            cout << "Escriba el documento: ";
            cin >> id;
        }

        cout << "\nProceso finalizado" << endl;

        }

    else if (opt == 2) return 0;

    else cout << "Usted es tonto o se hace?";

    return 0;
}

//Valida la clave del admin
bool validacion(string dir, string ps)
{
    string enps = leer(dir); //String que contiene la contraseña del txt

    for(unsigned int i = 0; i < enps.length() ; ++i){ //Compara termino a termino la clave
        if (ps.at(i) != enps.at(i)) return false;
    }

    return true;
}

//Lee lo de un archivo y lo asigna a una variable
string leer(string dir)
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
