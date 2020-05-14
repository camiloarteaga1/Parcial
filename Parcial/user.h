#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <encrypt.h>
#include <plantillas.h>
using namespace std;

class User
{
public:
    User(string dir);
    ~User();
    void Register(string diraux, unsigned int semi); //Realiza el registro de usuarios
    bool infouser(string nameusu, string claveusu, unsigned int semi); //Verifica el inicio de sesion

private:
    string dirUser;

    void escribir(string dir, string txt); //Escribe en un archivo el string recibido
};

#endif // USER_H
