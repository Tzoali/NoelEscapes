/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#ifndef Texture_h
#define Texture_h
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
using namespace std;
class Texture{
private:
    SDL_Texture *Tex;
    SDL_Rect Quads;
public:
    Texture(string,SDL_Renderer*,int,int,int,int);
    Texture(string,SDL_Renderer*,int,int);
    Texture(string textureText, SDL_Color textColor, TTF_Font * font, SDL_Renderer * renderer);
    ~Texture();
    inline SDL_Texture* getSDLTexture(){return Tex;}
    inline SDL_Rect* getSDLRect(){return &Quads;}
    void setPos(int x,int y);
    void sumPosX(int val);
    void sumPosY(int val);
    void setPosX(int x);
    void setPosY(int y);
    inline int getW(){return Quads.w;}
    inline int getH(){return Quads.h;}
    inline void setH(int h){Quads.h=h;}
    inline void setW(int w){Quads.w=w;}
    void print(SDL_Renderer *Render,SDL_Rect*);
    void print(SDL_Renderer *Render);
    void LoadTexture(string filePath, SDL_Renderer *renderTarget);
    void free();
};
//Constructor que guarda la imagen que se dé junto con su tamaño y posicion
Texture::Texture(string ruta,SDL_Renderer *Render,int w,int h)
{
    int Width=0,Height=0;
    LoadTexture(ruta, Render);
    SDL_QueryTexture(Tex, 0, 0, &Width, &Height);
    this->Quads.x = 0;
    this->Quads.y = 0;
    this->Quads.w = w;
    this->Quads.h = h;
}
//Constructor que guarda la imagen que se dé junto con su tamaño y posicion
Texture::Texture(string ruta,SDL_Renderer *Render,int w,int h,int x,int y)
{
    int Width=0,Height=0;
    LoadTexture(ruta, Render);
    SDL_QueryTexture(Tex, 0, 0, &Width, &Height);
    this->Quads.x = x;
    this->Quads.y = y;
    this->Quads.w = w;
    this->Quads.h = h;
}
//Destructor
Texture::~Texture()
{
    SDL_DestroyTexture(Tex);
}
//establece la posicion de la imagen
void Texture::setPos(int x,int y)
{
    Quads.x=x;
    Quads.y=y;
}
//imprime la imagen recortandola en las posiciones que se indiquen
void Texture::print(SDL_Renderer *Render,SDL_Rect *rect)
{
    SDL_RenderCopy(Render,Tex,rect,&Quads);
}
//imprime la imagen sin recortar
void Texture::print(SDL_Renderer *Render)
{
    SDL_RenderCopy(Render,Tex,NULL,&Quads);
}
//suma pixeles a la posicion en x de la imagen
void Texture::sumPosX(int val)
{
    Quads.x+=val;
}
//suma pixeles a la posicion en y de la imagen
void Texture::sumPosY(int val)
{
    Quads.y+=val;
}
//establece la posicion en x de la imagen
void Texture::setPosX(int x)
{
    Quads.x=x;
}
//establece la posicion en y de la imagen
void Texture::setPosY(int y)
{
    Quads.y=y;
}
//Convierte una frase en una textura
Texture::Texture(string textureText, SDL_Color textColor, TTF_Font * font, SDL_Renderer * renderer)
{
    SDL_Surface * textSurface = TTF_RenderText_Solid(font,textureText.c_str(),textColor);
    if (textSurface == NULL)
        cout<<endl<<"No se pudo renderizar el texto. TTF_ERROR: "<<TTF_GetError();
    else
    {
        Tex = SDL_CreateTextureFromSurface(renderer,textSurface);
        if (Tex == NULL)
            cout<<endl<<"No se pudo crear la textura a partir de las letras. SDL_ERROR: "<<SDL_GetError();
        else
        {
            Quads.w = textSurface->w;
            Quads.h = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
}
//Libera la textura
void Texture::free()
{
    if (Tex != NULL)
    {
        SDL_DestroyTexture(Tex);
        Tex = NULL;
        Quads.w = 0;
        Quads.h = 0;
    }
}
//Carga la textura
void Texture:: LoadTexture(string filePath, SDL_Renderer *renderTarget)
{
    SDL_Surface *surface = IMG_Load(filePath.c_str());
    if(surface==NULL)
        cout<<"Error1"<<endl;
    else
    {
        SDL_SetColorKey(surface,SDL_TRUE,SDL_MapRGB(surface->format,237,28,36));
        Tex = SDL_CreateTextureFromSurface(renderTarget,surface);
        if(Tex == NULL)
            cout<<"Error"<<endl;
    }
    SDL_FreeSurface(surface);
}
#endif // Texture_h
