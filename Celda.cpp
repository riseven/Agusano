#include <allegro.h>
#include "Celda.h"

#include "Excepcion.h"
#include "Agujero.h"
#include "Gusano.h"

Imagen *Celda::tile[NUM_TILES];

void
Celda::Inicializar()
{
    try
    {
        tile[icFondo] = new Imagen("Graficos\\fondo.bmp");
        tile[icBordeArriba]             = new Imagen("Graficos\\borde_top.bmp");
        tile[icBordeAbajo]              = new Imagen("Graficos\\borde_bottom.bmp");
        tile[icBordeDerecha]            = new Imagen("Graficos\\borde_right.bmp");
        tile[icBordeIzquierda]          = new Imagen("Graficos\\borde_left.bmp");
        tile[icBordeArribaIzquierda]    = new Imagen("Graficos\\borde_top_left.bmp");
        tile[icBordeArribaDerecha]      = new Imagen("Graficos\\borde_top_right.bmp");
        tile[icBordeAbajoIzquierda]     = new Imagen("Graficos\\borde_bottom_left.bmp");
        tile[icBordeAbajoDerecha]       = new Imagen("Graficos\\borde_bottom_right.bmp");
        tile[icGusanoHorizontal]        = new Imagen("Graficos\\gusano_horizontal.bmp");
        tile[icGusanoVertical]          = new Imagen("Graficos\\gusano_vertical.bmp");
        tile[icGusanoArribaIzquierda]   = new Imagen("Graficos\\gusano_arriba_izquierda.bmp");
        tile[icGusanoArribaDerecha]     = new Imagen("Graficos\\gusano_arriba_derecha.bmp");
        tile[icGusanoAbajoIzquierda]    = new Imagen("Graficos\\gusano_abajo_izquierda.bmp");
        tile[icGusanoAbajoDerecha]      = new Imagen("Graficos\\gusano_abajo_derecha.bmp");
        tile[icColaArriba]            = new Imagen("Graficos\\cola_arriba.bmp");
        tile[icColaDerecha]           = new Imagen("Graficos\\cola_derecha.bmp");
        tile[icColaAbajo]             = new Imagen("Graficos\\cola_abajo.bmp");
        tile[icColaIzquierda]         = new Imagen("Graficos\\cola_izquierda.bmp");
    }
    catch ( Excepcion &ex )
    {
        throw Excepcion(ex, "Celda::Inicializar()");
    }
}

void
Celda::Cerrar()
{
    try
    {
        for ( int i = 0 ; i < NUM_TILES ; i++ )
        {
            if ( !tile[i] )
            {
                throw Excepcion("Celda::Cerrar()");
            }
            delete tile[i] ;
        }
    }
    catch ( Excepcion &ex )
    {
        throw Excepcion(ex, "Celda::Cerrar()");
    }
}

Celda::Celda()
{
    imagenCelda = icFondo ;
    tipoCelda = tcVacio ;
    agujero = NULL ;
}

void
Celda::SetImagenCelda(ImagenCelda imagenCelda)
{
    Celda::imagenCelda = imagenCelda ;
}

void
Celda::SetTipoCelda(TipoCelda tipoCelda)
{
    Celda::tipoCelda = tipoCelda ;
}

TipoCelda
Celda::GetTipoCelda()
{
    return tipoCelda ;
}

void
Celda::SetAgujero(Agujero *agujero)
{
    Celda::agujero = agujero ;
}

bool
Celda::SePuedeCruzar()
{
    if ( agujero != NULL )
    {
        return agujero->SePuedeCruzar() ;
    }
    else
    {
        if ( tipoCelda == tcVacio )
        {
            return true ;
        }
    }
    return false ;
}

void
Celda::EntraGusano(Gusano *gusano)
{
    if ( agujero != NULL )
    {
        agujero->EntraGusano(gusano);
    }
}
        

void
Celda::Pintar(int x, int y)
{
    try
    {
        tile[imagenCelda]->Pintar(x, y);
    }
    catch ( Excepcion &ex )
    {
        throw Excepcion(ex, "Celda::Pintar(int, int)");
    }
}
