#include <allegro.h>
#include "Nivel.h"

#include "Excepcion.h"
#include "Partida.h"

Imagen *Partida::imagenBarra ;
Imagen *Partida::imagenCorre ;

Nivel::Nivel(Partida *partida, int nivel)
{
    Nivel::partida = partida ;
    
    w = 20 + nivel ;
    h = 20 + nivel ;
    
    celda = new Celda *[w] ;
    for ( int i = 0 ; i < w ; i++ )
    {
        celda[i] = new Celda[h] ;
    }
    
    // Pintamos el borde
    for ( int i = 0 ; i < w ; i++ )
    {
        celda[i][0].SetImagenCelda(icBordeArriba);
        celda[i][0].SetTipoCelda(tcBorde);
        celda[i][h-1].SetImagenCelda(icBordeAbajo);
        celda[i][h-1].SetTipoCelda(tcBorde);        
    }
    for ( int i = 0 ; i < h ; i++ )
    {
        celda[0][i].SetImagenCelda(icBordeIzquierda);
        celda[0][i].SetTipoCelda(tcBorde);        
        celda[w-1][i].SetImagenCelda(icBordeDerecha);
        celda[w-1][i].SetTipoCelda(tcBorde);        
    }
    celda[0][0].SetImagenCelda(icBordeArribaIzquierda);
    celda[w-1][0].SetImagenCelda(icBordeArribaDerecha);
    celda[0][h-1].SetImagenCelda(icBordeAbajoIzquierda);
    celda[w-1][h-1].SetImagenCelda(icBordeAbajoDerecha);
    
    estado = enVisualizacion ;

    esquinax = 0 ;
    esquinay = 0 ;
    
    gusano = NULL ;
    
    numAgujeros = nivel/2 ;
    if ( !(numAgujeros%2) )
    {
        numAgujeros++ ;
    }
    agujero = new Agujero[numAgujeros] ;
    for ( int i = 0 ; i < numAgujeros ; i++ )
    {
        int x, y ;
        do
        {
            x = rand()%(w-2)+1 ;
            y = rand()%(h-2)+1 ;
        } while ( !celda[x][y].SePuedeCruzar() );
        if ( i == 0 )
        {
            inicioX = -(x*30)+SCREEN_W/2 ;
            inicioY = -(y*30)+SCREEN_H/2 ;
        }
        agujero[i].SetPos( x, y );
        agujero[i].SetOrden(i);
        agujero[i].SetNivel(this);
        celda[x][y].SetAgujero(&agujero[i]);
    }
    
    // Linkamos los agujeros
    for ( int i = 1 ; i < numAgujeros ; i+=2 )
    {
        agujero[i].SetAgujeroLinkado(&agujero[i+1]);
    }
    
    
    numSalidas = 3 ;
    salida = new Agujero[numSalidas] ;
    
    for ( int i = 0 ; i < numSalidas ; i++ )
    {
        int x, y;
        do
        {
            x = rand()%(w-2)+1 ;
            y = rand()%(h-2)+1 ;
        } while ( !celda[x][y].SePuedeCruzar() );
        salida[i].SetPos( x, y );
        salida[i].SetOrden(i+50);
        salida[i].SetNivel(this);
        celda[x][y].SetAgujero(&salida[i]);
        //salida[i].SetSalidaNivel((SalidaNivel)i);
    }
    salida[0].SetSalidaNivelFijo(snMasVelocidad);
    salida[1].SetSalidaNivelUmbral(snMas1, snMenos5, 5);
    salida[2].SetSalidaNivelDecrementador(snMas10);
    
    // Texto del nivel
    imagenTextoNivel = new Imagen();
    char *textoTemp = new char[25] ;
    sprintf(textoTemp, "Nivel %d", nivel);
    imagenTextoNivel->GenerarTexto(textoTemp, makecol(255,255,0));
    delete[] textoTemp ;
    
}

