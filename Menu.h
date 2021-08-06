/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Songs.h"
#include "Game.h"
#include "Pantalla_Records.h"
#include "Instrucciones.h"
class LButtonP
{
protected:
    SDL_Point mPosition;
    Mix_Chunk * sound;
    Texture *texture;
public:
    LButtonP(SDL_Renderer * renderer);
    ~LButtonP();
    void render(SDL_Renderer * renderer);
    void setPosition(int x, int y);
    virtual bool handleEvent(SDL_Event * e)=0;
    void setDimensions(int w, int h);
    int getPositionX();
    int getPositionY();
    int getButtonWidht();
    int getButtonHeight();
    void setSound(string ruta);
};

class boton_esfera : public LButtonP
{
private:
    int cont;
    Mix_Music * musica;
public:
    boton_esfera(SDL_Renderer *renderer);
    bool handleEvent(SDL_Event * e);
};

class rodolfo_boton : public LButtonP
{
private:
    int cont;
public:
    rodolfo_boton(SDL_Renderer *renderer);
    bool handleEvent(SDL_Event * e);
};
//Constructor
LButtonP::LButtonP(SDL_Renderer * renderer)
{
    texture= new Texture("res/images/boton.png",renderer,0,0,0,0);
    mPosition.x = 0;
    mPosition.y = 0;
}
//Destructor
LButtonP::~LButtonP()
{
    texture->free();
    //Mix_FreeChunk(sound);
    //sound = NULL;
}
//Establece la posicion del boton
void LButtonP::setPosition(int x, int y)
{
    texture->setPos(x,y);
    mPosition.x = x;
    mPosition.y = y;
}
//Imprime el boton
void LButtonP::render(SDL_Renderer * renderer)
{
    texture->print(renderer);
}
//Establece las dimensiones del boton
void LButtonP::setDimensions(int w, int h)
{
    texture->setH(h);
    texture->setW(w);
}
//Regrresa la posicion en x del boton
int LButtonP::getPositionX()
{
    return mPosition.x;
}
//Regrresa la posicion en y del boton
int LButtonP::getPositionY()
{
    return mPosition.y;
}
//Regresa el ancho del boton
int LButtonP::getButtonWidht()
{
    return texture->getW();
}
//Regresa la altura del boton
int LButtonP::getButtonHeight()
{
    return texture->getH();
}
//Establece el sonido del boton
void LButtonP::setSound(string ruta)
{
    sound = Mix_LoadWAV(ruta.c_str());
}
//Constructor
boton_esfera::boton_esfera(SDL_Renderer *renderer):LButtonP(renderer){}
//Revisa si el boton fue presionado
bool boton_esfera::handleEvent(SDL_Event * e)
{
    bool s = false;
    static bool sonando = true;
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
                cont++;
                Mix_PlayChannel(-1,sound,0);
                if (cont >= 10 && sonando)
                {
                    sonando = false;
                    Mix_HaltMusic();
                    musica = Mix_LoadMUS("res/sfx/ALLIWANTFORSCREAMING.mp3");
                    Mix_PlayMusic(musica,0);
                }
                return true;
            }

        }
    }
    return s;
}
//Constructor
rodolfo_boton::rodolfo_boton(SDL_Renderer *renderer):LButtonP(renderer){}
//Revisa si el boton fue presionado
bool rodolfo_boton::handleEvent(SDL_Event * e)
{
    bool s = false;
    static bool sonando = true;
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
                cont++;
                Mix_PlayChannel(-1,sound,0);
                if (cont >= 15 && sonando)
                {
                    sonando = false;
                    Mix_FreeChunk(sound);
                    sound = Mix_LoadWAV("res/sfx/HOHOHO.wav");
                }
                return true;
            }
        }
    }
    return s;
}
enum gameState{MENU,GAME,RECORDS,INSTRUCTIONS,CHARGE,NEW};
class menu
{
private:
    gameState actual;
    Game *juego;
    Songs canc;
    Texture *background;
    Texture *Name;
    Texture *Charge;
    Texture *rodolfo;
    Texture *noel;
    Texture *esfera;
    Texture  *letters;
    Texture *letters_buttons[7];
    Texture *letters_name;
    LButton *menu_buttons[7];
    LButtonP * botones [2];
    Mix_Music * menu_music;
    Mix_Chunk * select;
    instrucciones * in;
public:
    menu(SDL_Renderer * renderer);
    void dibujar(SDL_Renderer * renderer);
    bool start(SDL_Renderer * renderer,const Uint8 *keyState,Uint32 Delay,SDL_Event e,char *nombre,int *tam,bool *read);
};
//Constructor
menu::menu(SDL_Renderer * renderer)
{
    in = new instrucciones(renderer);
    actual=MENU;
    for(int i=0;i<6;i++)
        menu_buttons[i]= new LButton(renderer);
    background= new Texture("res/images/snowman.png",renderer,1056,720);
    rodolfo = new Texture("res/images/rodolfo_menu.png",renderer,250,250,720,25);
    noel = new Texture("res/images/santa2.png",renderer,250,191,85,84);
    esfera= new Texture("res/images/esfera1.png",renderer,100,100,875,600);
    Name= new Texture("res/images/nombre.jpg",renderer,1056,720);
    Charge= new Texture("res/images/charge.jpg",renderer,1056,720);
    menu_music=canc.getMenu();
    TTF_Font * menuFont = TTF_OpenFont("res/Waving at Christmas.ttf",85);

    SDL_Color color = {0,0,0};

    letters=new Texture("NOEL   ESCAPES", color, menuFont, renderer);
    letters->setPos(222,600);

    TTF_CloseFont(menuFont);

    menuFont = NULL;
    TTF_Font * letter_menu_font = TTF_OpenFont("res/christmas.ttf",60);
    color={255,255,255};
    letters_buttons[0]=new Texture("Continue",color,letter_menu_font,renderer);
    letters_buttons[1]=new Texture("New Game",color,letter_menu_font,renderer);
    letters_buttons[2]=new Texture("Records",color,letter_menu_font,renderer);
    letters_buttons[3]=new Texture("Instructions",color,letter_menu_font,renderer);
    letters_buttons[4]=new Texture("Exit",color,letter_menu_font,renderer);
    letters_buttons[5]=new Texture("Begin",color,letter_menu_font,renderer);
    letters_buttons[0]->setPos(128,297);
    letters_buttons[1]->setPos(111,397);
    letters_buttons[2]->setPos(790,347);
    letters_buttons[3]->setPos(117,497);
    letters_buttons[4]->setPos(815,447);
    letters_buttons[5]->setPos(477,600);
    TTF_CloseFont(letter_menu_font);
    letter_menu_font = NULL;
    color={220,195,129};
    TTF_Font * select_font = TTF_OpenFont("res/santa.ttf",50);
    letters_name=new Texture("GIFT ME YOUR NAME",color,select_font,renderer);
    letters_name->setPos(100,50);
    TTF_CloseFont(select_font);
    select_font=NULL;
    for (int i = 0; i<6; i++)
        menu_buttons[i]->setDimensions(letters_buttons[i]->getW(),letters_buttons[i]->getH());
    menu_buttons[0]->setPosition(50,287);
    menu_buttons[1]->setPosition(50,387);
    menu_buttons[2]->setPosition(700,337);
    menu_buttons[3]->setPosition(50,487);
    menu_buttons[4]->setPosition(700,437);
    menu_buttons[5]->setPosition(370,590);
    for (int i = 0; i<6; i++)
        menu_buttons[i]->setSound("res/sfx/Campanas.wav");

    botones[0] = new boton_esfera(renderer);
    botones[0]->setDimensions(100,100);
    botones[0]->setPosition(875,600);
    botones[0]->setSound("res/sfx/sphere sound.wav");
    botones[1] = new rodolfo_boton(renderer);
    botones[1]->setDimensions(250,191);
    botones[1]->setPosition(85,25);
    botones[1]->setSound("res/sfx/HOHOHO.wav");
    Mix_PlayMusic(menu_music,0);
    juego=NULL;
}
//Dibuja la pantalla
void menu::dibujar(SDL_Renderer * renderer)
{
    background->print(renderer);
    rodolfo->print(renderer);
    noel->print(renderer);
    esfera->print(renderer);
    letters->print(renderer);
    for(int i=0;i<5;i++)
    {
        menu_buttons[i]->print(renderer);
        letters_buttons[i]->print(renderer);
    }
}
//Hace lo necesario dependiendo de en que estado del menu este
bool menu::start(SDL_Renderer * renderer,const Uint8 *keyState,Uint32 Delay,SDL_Event e,char *nombre,int *tam,bool *read)
{
    SDL_Rect Back;
    SDL_Color color={255,255,255};
    SDL_Surface *NickSurface = NULL;
    SDL_Texture *NickTexture = NULL;
    TTF_Font * Font = TTF_OpenFont("res/christmas.ttf",60);
    int temp;
    switch(actual)
    {
    case MENU:
        dibujar(renderer);
        if (menu_buttons[0]->handleEvent(&e))
        {
            if(juego!=NULL)
            {
                nombre[0]='\0';
                *tam=0;
                *read=true;
                actual=CHARGE;

            }
        }
        else if (menu_buttons[1]->handleEvent(&e))
        {
            *read=true;
            actual=NEW;
            nombre[0]='\0';
            *tam=0;
        }
        else if (menu_buttons[2]->handleEvent(&e))
        {
            actual = RECORDS;
        }
        else if (menu_buttons[3]->handleEvent(&e))
        {
            actual = INSTRUCTIONS;
        }
        else if (menu_buttons[4]->handleEvent(&e))
        {
            return false;
        }
        else if (botones[0]->handleEvent(&e))
        {
        }
        else if (botones[1]->handleEvent(&e))
        {
        }
        break;
    case GAME:
        temp=juego->play(keyState,renderer,Delay,e);
        if(temp!=0)
        {
           actual=MENU;
            Mix_PlayMusic(menu_music,0);
            if(temp!=3)
            {
                delete juego;
                juego=NULL;
            }
        }
        break;
    case NEW:
        Name->print(renderer);
        menu_buttons[5]->print(renderer);
        letters_buttons[5]->print(renderer);
        letters_name->print(renderer);
        Back.x = 468;
        Back.y = 270;
        Back.w = 320;
        Back.h = 60;
        SDL_SetRenderDrawColor(renderer, 0, 72, 110,200 );
        SDL_RenderFillRect(renderer, &Back);
        NickSurface = TTF_RenderText_Blended(Font,nombre, color);
        NickTexture = SDL_CreateTextureFromSurface(renderer, NickSurface);
        Back.w=10*strlen(nombre);
        SDL_RenderCopy(renderer, NickTexture, 0, &Back);
        if (menu_buttons[5]->handleEvent(&e))
        {
            string basura;
            for(int i=0;i<strlen(nombre);i++)
            {
                basura+=nombre[i];
            }
           if(juego!=NULL)
           {
                 delete juego;
           }
            juego =new Game(renderer,basura);
            actual=GAME;
            *read=false;
            temp=juego->play(keyState,renderer,Delay,e);
            if(temp!=0)
            {
               actual=MENU;
                Mix_PlayMusic(menu_music,0);
                if(temp!=3)
                {
                    delete juego;
                    juego=NULL;
                }
            }
            SDL_RenderPresent(renderer);

        }
        break;
    case CHARGE:
        Charge->print(renderer);
        menu_buttons[5]->print(renderer);
        letters_buttons[5]->print(renderer);
        letters_name->print(renderer);
        Back.x = 468;
        Back.y = 270;
        Back.w = 320;
        Back.h = 60;
        SDL_SetRenderDrawColor(renderer, 0, 72, 110,200 );
        SDL_RenderFillRect(renderer, &Back);
        NickSurface = TTF_RenderText_Blended(Font,nombre, color);
        NickTexture = SDL_CreateTextureFromSurface(renderer, NickSurface);
        Back.w=10*strlen(nombre);
        SDL_RenderCopy(renderer, NickTexture, 0, &Back);
        if (menu_buttons[5]->handleEvent(&e))
        {
            *read=false;
            string basura;
            for(int i=0;i<strlen(nombre);i++)
            {
                basura+=nombre[i];
            }
            if(basura==juego->getContrasena())
            {
              Mix_PlayMusic(canc[4],-1);
                juego->pantalla(renderer);
                temp=juego->play(keyState,renderer,Delay,e);
                actual=GAME;
                if(temp!=0)
                {
                   actual=MENU;
                    Mix_PlayMusic(menu_music,0);
                    if(temp!=3)
                    {
                        delete juego;
                        juego=NULL;
                    }
                }
                SDL_RenderPresent(renderer);
            }
            else
                actual=MENU;

        }
        break;
    case INSTRUCTIONS:

        in->start(renderer);

        actual = MENU;
        break;
    case RECORDS:
        {
            Pantalla_Records * pantalla = new Pantalla_Records(renderer);
            pantalla->start(renderer);
            delete pantalla;
        }


        actual = MENU;
        break;
    }
    TTF_CloseFont(Font);
    Font = NULL;
    return true;
}

#endif // MENU_H_INCLUDED
