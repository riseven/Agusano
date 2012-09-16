#ifndef __FRECUENCIA_H__
#define __FRECUENCIA_H__

#include <allegro.h>
#include <alleggl.h>
#include <windows.h>

class Frecuencia
{
private:
    int ultimo ;
    int periodo ;
    
    
public:
    Frecuencia(float frec);
    ~Frecuencia();
    bool Comprobar();
};

#endif
