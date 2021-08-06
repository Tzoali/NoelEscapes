/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#ifndef Reno_h
#define Reno_h
#include <iostream>
#include "Character.h"
#include "Santa.h"
using namespace std;
class Santa;
class Reno:public Character{
    friend state getPosSRX(Reno rudolph,Santa noel);
    friend state getPosSRY(Reno rudolph,Santa noel);
    friend bool touch(Reno rudolph,Santa noel);
private:
    int corralx;
    int corraly;
    int intel;
    state random(Santa noel,int psycho);
    state invertir(state dir);
    Uint32 ini;
public:
    Reno(int intel,int corralx,int corraly,int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h,int,int);
    Reno(int intel,int corralx,int corraly,int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h);
    //inline void setDir(state dir){this->dir=dir;}
    inline operator=(state d){dir=d;}
    bool movimiento(char tablero[210][430],Santa noel,int psycho,Uint32 delay);
    void corral();
    void muerto(Uint32 delay);
    void setCorral(int x,int y);
};
//Constructor de los renos
Reno::Reno(int intel,int corralx,int corraly,int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h,int x,int y):Character(w1,h1,x1,y1,ruta,Render,w,h,x,y)
{
    this->intel=intel;
    srand(time(0));
    dir=DOWN;
    this->corralx=corralx;
    this->corraly=corraly;
}
//Constructor de los renos
Reno::Reno(int intel,int corralx,int corraly,int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h):Character(w1,h1,x1,y1,ruta,Render,w,h)
{
    this->intel=intel;
    srand(time(0));
    dir=DOWN;
    this->corralx=corralx;
    this->corraly=corraly;
}
//Coloca al reno en la posicion de su corral
void Reno::corral()
{
    setPos(corralx,corraly);
}
//Marca al reno que esta muerto para que no salga de su corral
void Reno::muerto(Uint32 delay)
{
    ini=delay;
    corral();
    die=1;
}
//Establece las coordenadas del corral del reno
void Reno::setCorral(int x,int y)
{
    corralx=x;
    corraly=y;
}
#endif // Reno_h
