#ifndef __NIVEL_H__
#define __NIVEL_H__

#include <allegro.h>
#include "Celda.h"
#include "Gusano.h"
#include "Agujero.h"

typedef enum EstadoNivel
{
    enTransicion, 
    enDesactivado ,
    enVisualizacion ,
    enEnJuego ,
    enMostrandoVictoria ,
    enMostrandoDerrota 
};     

class Partida ;

class Nivel
{
private:
    Celda **celda;
    int w, h;
    EstadoNivel estado ;
    int esquinax, esquinay ;
    Gusano *gusano ;
    Agujero *agujero ;
    int numAgujeros ;
    Partida *partida ;
    int numSalidas ;
    Agujero *salida ;
    Imagen *imagenTextoNivel ;
    int inicioX, inicioY ;
    

        
public:
    Nivel(Partida *partida, int nivel);
    ~Nivel();
    int GetAncho();
    int GetAlto();
    int GetEsquinaX();
    int GetEsquinaY();
    int GetInicioX();
    int GetInicioY();
    void SetEsquina(int esquinax, int esquinay);
    Celda * GetCelda(int x, int y);
    Imagen * GetImagenTextoNivel();
    EstadoNivel GetEstado();
    void SetEstado(EstadoNivel estado);
    void ActivarAgujero(int orden);
    void FinalizaNivel(SalidaNivel salidaNivel);
    void Pintar();
    void Actualizar();
    void EmpezarNivel();

};

#endif
