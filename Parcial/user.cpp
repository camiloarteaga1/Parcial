#include "user.h"

User::User(string dir)
{
    dirUser = dir;
}

User::~User()
{

}

void User::Register(string diraux, unsigned int semi)
{
    string id = "", psusu = "", name = "", data = "", codi = "", ps, txt;
    bool aux = false;

    cout << "\nRegistrando un Usuario" << endl;
    cout << "Escriba su documento: ";
    cin >> id;

    while (valnum(id) == false){ //Verifica si los caracteres son numericos

        cout << "Ingrese solo caracteres numericos" << endl;
        cout << "Escriba su documento: ";
        cin >> id;
    }

    data += id + ',';

    while (aux == false){ //Verifica si los caracteres son numericos

        cout << "\nIngrese la clave (4 numeros)" << endl;
        cout << "Escriba la clave: ";
        cin >> ps;

        if ((ps.length() != 4) || (valnum(ps) == false)){

            cout << "\nPor favor escriba 4 numeros" << endl;
            cout << "Escriba la clave: ";
            cin >> ps;
        }

        else aux = true;
    }

    data += ps + ',';

    cout << "\nEscriba su nombre completo: ";
    cin.ignore(100, '\n');
    getline(cin, name);

    data += name; //String con los datos del usuario

    encrypt code(data, diraux);

    code.convert(); //Convierte a binario los datos

    data = code.codificacion2(semi); //Codifica el archivo

    escribir(dirUser, data); //Escribe la informacion en el archivo de usuarios

    borrar(diraux); //Borra diraux

    cout << "\nProceso finalizado" << endl;

}

bool User::valuser(string nameusu, string claveusu, unsigned int semi)
{
    int cont = 0;
    string ps = "", id = "", name = "";
    bool aux = false;
    class encrypt usuario;

    ifstream input(dirUser); //Abre el archivo de usuarios y lo lee linea a linea

    for (string line; getline (input, line); )
    {
        ps = "";
        id = "";
        name = "";

        string ayuda = ""; //Info decodificada
        ayuda = usuario.decodificacion2(line, semi); //Decodifica la informacion
        ayuda = usuario.bin_to_string(ayuda); //Convierte el bin ayuda en string

        for (unsigned int i = 0; i < ayuda.find(","); ++i){ //Hasta que encuentre la primera ","
            id += ayuda.at(i); //String con el ID del usuario
        }

        for (unsigned int i = 0; i < id.length(); ++i){
            if (id.at(i) != nameusu.at(i)) //Compara el id del usuario con las claves del archivo
                break;

            else if (i == id.length())
                aux = true;
        }

        for (unsigned int i = ayuda.find(",") + 1; i < ayuda.find(",") + 5; ++i){
            ps += ayuda.at(i);
        }

        for (unsigned int i = 0; i < 4; ++i){ //La clave va hasta encontrar la segunda ","
            if (ps.at(i) != claveusu.at(i)) //Compara la clave del usuario con las claves del archivo
                break;

            else if (i == 3)
                aux = true;
        }

        for (unsigned int i = ayuda.find(",") + 6; i < ayuda.length(); ++i){
            name += ayuda.at(i); //El saldo es el que esta despues de la segunda ","
        }

        if (aux == true){ //True si la clave esta en el archivo
            cont = 1;

            cout << "\nBienvenido: " << name << "\nNumero identificacion: " << id << "\n" << endl;

            return aux;
        }

        else{
            aux = false;
            return aux;
        }
    }
    input.close(); //Cierra el archivo

    if (cont == 0){
        cout << "\nEl usuario no esta la base, intenta nuevamente.\n" << endl;
        return aux;
    }
    return aux;
}


//Ecribir en un archivo
void User::escribir(string dir, string txt)
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

