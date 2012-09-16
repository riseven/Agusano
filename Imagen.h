#ifndef __IMAGEN_H__
#define __IMAGEN_H__

#include <allegro.h>
#include <string>
#include "Imagen.h"

using namespace std;

class Imagen
{
private:
    BITMAP *bitmap ;
    bool mascara ;
    int alpha ;
public:
    Imagen();
    Imagen(string fichero);
    ~Imagen();
    void SetMascara(bool mascara);
    void SetAlpha(int alpha);
    int GetWidth();
    int GetHeight();
    void CargarFichero(string fichero);
    void GenerarTexto(string texto, int color);
    void Pintar(int x, int y);
};

#endif
