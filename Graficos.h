#ifndef __GRAFICOS_H__
#define __GRAFICOS_H__

#include <allegro.h>


#ifdef __GRAFICOS_CPP__
 #define EXTERN
#else
 #define EXTERN extern
#endif

class Graficos
{
private:
    int pageActual ;
    BITMAP *page[2] ;
public:
    Graficos();
    ~Graficos();
    void Inicializar(int w, int h, int depth) ;    
    BITMAP * GetScreen();
    void Actualizar();
};

EXTERN Graficos graficos ;

#endif
