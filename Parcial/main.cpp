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
#include <user.h>

using namespace std;

//Archivos
const string psAdmin = "../Archivos/ClaveAdmin.txt"; //Direccion clave administrador
const string diraux = "../Archivos/txtAux.txt"; //Direccion auxiliar, no hay que cambiarla
const string dirCombos = "../Archivos/Combos.txt"; //TXT con los combos creados por el admin
const string dirDescripCombos = "../Archivos/DescripCombos.txt"; //Direccion descripcion de combos
const string dirUser = "../Archivos/user.txt"; //Direccion descripcion de combos
const string dirInventario = "../Archivos/Inventario.txt"; //Direccion inventario, está en inventario.h tambien
const string dirInventarioActu = "../Archivos/InventarioActu.txt"; //Direccion inventario en ejecucion, está en inventario.h tambien
const string dirfact = "../Archivos/dirfact.txt"; //Direccion facturas, está en inventario.h tambien
const string dirtemp = "../Archivos/dirtemp.txt"; //Direccion temporal, está en inventario.h tambien

//La clave del adm está codificada por defecto con esa semilla
//Semilla codificacion
unsigned int semi = 4;

//Funciones
int adm(int &var, int &cont);
int user();

int main()
{
    int opt = 0, var = 1, cont = 1;
    bool conta = false;
    inventario inv;
    inv.Copy();

    cout << "BIENVENIDO A CINE KAKARIKO" << endl;

    while (conta == false){
        cout << "Menu" << endl;
        cout << "Operacion a realizar. Escriba 1, 2 o 3." << endl;
        cout << "1. Administrador." << endl;
        cout << "2. Usuario." << endl;
        cout << "3. Salir." << endl;
        cout << "Opcion: ";
        cin >> opt;

        if (opt == 1) adm(var, cont);

        else if (opt == 2) user();

        else if (opt == 3){
            borrar(dirCombos);
            borrar(dirDescripCombos);
            borrar(dirInventarioActu);
            conta = true;
        }

        else{
            cout << "No me parece que este chico sea muy listo." << endl;
            conta = true;
       }
    }
}

//Despliega el menu del adm y ejecuta sus procesos
int adm(int &var, int &cont)
{
    int opt = 0, wish = 0;
    string id = "", unidades = "", ps, help = "Si", code, val = "";
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
        cout << "1. Crear combos" << "\n2. Facturas" << "\n3. Inventario actual" << "\n4. Rellenar inventario" << "\n5. Salir" << endl;
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
                    inv.imprimir(dirInventario); //Imprime el inventario disponible

                    cout << "\nIngrese el ID del producto para el combo: ";
                    cin >> id;
                    producto.push_back(id);
                    producto.push_back(";");

                    cout << "Recuerde no pasarse del numero de unidades por paquete." << endl;
                    cout << "Unidades a utilizar en el combo: ";
                    cin >> unidades;

                    producto.push_back(unidades);

                    cout << "Desea ingresar otro producto? Mayuscula inicial Si o No: ";
                    cin >> help;

                    if (help == "Si"){
                        producto.push_back(":");
                    }
                    if (help == "No"){
                        producto.push_back(":|");
                        cout << "Escriba el precio del combo: ";
                        cin >> val;
                        producto.push_back(val);
                    }
                }

                cout << "Combo creado" << endl;

                combos.insert({cont, producto}); //Se agrega el combo al mapa

                inv.combos(combos, dirCombos);

                help = "Si";

                producto.clear();
                combos.clear();

                inv.descript(cont, dirDescripCombos); //Descripcion del combo ingresado
                ++cont;
                ++var;
            }

            cout << "\nDesea crear otro combo? 1 para si, 2 para no: ";
            cin >> wish;

            while (wish == 1){
                cout << "\nPresione enter para avanzar." << endl;
                getch();
                system("cls");

                while (help == "Si"){

                    system("cls");
                    cout << "\nProductos disponibles: " << endl;
                    inv.imprimir(dirInventario); //Imprime el inventario disponible

                    cout << "\nIngrese el ID del producto para el combo: ";
                    cin >> id;
                    producto.push_back(id);
                    producto.push_back(";");

                    cout << "Recuerde no pasarse del numero de unidades por paquete." << endl;
                    cout << "Unidades a utilizar en el combo: ";
                    cin >> unidades;

                    producto.push_back(unidades);

                    cout << "Desea ingresar otro producto? Mayuscula inicial Si o No: ";
                    cin >> help;

                    if (help == "Si"){
                        producto.push_back(":");
                    }
                    if (help == "No"){
                        producto.push_back(":|");
                        cout << "Escriba el precio del combo: ";
                        cin >> val;
                        producto.push_back(val);
                    }
                }

                cout << "Combo creado" << endl;

                combos.insert({cont, producto}); //Se agrega el combo al mapa

                inv.combos(combos, dirCombos);

                help = "Si";

                producto.clear();
                combos.clear();

                inv.descript(cont, dirDescripCombos); //Descripcion del combo ingresado
                ++cont;

                cout << "Desea crear otro combo? 1 para si, 2 para no: ";
                cin >> wish;
            }
        }

        else if (opt == 2){
            system("cls");
            string fecha;

            while (help == "Si"){
                cout << "Ingrese la fecha del dia a visualizar (dd/mm/aa) sin 0 inicial: ";
                cin >> fecha;

                inv.printfact(fecha);

                cout << "Desea ingresar otra fecha? Mayuscula inicial Si o No: ";
                cin >> help;
            }
        }
        else if (opt == 3){
            inv.imprimir(dirInventarioActu);

            cout << "\nPresione enter para avanzar." << endl;
            getch();
            system("cls");
        }
        else if (opt == 4){
            inv.Copy();
            cout << "\nPresione enter para avanzar." << endl;
            getch();
            system("cls");
        }

        else if (opt == 5){
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
    return 0;
}

