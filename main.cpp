#include <iostream>
#include <irrlicht.h>

#include "viewer/viewer.h"
#include "args/commandLineArgumentParser.h"

using namespace std;

int main(int argc, const char *argv[])
{
	int x_res, y_res, fps, red, green, blue;
	bool autoResolution;
	std::string heightmap;
	cout << "Parsing command line info." << endl;
	parseCommandLineArguments(argc, const_cast<char**>(argv), &heightmap,
				  &autoResolution, &x_res, &y_res, &fps, &red, &green, &blue);
	
	cout << "Setting up renderer" << endl;

	HeightmapViewer* viewer = new HeightmapViewer(1024, 780, false, 255,255,255,50);

	viewer->loadHeightmap(heightmap);
	viewer->run();

	cout << "Done." << endl;
	
	return 0;
}
