#include <allegro.h>
#include "Agujero.h"

#include "Excepcion.h"
#include "Gusano.h"
#include "Nivel.h"

Imagen *Agujero::imagenAgujeroCerrado = NULL ;
Imagen *Agujero::imagenTeleporte = NULL ;
Imagen *Agujero::imagenFlecha = NULL ;
Imagen *Agujero::imagenSalidaNivel = NULL ;

Agujero::Agujero()
{
    activado = false ;
    agujeroLinkado = NULL ;
    anguloRodea = ftofix(0.0) ;
    rodeaAgujero = NULL ;
    gusanoApareciendo = NULL ;
}

Agujero::~Agujero()
{
}

void
Agujero::SetPos(int x, int y)
{
    Agujero::x = x ;
    Agujero::y = y ;
}

void
Agujero::SetOrden(int orden)
{
    Agujero::orden = orden ;
    
    char * texto = new char[25] ;
    sprintf(texto, "%d", orden);
    numeroAgujero.GenerarTexto( texto , makecol(255,0,0) );
    delete[] texto ;
    rodeaAgujero = &numeroAgujero ;
}

void
Agujero::SetNivel(Nivel *nivel)
{
    Agujero::nivel = nivel ;
}

void
Agujero::SetAgujeroLinkado(Agujero *agujeroLinkado)
{
    Agujero::agujeroLinkado = agujeroLinkado ;
}

void
Agujero::Activar()
{
    activado = true ;
    teleActual = 0 ;
    teleSiguiente = 1 ;
    if ( apareciendo )
    {
        alphaActual = 0 ;
    }
    else
    {
        alphaActual = 255 ;
    }
}

void
Agujero::Desactivar()
{
    activado = false ;
}

void
Agujero::EntraGusano(Gusano *gusano)
{
    if ( agujeroLinkado )
    {
        agujeroLinkado->ApareceGusano(gusano);
        Desactivar();
    }
    else if ( esSalidaNivel )
    {
        Desactivar();
        // Pasamos de nivel
        nivel->FinalizaNivel(tipoSalidaNivel);
    }
}

void
Agujero::ApareceGusano(Gusano *gusano)
{
    apareciendo = true ;
    gusano->SetPosicion(x, y);
    gusano->ComienzaGusano();
    gusano->SetActivo(false);
    gusanoApareciendo = gusano ;
    Activar();

}

bool
Agujero::SePuedeCruzar()
{
    return activado ;
}

void
Agujero::SetSalidaNivel(SalidaNivel tipoSalidaNivel)
{
    esSalidaNivel = true ;
    Agujero::tipoSalidaNivel = tipoSalidaNivel ;
    rodeaAgujero = &(imagenSalidaNivel[tipoSalidaNivel]) ;
}

void
Agujero::SetSalidaNivelFijo(SalidaNivel salidaNivel)
{
    comportamiento = caFijo ;
    SetSalidaNivel(salidaNivel);
}

void
Agujero::SetSalidaNivelUmbral(SalidaNivel base, SalidaNivel pen, int umbral)
{
    comportamiento = caUmbral ;
    Agujero::umbral = umbral ;
    umbralActual = umbral ;
    tipoSalidaNivelBase = base ,
    tipoSalidaNivelPenalizacion = pen ;
    SetSalidaNivel(base);
}

void
Agujero::SetSalidaNivelDecrementador(SalidaNivel base)
{
    comportamiento = caDecrementador ;
    tipoSalidaNivelBase = base ;
    SetSalidaNivel(base);
}

void
Agujero::NuevoIntento()
{
    if ( esSalidaNivel )
    {
        switch ( comportamiento )
        {
        case caUmbral:
            umbralActual-- ;
            if ( umbralActual <= 0 )
            {
                SetSalidaNivel(tipoSalidaNivelPenalizacion);
            }
            else
            {
                SetSalidaNivel(tipoSalidaNivelBase);
            }
            break ;
        case caDecrementador:
            if ( tipoSalidaNivel != snMenos10 )
            {
                tipoSalidaNivel = (SalidaNivel)(tipoSalidaNivel-1);
                SetSalidaNivel(tipoSalidaNivel);
            }
            break ;
        }
    }
}

void
Agujero::Reset()
{
    if ( esSalidaNivel )
    {
        switch ( comportamiento )
        {
        case caUmbral:
            umbralActual = umbral ;
            SetSalidaNivel(tipoSalidaNivelBase);
            break ;
        case caDecrementador:
            tipoSalidaNivel = tipoSalidaNivelBase ;
            SetSalidaNivel(tipoSalidaNivel);
            break ;
        }
    }
}

void
Agujero::Actualizar()
{
    
    if ( apareciendo )
    {
        if ( !gusanoApareciendo )
        {
            throw Excepcion("Agujero::Actualizar()");
        }
        
        if ( alphaActual >= 240 )
        {
            apareciendo = false ;
            nivel->ActivarAgujero(orden+1);
            Desactivar();
            gusanoApareciendo->SetActivo(true);
        }
    }
       
    
}

