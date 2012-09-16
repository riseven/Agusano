#ifndef __PARTIDA_H__
#define __PARTIDA_H__

#include <allegro.h>

#include "Nivel.h"

class Partida
{
private:
    Nivel **nivel ; // Necesitamos inicializar cada nivel por separado
    int nivelActual ;
    float frecuenciaGusano ;
    int secs ;
    Imagen imagenSecs ;
    Frecuencia *frecSec ;
    bool transicion ;
    int nivelAntiguo ;
    
    static Imagen *imagenBarra ;
    static Imagen *imagenCorre ;    
    
public:
    Partida();
    ~Partida();
    void SaltoNivel(int salto);
    void SubirVelocidadGusano();
    float GetVelocidadGusano();
    void Actualizar();
    void Pintar();
    bool Finalizado();
    
    static void Inicializar();
    static void Cerrar();
};

#endif
