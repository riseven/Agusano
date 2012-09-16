#include <allegro.h>

#include "Excepcion.h"
#include "Graficos.h"
#include "Celda.h"
#include "Nivel.h"
#include "Agujero.h"
#include "Frecuencia.h"
#include "Partida.h"

int main(int argc, char *argv[])
{
    try
    {
        srand(time(NULL));
        
        allegro_init();
        install_keyboard();
        install_mouse();
        
        graficos.Inicializar(640,480,32);
        Celda::Inicializar();
        Gusano::Inicializar();
        Agujero::Inicializar();
        Partida::Inicializar();
        
        Frecuencia frec(25.0);
        Partida *partida = new Partida();
        
        while ( !key[KEY_ESC] )
        {
            if ( frec.Comprobar() )
            {
                partida->Actualizar();
            }
            partida->Pintar();
            graficos.Actualizar();
        }
        
        delete partida;
        Partida::Cerrar();
        Agujero::Cerrar();
        Celda::Cerrar();
        Gusano::Cerrar();
    }
    catch ( Excepcion &ex )
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("%s", ex.GetMensajeDeError().c_str()) ;
    }
}
END_OF_MAIN();
