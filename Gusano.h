#ifndef __GUSANO_H__
#define __GUSANO_H__

#include <allegro.h>

#include "Imagen.h"
#include "Frecuencia.h"

typedef enum Direccion
{
    dArriba,
    dDerecha,
    dAbajo,
    dIzquierda
};

class Nivel;

class Gusano
{
private:
    static Imagen *imagenCabeza[4];
    
    int x,y;
    Direccion dir ;
    Nivel *nivel ;
    bool comienzaGusano ;
    Frecuencia frecAvance ;
    int teclaPulsada[2] ;
    int numTeclasPulsadas ;
    bool muerto ;
    bool activo ;
    
public:
    Gusano(Nivel *nivel, int x, int y, Direccion dir, float frec);
    ~Gusano();
    
    int GetX();
    int GetY();
    void SetPosicion(int x, int y);
    void ComienzaGusano();
    bool Muerto();
    void SetActivo(bool activo);
    void Actualizar();
    void Pintar(int esquinax, int esquinay);
    
    static void Inicializar();
    static void Cerrar();
};

#endif

