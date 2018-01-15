#include <iostream>
using namespace std;

#include "WindowSDL.h"

//************************************************************************************************
int main(int argc,char* argv[])
{
  cout << "Hello WindowSDL !" << endl;

  WindowSDL::open(640,480);
  WindowSDL::setBackground(0,0,0);

  int i=0;
  while (i < 3)
  {
    WindowSDLclick click1,click2;

    cout << "Cliquez sur la fenetre... " << endl;
    click1 = WindowSDL::waitClick();
    cout << "Vous avez clique en (" << click1.getX() << "," << click1.getY() << ")" << endl;
    WindowSDL::setPixel(255,255,255,click1.getX(),click1.getY());

    cout << "Cliquez sur la fenetre... " << endl;
    click2 = WindowSDL::waitClick();
    cout << "Vous avez clique en (" << click2.getX() << "," << click2.getY() << ")" << endl;

    if (i == 0)
      WindowSDL::drawLine(255,0,0,click1.getX(),click1.getY(),click2.getX(),click2.getY());    

    if (i == 1)
      WindowSDL::drawRectangle(0,255,0,click1.getX(),click1.getY(),click2.getX()-click1.getX(),click2.getY()-click1.getY());    

    if (i == 2)
      WindowSDL::fillRectangle(0,0,255,click1.getX(),click1.getY(),click2.getX()-click1.getX(),click2.getY()-click1.getY());    

    i++;
  }

  cout << "Cliquez pour quitter..." << endl;
  WindowSDL::waitClick();
  WindowSDL::close();

  return 0;
}


