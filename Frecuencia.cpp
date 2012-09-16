#include <allegro.h>
#include "Frecuencia.h"

Frecuencia::Frecuencia(float frec)
{
    periodo = (int)(1000.0/frec);
    ultimo = GetTickCount();
}

Frecuencia::~Frecuencia()
{
}

bool
Frecuencia::Comprobar()
{
    if ( GetTickCount() > ultimo + periodo )
    {
        ultimo += periodo ;
        return true ;
    }
    return false ;
}
