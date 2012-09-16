#ifndef __EXCEPCION_H__
#define __EXCEPCION_H__

#include <allegro.h>
#include <string>

using namespace std;

class Excepcion
{
private:
    string mensajeDeError ;
public:
    Excepcion();
    Excepcion(string mensajeDeError);
    Excepcion(const Excepcion &ex);
    Excepcion(Excepcion &ex, string mensajeDeTraza);
    Excepcion & operator =(const Excepcion &ex);
    ~Excepcion();
    string GetMensajeDeError();
};

#endif
