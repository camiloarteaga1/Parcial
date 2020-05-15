#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class encrypt
{
public:
    encrypt();
    encrypt(string a, string b);
    ~encrypt();

    string codificacion2(unsigned int seed); //Codifica lo que haya en un archivo de texto
    string decodificacion2(string bin, unsigned int seed); //Decodifica lo que haya en un archivo de texto
    string bin_to_string(string bin); //Convierte de binario a string
    void convert(); //Convierte un string en binario


private:
    string texto, dir;

    string leer(string dir); //Lee lo de un archivo y lo asigana a una variable
    int tobin(int numero); //Para convertir a binario
    int dig_num(int num); //Da los digitos de un numero
    void fun_a(int *px, int *py); //Para codificar
    void fun_b(int a[], int tam); //Para codificar
    void desfun_b(int a[], int tam); //Para decodificar


};

#endif // ENCRYPT_H
