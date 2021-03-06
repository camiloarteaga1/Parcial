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

//Ecribir en un archivo
void inventario::escribir(string dir, string txt)
{
    ofstream archivo;
    archivo.open(dir, ios::app);
    if (archivo.fail()){
        cout << "No se pudo abrir el archivo";
        exit(1);
    }

    archivo << txt << "\n";
    archivo.close();
}

//Guarda los combos
void inventario::combos(map <int, vector<string>> combo, string dircombo)
{
    string combito = "";
    int num = 0;

    auto v = combo.begin();
    num = v->first;

    combito += to_string(num) + ":";

    for (auto i = v->second.begin(); i != v->second.end(); ++i){

        combito += i[0];
    }

    escribir(dircombo, combito);
}

//Imprime el inventario que se desee
void inventario::imprimir(string dir)
{
    ifstream invent;

    invent.open(dir, ios::in);

    if(!invent.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    printElement("ID:", 7);
    printElement("Producto:", 25);
    printElement("Paquetes:", 15);
    printElement("Unidades:", 15);
    printElement("Unidades en total:", 25);
    printElement("Costo unidad en pesos:", 15);
    cout << endl;

    for (string line; getline (invent, line); ){

        string product = "", uni = "", id = "", costo = "", paq = "", total = "";


        for (unsigned int i = 0; i < line.find(","); ++i){ //Hasta que encuentre la ","
            id += line.at(i); //String con el ID del producto
        }

        for (unsigned int i = line.find(",") + 1; i < line.find(";"); ++i){ //Desde la "," hasta el";"
            product += line.at(i); //String con el producto
        }

        for (unsigned int i = line.find(";") + 1; i < line.find("~"); ++i){ //Desde el ";" hasta la "~"
            paq += line.at(i); //String con la cant de paquetes del producto
        }

        for (unsigned int i = line.find("~") + 1; i < line.find(":"); ++i){ //Desde la "~" hasta el ":"
            uni += line.at(i); //String con la cant de unidades por paquetes
        }

        for (unsigned int i = line.find(":") + 1; i < line.find("|"); ++i){ //Desde el ":" hasta el "|"
            total += line.at(i); //String con la cant de unidades en total
        }

        for (unsigned int i = line.find("|") + 1; i < line.length(); ++i){ //Desde el ":" hasta el final
            costo += line.at(i); //String con el costo total de los paquetes
        }

        if (id != "ID"){
            printElement(id, 7);
            printElement(product, 25);
            printElement(paq, 15);
            printElement(uni, 15);
            printElement(total, 25);
            cout << "$";
            printElement(costo, 15);
            cout << endl;
        }
    }
    invent.close();
}

//Lee un archivo
void inventario::leer(string dir)
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
        cout << txt << endl;
    }

    archivo.close(); //Cierra el archivo
}

//Guarda la descripcion de los combos
void inventario::descript(int cont, string dirDescripCombos)
{
    string descript = "", combito = "Combo ", val = "";

    combito += to_string(cont) + ": ";

    cout << "\nOferta del combo: ";

    cin.ignore(100, '\n');
    getline (cin, descript);

    combito += descript;

    cout << "\nConfirmacion. Repita el valor del combo: ";
    cin >> val;

    combito += " $" + val;

    cout << "Descripcion del combo: " << combito << endl;

    escribir(dirDescripCombos, combito); //Escribe la descrip en un archivo dedicado a ello
}

