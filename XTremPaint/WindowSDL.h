#ifndef WINDOW_SDL_H
#define WINDOW_SDL_H

#include <SDL/SDL.h>
#include <pthread.h>
#include "WindowSDLexception.h"
#include "WindowSDLclick.h"

class WindowSDL
{
  private:
    static SDL_Surface      *screen;
    static int              width;
    static int              height;
    static pthread_t        threadEventSDL;
    static char             alive;
    static void*            FctThreadEventSDL(void *p);

    // Gestion du Click
    static WindowSDLclick   click;
    static char             clicked;
    static pthread_mutex_t  mutexClick;
    static pthread_cond_t   condClick;

  public:
    static void open(int w,int h) throw (WindowSDLexception);
    static char isAlive();
    static void close() throw (WindowSDLexception);
    static void setBackground(int R,int G,int B) throw (WindowSDLexception);
    static void setPixel(int R,int G,int B,int x,int y) throw (WindowSDLexception);
    static void drawLine(int R,int G,int B,int x1,int y1, int x2,int y2) throw (WindowSDLexception);
    static void drawRectangle(int R,int G,int B,int x,int y,int w,int h) throw (WindowSDLexception);
    static void fillRectangle(int R,int G,int B,int x,int y,int w,int h) throw (WindowSDLexception);
    static WindowSDLclick waitClick() throw (WindowSDLexception);
};

#endif