void
Agujero::Pintar(int esquinax, int esquinay)
{
    imagenAgujeroCerrado->Pintar(esquinax + x *30, esquinay + y * 30);
    if ( activado )
    {
        alphaSiguiente += 25 ;
        if ( alphaActual < 240 )
        {
            alphaActual += 8 ;
            if (alphaSiguiente > alphaActual)
            {
                alphaSiguiente = alphaActual ;
            }
        }
        else
        {
            alphaActual = 255 ;
        }
        imagenTeleporte[teleActual].SetAlpha(alphaActual);
        imagenTeleporte[teleActual].Pintar(esquinax + x*30, esquinay +y*30);
        imagenTeleporte[teleSiguiente].SetAlpha(alphaSiguiente);
        imagenTeleporte[teleSiguiente].Pintar(esquinax + x*30, esquinay +y*30);
        
        if ( alphaSiguiente >= 240 )
        {
            teleActual = teleSiguiente ;
            teleSiguiente = (teleSiguiente+1)%numImagenesTeleporte ;
            alphaSiguiente = 0 ;
        }
    }
    
    
    anguloRodea = fixadd(anguloRodea, itofix(3));
    
    for ( int i = 0 ; i < 3 ; i++ )
    {
        fixed ang = fixadd(anguloRodea, itofix(i*85));
        int dx = fixtoi(fixmul(fixcos(ang) , itofix(25))) ;
        int dy = fixtoi(fixmul(fixsin(ang) , itofix(25))) ;
    
    
        rodeaAgujero->Pintar(esquinax + x *30 + 15 - rodeaAgujero->GetWidth()/2 +dx, 
                            esquinay + y *30 + 15 - rodeaAgujero->GetHeight()/2 +dy) ;
    }
                        
    if ( activado )
    {
        int itemx , itemy ;
        bool doble = false ;
        bool pintaFlecha = true ;
        if ( y*30 < -esquinay )
        {
            if ( x*30 < -esquinax || x*30 > -esquinax + SCREEN_W)
            {
                doble = true ;
            }
            else
            {            
                itemx = esquinax + x*30 + 5 ;
                itemy = 90 ;
                imagenFlecha[0].Pintar(esquinax + x*30 -15, 30);
            }
        }
        else if ( y*30 > -esquinay + SCREEN_H )
        {
            if ( x*30 < -esquinax || x*30 > -esquinax + SCREEN_W)
            {
                doble = true ;
            }
            else
            {
                itemx = esquinax + x*30 + 5 ;
                itemy = SCREEN_H-80 ;            
                imagenFlecha[2].Pintar(esquinax + x*30 -15, SCREEN_H-60);
            }
        }
        else if ( x*30 < -esquinax )
        {
            if ( y*30 < -esquinay || y*30 > -esquinay + SCREEN_H)
            {
                doble = true ;
            }
            else
            {            
                itemx = 60 ;
                itemy = esquinay + y*30 + 5 ;                
                imagenFlecha[3].Pintar(0, esquinay + y*30 -15);
            }
        }
        else if ( x*30 > -esquinax + SCREEN_W )
        {
            if ( y*30 < -esquinay || y*30 > -esquinay + SCREEN_H)
            {
                doble = true ;
            }
            else
            {            
                itemx = SCREEN_W - 80 ;
                itemy = esquinay + y*30 + 5 ;                   
                imagenFlecha[1].Pintar(SCREEN_W-60, esquinay + y*30 -15);
            }
        }
        else
        {
            pintaFlecha = false ;
        }
            
        if ( doble )
        {
            int difx, dify ;
            int posx, posy ;
            if ( x*30 < -esquinax )
            {
                difx = x*30 + esquinax ;
            }
            else
            {
                difx = x*30 + esquinax - SCREEN_W ;
            }
            
            if ( y*30 < -esquinay )
            {
                dify = y*30 + esquinay ;
            }
            else
            {
                dify = y*30 + esquinay - SCREEN_H ;
            }
            
            if ( difx > dify )
            {
                if ( y*30 < -esquinay )
                {
                    posy = 30 ;
                    itemy = 50 ;
                }
                else
                {
                    posy = SCREEN_H - 60 ;
                    itemy = SCREEN_H - 40 ;
                }
                
                if ( x*30 < -esquinax )
                {
                    imagenFlecha[3].Pintar(0, posy);
                    itemx = 60 ;
                }
                else
                {
                    imagenFlecha[1].Pintar(SCREEN_W-60, posy);
                    itemx = SCREEN_W-80 ;
                }
            }
            else
            {
                if ( x*30 < -esquinax )
                {
                    posx = 0 ;
                    itemx = 20 ;
                }
                else
                {
                    posx = SCREEN_W - 60 ;
                    itemx = SCREEN_W - 40 ;
                }
                
                if ( y*30 < -esquinay )
                {
                    imagenFlecha[0].Pintar(posx, 30);
                    itemy = 90 ;
                }
                else
                {
                    imagenFlecha[2].Pintar(posx, SCREEN_H-60);
                    itemy = SCREEN_H-80 ;
                }
            }
        }

        if ( pintaFlecha )
        {
            rodeaAgujero->Pintar(itemx, itemy);
        }
 
    }
    
}

