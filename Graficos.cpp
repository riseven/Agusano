#define __GRAFICOS_CPP__

#include <allegro.h>

#include "Graficos.h"
#include "Excepcion.h"

Graficos::Graficos()
{
}

Graficos::~Graficos()
{
}

void
Graficos::Inicializar(int w, int h, int depth)
{
    set_color_depth(depth);
    if (set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, w, h, 0, 0) != 0) 
    {
        string temp = "Graficos::Graficos(int, int, int): ";
        temp += allegro_error ;
        throw Excepcion(temp);
    }
    
    page[0] = create_video_bitmap(SCREEN_W, SCREEN_H);
    page[1] = create_video_bitmap(SCREEN_W, SCREEN_H);
    pageActual = 0 ;
}

BITMAP *
Graficos::GetScreen()
{
    return page[pageActual] ;
}

void
Graficos::Actualizar()
{
    release_bitmap(page[pageActual]);
    show_video_bitmap(page[pageActual]);
    pageActual = 1-pageActual;
    acquire_bitmap(page[pageActual]);
    clear_bitmap(page[pageActual]);
}