//Despliega el menu del usuario
int user()
{
    User usuario(dirUser);
    int opt = 0;
    bool aux = false, help, relleno = false;
    string id = "", pass = "", combo = "", cant = "", silla = "", sala = "", fecha = "";
    vector <string> datos;

    system("cls");

    while (aux == false){
        cout << "Bienvenido usuario" << endl;
        cout << "\nQue desea hacer? Escriba solo el numero" << endl;
        cout << "1. Registrarse" << "\n2. Iniciar sesion" << "\n3. Salir" << "\nOpcion: ";
        cin >> opt;

        if (opt == 1){
            usuario.Register(diraux, semi);
        }
        else if (opt == 2){
            cout << "Escriba su documento: ";
            cin >> id;
            cout << "Escriba su contrasena: ";
            cin >> pass;

            help = usuario.valuser(id, pass, semi);

            if (help == true){

                cout << "\nPresione enter para avanzar." << endl;
                getch();
                system("cls");

                inventario combitos;
                cout << "Bienvenido al sistema de compras." << endl;
                cout << "Ingrese la fecha del dia (dd/mm/aa) sin 0 inicial: ";
                cin >> fecha;

                cout << "Los combos que ofrecemos son: " << endl;

                combitos.leer(dirDescripCombos);

                cout << "Escriba el numero del combo a comprar: ";
                cin >> combo;

                cout << "Cuantos desea: ";
                cin >> cant;

                cout << "Cual es su asiento: ";
                cin >> silla;

                cout << "De que sala: ";
                cin >> sala;

                datos.push_back(combo);
                datos.push_back(cant);
                datos.push_back(id);
                datos.push_back(silla);
                datos.push_back(sala);
                datos.push_back(dirCombos);
                datos.push_back(fecha);
                relleno = combitos.compra(datos);
                datos.clear();
                if (relleno == true){
                    cout << "Se debe rellenar el inventario." << endl;
                    aux = true;
                }
            }

            else{
                cout << "\nNo aparece en el sistema, trate de registrarse." << endl;

                cout << "\nPresione enter para avanzar." << endl;
                getch();
                system("cls");
            }
        }

        else if (opt == 3){
            cout << "\nRegrese pronto! :)" << endl;
            cout << "\nPresione enter para avanzar." << endl;
            getch();
            system("cls");
            aux = true;
        }
        else{
            cout << "Ingrese un numero valido." << endl;
        }
    }

    return 0;
}
