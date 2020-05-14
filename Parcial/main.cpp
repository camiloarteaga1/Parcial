//#include <iostream>
//#include <fstream>
//#include <string.h>
#include <windows.h>
#include <conio.h>
#include <map>
#include <inventario.h>
#include <plantillas.h>
#include <encrypt.h>
#include <vector>

using namespace std;

//Archivos
const string psAdmin = "../Archivos/ClaveAdmin.txt";
const string diraux = "../Archivos/txtAux.txt"; //Direccion auxiliar, no hay que cambiarla
const string dirCombos = "../Archivos/Combos.txt"; //TXT con los combos creados por el admin

//La clave del adm está codificada por defecto con esa semilla
//Semilla codificacion
unsigned int semi = 4;

//Funciones
int adm(int var);
int user();

int main()
{
    int opt = 0, var = 1;
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

        if (opt == 1) adm(var);

        else if (opt == 2) user();

        else if (opt == 3) conta = true;

        else{
            cout << "No me parece que este chico sea muy listo." << endl;
            conta = true;
       }
    }
}

//Despliega el menu del adm y ejecuta sus procesos
int adm(int var)
{
    int opt = 0, cont = 1, wish = 0;
    string id = "", unidades = "", ps, help = "Si", code;
    bool aux = false;
    map <int, vector <string>> combos;
    vector <string> producto;
    inventario inv;

    cout << "\nIngresando como administrador" << endl;
    cout << "Por favor escriba su clave:";
    cin >> ps;

    encrypt data(ps, diraux);
    data.convert(); //Se convierte el string ingresado en bin
    code = data.codificacion2(semi); //Contraseña encriptada ingresada por el usuario
    borrar(diraux); //Se borra el archivo aux

    while (validacion(psAdmin, code) == false){ //Verifica si la clave es correcta

        cout << "\nContrasena incorrecta,intente nuevamente" << endl;
        cout << "Ingrese de nuevo: ";
        cin >> ps;

        encrypt data(ps, diraux);
        data.convert(); //Se convierte el string ingresado en bin
        code = data.codificacion2(semi); //Contraseña encriptada ingresada por el usuario
        borrar(diraux); //Se borra el archivo aux
    }

    system("cls");
    cout << "Bienvenido administrador" << endl;

    while (aux == false){

        cout << "Operacion a realizar: " << endl;
        cout << "1.Crear combos" << "\n2.Salir" << endl;
        cout << "Opcion: ";
        cin >> opt;

        if (opt == 1){ //Se empieza a crear el combo de acuerdo al inventario

            while (var <= 3){

                cout << "\nPresione enter para avanzar." << endl;
                getch();
                system("cls");

                cout << "Recuerde que minimo debe crear 3 combos" << endl;
                cout << "Combos restantes: " << 4-var << endl;
                while (help == "Si"){

                    cout << "\nProductos disponibles: " << endl;
                    inv.imprimir(); //Imprime el inventario disponible

                    cout << "\nIngrese el ID del producto para el combo: ";
                    cin >> id;
                    producto.push_back(id);
                    producto.push_back(";");

                    cout << "Unidades a utilizar en el combo: ";
                    cin >> unidades;

                    producto.push_back(unidades);

                    cout << "Desea ingresar otro producto? Mayuscula inicial Si o No: ";
                    cin >> help;

                    if (help == "Si"){
                        producto.push_back(":");
                    }
                    if (help == "No"){
                        producto.push_back("|");
                    }
                }

                system("cls");
                cout << "Combo creado" << endl;

                combos.insert({cont, producto}); //Se agrega el combo al mapa

                inv.combos(combos, dirCombos);

                help = "Si";

                ++cont;
                producto.clear();
                combos.clear();

                inv.descript(); //Descripcion del combo ingresado
                ++var;
            }

            cout << "Desea crear otro combo? 1 para si, 2 para no: ";
            cin >> wish;

            while (wish == 1){
                while (help == "Si"){

                    system("cls");
                    cout << "\nProductos disponibles: " << endl;
                    inv.imprimir(); //Imprime el inventario disponible

                    cout << "\nIngrese el ID del producto para el combo: ";
                    cin >> id;
                    producto.push_back(id);
                    producto.push_back(";");

                    cout << "Unidades a utilizar en el combo: ";
                    cin >> unidades;

                    producto.push_back(unidades);

                    cout << "Desea ingresar otro producto? Mayuscula inicial Si o No: ";
                    cin >> help;

                    if (help == "Si"){
                        producto.push_back(":");
                    }
                    if (help == "No"){
                        producto.push_back("|");
                    }
                }

                system("cls");
                cout << "Combo creado" << endl;

                combos.insert({cont, producto}); //Se agrega el combo al mapa

                inv.combos(combos, dirCombos);

                help = "Si";

                ++cont;
                producto.clear();
                combos.clear();

                inv.descript(); //Descripcion del combo ingresado

                cout << "Desea crear otro combo? 1 para si, 2 para no: ";
                cin >> wish;

            }
        }

        else if (opt == 2){
            aux = true;
            system("cls");
        }
        else if (wish == 2){
            cout << "Hey listen" << endl;
        }

        else{
            cout << "Ingrese un numero valido." << endl;
        }
    }
    return var;
}

//Despliega el menu del usuario
int user()
{

    return 0;
}
