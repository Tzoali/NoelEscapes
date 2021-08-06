/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#ifndef Character_h
#define Character_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <string>
using namespace std;
enum state{DOWN,LEFT,RIGHT,UP,NOTHING};
class Character{
protected:
    SDL_Rect rect;
    Texture *charTexture;
    int die;
    int mov;
    state dir;
public:
    Character(int,int,int,int,string,SDL_Renderer*,int,int,int,int);
    Character(int,int,int,int,string,SDL_Renderer*,int,int);
    inline SDL_Texture* getSDLTexture(){return charTexture->getSDLTexture();}
    inline SDL_Rect* getSDLRectPos(){return charTexture->getSDLRect();}
    inline SDL_Rect* getSDLRect(){return &rect;}
    inline void setPos(int x,int y){charTexture->setPos(x,y);}
    void sumPosX(int val);
    void sumPosY(int val);
    inline void setRect(int y){rect.y=y*rect.h;}
    inline void print(SDL_Renderer *Render){charTexture->print(Render,&rect);}
    int getPosX(int pos,int div);
    int getPosX();
    int getPosX(int pos);
    int getPosY(int pos,int div);
    int getPosY(int pos);
    int getPosY();
    inline state getDir(){return dir;}
};
//constructor que inicializa el sprite del personaje y la posicion en la que la recortara
Character::Character(int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h,int x,int y)
{
    charTexture= new Texture(ruta,Render,w,h,x,y);
    rect.x=x1;
    rect.y=y1;
    rect.w=w1;
    rect.h=h1;
    mov=0;
    die=0;
}
//constructor que inicializa el sprite del personaje y la posicion en la que la recortara
Character::Character(int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h)
{
    charTexture= new Texture(ruta,Render,w,h,0,0);
    rect.x=x1;
    rect.y=y1;
    rect.w=w1;
    rect.h=h1;
    mov=0;
    die=0;
}
//suma pixeles a las coordenadas en x, controla las coordenadas en y, hace la animacion del personaje
void Character::sumPosX(int val)
{
    charTexture->sumPosX(val);
    charTexture->setPosY(getPosY()*31);
    mov++;
    if(mov%10==0)
    {
        rect.x=(rect.w+rect.x)%(3*rect.w);
    }
}
//suma pixeles a las coordenadas en y, controla las coordenadas en x, hace la animacion del personaje
void Character::sumPosY(int val)
{
    charTexture->sumPosY(val);
    charTexture->setPosX(getPosX()*24);
    mov++;
    if(mov%10==0)
    {
        rect.x=(rect.w+rect.x)%(3*rect.w);
    }
}
//obtiene en que coordenada en x del tablero esta el personaje, dependiendo de que punto superior de la imagen se pida
int Character::getPosX(int pos,int div)
{
    SDL_Rect *temp = charTexture->getSDLRect();
    int x1=temp->x +(pos*temp->w)/div;
    x1/=24;
    return x1;
}
//obtiene en que coordenada en x del tablero esta el personaje, dependiendo de que punto superior de la imagen se pida
int Character::getPosX(int pos)
{
    SDL_Rect *temp = charTexture->getSDLRect();
    int x1=temp->x +(pos*temp->w)/4;
    x1/=24;
    return x1;
}
//obtiene en que coordenada en x del tablero esta el personaje, dependiendo de que punto superior de la imagen se pida
int Character::getPosX()
{
    SDL_Rect *temp = charTexture->getSDLRect();
    int x1=temp->x;
    x1/=24;
    return x1;
}
//obtiene en que coordenada en y del tablero esta el personaje, dependiendo de que punto lateral izquierdo de la imagen se pida
int Character::getPosY(int pos,int div)
{
    SDL_Rect *temp = charTexture->getSDLRect();
    int y1=temp->y + pos*temp->h/div;
    y1/=31;
    return y1;
}
//obtiene en que coordenada en y del tablero esta el personaje, dependiendo de que punto lateral izquierdo de la imagen se pida
int Character::getPosY(int pos)
{
    SDL_Rect *temp = charTexture->getSDLRect();
    int y1=temp->y + pos*temp->h/4;
    y1/=31;
    return y1;
}
//obtiene en que coordenada en y del tablero esta el personaje, dependiendo de que punto lateral izquierdo de la imagen se pida
int Character::getPosY()
{
    SDL_Rect *temp = charTexture->getSDLRect();
    int y1=temp->y;
    y1/=31;
    return y1;
}
#endif // Character_h