void
Agujero::Inicializar()
{
    try
    {
        imagenAgujeroCerrado = new Imagen("Graficos\\agujero_cerrado.bmp");
        imagenAgujeroCerrado->SetMascara(true);
        if ( !imagenAgujeroCerrado )
        {
            throw Excepcion("Agujero::Inicialiar()");
        }
        imagenTeleporte = new Imagen[numImagenesTeleporte];
        imagenTeleporte[0].CargarFichero("Graficos\\tele1.bmp");
        imagenTeleporte[1].CargarFichero("Graficos\\tele2.bmp");
        imagenTeleporte[2].CargarFichero("Graficos\\tele3.bmp");
        imagenTeleporte[3].CargarFichero("Graficos\\tele4.bmp");
        imagenTeleporte[4].CargarFichero("Graficos\\tele5.bmp");
        imagenTeleporte[5].CargarFichero("Graficos\\tele6.bmp");
        imagenTeleporte[6].CargarFichero("Graficos\\tele7.bmp");
        imagenTeleporte[7].CargarFichero("Graficos\\tele8.bmp");
        imagenTeleporte[8].CargarFichero("Graficos\\tele9.bmp");
        imagenTeleporte[9].CargarFichero("Graficos\\tele10.bmp");
        imagenTeleporte[10].CargarFichero("Graficos\\tele11.bmp");
        imagenTeleporte[11].CargarFichero("Graficos\\tele12.bmp");
        for ( int i = 0 ; i < numImagenesTeleporte ; i++ )
        {
            imagenTeleporte[i].SetMascara(true);
        }
        
        imagenFlecha = new Imagen[numImagenesFlecha] ;
        imagenFlecha[0].CargarFichero("Graficos\\flecha_arriba.bmp");
        imagenFlecha[1].CargarFichero("Graficos\\flecha_derecha.bmp");
        imagenFlecha[2].CargarFichero("Graficos\\flecha_abajo.bmp");
        imagenFlecha[3].CargarFichero("Graficos\\flecha_izquierda.bmp");
        for ( int i = 0 ; i < numImagenesFlecha ; i++ )
        {
            imagenFlecha[i].SetMascara(true);
            imagenFlecha[i].SetAlpha(128);
        }
        
        imagenSalidaNivel = new Imagen[numSalidasNivel] ;
        imagenSalidaNivel[snMenos10].CargarFichero("Graficos\\salida_menos_10.bmp");
        imagenSalidaNivel[snMenos5].CargarFichero("Graficos\\salida_menos_5.bmp");
        imagenSalidaNivel[snMenos3].CargarFichero("Graficos\\salida_menos_3.bmp");
        imagenSalidaNivel[snMenos2].CargarFichero("Graficos\\salida_menos_2.bmp");
        imagenSalidaNivel[snMenos1].CargarFichero("Graficos\\salida_menos_1.bmp");
        imagenSalidaNivel[snMasVelocidad].CargarFichero("Graficos\\salida_mas_velocidad.bmp");
        imagenSalidaNivel[snMas1].CargarFichero("Graficos\\salida_mas_1.bmp");
        imagenSalidaNivel[snMas2].CargarFichero("Graficos\\salida_mas_2.bmp");
        imagenSalidaNivel[snMas3].CargarFichero("Graficos\\salida_mas_3.bmp");
        imagenSalidaNivel[snMas5].CargarFichero("Graficos\\salida_mas_5.bmp");
        imagenSalidaNivel[snMas10].CargarFichero("Graficos\\salida_mas_10.bmp");
        for ( int i = 0 ; i < numSalidasNivel ; i++ )
        {
            imagenSalidaNivel[i].SetMascara(true);
            imagenSalidaNivel[i].SetAlpha(128);
        }        
    }
    catch ( Excepcion &ex )
    {
        throw Excepcion(ex, "Agujero::Inicializar()");
    }
}

void
Agujero::Cerrar()
{
    try
    {
        if ( !imagenAgujeroCerrado || !imagenTeleporte || !imagenFlecha || !imagenSalidaNivel)
        {
            throw Excepcion("Agujero::Cerrar()");
        }
        delete imagenAgujeroCerrado ;
        delete[] imagenTeleporte ;
        delete[] imagenFlecha ;
        delete[] imagenSalidaNivel ;
    }
    catch ( Excepcion &ex )
    {
        throw Excepcion(ex, "Agujero::Cerrar()");
    }
}