Nivel::~Nivel()
{
    if ( !celda )
    {
        throw Excepcion("Nivel::~Nivel(): E1");
    }
        
    for ( int i = 0 ; i < w ; i++ )
    {
        if ( !celda[i] )
        {
            throw Excepcion("Nivel::~Nivel(): E2");
        }
        delete [] celda[i] ;
    }
    
    delete[] celda ;
    delete[] salida ;
    delete[] agujero ;
    delete imagenTextoNivel ;
}

int
Nivel::GetAncho()
{
    return w;
}

int
Nivel::GetAlto()
{
    return h;
}

int
Nivel::GetEsquinaX()
{
    return esquinax ;
}

int
Nivel::GetEsquinaY()
{
    return esquinay ;
}

int
Nivel::GetInicioX()
{
    return inicioX ;
}

int
Nivel::GetInicioY()
{
    return inicioY ;
}

void
Nivel::SetEsquina(int esquinax, int esquinay)
{
    Nivel::esquinax = esquinax ;
    Nivel::esquinay = esquinay ;
    
    if ( estado != enTransicion )
    {   
        if ( Nivel::esquinax > 0 )
        {
            Nivel::esquinax = 0 ;
        }
        if ( Nivel::esquinay > 30 )
        {
            Nivel::esquinay = 30 ;
        }
        if ( Nivel::esquinax < -w*30+SCREEN_W )
        {
            Nivel::esquinax = -w*30+SCREEN_W;
        }
        if ( Nivel::esquinay < -h*30+SCREEN_H )
        {
            Nivel::esquinay = -h*30+SCREEN_H;
        }
    }
}

Celda *
Nivel::GetCelda(int x, int y)
{
    return &celda[x][y] ;
}
Imagen *
Nivel::GetImagenTextoNivel()
{
    return imagenTextoNivel ;
}

void
Nivel::ActivarAgujero(int orden)
{
    if ( orden < numAgujeros )
    {
        agujero[orden].Activar();
    }
    else
    {
        for ( int i = 0 ; i < numSalidas ; i++ )
        {
            salida[i].Activar();
        }
    }
}

EstadoNivel
Nivel::GetEstado()
{
    return estado ;
}

void
Nivel::SetEstado(EstadoNivel estado)
{
    Nivel::estado = estado ;
}

void
Nivel::FinalizaNivel(SalidaNivel salidaNivel)
{
    delete gusano ;
    gusano = NULL ;
    for ( int x = 0 ; x < w ; x++ )
    {
        for ( int y = 0 ; y < h ; y++ )
        {
            if ( celda[x][y].GetTipoCelda() == tcGusano )
            {
                celda[x][y].SetImagenCelda(icFondo);
                celda[x][y].SetTipoCelda(tcVacio);
            }
        }             
    }
        
    for ( int i = 0 ; i < numAgujeros ; i++ )
    {
        agujero[i].Desactivar();
    }
    for ( int i = 0 ; i < numSalidas ; i++ )
    {
        salida[i].Desactivar();
        salida[i].Reset();
    }               
    
    estado = enVisualizacion ;    

    
    switch ( salidaNivel )
    {
    case snMenos10:
        partida->SaltoNivel(-10);
        break ;
    case snMenos5:
        partida->SaltoNivel(-5);
        break ;
    case snMenos3:
        partida->SaltoNivel(-3);
        break ;
    case snMenos2:
        partida->SaltoNivel(-2);
        break ;
    case snMenos1:
        partida->SaltoNivel(-1);
        break ;
    case snMasVelocidad:
        partida->SubirVelocidadGusano();
        partida->SaltoNivel(1);
        break ;
    case snMas1:
        partida->SaltoNivel(1);
        break ;
    case snMas2:
        partida->SaltoNivel(2);
        break ;
    case snMas3:
        partida->SaltoNivel(3);
        break ;
    case snMas5:
        partida->SaltoNivel(5);
        break ;
    case snMas10:
        partida->SaltoNivel(10);
        break ;
    }

}
        

