/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#ifndef Songs_h
#define Songs_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
struct canciones{
    Mix_Music *cancion[10];
    Mix_Chunk *cascabel;
    Mix_Music *intro;
    Mix_Music *next;
    Mix_Music *menu;
};
class Songs{
private:
    canciones mix1;
public:
    Songs();
    //inline Mix_Music *getSong(int val){return mix1.cancion[val];}
    inline Mix_Music* operator[](int val){return mix1.cancion[val];}
    inline Mix_Music* operator()(){return mix1.cancion[0];}
    inline Mix_Chunk* getCascabel(){return mix1.cascabel;}
    inline Mix_Music *getIntro(){return mix1.intro;}
    inline Mix_Music *getNext(){return mix1.next;}
    inline Mix_Music *getMenu(){return mix1.menu;}
};
//Constructor que carga todas las canciones y sonidos
Songs::Songs()
{
    mix1.cancion[0]=Mix_LoadMUS("res/sfx/psycho.mp3");
    mix1.cancion[1]= Mix_LoadMUS("res/sfx/last.mp3");
    mix1.cancion[2]= Mix_LoadMUS("res/sfx/xmas.mp3");
    mix1.cancion[3]= Mix_LoadMUS("res/sfx/santa_baby.mp3");
    mix1.cancion[4]= Mix_LoadMUS("res/sfx/sleigh.mp3");
    mix1.cancion[5]= Mix_LoadMUS("res/sfx/white.mp3");
    mix1.cancion[6]= Mix_LoadMUS("res/sfx/believe_in_me.mp3");
    mix1.cancion[7]= Mix_LoadMUS("res/sfx/backToTown.mp3");
    mix1.cancion[8]= Mix_LoadMUS("res/sfx/brokenDreams.mp3");
    mix1.cascabel=Mix_LoadWAV("res/sfx/cascabel.wav");
    mix1.intro=Mix_LoadMUS("res/sfx/intro.mp3");
    mix1.next=Mix_LoadMUS("res/sfx/next.mp3");
    mix1.menu=Mix_LoadMUS("res/sfx/Last christmas.mp3");
}
#endif // Songs_h

