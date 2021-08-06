/* Omar Arturo Ruiz Bernal
   Daniel Tzoali Arroyo Valdivia*/

#ifndef Santa_h
#define Santa_h
#include "Character.h"
#include "Reno.h"
class Santa:public Character{
    friend state getPosSRX(Reno rudolph,Santa noel);
    friend state getPosSRY(Reno rudolph,Santa noel);
    friend bool touch(Reno rudolph,Santa noel);
private:
public:
    Santa(int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h,int,int);
    Santa(int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h);
    inline void operator=(state d){dir=d;}
    int movimiento(const Uint8 * keyState,char tablero[210][430],int tablero2[210][430]);
};
//Constructor de santa
Santa::Santa(int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h,int x,int y):Character(w1,h1,x1,y1,ruta,Render,w,h,x,y)
{
    dir=NOTHING;
}
//Constructor de santa
Santa::Santa(int w1,int h1,int x1,int y1,string ruta,SDL_Renderer *Render,int w,int h):Character(w1,h1,x1,y1,ruta,Render,w,h)
{
    dir=NOTHING;
}
//Movimiento de santa y tambien ve si agarro algun punto, poder o premio
int Santa::movimiento(const Uint8 * keyState,char tablero[210][430],int tablero2[210][430])
{
        if(keyState[SDL_SCANCODE_D])
        {
            if((tablero[getPosY(1,4)][getPosX()+2]==' ' || tablero[getPosY(1,4)][getPosX()+2]=='|') && (tablero[getPosY(3,4)][getPosX()+2]==' ' || tablero[getPosY(3,4)][getPosX()+2]=='|'))
            {
                dir=RIGHT;
                setRect(RIGHT);
                charTexture->setPosY(31*getPosY(1));
            }
        }
        else if(keyState[SDL_SCANCODE_A])
        {
            if((tablero[getPosY(1)][getPosX(0)]==' ' || tablero[getPosY(1)][getPosX(0)]=='|') && (tablero[getPosY(3)][getPosX(0)]==' ' || tablero[getPosY(3)][getPosX(0)]=='|'))
            {
                dir=LEFT;
                setRect(LEFT);
                charTexture->setPosY(31*getPosY(1));
            }
        }
        else if(keyState[SDL_SCANCODE_S])
        {
            if((tablero[getPosY(0)+1][getPosX(1)+1]==' ' || tablero[getPosY(0)+1][getPosX(1)+1]=='|') && (tablero[getPosY(0)+1][getPosX(3)+1]==' ' || tablero[getPosY(0)+1][getPosX(3)+1]=='|'))
            {
                dir=DOWN;
                setRect(DOWN);
                charTexture->setPosX(24*getPosX(1));
            }
        }
        else if(keyState[SDL_SCANCODE_W])
        {
            if((tablero[getPosY(0)-1][getPosX(1)+1]==' ' || tablero[getPosY(0)-1][getPosX(1)+1]=='|') && (tablero[getPosY(0)-1][getPosX(3)+1]==' ' || tablero[getPosY(0)-1][getPosX(3)+1]=='|'))
            {
                dir=UP;
                setRect(UP);
                charTexture->setPosX(24*getPosX(1));
            }
        }
        if(dir==RIGHT && (tablero[getPosY()][getPosX()+2]==' ' ||  tablero[getPosY()][getPosX()+2]=='|' || tablero[getPosY()][getPosX(3)+2]==' ' || tablero[getPosY()][getPosX(3)+2]=='|'))
        {
            sumPosX(2);
        }
        else if(dir==LEFT && (tablero[getPosY()][getPosX()]==' ' ||  tablero[getPosY()][getPosX()]=='|' || tablero[getPosY()][getPosX(3)]==' ' || tablero[getPosY()][getPosX(3)]=='|'))
        {
            sumPosX(-2);
        }
        else if(dir==UP && (tablero[getPosY()-1][getPosX()+1]==' ' || tablero[getPosY()-1][getPosX()+1]=='|' || tablero[getPosY(3)-1][getPosX(0)+1]==' ' || tablero[getPosY(3)-1][getPosX(0)+1]=='|'))
        {
            sumPosY(-2);
        }
        else if(dir==DOWN && (tablero[getPosY()+1][getPosX()+1]==' ' || tablero[getPosY()+1][getPosX()+1]=='|' || tablero[getPosY(3)+1][getPosX(0)+1]==' ' || tablero[getPosY(3)+1][getPosX(0)+1]=='|'))
        {
            sumPosY(2);
        }
        if(getPosY()==9 && getPosX(3,4)==0 && dir==LEFT)
        {
            charTexture->setPosX(44*24);
        }
        else if(getPosY()==9 && getPosX(0)==44 && dir==RIGHT)
        {
            charTexture->setPosX(0);
        }
        if(tablero2[getPosY(2,4)][getPosX(2,4)+1]==0)
        {
            tablero2[getPosY(2,4)][getPosX(2,4)+1]=2;
            return 1;
        }
        else if(tablero2[getPosY(2,4)][getPosX(2,4)+1]==1)
        {
            tablero2[getPosY(2,4)][getPosX(2,4)+1]=2;
            return 2;
        }
        else if(tablero2[getPosY(2,4)][getPosX(2,4)+1]>2)
        {
            int qwer=tablero2[getPosY(2,4)][getPosX(2,4)+1];
            tablero2[getPosY(2,4)][getPosX(2,4)+1]=2;
            return qwer;
        }
        return 0;
}
//Devuelve si santa esta mas a la derecha o izquierda que el reno
state getPosSRX(Reno rudolph,Santa noel)
{
    int r=rudolph.getPosX();
    int n=noel.getPosX();
    if(r<n)
        return RIGHT;
    return LEFT;
}
//Devuelve si santa esta mas arriba o abajo que el reno
state getPosSRY(Reno rudolph,Santa noel)
{
    int r=rudolph.getPosY();
    int n=noel.getPosY();
    if(r<n)
        return DOWN;
    return UP;
}
//Hace un random entre las cuatro direcciones y la direccion en la que esta santa
state Reno::random(Santa noel,int psycho)
{
    int n;
    n=4+2*intel;
    int temp=rand()%n;
    switch (temp)
    {
    case 0:
        return (psycho ? DOWN : UP);
    case 1:
        return (psycho ? RIGHT : LEFT);
    case 2:
        return (psycho ? LEFT : RIGHT);
    case 3:
        return (psycho ? UP : DOWN);
    case 4:
        return (psycho ? invertir(getPosSRY(*this,noel)) : getPosSRY(*this,noel));
    case 5:
        return (psycho ? invertir(getPosSRX(*this,noel)) : getPosSRX(*this,noel));
    case 6:
        return (psycho ? invertir(getPosSRY(*this,noel)) : getPosSRY(*this,noel));
    case 7:
        return (psycho ? invertir(getPosSRX(*this,noel)) : getPosSRX(*this,noel));
    case 8:
        return (psycho ? invertir(getPosSRY(*this,noel)) : getPosSRY(*this,noel));
    case 9:
        return (psycho ? invertir(getPosSRX(*this,noel)) : getPosSRX(*this,noel));

    }
    return DOWN;
}
//movimiento del reno
bool Reno::movimiento(char tablero[210][430],Santa noel,int psycho,Uint32 delay)
{
    if(die==1)
    {
        if(delay-ini>=4000)
            die=0;
        return false;
    }
    bool rep=true;
    if(getPosX()==getPosX(30,31) && getPosY()==getPosY(30,31))
    {
        while(rep)
        {
            if(getPosY()==9 && getPosX(3)==0 && dir==LEFT)
            {
                charTexture->setPosX(44*24);
            }
            else if(getPosY()==9 && getPosX(0)==44 && dir==RIGHT)
            {
                charTexture->setPosX(0);
            }
            if(tablero[getPosY()][getPosX()+1]=='|' )
            {
                dir=random(noel,psycho);
            }
            if(dir==RIGHT && (tablero[getPosY()][getPosX()+2]=='X' || tablero[getPosY()][getPosX()+2]=='B' || tablero[getPosY()][getPosX()+2]=='H'))
            {
                dir=random(noel,psycho);
            }
            else if(dir==LEFT && (tablero[getPosY()][getPosX()]=='X' || tablero[getPosY()][getPosX()]=='B' || tablero[getPosY()][getPosX()]=='H'))
            {
                dir=random(noel,psycho);
            }
            else if(dir==DOWN && (tablero[getPosY()+1][getPosX()+1]=='X' || tablero[getPosY()+1][getPosX()+1]=='B' || tablero[getPosY()+1][getPosX()+1]=='H'))
            {
                dir=random(noel,psycho);
            }
            else if(dir==UP && (tablero[getPosY()-1][getPosX()+1]=='X' || tablero[getPosY()-1][getPosX()+1]=='B' || tablero[getPosY()-1][getPosX()+1]=='H'))
            {
                dir=random(noel,psycho);
            }
            else
            {
                 rep=false;
                 setRect(dir);
            }

        }
    }
    if(dir==RIGHT)
        sumPosX(1);
    else if(dir==LEFT)
        sumPosX(-1);
    else if(dir==DOWN)
        sumPosY(1);
    else if(dir==UP)
        sumPosY(-1);
    return touch(*this,noel);
}
//Funcion que sirve para saber si se tocan santa y el reno
bool touch(Reno rudolph,Santa noel)
{
    SDL_Rect *Right=rudolph.getSDLRectPos();
    SDL_Rect *Left=noel.getSDLRectPos();
    if((Right->x < Left->x+Left->w) &&
       (Right->y < Left->y+Left->h) &&
       (Right->x+Right->w > Left->x) &&
       (Right->y+Right->h > Left->y))
        return true;
    return false;
}
//Regresa la direccion contraria a la que se recibio
state Reno::invertir(state dir)
{
    switch(dir)
    {
    case UP:
        return DOWN;
    case DOWN:
        return UP;
    case LEFT:
        return RIGHT;
    default:
        return LEFT;
    }
}
#endif // Santa_h
