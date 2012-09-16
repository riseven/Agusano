#include <allegro.h>
#include "Gusano.h"

#include "Celda.h"
#include "Nivel.h"
#include "Excepcion.h"

Imagen *Gusano::imagenCabeza[4];

Gusano::Gusano(Nivel *nivel, int x, int y, Direccion dir, float frec):
    frecAvance(frec)
{
    Gusano::nivel = nivel ;
    Gusano::x = x ;
    Gusano::y = y ;
    Gusano::dir = dir ;
    numTeclasPulsadas = 0 ;
    muerto = false ;
    activo = false ;
}

Gusano::~Gusano()
{
    nivel = NULL ;
    x = 0 ;
    y = 0 ;
    dir = dArriba ;
}

int
Gusano::GetX()
{
    return x ;
}

int 
Gusano::GetY()
{
    return y ;
}

void
Gusano::SetActivo(bool activo)
{
    Gusano::activo = activo ;
}

void
Gusano::SetPosicion(int x, int y)
{
    Gusano::x = x ;
    Gusano::y = y ;
}

void
Gusano::ComienzaGusano()
{
    comienzaGusano = true ;
}

bool
Gusano::Muerto()
{
    return muerto ;
}

void
Gusano::Actualizar()
{
    if ( key[KEY_RIGHT] && numTeclasPulsadas < 2 )
    {
        if ( numTeclasPulsadas != 1 || teclaPulsada[0] != KEY_RIGHT )
        {
            teclaPulsada[numTeclasPulsadas] = KEY_RIGHT ;
            numTeclasPulsadas++ ;
        }
    }
    if ( key[KEY_LEFT] && numTeclasPulsadas < 2 )
    {
        if ( numTeclasPulsadas != 1 || teclaPulsada[0] != KEY_LEFT )
        {
            teclaPulsada[numTeclasPulsadas] = KEY_LEFT ;
            numTeclasPulsadas++ ;            
        }
    }
    if ( key[KEY_UP] && numTeclasPulsadas < 2 )
    {
        if ( numTeclasPulsadas != 1 || teclaPulsada[0] != KEY_UP )
        {
            teclaPulsada[numTeclasPulsadas] = KEY_UP ;
            numTeclasPulsadas++ ;            
        }
    }
    if ( key[KEY_DOWN] && numTeclasPulsadas < 2 )
    {
        if ( numTeclasPulsadas != 1 || teclaPulsada[0] != KEY_DOWN )
        {
            teclaPulsada[numTeclasPulsadas] = KEY_DOWN ;
            numTeclasPulsadas++ ;
        }
    }            

            
    if ( frecAvance.Comprobar() && activo)
    {
        ImagenCelda imagenCelda = icGusanoHorizontal;    
        switch ( dir )
        {
        case dArriba:
            imagenCelda = icGusanoVertical ;
            if ( numTeclasPulsadas )
            {
                if ( teclaPulsada[0] == KEY_RIGHT )
                {
                    dir = dDerecha ;
                    imagenCelda = icGusanoAbajoDerecha ;
                }
                if ( teclaPulsada[0] == KEY_LEFT )
                {
                    dir = dIzquierda ;
                    imagenCelda = icGusanoAbajoIzquierda ;
                }
            }
            break ;
        case dAbajo:
            imagenCelda = icGusanoVertical ;
            if ( numTeclasPulsadas)
            {
                if ( teclaPulsada[0] == KEY_RIGHT )
                {
                    dir = dDerecha ;
                    imagenCelda = icGusanoArribaDerecha ;
                }
                if ( teclaPulsada[0] == KEY_LEFT )
                {
                    dir = dIzquierda ;
                    imagenCelda = icGusanoArribaIzquierda ;
                }
            }
            break ;
        case dDerecha:
            imagenCelda = icGusanoHorizontal ;        
            if ( numTeclasPulsadas )
            {
                if ( teclaPulsada[0] == KEY_UP )
                {
                    dir = dArriba ;
                    imagenCelda = icGusanoArribaIzquierda ;
                }
                if ( teclaPulsada[0] == KEY_DOWN )
                {
                    dir = dAbajo ;
                    imagenCelda = icGusanoAbajoIzquierda ;
                }
            }   
            break ;
        case dIzquierda:
            imagenCelda = icGusanoHorizontal ;        
            if ( numTeclasPulsadas )
            {
                if ( teclaPulsada[0] == KEY_UP )
                {
                    dir = dArriba ;
                    imagenCelda = icGusanoArribaDerecha ;
                }
                if ( teclaPulsada[0] == KEY_DOWN )
                {
                    dir = dAbajo ;
                    imagenCelda = icGusanoAbajoDerecha ;
                }
            }
            break ;
        }
        
        if ( numTeclasPulsadas )
        {
            teclaPulsada[0] = teclaPulsada[1] ;
            numTeclasPulsadas -- ;
        }
        
        if ( comienzaGusano )
        {
            comienzaGusano = false ;
            switch (dir)
            {
            case dArriba:
                imagenCelda = icColaAbajo ;
                break ;
            case dDerecha:
                imagenCelda = icColaIzquierda ;
                break ;
            case dAbajo:
                imagenCelda = icColaArriba ;
                break ;
            case dIzquierda:
                imagenCelda = icColaDerecha ;
                break ;
            }
        }
        
        int tx = x ;
        int ty = y ;
        switch ( dir )
        {
        case dArriba:
            ty-- ;
            break ;
        case dAbajo:
            ty++ ;
            break ;
        case dDerecha:
            tx++ ;
            break ;
        case dIzquierda:
            tx-- ;
            break ;        
        }
    
        Celda *celda = nivel->GetCelda(tx, ty);
        if ( celda->SePuedeCruzar() )
        {
            // Se pinta la posicion anterior de serpiente
            nivel->GetCelda(x, y)->SetImagenCelda(imagenCelda);
            nivel->GetCelda(x, y)->SetTipoCelda(tcGusano);
            x = tx ;
            y = ty ;
            switch ( dir )
            {
            case dArriba:
                imagenCelda = icColaArriba ;
                break ;
            case dDerecha:
                imagenCelda = icColaDerecha ;
                break ;
            case dAbajo :
                imagenCelda = icColaAbajo ;
                break ;
            case dIzquierda:
                imagenCelda = icColaIzquierda ;
                break ;
            }
            nivel->GetCelda(x, y)->SetImagenCelda(imagenCelda);
            nivel->GetCelda(x, y)->SetTipoCelda(tcGusano);
            nivel->GetCelda(x, y)->EntraGusano(this);
        }else
        {
            muerto = true ;
        }
    }
}

