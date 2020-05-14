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

void inventario::combos(map <int, vector<string>> combo, string dircombo)
{
    string combito = "Combo";
    int num = 0;

    auto v = combo.begin();
    num = v->first;

    combito += to_string(num) + ":";

    for (auto i = v->second.begin(); i != v->second.end(); ++i){

        combito += i[0];
    }

    escribir(dircombo, combito);
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
    printElement("Producto:", 25);
    printElement("Paquetes:", 15);
    printElement("Unidades:", 15);
    printElement("Costo unidad en pesos:", 15);
    cout << endl;

    for (string line; getline (invent, line); ){

        string product = "", uni = "", id = "", costo = "", paq = "";


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

        for (unsigned int i = line.find(":") + 1; i < line.length(); ++i){ //Desde el ":" hasta el final
            costo += line.at(i); //String con el costo total de los paquetes
        }

        if (id != "ID"){
            printElement(id, 7);
            printElement(product, 25);
            printElement(paq, 15);
            printElement(uni, 15);
            cout << "$";
            printElement(costo, 15);
            cout << endl;
        }
    }
    invent.close();
}

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

void inventario::descript(int cont, string dirDescripCombos)
{
    string descript = "", combito = "Combo ", val = "";

    combito += to_string(cont) + ": ";

    cout << "Oferta del combo: ";

    cin.ignore(100, '\n');
    getline (cin, descript);

    combito += descript;

    cout << "Repita el valor del combo: ";
    cin >> val;

    combito += " $" + val;

    cout << "Descripcion del combo: " << combito << endl;

    escribir(dirDescripCombos, combito);
}

int inventario::compra(string comb, string cant, string dircombo)
{

    bool aux = false;

    ifstream invent;

    invent.open(dircombo, ios::in);

    if(!invent.is_open()){ //Verifica si el archivo abrio exitosamente
        std::cout << "Error al abrir el archivo" << endl;
        exit(1);
    }

    for (string line; getline (invent, line); ){

        string product = "", uni = "", idc = "", costo = "", cantip = "", idp = "";


        for (unsigned int i = 0; i < line.find(":"); ++i){ //Hasta que encuentre la ","
            idc += line.at(i); //String con el ID del combo
        }
        for (unsigned int i = 0; i < 4; ++i){
            if (idc.at(i) != comb.at(i)) //Compara el ID del combo con los del archivo
                break;

            else if (i == idc.length())
                aux = true;
        }

        if (aux == true){
            for (unsigned int i = line.find(":") ; i == line.find("|"); ++i){ //Desde el ":" hasta el "|"
                product += line.at(i); //String con el combo

                for(unsigned int j = 0; j < product.find("|"); ++j){

                    if (j == product.find(":")){
                        ++j;
                        idp = product[j];
                    }
                    else if (j == product.find(";")){
                        ++j;
                        cantip = product[j];

                }

            }
            for (unsigned int i = line.find("|") + 1; i < line.length(); ++i){
                costo = line.at(i);
                costo = stoi(costo); //Debo continuar con otra funcion
            }
        }

    }
    invent.close();
}
