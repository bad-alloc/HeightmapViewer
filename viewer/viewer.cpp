#include <iostream>

#include "viewer.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;



HeightmapViewer::HeightmapViewer(int x_res, int y_res,
				 bool autoResolution,
				 int newred, int newgreen, int newblue,
				 int fps)
{
	//save the parameters
	X_Resolution = x_res;
	Y_Resolution = y_res;
	red = newred;
	green = newgreen;
	blue = newblue;
	max_fps = fps;

	if(autoResolution) { //if in auto mode, get screen size and
			     //reset reolution variables, discarding
			     //parameter data.
		
		//get temporary device to get screen resolution
		IrrlichtDevice *nulldevice = irr::createDevice(video::EDT_NULL);
		core::dimension2d<u32> deskres =
			nulldevice->getVideoModeList()->getDesktopResolution();
		nulldevice -> drop(); //get rid of temporary device
		//reset data
		X_Resolution = deskres.Width;
		Y_Resolution = deskres.Height;
	}


	//use this structure with createDeviceEx instead of only
	//createDevice, since we can only enable anti alialising this
	//way.
	SIrrlichtCreationParameters param;

	param.DriverType = EDT_OPENGL;
	param.WindowSize = dimension2d<u32>(X_Resolution, Y_Resolution);
	param.Bits = 32;
	param.Fullscreen = false;
	param.Stencilbuffer = false;
	param.Vsync = false;
	param.AntiAlias = false;
	param.EventReceiver = NULL;
	device = createDeviceEx(param);
	if (!device){
		//Do not throw in constructors.
		cerr << "Could not create device! "
		     << "Terminating display initialization." << endl;
		return;
	}

	device->setResizable(false);
	
	delayFPS.maxFPS = max_fps; //set max FPS
	delayFPS.device = device; //set device

	//get other Irrlicht stuff
	driver = device->getVideoDriver();
	sceneManager = device->getSceneManager();
	collisionManager = sceneManager->getSceneCollisionManager();
	//keymap for camera, so we steer with WASD
	SKeyMap keyMap[4];
	keyMap[0].Action = EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = KEY_KEY_W;
	keyMap[1].Action = EKA_STRAFE_LEFT;
	keyMap[1].KeyCode = KEY_KEY_A;
	keyMap[2].Action = EKA_STRAFE_RIGHT;
	keyMap[2].KeyCode = KEY_KEY_D;
	keyMap[3].Action = EKA_MOVE_BACKWARD;
	keyMap[3].KeyCode = KEY_KEY_S;
	
	//Camera parameters: parent, rotatespeed, movespeed, id, keymap, mapsize
	camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.05f, -1, keyMap, 4);
	//remove the cursor
	device->getCursorControl()->setVisible(false);
}

HeightmapViewer::~HeightmapViewer() {}

void HeightmapViewer::run() {
	cout << "Render Loop starting." << endl;
	while(device->run()) {

		driver->beginScene(true, true, SColor(255,red,green,blue));

		sceneManager->drawAll();

		driver->endScene();
		delayFPS.delay();
	}
	cout << "Render loop terminated." << endl;
}

void HeightmapViewer::loadHeightmap(std::string pathToHeightmap) {
	cout << "Loading \"" << pathToHeightmap << "\"" << endl;
	
	// add terrain scene node
	scene::ITerrainSceneNode* terrain = sceneManager->addTerrainSceneNode(
		pathToHeightmap.c_str(),
		0,                                    // parent node
		-1,                                   // node id
		core::vector3df(0.f, -200.f, 0.f),    // position
		core::vector3df(0.f, 0.f, 0.f),       // rotation
		core::vector3df(1.f, 1.f, 1.f),       // scale
		video::SColor ( 255, 255, 255, 255 ), // vertexColor
		5,                                    // maxLOD
		scene::ETPS_17,                       // patchSize
		4                                     // smoothFactor
		);
	
	terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	// overlay heightmap as texture on terrain, so you can see the
	// colors corresponding to the height.
	terrain->setMaterialTexture(0, driver->getTexture(pathToHeightmap.c_str()));
	
	terrain->setMaterialType(video::EMT_DETAIL_MAP);
	
	terrain->scaleTexture(1.0f, 20.0f);
	terrain->setVisible(true);

}
