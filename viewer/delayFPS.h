#ifndef DELAY_FPS
#define DELAY_FPS

using namespace irr;

struct IrrlichtDelayFPS {
int maxFPS;
int lastFPS;
int yieldCounter;
IrrlichtDevice *device;
IrrlichtDelayFPS() { maxFPS = 50;  yieldCounter = 0;  device = 0; }
void delay() {
    video::IVideoDriver* driver = device->getVideoDriver();
    int lastFPS = driver->getFPS();
    for( int i = 0 ; i < yieldCounter ; i++ ) {
      device->yield();
    }
    if ( lastFPS >maxFPS ) { yieldCounter++ ; }
    else {
      if (yieldCounter > 0 ) { --yieldCounter; }
      else { yieldCounter = 0 ; }
    }
  }
};

#endif

/* 

  IrrlichtDelayFPS delayFPS;
  delayFPS.maxFPS = 50; //set max FPS
  delayFPS.device = device; //set device

while(device->run()) {
   //your code here
  //delay loop
  delayFPS.delay();
}

*/

//source: http://julien.boucaron.free.fr/wordpress/?p=269
