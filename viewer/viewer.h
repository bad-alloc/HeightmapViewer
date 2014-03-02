#ifndef VIEWER_H
#define VIEWER_H

#include <string>
#include <irrlicht.h>

#include "delayFPS.h"


class HeightmapViewer
{
public:
	HeightmapViewer(int x_res, int y_res,
			bool autoResolution,
			int newred, int newgreen, int newblue,
			int fps);
        virtual ~HeightmapViewer();
        void run();
	void loadHeightmap(std::string pathToHeightmap);
private:
	int X_Resolution, Y_Resolution; //size of the render window
        int red, green, blue; //color of background
        int max_fps; //maximum framerate

	irr::scene::ISceneManager* sceneManager;
        irr::video::IVideoDriver* driver;
        irr::IrrlichtDevice* device;
        irr::scene::ISceneCollisionManager* collisionManager;
	irr::scene::ICameraSceneNode* camera;
	
	IrrlichtDelayFPS delayFPS;
};

#endif // VIEWER_H
