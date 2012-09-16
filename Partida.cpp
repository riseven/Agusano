#include <allegro.h>
#include "Partida.h"

#include "Excepcion.h"

Partida::Partida()
{
    nivel = new Nivel *[100] ;
    for ( int i = 0 ; i < 100 ; i++ )
    {
        nivel[i] = new Nivel(this, i+1);
    }
    
    nivelActual = 1 ;
    frecuenciaGusano = 5.0 ;
    frecSec = new Frecuencia(1.0);
    secs = 12 ;
    imagenSecs.GenerarTexto("Tiempo: 12", makecol(255,255,0));
    transicion = false ;
}

Partida::~Partida()
{
    if ( !nivel )
    {
        throw Excepcion("Partida::~Partida()");
    }
    for ( int i = 0 ; i < 100 ; i++ )
    {
        if ( !nivel[i] )
        {
            throw Excepcion("Partida::~Partida()");
        }
        delete nivel[i] ;
    }
    delete[] nivel ;  
    delete[] frecSec ;  
}

void
Partida::SaltoNivel(int salto)
{
    nivelAntiguo = nivelActual ;
    nivelActual += salto ;
    
    nivel[nivelAntiguo-1]->SetEstado(enTransicion);
    
    int esqx = nivel[nivelAntiguo-1]->GetEsquinaX();
    int esqy = nivel[nivelAntiguo-1]->GetEsquinaY();
    
    if (nivelActual < 1 )
    {
        nivelActual = 1 ;
    }
    if ( nivelActual > 100 )
    {
        nivelActual = 100 ;
    }
    
    nivel[nivelActual-1]->SetEstado(enTransicion);
    if ( nivelActual > nivelAntiguo )
    {
        nivel[nivelActual-1]->SetEsquina( esqx, esqy + (nivel[nivelAntiguo]->GetAlto()-1)*30);
    }
    else
    {
        nivel[nivelActual-1]->SetEsquina( esqx, esqy - (nivel[nivelActual]->GetAlto()-1)*30);        
    }
    
    secs = nivelActual*12 ;    
    transicion = true ;
}

void
Partida::SubirVelocidadGusano()
{
    frecuenciaGusano += 0.2 ;
    if ( frecuenciaGusano > 10.0 )
    {
        frecuenciaGusano = 10.0 ;
    }
}

float 
Partida::GetVelocidadGusano()
{
    return frecuenciaGusano ;
}

void
Partida::Actualizar()
{
    if ( secs > 0 )
    {
        nivel[nivelActual-1]->Actualizar();
        
        if ( frecSec->Comprobar() )
        {
            if ( nivel[nivelActual-1]->GetEstado() == enEnJuego )
            {
                secs-- ;
                char *temp = new char[25] ;
                sprintf(temp, "Tiempo: %d", secs);
                imagenSecs.GenerarTexto(temp, makecol(255,255,0));
                delete[] temp ;
            }
        }
    }
}

void
Partida::Pintar()
{
    if ( transicion )
    {
        int difx=0 ;
        int dify=0 ;
        
        if ( nivel[nivelActual-1]->GetEsquinaX() < nivel[nivelActual-1]->GetInicioX() -11 )
        {
            difx = 20 ;
        }
        if ( nivel[nivelActual-1]->GetEsquinaX() > nivel[nivelActual-1]->GetInicioX() +11 )
        {
            difx = -20 ;
        }
        if ( nivel[nivelActual-1]->GetEsquinaY() < nivel[nivelActual-1]->GetInicioY() -11 )
        {
            dify = 20 ;
        }
        if ( nivel[nivelActual-1]->GetEsquinaY() > nivel[nivelActual-1]->GetInicioY() +11 )
        {
            dify = -20 ;
        }
        
        nivel[nivelActual-1]->SetEsquina( nivel[nivelActual-1]->GetEsquinaX()+difx, nivel[nivelActual-1]->GetEsquinaY()+dify);
        nivel[nivelAntiguo-1]->SetEsquina( nivel[nivelAntiguo-1]->GetEsquinaX()+difx, nivel[nivelAntiguo-1]->GetEsquinaY()+dify);        
        
        if ( difx == 0 && dify == 0 )
        {
            transicion = false ;
            nivel[nivelActual-1]->SetEstado(enVisualizacion);
        }
    }

    
    nivel[nivelActual-1]->Pintar();
    if ( transicion )
    {
        nivel[nivelAntiguo-1]->Pintar();
    }
    
    // Pintamos la barra
    imagenBarra->Pintar(0,0);
    Imagen * imagenTexto = nivel[nivelActual-1]->GetImagenTextoNivel() ;
    imagenTexto->Pintar( 10, (30-imagenTexto->GetHeight())/2 ); 
    int velocidad = ((int)(( GetVelocidadGusano() - 5.0 )*5))  ;
    for ( int i = 0 ; i < velocidad ; i++ )
    {
        imagenCorre->Pintar( SCREEN_W-20*(i+1),5) ;
    }
    imagenSecs.Pintar( 100, (30-imagenSecs.GetHeight())/2 );    
}

bool
Partida::Finalizado()
{
    return secs <= 0 ;
}

void
Partida::Inicializar()
{
    imagenBarra = new Imagen("Graficos\\barra.bmp");
    imagenCorre = new Imagen("Graficos\\salida_mas_velocidad.bmp");
    imagenCorre->SetMascara(true);
}

void
Partida::Cerrar()
{
    delete imagenBarra ;
    delete imagenCorre ;
}
