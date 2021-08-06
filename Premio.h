#ifndef Premio_h
#define Premio_h
class Premio{
protected:
    Texture *premTexture;
    int puntMin;
    int puntMax;
    bool ban;
    bool act;
    bool dead;
public:
    Premio(int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y);
    inline void print(SDL_Renderer *Render){premTexture->print(Render);}
    virtual int points()=0;
    inline void setPos(int x,int y){premTexture->setPos(x,y);}
    inline int getMin(){return puntMin;}
    inline int getMax(){return puntMax;}
    inline void setBan(bool b){ban=b;}
    inline bool getBan(){return ban;}
    inline bool getAct(){return act;}
    inline void setAct(bool a){act=a;}
    inline int getW(){return premTexture->getW();}
    inline int getH(){return premTexture->getH();}
    inline bool getDead(){return dead;}
    inline void operator=(bool d){dead=d;}
};
//Constructor
Premio::Premio(int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y)
{
    premTexture= new Texture(ruta,Render,w,h,x,y);
    this->puntMin=puntMin;
    this->puntMax=puntMax;
    ban=false;
    act=false;
    dead=false;
}
class Regalo:public Premio{
private:
    Mix_Chunk* sound;
public:
    Regalo(char* sruta,int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y);
    int points();
};
//Constructor
Regalo::Regalo(char* sruta,int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y):Premio(puntMin,puntMax,ruta,Render,w,h,x,y)
{
    sound=Mix_LoadWAV(sruta);
}
//Regresa los puntos que le corresponden y reproduce un sonido
int Regalo::points()
{
    Mix_PlayChannel(1,sound,0);
    return 25;
}
class Baston:public Premio{
private:
public:
    Baston(int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y);
    int points();
};
//Constructor
Baston::Baston(int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y):Premio(puntMin,puntMax,ruta,Render,w,h,x,y){}
//Regresa los puntos que le corresponden
int Baston::points()
{
    return 30;
}
class Dulce:public Premio{
private:
    Mix_Chunk* sound;
public:
    Dulce(char* sruta,int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y);
    int points();
};
//Constructor
Dulce::Dulce(char* sruta,int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y):Premio(puntMin,puntMax,ruta,Render,w,h,x,y)
{
    sound=Mix_LoadWAV(sruta);
}
//Regresa los puntos que le corresponden y reproduce un sonido
int Dulce::points()
{
    Mix_PlayChannel(1,sound,0);
    return 35;
}
class Helado:public Premio{
private:
public:
    Helado(int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y);
    int points();
};
//Constructor
Helado::Helado(int puntMin,int puntMax,string ruta,SDL_Renderer *Render,int w,int h,int x,int y):Premio(puntMin,puntMax,ruta,Render,w,h,x,y){}
//Regresa los puntos que le corresponden
int Helado::points()
{
    return 40;
}
#endif // Premio_h
