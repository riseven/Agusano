#ifndef __CELDA_H__
#define __CELDA_H__

#include <allegro.h>
#include "Imagen.h"

typedef enum ImagenCelda
{
    icFondo,
    icBordeArriba,
    icBordeAbajo,
    icBordeDerecha,
    icBordeIzquierda,
    icBordeArribaIzquierda,
    icBordeArribaDerecha,
    icBordeAbajoIzquierda,
    icBordeAbajoDerecha,
    icGusanoHorizontal,
    icGusanoVertical,
    icGusanoArribaIzquierda,
    icGusanoArribaDerecha,
    icGusanoAbajoIzquierda,
    icGusanoAbajoDerecha,
    icColaArriba,
    icColaDerecha,
    icColaAbajo,
    icColaIzquierda
};
#define NUM_TILES 19

typedef enum TipoCelda
{
    tcVacio,
    tcBorde,
    tcGusano
};

class Agujero ;
class Gusano ;

class Celda
{
private:
    static Imagen *tile[NUM_TILES] ;
    
    ImagenCelda imagenCelda ;
    TipoCelda tipoCelda ;
    Agujero *agujero ;

public:
    Celda();
    void SetImagenCelda(ImagenCelda imagenCelda);
    void SetTipoCelda(TipoCelda tipoCelda);
    TipoCelda GetTipoCelda();
    void SetAgujero(Agujero *agujero);
    void EntraGusano(Gusano *gusano);
    bool SePuedeCruzar();
    
    void Pintar(int x, int y);
    
    static void Inicializar();
    static void Cerrar();
};

#endif
