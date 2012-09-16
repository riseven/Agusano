#ifndef __AGUJERO_H__
#define __AGUJERO_H__

#include <allegro.h>
#include "Imagen.h"

typedef enum ComportamientoAgujero
{
    caFijo,
    caUmbral,
    caDecrementador
};

typedef enum SalidaNivel
{
    snMenos10,
    snMenos5,
    snMenos3,
    snMenos2,
    snMenos1,
    snMasVelocidad,
    snMas1,
    snMas2,
    snMas3,
    snMas5,
    snMas10    
};

typedef enum TipoAgujeroSalida
{
    tasSiempreMasVelocidad,
    tasUmbralCambio,
    tasDecrementador
};

class Gusano ;
class Nivel ;

class Agujero
{
private:
    int x, y;
    int orden ;
    bool esFinal ;
    bool activado ;
    int teleActual ;
    int teleSiguiente ;
    int alphaActual ;
    int alphaSiguiente ;
    bool apareciendo ;
    Nivel *nivel ;
    Agujero *agujeroLinkado ;
    Imagen numeroAgujero ;
    Imagen *rodeaAgujero ;
    fixed anguloRodea ;
    bool esSalidaNivel ;
    SalidaNivel tipoSalidaNivel ; 
    ComportamientoAgujero comportamiento ;
    int umbral, umbralActual ;
    SalidaNivel tipoSalidaNivelBase ;
    SalidaNivel tipoSalidaNivelPenalizacion ;   
    Gusano *gusanoApareciendo ;
    
    static Imagen *imagenAgujeroCerrado ;
    static Imagen *imagenTeleporte ;
    static const int numImagenesTeleporte = 12 ;
    static Imagen *imagenFlecha ;
    static const int numImagenesFlecha = 4 ;
    static Imagen *imagenSalidaNivel ;
    static const int numSalidasNivel = 11 ;
    
public:
    Agujero();
    ~Agujero();
    void SetPos(int x, int y);
    void SetOrden(int orden);
    void SetNivel(Nivel *nivel);
    void SetAgujeroLinkado(Agujero *agujeroLinkado);
    void Activar();
    void Desactivar();
    void SetSalidaNivel(SalidaNivel tipoSalidaNivel);
    void SetSalidaNivelFijo(SalidaNivel salidaNivel);
    void SetSalidaNivelUmbral(SalidaNivel base, SalidaNivel pen, int umbral);
    void SetSalidaNivelDecrementador(SalidaNivel base);
    void NuevoIntento();
    void Reset();
    void EntraGusano(Gusano *gusano);
    void ApareceGusano(Gusano *gusano);
    bool SePuedeCruzar();
    void Actualizar();
    void Pintar(int esquinax, int esquinay);

    
    
    static void Inicializar();
    static void Cerrar();
};

#endif
