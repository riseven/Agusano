#include <allegro.h>
#include "Imagen.h"

#include "Excepcion.h"
#include "Graficos.h"

Imagen::Imagen()
{
    bitmap = NULL ;
    mascara = false ;
    alpha = 255 ;    
}

Imagen::Imagen(string fichero)
{
    bitmap = NULL ;
    bitmap = load_bitmap(fichero.c_str(), NULL);
    if ( !bitmap )
    {
        string temp = "Imagen::Imagen(string): No se pudo cargar el fichero: ";
        temp += fichero ;
        throw Excepcion(temp);
    }
    mascara = false ;
    alpha = 255 ;
}

Imagen::~Imagen()
{
    if ( bitmap )
    {
        destroy_bitmap(bitmap);
        bitmap = NULL ;
    }
}

void
Imagen::CargarFichero(string fichero)
{
    if ( bitmap )
    {
        destroy_bitmap(bitmap);
        bitmap = NULL ;
    }
    bitmap = load_bitmap(fichero.c_str(), NULL);
    if ( !bitmap )
    {
        string temp = "Imagen::CargarFichero(string): No se pudo cargar el fichero: ";
        temp += fichero ;
        throw Excepcion(temp);
    }
}  

void
Imagen::GenerarTexto(string texto, int color)
{
    if ( bitmap )
    {
        destroy_bitmap(bitmap);
        bitmap = NULL ;
    }
        
    bitmap = create_bitmap( text_length(font, texto.c_str()), text_height(font) );
    textout_ex(bitmap, font, texto.c_str(), 0, 0, color, makecol(255,0,255));
    mascara = true ;
}  

void
Imagen::SetMascara(bool mascara)
{
    Imagen::mascara = mascara ;
}

void
Imagen::SetAlpha(int alpha)
{
    Imagen::alpha = alpha ;
}

int
Imagen::GetWidth()
{
    return bitmap->w ;
}

int
Imagen::GetHeight()
{
    return bitmap->h ;
}

void
Imagen::Pintar(int x, int y)
{
    set_trans_blender(0, 0, 0, alpha);
    if ( !bitmap )
    {
        //throw Excepcion("Imagen::Pintar(int, int): Imagen no valida");
        return ;
    }
    if ( !mascara && alpha == 255)
    {
        blit( bitmap, graficos.GetScreen(), 0, 0, x, y, bitmap->w, bitmap->h );
    }
    else if ( mascara && alpha == 255)
    {
        masked_blit( bitmap, graficos.GetScreen(), 0, 0, x, y, bitmap->w, bitmap->h );
    }
    else
    {
        set_trans_blender(0, 0, 0, alpha);
        draw_trans_sprite( graficos.GetScreen(), bitmap, x, y);
    }
}