void
Gusano::Pintar(int esquinax, int esquinay)
{
    if ( activo )
    {
        imagenCabeza[dir]->Pintar(esquinax + x*30, esquinay + y*30);
    }
}

void
Gusano::Inicializar()
{
    try
    {
        imagenCabeza[dArriba]   = new Imagen("Graficos\\cabeza_arriba.bmp");
        imagenCabeza[dDerecha]  = new Imagen("Graficos\\cabeza_derecha.bmp");
        imagenCabeza[dAbajo]    = new Imagen("Graficos\\cabeza_abajo.bmp");
        imagenCabeza[dIzquierda]= new Imagen("Graficos\\cabeza_izquierda.bmp");
        for ( int i = 0 ; i < 4 ; i++ )
        {
            imagenCabeza[i]->SetMascara(true);
        }
    }
    catch ( Excepcion &ex )
    {
        throw Excepcion(ex, "Gusano::Inicializar()");
    }
}

void
Gusano::Cerrar()
{
    try
    {
        for ( int i = 0 ; i < 4 ; i++ )
        {
            if ( !imagenCabeza[i] )
            {
                throw Excepcion("Gusano::Cerrar()");
            }
            delete imagenCabeza[i] ;
        }
    }
    catch ( Excepcion &ex )
    {
        throw Excepcion(ex, "Gusano::Cerrar()");
    }
}
    
