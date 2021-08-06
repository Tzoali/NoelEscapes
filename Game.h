/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#ifndef Game_h
#define Game_h
#include <iostream>
#include <string>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <algorithm>
#include <queue>
#include <fstream>
#include "Santa.h"
#include "Songs.h"
#include "Reno.h"
#include "Records.h"
#include "Premio.h"
class LButton
{
private:
    SDL_Point mPosition;
    Texture *texture;
    Mix_Chunk * sound;
public:
    LButton(SDL_Renderer * renderer);
    ~LButton();
    void setPosition(int x, int y);
    bool handleEvent(SDL_Event * e);
    void setDimensions(int w, int h);
    void setDimensions(int w, int h,int small);
    int getPositionX();
    void print(SDL_Renderer *renderer);
    int getPositionY();
    int getButtonWidht();
    int getButtonHeight();
    void setSound(string ruta);
};
//Constructor del boton
LButton::LButton(SDL_Renderer * renderer)
{
    texture = new Texture("res/images/boton.png",renderer,0,0,0,0);
    mPosition.x=0;
    mPosition.y=0;
}
//destructor del boton
LButton::~LButton()
{
    texture->free();
    //Mix_FreeChunk(sound);
    //sound = NULL;
}
//Imprime el boton
void LButton::print(SDL_Renderer *renderer)
{
    texture->print(renderer);
}
//Establece la posicion del boton
void LButton::setPosition(int x, int y)
{
    texture->setPos(x,y);
    mPosition.x=x;
    mPosition.y=y;
}
//Revisa si el boton fue presionado e indica que hace
bool LButton::handleEvent(SDL_Event * e)
{
    bool s = false;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState(&x,&y);

        bool inside = true;

        if (x < mPosition.x)
            inside = false;
        if (x > mPosition.x + texture->getW())
            inside = false;
        if (y < mPosition.y)
            inside = false;
        if (y > mPosition.y + texture->getH())
            inside = false;

        if (inside)
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                Mix_PlayChannel(-1,sound,0);
                return true;
            }

        }
    }
    return s;
}
//Establece el tamaño del boton
void LButton::setDimensions(int w, int h)
{
    texture->setH(h+20);
    texture->setW(320);
}
//Establece el tamaño del boton pequeño
void LButton::setDimensions(int w, int h,int small)
{
    texture->setH(h+20);
    texture->setW(240);
}
//Regresa la posicion en x del boton
int LButton::getPositionX()
{
    return mPosition.x;
}
//Regresa la posicion en y del boton
int LButton::getPositionY()
{
    return mPosition.y;
}
//Regresa el ancho del boton
int LButton::getButtonWidht()
{
    return texture->getW();
}
//Regresa la altura del boton
int LButton::getButtonHeight()
{
    return texture->getH();
}
//Establece el sonido del boton
void LButton::setSound(string ruta)
{
    sound = Mix_LoadWAV(ruta.c_str());
}
struct game_assets
{
    Texture *Intro;
    Texture *Intro2;
    Texture *Sig;
    Texture *Sig2;
    Texture *Fondo;
    Texture *Fondo2;
    Texture *Arbol;
    Texture *House;
    Texture *Fence;
    Texture *Fence2;
    Texture *Floor;
    Texture *Bush;
    Texture *Esfera;
    Texture *Vidas;
    Texture *Candy;
    Texture *Campana;
    Texture *ArbolNav;
    Texture *Next;
    Texture *Win;
};
class Game{
private:
    bool ban;
    bool ban1;
    bool ban2;
    bool ban3;
    bool ban4;
    bool ban5;
    Songs sonido;
    LButton *Button;
    LButton *SkipButton;
    Texture *Letters;
    Texture *SkipLetters;
    Premio *premios[4];
    int contSong;
    char tablero[210][430];
    int tablero2[210][430];
    char nombre[30];
    game_assets Assets;
    game_assets AssetsPsycho;
    game_assets *act;
    int puntuacion;
    int santaDots;
    const Uint8 *keyState;
    Santa *noel;
    Reno *rodolfos[10];
    string contrasena;
    void LoadAllGameAssets(SDL_Renderer *Render);
    int nivel;
    int vidas;
    int psycho;
    Uint32 ini;
    Uint32 iniIntro;
    Uint32 iniSig;
    void muerte();
    Records * r;
public:
    Game(SDL_Renderer *Render,string contrasena);
    ~Game();
    void nextLevel();
    int play(const Uint8 *keyState,SDL_Renderer *Render,Uint32 Delay,SDL_Event e);
    void pantalla(SDL_Renderer *Render);
    inline int getPuntuacion(){return puntuacion;}
    inline string getContrasena(){return contrasena;}
};
//Destructor del juego
Game::~Game()
{
    delete r;
}
//constructor que inicializa los tableros, las imagenes, los sonidos, la puntuacion, los personajes, la contraseña, el nivel y las vidas
Game::Game(SDL_Renderer *Render,string contrasena)
{
    r = new Records;
    strcpy(nombre,contrasena.c_str());
    ban=false;
    ban1=false;
    ban2=false;
    ban3=true;
    ban4=false;
    ban5=false;
    LoadAllGameAssets(Render);
    act=&Assets;
    strcpy(tablero[0], "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    strcpy(tablero[1], "XXC    |    |    |    |    |    |    |    |CXX");
    strcpy(tablero[2], "XX XHHX XXXX XHHX XXXX XHHX XXXX XHHX XXXX BXX");
    strcpy(tablero[3], "XX XXXX XttX XXXX XttX XXXX XttX XXXX XttX BXX");
    strcpy(tablero[4], "XX XHHX XFFX XHHX XFFX XHHX XFFX XHHX XFFX BXX");
    strcpy(tablero[5], "XX   | | |  |  | |    ||   |   |||   | |  | XX");
    strcpy(tablero[6], "XXXXX B X BBB X X XXXXX XHHHHHH X BB BB XXXXXX");
    strcpy(tablero[7], "XtttX B XX  B X X B   X X      |X| B  B XttttX");
    strcpy(tablero[8], "XXXXX B X X  |X X B B X XXXXXXX X BBB B XXXXXX");
    strcpy(tablero[9], "ttttt| |X BXB X X BCB X XHHHHHX X|  B B|tttttt");
    strcpy(tablero[10],"XXXXX B X|  X X X BBB X XXXXXXX X BBB B XXXXXX");
    strcpy(tablero[11],"XtttX B X B  XX X     X X      |X     B XttttX");
    strcpy(tablero[12],"XXXXX B X BBB X XXXXXXX XHHHHHH XXXXX B XXXXXX");
    strcpy(tablero[13],"XX   | |||    ||    |  |  |    ||    |||    XX");
    strcpy(tablero[14],"XX XXXXX XXXXX XXXXX XXXXX XXXXX XXXXX XXXX XX");
    strcpy(tablero[15],"XX X    |X    |X    |XtttX XtttX X    |X   |XX");
    strcpy(tablero[16],"XX XXXXX XXXXX X BBB XXXXX XXXXX XXXXX XXXX XX");
    strcpy(tablero[17],"XX X    |    X X    |X C X X   B X    |   X XX");
    strcpy(tablero[18],"XX XXXXX XXXXX XXXXX X B X X B B XXXXX XXXX XX");
    strcpy(tablero[19],"XX   C  |     |     | | | | | | |  C  |     XX");
    strcpy(tablero[20],"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<50;j++)
        {
            if(tablero[i][j]==' ')
                tablero2[i][j]=0;
            else if(tablero[i][j]=='t')
            {
                tablero[i][j]=' ';
                tablero2[i][j]=2;
            }
            else if(tablero[i][j]=='C')
            {
                tablero[i][j]=' ';
                tablero2[i][j]=1;
            }
            else if(tablero[i][j]=='|')
                tablero2[i][j]=0;
        }
    }
    noel = new Santa(39,56,0,0,"res/images/santa_sprite.png",Render,24,31,528,403);
    rodolfos[0]= new Reno(0,192,93,48,56,0,0,"res/images/reno1_sprite.png",Render,24,31,192,93);
    rodolfos[1]= new Reno(1,432,93,48,56,0,0,"res/images/reno2_sprite.png",Render,24,31,432,93);
    rodolfos[2]= new Reno(2,696,93,48,56,0,0,"res/images/reno3_sprite.png",Render,24,31,696,93);
    rodolfos[3]= new Reno(3,936,93,48,56,0,0,"res/images/reno4_sprite.png",Render,24,31,936,93);
    rodolfos[4]= new Reno(0,216,93,48,56,0,0,"res/images/reno1_sprite.png",Render,24,31,216,93);
    rodolfos[5]= new Reno(1,456,93,48,56,0,0,"res/images/reno2_sprite.png",Render,24,31,456,93);
    rodolfos[6]= new Reno(2,672,93,48,56,0,0,"res/images/reno3_sprite.png",Render,24,31,672,93);
    rodolfos[7]= new Reno(3,912,93,48,56,0,0,"res/images/reno4_sprite.png",Render,24,31,912,93);
    puntuacion=0;
    this->contrasena=contrasena;
    nivel=1;
    vidas=5;
    santaDots=397;
    psycho=0;
    contSong=1;
    SDL_Color color = {255,255,255};
    TTF_Font * letter_menu_font = TTF_OpenFont("res/christmas.ttf",40);
    Letters= new Texture("Main Menu",color,letter_menu_font,Render);
    Letters->setPos(800,668);
    SkipLetters= new Texture("Skip",color,letter_menu_font,Render);
    SkipLetters->setPos(148,668);
    TTF_CloseFont(letter_menu_font);
    letter_menu_font = NULL;
    Button=new LButton(Render);
    Button->setDimensions(Letters->getW(),Letters->getH(),1);
    Button->setPosition(760,658);
    Button->setSound("res/sfx/Campanas.wav");
    SkipButton=new LButton(Render);
    SkipButton->setDimensions(SkipLetters->getW(),SkipLetters->getH(),1);
    SkipButton->setPosition(60,658);
    SkipButton->setSound("res/sfx/Campanas.wav");
    premios[0]=new Regalo("res/sfx/regalo.wav",1000,1500,"res/images/regalo.png",Render,18,18,0,0);
    premios[1]=new Baston(2500,3000,"res/images/baston.png",Render,11,18,0,0);
    premios[2]=new Dulce("res/sfx/dulce.wav",6000,6500,"res/images/dulce.png",Render,18,18,0,0);
    premios[3]=new Helado(8000,8500,"res/images/helado.png",Render,9,18,0,0);

}
//imprime todo lo que hay que imprimir y hace que santa se mueva
int Game::play(const Uint8 *keyState,SDL_Renderer *Render,Uint32 Delay,SDL_Event e)
{
    if(!ban)
    {
        if(!ban1)
        {
            ban1=true;
            iniIntro=Delay;
            act->Intro->print(Render);
            Mix_PlayMusic(sonido.getIntro(),0);
            SDL_RenderPresent(Render);
        }
      if(!ban2 && Delay-iniIntro>=15300)
      {
        ban2=true;
        act->Intro2->print(Render);
        SDL_RenderPresent(Render);

      }
      if(Delay-iniIntro>=27800)
        {
            ban=true;
            Mix_PlayMusic(sonido[1], -1);
        }
      else
      {
        SkipButton->print(Render);
        SkipLetters->print(Render);
        if(SkipButton->handleEvent(&e))
        {
            ban=true;
            Mix_PlayMusic(sonido[1], -1);
        }
        return 0;
      }
    }
    if(!ban3)
    {
        if(!ban4)
        {
            ban4=true;
            iniSig=Delay;
            Mix_ResumeMusic();
            Mix_PlayMusic(sonido.getNext(),0);
            act->Sig->print(Render);
            SDL_RenderPresent(Render);
        }
      if(!ban5 && Delay-iniSig>=15300)
      {
        ban5=true;
        act->Sig2->print(Render);
        SDL_RenderPresent(Render);

      }
      if(Delay-iniSig>=27800)
        {
            ban3=true;
            Mix_PlayMusic(sonido[5], -1);
        }
      else
      {
        SkipButton->print(Render);
        SkipLetters->print(Render);
        if(SkipButton->handleEvent(&e))
        {
            ban3=true;
            Mix_PlayMusic(sonido[5], -1);
        }
        return 0;
      }
    }
    int temp;
    temp=noel->movimiento(keyState,tablero,tablero2);
    if(temp>0)
    {
        if(temp<=2)
            santaDots--;
        if(temp==2)
        {
            psycho=1;
            Mix_PlayMusic(sonido(), 0);
            act=&AssetsPsycho;
            ini=Delay;
        }
        else if(temp>2)
        {
            puntuacion+=premios[temp-3]->points();
            premios[temp-3]->setBan(true);
        }
        if(!santaDots)
        {
            if(nivel==1)
            {
                act->Next->print(Render);
                SDL_RenderPresent(Render);
                psycho=0;
                act=&Assets;
                contSong++;
                if(contSong>4*nivel)
                    contSong=1+(nivel-1)*4;
                Mix_PausedMusic();
                nextLevel();
                ban3=false;
            }
            else
            {
                act->Win->print(Render);
                SDL_RenderPresent(Render);
                SDL_Delay(3000);
                return 2;
            }
        }
        Mix_PlayChannel(0,sonido.getCascabel(),0);
        puntuacion+=10;
        /// Records
        r->actualizar(nombre,puntuacion);
        pantalla(Render);
    }
    if(psycho && Delay-ini>=12000)
    {
        psycho=0;
        act=&Assets;
        contSong++;
        if(contSong>4*nivel)
            contSong=1+(nivel-1)*4;
        Mix_PlayMusic(sonido[contSong], 0);
    }
    for(int i=0;i<8;i++)
    {
        if(rodolfos[i]->movimiento(tablero,*noel,psycho,Delay))
        {
            if(!psycho)
            {
                vidas--;
                pantalla(Render);
                muerte();
                if(vidas<0)
                    return 1;
                break;
            }
            else
            {
                puntuacion+=20;
                r->actualizar(nombre,puntuacion);
                pantalla(Render);
                rodolfos[i]->setRect(DOWN);
                rodolfos[i]->muerto(Delay);
            }
        }
    }
    for(int i=0;i<21;i++)
    {
        for(int j=1;j<45;j++)
        {
            act->Floor->setPos((j-1)*24,i*31);
            act->Floor->print(Render);
            if(tablero[i][j]=='X')
            {
                act->Arbol->setPos((j-1)*24,i*31);
                act->Arbol->print(Render);
            }
            else if(tablero[i][j]=='H')
            {
                act->House->setPos((j-1)*24,i*31-9);
                act->House->print(Render);
            }
            else if(tablero[i][j]=='F')
            {
                act->Fence->setPos((j-1)*24,i*31);
                act->Fence->print(Render);
            }
            else if(tablero[i][j]=='f')
            {
                act->Fence2->setPos((j-1)*24,i*31);
                act->Fence2->print(Render);
            }
            else if(tablero[i][j]=='B')
            {
                act->Bush->setPos((j-1)*24,i*31);
                act->Bush->print(Render);
            }
            else if((tablero[i][j]==' ' || tablero[i][j]=='|') && tablero2[i][j]==false)
            {
                act->Esfera->setPos((j-1)*24+8,i*31+11);
                act->Esfera->print(Render);
            }
            else if((tablero[i][j]==' ' || tablero[i][j]=='|') && tablero2[i][j]==1)
            {
                act->Candy->setPos((j-1)*24+3,i*31+6);
                act->Candy->print(Render);
            }
            else if((tablero[i][j]==' ' || tablero[i][j]=='|') && tablero2[i][j]>2)
            {
                premios[tablero2[i][j]-3]->setPos((j-1)*24+8,i*31+11);
                premios[tablero2[i][j]-3]->print(Render);
            }
        }

    }
    noel->print(Render);
    for(int i=0;i<8;i++)
        rodolfos[i]->print(Render);
    for(int i=0;i<4;i++)
    {
        if(!premios[i]->getAct() && !premios[i]->getDead())
        {
            if(puntuacion>=premios[i]->getMin() && puntuacion<=premios[i]->getMax())
            {
                premios[i]->setAct(true);
                if(nivel==1)
                {
                    tablero2[13][23]=i+3;
                }
                else
                {
                    tablero2[17][22]=i+3;
                }
            }
        }
        else if(premios[i]->getAct())
        {
            if(!premios[i]->getBan())
            {
                if(!(puntuacion>=premios[i]->getMin() && puntuacion<=premios[i]->getMax()))
                {
                    premios[i]->setAct(false);
                    if(nivel==1)
                    {
                        tablero2[13][23]=2;
                    }
                    else
                    {
                        tablero2[17][22]=2;
                    }

                }
            }
        }
    }
    act->Campana->setPos(0,600);
    act->Campana->print(Render);
    if(Button->handleEvent(&e))
    {
        return 3;
    }
    act->ArbolNav->setPos(963,580);
    act->ArbolNav->print(Render);
    return 0;
}
//Carga todas las imagenes
void Game::LoadAllGameAssets(SDL_Renderer *Render)
{
    Assets.Intro= new Texture("res/images/intro.png ",Render,1060,720);
    Assets.Intro2= new Texture("res/images/intro2.png ",Render,1060,720);
    Assets.Sig= new Texture("res/images/sig.png ",Render,1060,720);
    Assets.Sig2= new Texture("res/images/sig2.png ",Render,1060,720);
    Assets.Fondo= new Texture("res/images/fondo1.jpg",Render,1060,720);
    Assets.Fondo2= new Texture("res/images/fondo2.jpg",Render,1060,360,0,360 );
    Assets.Arbol= new Texture("res/images/arbol.png ",Render,24,31);
    Assets.House= new Texture("res/images/house.png ",Render,24,40);
    Assets.Fence= new Texture("res/images/fence.png ",Render,24,31);
    Assets.Fence2= new Texture("res/images/fence2.png ",Render,24,31);
    Assets.Floor= new Texture("res/images/floor.jpg",Render,31,31);
    Assets.Bush= new Texture("res/images/bush.png",Render,24,31);
    Assets.Esfera= new Texture("res/images/esfera1.png",Render,8,8);
    Assets.Vidas = new Texture("res/images/vidas.png",Render,36,46);
    Assets.Candy = new Texture("res/images/candy.png",Render,18,18);
    Assets.Campana= new Texture("res/images/campana.png",Render,223,120);
    Assets.ArbolNav = new Texture("res/images/arbolnav.png",Render,152,180);
    Assets.Next = new Texture("res/images/next.png",Render,895,264,82,193);
    Assets.Win = new Texture("res/images/win.png",Render,877,415,92,118);

    AssetsPsycho.Intro= new Texture("res/images/intro.png ",Render,1060,720);
    AssetsPsycho.Intro2= new Texture("res/images/intro2.png ",Render,1060,720);
    AssetsPsycho.Sig= new Texture("res/images/sig.png ",Render,1060,720);
    AssetsPsycho.Sig2= new Texture("res/images/sig2.png ",Render,1060,720);
    AssetsPsycho.Fondo= new Texture("res/images/fondo1.jpg",Render,1060,720);
    AssetsPsycho.Fondo2= new Texture("res/images/fondo2.jpg",Render,1060,360,0,360 );
    AssetsPsycho.Arbol= new Texture("res/images/arbol2.png ",Render,24,31);
    AssetsPsycho.House= new Texture("res/images/house.png ",Render,24,40);
    AssetsPsycho.Fence= new Texture("res/images/fence.png ",Render,24,31);
    AssetsPsycho.Fence2= new Texture("res/images/fence2.png ",Render,24,31);
    AssetsPsycho.Floor= new Texture("res/images/floor2.png",Render,31,31);
    AssetsPsycho.Bush= new Texture("res/images/bush.png",Render,24,31);
    AssetsPsycho.Esfera= new Texture("res/images/esfera1.png",Render,8,8);
    AssetsPsycho.Vidas = new Texture("res/images/vidas.png",Render,36,46);
    AssetsPsycho.Candy = new Texture("res/images/candy.png",Render,18,18);
    AssetsPsycho.Campana= new Texture("res/images/campana.png",Render,223,120);
    AssetsPsycho.ArbolNav = new Texture("res/images/arbolnav.png",Render,135,160);
    AssetsPsycho.Next = new Texture("res/images/next.png",Render,895,264,82,193);
    AssetsPsycho.Win = new Texture("res/images/win.png",Render,877,415,92,118);
}
//Funcion que carga lo necesario cuando santa muere
void Game::muerte()
{
    for(int i=0;i<4;i++)
    {
        if(premios[i]->getAct())
        {
            if(!premios[i]->getBan())
            {
                if((puntuacion>=premios[i]->getMin() && puntuacion<=premios[i]->getMax()))
                {
                    *premios[i]=true;
                    premios[i]->setAct(false);
                    if(nivel==1)
                    {
                        tablero2[13][23]=2;
                    }
                    else
                    {
                        tablero2[17][22]=2;
                    }

                }
            }
        }
    }
    SDL_Delay(1000);
    for(int i=0;i<8;i++)
    {
        rodolfos[i]->corral();
        *rodolfos[i]=DOWN;
    }
    if(nivel==1)
    {
      noel->setPos(528,403);
      (*noel)=DOWN;
    }
    else
    {
        noel->setPos(504,527);
        *noel=UP;
    }
    noel->setRect(DOWN);
    if(psycho==1)
    {
        psycho=0;
        act=&Assets;
        contSong++;
        if(contSong>4*nivel)
            contSong=1+(nivel-1)*4;
        Mix_PlayMusic(sonido[contSong], 0);
    }
}
//Imprime las imagenes que aparecen en la parte inferior del juego
void Game::pantalla(SDL_Renderer *Render)
{
    act->Fondo2->print(Render);
    TTF_Font *Font2 = TTF_OpenFont("res/snow.ttf", 46);
    SDL_Color TextColor = {0xFF, 0xFF, 0xFF};
    SDL_Surface *TextSurface = TTF_RenderText_Blended(Font2, "SCORE ", TextColor);
    SDL_Texture *TextTexture = SDL_CreateTextureFromSurface(Render, TextSurface);
    SDL_Rect Rect = {140, 663, 150 ,46};
    SDL_RenderCopy(Render, TextTexture, 0, &Rect);
    SDL_FreeSurface(TextSurface);
    SDL_DestroyTexture(TextTexture);

    char temp[1000];
    itoa(puntuacion,temp,10);
    SDL_Surface *TextSurface2 = TTF_RenderText_Blended(Font2, temp, TextColor);
    SDL_Texture *TextTexture2 = SDL_CreateTextureFromSurface(Render, TextSurface2);
    SDL_Rect Rect2 = {290, 663, strlen(temp)*25 ,46};
    SDL_RenderCopy(Render, TextTexture2, 0, &Rect2);
    SDL_FreeSurface(TextSurface2);
    SDL_DestroyTexture(TextTexture2);
    for(int i=0;i<vidas;i++)
    {
        act->Vidas->setPos(430+30*i,663);
        act->Vidas->print(Render);
    }
    for(int i=0;i<4;i++)
    {
        if(premios[i]->getBan())
        {
            premios[i]->setPos(630+i*30,682);
            premios[i]->print(Render);
        }
    }
    Button->print(Render);
    Letters->print(Render);
}
//Carga todo lo necesario para el segundo nivel
void Game::nextLevel()
{
    SDL_Delay(1000);
    strcpy(tablero[0], "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    strcpy(tablero[1], "XXtf    H B|    |  |  |  |  |    |B H    ftBXX");
    strcpy(tablero[2], "XXtf XX H X HXXX BB HBCBH BB XXXH X H XX ftBXX");
    strcpy(tablero[3], "XXXXXXX H X|  CX BBH|B B|HBB XC  |X H XXXXXXXX");
    strcpy(tablero[4], "XXCXXXX H BXXXXX| H||X X||H |XXXXXB H XXXXCXXX");
    strcpy(tablero[5], "XX|  | | |     ||H||BX XB||H |     | | |  |BXX");
    strcpy(tablero[6], "XXXXX B XBBBBBB HB|XXX XXX|BH BBBBBBX B XXXXXX");
    strcpy(tablero[7], "XtttX B|       ||     |     ||       |B XttttX");
    strcpy(tablero[8], "XXXXX B XBBBBBHH XXXXX XXXXX HHBBBBBX B XXXXXX");
    strcpy(tablero[9], "ttttt| |     HB XXXXXX XXXBXX BH     | |tttttt");
    strcpy(tablero[10],"XXXXX B HXHXH||       |       ||HXHXH B XXXXXX");
    strcpy(tablero[11],"XtttX B|    ||XXXXXXXXXXXXXXBXX||    |B XttttX");
    strcpy(tablero[12],"XXXXX B HXXH XXBXXXXXXBXXXXXXXXB HXXH B XXXXXX");
    strcpy(tablero[13],"XX|  ||| |  |     | |HHH| |     |  | |||  |BXX");
    strcpy(tablero[14],"XX XXXXXX XXXXXXXX B HHH B XXXXXXXX XXXXXX BXX");
    strcpy(tablero[15],"XX BBBBBB|        |B HHH B|        |BBBBBB BXX");
    strcpy(tablero[16],"XX|    |B XXXXXXXX BHHHHHB XXXXXXXX B|    |BXX");
    strcpy(tablero[17],"XXXXXXX B|        |   |   |        |B XXXXXXXX");
    strcpy(tablero[18],"XXtf XX B XXXXXXXXXXXX XXXXXXXXXXXX B XX ftBXX");
    strcpy(tablero[19],"XXtf   | |            |            |     ftBXX");
    strcpy(tablero[20],"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    for(int i=0;i<24;i++)
    {
        for(int j=0;j<50;j++)
        {
            if(tablero[i][j]==' ')
                tablero2[i][j]=0;
            else if(tablero[i][j]=='t')
            {
                tablero[i][j]=' ';
                tablero2[i][j]=2;
            }
            else if(tablero[i][j]=='C')
            {
                tablero[i][j]=' ';
                tablero2[i][j]=1;
            }
            else if(tablero[i][j]=='|')
                tablero2[i][j]=0;
        }
    }
    noel->setPos(504,527);
    *noel=UP;
    noel->setRect(DOWN);
    rodolfos[0]->setCorral(24,31);
    rodolfos[0]->corral();
    *rodolfos[0]=UP;
    rodolfos[0]->setRect(RIGHT);
    rodolfos[1]->setCorral(984,31);
    rodolfos[1]->corral();
    *rodolfos[1]=UP;
    rodolfos[1]->setRect(LEFT);
    rodolfos[2]->setCorral(24,558);
    rodolfos[2]->corral();
    *rodolfos[2]=UP;
    rodolfos[2]->setRect(RIGHT);
    rodolfos[3]->setCorral(984,558);
    rodolfos[3]->corral();
    *rodolfos[3]=UP;
    rodolfos[3]->setRect(LEFT);
    rodolfos[4]->setCorral(24,62);
    rodolfos[4]->corral();
    *rodolfos[4]=DOWN;
    rodolfos[4]->setRect(RIGHT);
    rodolfos[5]->setCorral(984,62);
    rodolfos[5]->corral();
    *rodolfos[5]=DOWN;
    rodolfos[5]->setRect(LEFT);
    rodolfos[6]->setCorral(24,589);
    rodolfos[6]->corral();
    *rodolfos[6]=DOWN;
    rodolfos[6]->setRect(RIGHT);
    rodolfos[7]->setCorral(984,589);
    rodolfos[7]->corral();
    *rodolfos[7]=DOWN;
    rodolfos[7]->setRect(LEFT);

    nivel++;
    santaDots=385;
    contSong=5;
}
#endif // Game_h