void 
Nivel::Pintar()
{
    // Pintamos las celdas
    for ( int i = 0 ; i < w ; i++ )
    {
        for ( int j = 0 ; j < h ; j++ )
        {
            celda[i][j].Pintar(i*30+esquinax, j*30+esquinay);
        }
    }
    // Pintamos la cabeza del gusano
    if ( gusano )
    {
        gusano->Pintar(esquinax, esquinay);    
    }
    // Pintamos los agujeros
    for ( int i = 0 ; i < numAgujeros ; i++ )
    {
        agujero[i].Pintar(esquinax, esquinay);
    }
    // Pintamos los agujeros de salida
    for ( int i = 0 ; i < numSalidas ; i++ )
    {
        salida[i].Pintar(esquinax, esquinay);
    }
    
       

}

void
Nivel::Actualizar()
{
    switch ( estado )
    {
    case enTransicion:
        break ;
    case enVisualizacion:
        int x, y;
        get_mouse_mickeys(&x, &y);
        if ( x || y )
        {
            SetEsquina(esquinax-x,esquinay-y);
        }
        if ( mouse_b & 1 || key[KEY_SPACE])
        {
            EmpezarNivel();
        }
        break ;
    case enEnJuego:
        for ( int i = 0 ; i < numAgujeros ; i++ )
        {
            agujero[i].Actualizar();
        }
        
        for ( int i = 0 ; i < numSalidas ; i++ )
        {
            salida[i].Actualizar();
        }
        
        if ( gusano->Muerto() )
        {
            delete gusano ;
            gusano = NULL ;
            for ( int x = 0 ; x < w ; x++ )
            {
                for ( int y = 0 ; y < h ; y++ )
                {
                    if ( celda[x][y].GetTipoCelda() == tcGusano )
                    {
                        celda[x][y].SetImagenCelda(icFondo);
                        celda[x][y].SetTipoCelda(tcVacio);
                    }
                }             
            }
                
            for ( int i = 0 ; i < numAgujeros ; i++ )
            {
                agujero[i].Desactivar();
            }
            for ( int i = 0 ; i < numSalidas ; i++ )
            {
                salida[i].Desactivar();
                salida[i].NuevoIntento();
            }               
            
            estado = enVisualizacion ;
        }
        else
        {
            gusano->Actualizar();
            if ( gusano )
            {
                if ( abs(-gusano->GetX()*30+SCREEN_W/2 - esquinax) > 200 )
                {
                    esquinax = -gusano->GetX()*30+SCREEN_W/2 ;
                }
                if ( abs((-gusano->GetY()+1)*30+SCREEN_H/2 - esquinay) > 200 )
                {
                    esquinay = (-gusano->GetY()+1)*30+SCREEN_H/2 ;
                }
                
                int dx = 0, dy = 0 ;
                if ( -gusano->GetX()*30+SCREEN_W/2 < esquinax )
                {
                    dx = -1 ;
                }
                if ( -gusano->GetX()*30+SCREEN_W/2 > esquinax )
                {
                    dx = 1 ;
                }
                if ( (-gusano->GetY()+1)*30+SCREEN_H/2 < esquinay )
                {
                    dy = -1 ;
                }
                if ( (-gusano->GetY()+1)*30+SCREEN_H/2 > esquinay )
                {
                    dy = 1 ;
                }


                
                int factor = 10 ;
                
                int difx = 1, dify = 1;
                bool continua = true ;
                for ( int i = 0 ; continua ; i ++ )
                {                
                    continua = false ;
                    if ( abs(-gusano->GetX()*30+SCREEN_W/2 - esquinax) > factor )
                    {
                        difx+=1*dx ;
                        continua = true ;
                    }
                    if ( abs((-gusano->GetY()+1)*30+SCREEN_H/2 - esquinay) > factor )
                    {
                        dify+=1*dy ;
                        continua = true ;
                    }
                    factor += 5 ;
                }
                             
                //SetEsquina(-gusano->GetX()*30+SCREEN_W/2, -(gusano->GetY()+1)*30+SCREEN_H/2);
                SetEsquina(esquinax+difx, esquinay+dify);
            }
        }
    }
}

void
Nivel::EmpezarNivel()
{
    estado = enEnJuego ;
    gusano = new Gusano(this, 10, 10, dArriba, partida->GetVelocidadGusano());

    agujero[0].ApareceGusano(gusano);    
}
    
    


