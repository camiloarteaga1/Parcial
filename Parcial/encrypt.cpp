#include "encrypt.h"

encrypt::encrypt(string a, string b)
{
    texto = a;
    dir = b;
}

encrypt::~encrypt()
{

}

//Metodo de codificacion 2
string encrypt::codificacion2(unsigned int seed)
{

    string txt = leer(dir);
    unsigned int Jump = seed, largo = txt.length();

    int *arraycode = nullptr;
    unsigned int k = 0;
    int *numbin = new int[largo];


    for (unsigned int i = 0; i < txt.length(); ++i){
        numbin[i] = txt[i] - 48;
    }


    while (k < largo){

        arraycode = new int[seed];

        if (largo - k < seed){
            Jump = largo - k;
        }

        for (unsigned int x = 0; x < Jump; ++x){
            arraycode[x] = numbin[k+x];
        }

        fun_b(arraycode, Jump);

        for (unsigned int x = 0; x < Jump; ++x){
            txt[x+k] = arraycode[x] + 48;
        }

        k += Jump;
        delete[] arraycode;
    }

    delete[] numbin;

    return txt;
}

//Metodo de decodificacion 2
string encrypt::decodificacion2(string bin, unsigned int seed)
{
    unsigned int Jump = seed, largo = bin.length();

    int *arraycode = nullptr;
    unsigned int k = 0;
    int *numbin = new int[largo];


    for (unsigned int i = 0; i < bin.length(); ++i){
        numbin[i] = bin[i] - 48;
    }


    while (k < largo){

        arraycode = new int[seed];

        if (largo - k < seed){
            Jump = largo - k;
        }

        for (unsigned int x = 0; x < Jump; ++x){
            arraycode[x] = numbin[k+x];
        }

        desfun_b(arraycode, Jump);

        for (unsigned int x = 0; x < Jump; ++x){
            bin[x+k] = arraycode[x]+48;
        }

        k += Jump;
        delete[] arraycode;
    }

    delete[] numbin;

    return bin;
}

//Convertir texto a binario y lo guarda en el archivo
void encrypt::convert()
{
    ofstream archivo;

    archivo.open(dir.c_str(), ios::out);

    if (archivo.fail()){
        cout << "No se pudo abrir el archivo";
        exit(1);
    }
    int binario[1500] = {};
    int longitud = 0, ascii;
    longitud = texto.length();

    for (int i = 0; i < longitud; ++i) {
        ascii = texto[i];
        binario[i] = tobin(ascii);

        for (int j = dig_num(binario[i]); j < 8; ++j){
            archivo << 0;
        }

        archivo << binario[i];
    }

    archivo.close();
}

//Convierte de binario a string
string encrypt::bin_to_string(string bin)
{
    unsigned int seed = 8;
    unsigned int Jump = seed, largo = bin.length(), longi = (bin.length())/8;

    int *arraycode = nullptr;
    unsigned int k = 0, cont = 0;
    int *numbin = new int[largo];
    char *texto = new char[longi];
    char *aux = nullptr;
    string cojo = "", cosa = "";


    for (unsigned int i = 0; i < bin.length(); ++i){
        numbin[i] = bin[i] - 48;
    }

    while (k < largo){

        arraycode = new int[seed];
        aux = new char[longi];

        if (largo - k < seed){
            Jump = largo - k;
        }

        for (unsigned int x = 0; x < Jump; ++x){
            arraycode[x] = numbin[k+x];
        }

        for (unsigned int x = 0; x < Jump; ++x){
            aux[x] = arraycode[x]+48;
            cosa.push_back(aux[x]);
        }

        unsigned int i = stoi(cosa, nullptr, 2);

        texto[cont] = i;

        ++cont;
        k += Jump;
        cosa = "";
        delete[] arraycode;
        delete[] aux;
    }

    for (unsigned int z = 0; z < longi; ++z)
        cojo.push_back(texto[z]);

    delete[] numbin;
    delete[] texto;

    return cojo;
}

//Lee lo de un archivo y lo asigna a una variable
string encrypt::leer(string dir)
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

//Ecribir en un archivo
void encrypt::escribir(string dir, string txt)
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

void encrypt::fun_a(int *px, int *py)
{
    int tmp = *px;
    *px = *py;
    *py = tmp;
}

void encrypt::fun_b(int a[], int tam)
{
    int f, l, k = a[tam-1];
    int *b = a;

    for (f = tam-2, l = tam-1; true; f -=1, l -=1){
        if (l == 0){
            break;
        }
        fun_a(&b[f], &b[l]);
    }
    a[0] = k;
}

void encrypt::desfun_b(int a[], int tam)
{
    int f, l;
    int *b = a;

    for (f = 0, l = 1; true; f += 1, l += 1){
        if (l == tam){
            break;
        }

        fun_a(&b[f], &b[l]);
    }
}

//Convierte el número en binario
int encrypt::tobin(int numero)
{
    int residuo, base = 1, binario = 0;

    while(numero > 0){
        residuo = numero%2;
        binario = binario + residuo*base;
        numero = numero/2;
        base = base*10;
    }
    return binario;
}

//Dice los digitos de un numero.
int encrypt::dig_num(int num)
{
    int k = 0;

    while (num > 0){
        num /= 10;
        ++k;
    }
    return k;
}

void encrypt::nuename(string dirtemp, string diruser)
{
    int newname;
    newname = rename(dirtemp.c_str(), diruser.c_str()); //Renombra el archivo temp por el de user

    if (newname != 0)
        perror("Error al renombrar archivo.");
}