//Realiza el proceso de compra por parte del usuario
bool inventario::compra(vector <string> datos) //Revibe el vector con los datos de compra
{

    int A, dev;
    bool aux = false, relleno = false;
    vector <string> data; //Contiene los datos de los productos a modificar

    ifstream invent;

    invent.open(datos[5], ios::in);

    if(!invent.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    for (string line; getline (invent, line); ){

        string product = "", uni = "", idc = "", costo = "", cantip = "", idp = "", facture = "";


        for (unsigned int i = 0; i < line.find(":"); ++i){ //Hasta que encuentre la ","
            idc += line.at(i); //String con el ID del combo
        }

        for (unsigned int i = 0; i < idc.length(); ++i){
            if (idc.at(i) != datos[0].at(i)) //Compara el ID del combo con los del archivo
                break;

            else if (idc[i] == datos[0][i])
                aux = true;
        }

        if (aux == true){
            aux = false;
            for (unsigned int i = line.find(":") ; i <= line.find("|"); ++i){ //Desde el ":" hasta el "|"
                product += line.at(i); //String con el combo
            }

            for(unsigned int j = 0; j < product.find("|"); ++j){

                if (product[j] == ':'){
                    ++j;
                    while (product[j] != ';' && product[j] != '|'){
                        idp += product[j];
                        ++j;
                    }
                    data.push_back(idp);
                }
                if (product[j] == ';'){
                    ++j;
                    while (product[j] != '|' && product[j] != ':'){
                        cantip += product[j];
                        ++j;
                    }
                    cantip = to_string(stoi(cantip)*stoi(datos[1]));
                    data.push_back(cantip);
                    if (data[0] != "|" || data[1] != "|"){
                        relleno = modinv(data); //Modifica el inventario de acuerdo al vector que va obteniendo los datos del combo del usuario
                        idp = "";
                        cantip = "";
                    }
                    data.clear();
                    --j;
                 }

            }
            for (unsigned int i = line.find("|") + 1; i < line.length(); ++i){
                costo += line.at(i);
            }

            costo = to_string(stoi(costo) * stoi(datos[1])); //Guarda el costo total de la compra
            cout << "Total a pagar $" << costo << endl;

            if (relleno == false){
                cout << "Ingrese la cantidad con la que va a pagar: ";
                cin >> A;
                dev = pago(stoi(costo), A); //Realiza el proceso de pago de acuerdo al problema 1


                datos.push_back(costo);
                datos.push_back(to_string(A));
                datos.push_back(to_string(dev)); //Se agregan el costo, dinero ingresado y devuelta

                genfact(datos); //Genera la factura al usuario, mostrando los datos de compra y sus datos en el cine
            }
            else{
                cout << "Se debe rellenar el inventario, no se puede realizar la compra." << endl;
                return relleno;
            }
        }
    }
    invent.close();
    return relleno;
}

//Modifica el inventario
bool inventario::modinv(vector <string> mod)
{
    bool aux = false, relleno = false;

    ifstream invent;

    invent.open(dirInventarioActu, ios::in);

    if(!invent.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    for (string line; getline (invent, line); ){

        string product = "", uni = "", idc = "", costo = "", idp = "", paq = "", total = "", linea;
        int cantip = 0;


        for (unsigned int i = 0; i < line.find(","); ++i){ //Hasta que encuentre la ","
            idc += line.at(i); //String con el ID del combo
        }

        for (unsigned int i = 0; i < idc.length(); ++i){
            if (idc.at(i) != mod[0].at(i)) //Compara el ID del combo con los del archivo
                break;

            else if (idc == mod[0])
                aux = true;
        }

        if (aux == true){ //True si esta en el ID de producto a modificar en el archivo
            aux = false;

            for (unsigned int i = line.find(",") + 1; i < line.find(";"); ++i){ //Desde la "," hasta el";"
                product += line.at(i); //String con el producto
            }

            for (unsigned int i = line.find(";") + 1; i < line.find("~"); ++i){ //Desde el ";" hasta la "~"
                paq += line.at(i); //String con la cant de paquetes del producto
            }

            for (unsigned int i = line.find("~") + 1; i < line.find(":"); ++i){ //Desde la "~" hasta el ":"
                uni += line.at(i); //String con la cant de unidades por paquetes
            }

            for (unsigned int i = line.find(":") + 1; i < line.find("|"); ++i){ //Desde el ":" hasta el "|"
                total += line.at(i); //String con la cant de unidades en total
            }

            for (unsigned int i = line.find("|") + 1; i < line.length(); ++i){ //Desde el ":" hasta el final
                costo += line.at(i); //String con el costo total de los paquetes
            }

            cantip = stoi(total) - stoi(mod[1]);

            if (cantip <= 0){
                cout << "Rellenar inventario." << endl;
                relleno = true;
            }

            else if (cantip > 0){
                total = to_string(cantip); //Convierte el saldo a un string
                linea = idc + ',' + product + ';' + paq + "~" + uni + ":" + total + "|" + costo; //Se crea un string para guardar la informacion

                escribir(dirtemp, linea); //Actualiza la informacion en el archivo temporal
                relleno = false;
            }
        }

        else{
            escribir(dirtemp, line); //Actualiza la informacion en el archivo en el archivo temporal
        }
    }
    invent.close(); //Se cierra el archivo

    borrar(dirInventarioActu); //Borra el archivo sin los cambios
    rename(dirtemp, dirInventarioActu); //Se renombra el archivo temporal para posteriormente ser utilizado

    return relleno;
}

//Genera la factura del usuario y se la da a conocer
void inventario::genfact(vector<string> fact)
{
    string compra;
    compra = "Fecha = " + fact[6];
    compra += "|Usuario: " + fact[2];
    compra += " Asiento: " + fact[3];
    compra += " Sala: " + fact[4] + "~";
    compra += "Valor de la compra; " + fact[7];
    compra += "*Dinero ingresado: " + fact[8];
    compra += " Devuelta: " + fact[9];

    escribir(dirfact, compra);

    cout << "Factura de la compra:" << endl;
    cout << "Fecha: " << fact[6] << endl;
    cout << "Usuario: " << fact[2];
    cout << " Asiento: " << fact[3];
    cout << " Sala: " << fact[4] << endl;
    cout << "Valor de la compra " << fact[7];
    cout << " Dinero ingresado: " << fact[8];
    cout << " Devuelta: " << fact[9];

    cout << "\nPresione enter para avanzar." << endl;
    getch();
    system("cls");
}

//Imprime las facturas pedidas por el administrador de acuerdo a la fecha recibida
void inventario::printfact(string fecha)
{
    int  ctotal = 0;
    ifstream invent;

    invent.open(dirfact, ios::in);

    if(!invent.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    printElement("Fecha:", 15);
    printElement("Datos usuario:", 40);
    printElement("Datos compra:", 40);
    cout << endl;

    for (string line; getline (invent, line); ){

        string pt1 = "", pt2 = "", date = "", costo = "", pt3 = "", total = "";

        for (unsigned int i = line.find("=") + 2; i < line.find("|"); ++i){ //Hasta que encuentre la ","
            date += line.at(i); //String con el ID del producto
        }
        if (date == fecha){

            for (unsigned int i = line.find("|") + 1; i < line.find("~"); ++i){ //Desde el "|" hasta el"~"
                pt1 += line.at(i); //String con datos usu
            }
            pt1 += " ";

            /*for (unsigned int i = line.find("~") + 1; i < line.find(";"); ++i){ //Desde la "~" hasta el final
                pt2 += line.at(i); //String con datos compra
            }
            pt2 += ": ";*/

            for (unsigned int i = line.find(";") + 2; i < line.find("*"); ++i){ //Desde el ";" hasta el "*"
                costo += line.at(i); //String con costo compra
            }
            ctotal += stoi(costo); //Costo total compras del dia
            costo += " ";
            for (unsigned int i = line.find("*") + 1; i < line.length(); ++i){ //Desde la "~" hasta el final
                pt3 += line.at(i); //String con datos compra
            }
            pt3 += " ";
            printElement(date, 15);
            printElement(pt1, 40);
            cout << "Costo compra: ";
            printElement(costo, 10);
            printElement(pt3, 30);
            cout << endl;
        }
    }
    cout << "Ventas del dia en dinero: " << ctotal << endl;
    cout << "\nPresione enter para avanzar." << endl;
    getch();
    system("cls");
    invent.close();
}

//Permite agregar productos al inventario
void inventario::add()
{
    string id = "", product = "", paq = "", cantxp = "", tcant = "", precio = "", line = "";
    imprimir(dirInventario); //Imprime el inventario antes de agregar los productos

    cout << "\nAgregue el producto teniendo en cuenta lo anterior." << endl;

    cout << "\nIngrese el siguiente ID del producto, tenga en cuenta que va despues del ultimo en pantalla: ";
    cin >> id;
    line += id + ",";
    cout << "\nIngrese el producto: ";
    cin.ignore(100, '\n');
    getline(cin, product);
    line += product + ";";
    cout << "\nIngrese el numero de paquetes: ";
    cin >> paq;
    line += paq + "~";
    cout << "\nIngrese el numero de unidades por paquete: ";
    cin >> cantxp;
    line += cantxp + ":";
    tcant = to_string(stoi(paq)*stoi(cantxp));
    cout << "\nEl numero total de unidades es: " << tcant << endl;
    line += tcant + "|";
    cout << "\nIngrese el precio por unidad: ";
    cin >> precio;
    line += precio;

    escribir(dirInventario, line); //Modifica el inventario agregando el producto
    Copy();
    cout << "\nPresione enter para avanzar." << endl;
    getch();
    system("cls");
}

//Copia un archivo de texto para rellenar el inventario
void inventario::Copy()
{
    ifstream invent;

    invent.open(dirInventario, ios::in);

    if(!invent.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    borrar(dirInventarioActu); //Borra el inventario vacio

    for (string line; getline (invent, line); ){
        escribir(dirInventarioActu, line); //Lo escribe de nuevo
    }

    invent.close();
}


//Problema 1, para devolver dinero
int inventario::pago(int costo, int A){
    int money[10]={50000,20000,10000,5000,2000,1000,500,200,100,50}, money_count[10]={0,0,0,0,0,0,0,0,0,0}, dev;
    string money_names[10]={"50000","20000","10000","5000","2000","1000","500","200","100","50"};

    A = A - costo;
    dev = A;

    cout<<"\nBilletes necesarios:" << endl;

    for (int i=0;i<10;i++){
        for (int j=0;A>=money[i];j++){
           A-=money[i];
           money_count[i]+=1;

        }
        cout << money_names[i] << ": " << money_count[i] << endl;
    }
    cout << "Restante: " << A << endl;
    cout << "\nDevuelta: " << dev << endl; //Da la devuelta
    cout << "\nPresione enter para avanzar." << endl;
    getch();
    system("cls");
    return dev;
}

