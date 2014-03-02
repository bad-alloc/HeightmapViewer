#include "commandLineArgumentParser.h"

using namespace std;
namespace po = boost::program_options;

void parseCommandLineArguments(int argumentCount, char* argumentVector[],
			       string* heightmapFile,
			       bool* autoResolution,
			       int* X_Resolution, int* Y_Resolution,
			       int* fps, int* red, int* green, int* blue) {

    //set default values, so we can abort if something is missing and still have valid state
    *X_Resolution = 1280;
    *Y_Resolution = 800;
    *autoResolution = true;
    *fps = 50;
    *red = 255;
    *green = 255;
    *blue = 255;


    // Declare the supported options for the CLI
    po::options_description desc("Allowed options");
    desc.add_options()
	    ("help", "produce help message")
	    ("file", po::value<string>(), "The file containing the heightmap")
	    ("xres", po::value<int>(), "Horizontal resolution of window")
	    ("yres", po::value<int>(), "Vertical resolution of window")
	    ("fps", po::value<int>(), "Maximum frames per second")
	    ("red", po::value<int>(), "Red value of skydome")
	    ("green", po::value<int>(), "Green value of skydome")
	    ("blue", po::value<int>(), "Blue value of skydome")
    ;

    try {
        //parse and store the comamndline stuff
        po::variables_map cli_map;
        po::store(po::parse_command_line(argumentCount, argumentVector, desc), cli_map);
        po::notify(cli_map);

        //handle help request
        if(cli_map.count("help")) {
            cout << desc << "\n";
            exit(0); // do not continue launching.
        }

        if(cli_map.count("file")) {
            try {
                *heightmapFile = cli_map["file"].as<bool>();
            } catch (...) {
                cerr << "Error whilst reading path to heightmap. Assuming ./heightmap.png" << endl;
		*heightmapFile = "./heightmap.png";
            }
        }

	//check for file we just got
	if(!boost::filesystem::exists(*heightmapFile)) {
		cout << "No such file: \"" << *heightmapFile << "\". Aborting." << endl;
		exit(-1);
	}
	
        if(cli_map.count("xres") && cli_map.count("yres")) {
            try {
                *X_Resolution = cli_map["xres"].as<int>();
		*Y_Resolution = cli_map["yres"].as<int>();
		*autoResolution = false;
            } catch (...) {
                cerr << "Error whilst reading resolution. Autoscaling." << endl;
                *autoResolution = true;
            }
        }
        if(cli_map.count("max_fps")) {
            try {
                *fps = cli_map["max_fps"].as<int>();
            } catch (...) {
                cerr << "Error whilst reading maximum framerate. Assuming 50" << endl;
                *fps = 50;
            }
        }

        //get the colors
        if(cli_map.count("red")) {
            try {
                *red = cli_map["red"].as<int>();
            } catch (...) {
                cerr << "Error whilst reading red channel. Assuming 255" << endl;
                *red = 255;
            }
        }
        if(cli_map.count("green")) {
            try {
                *green = cli_map["green"].as<int>();
            } catch (...) {
                cerr << "Error whilst reading green channel. Assuming 255" << endl;
                *green = 255;
            }
        }
        if(cli_map.count("blue")) {
            try {
                *blue = cli_map["blue"].as<int>();
            } catch (...) {
                cerr << "Error whilst reading blue channel. Assuming 255" << endl;
                *blue = 255;
            }
        }
    }
    catch(boost::exception_detail::clone_impl<boost::exception_detail::error_info_injector<boost::program_options::unknown_option> > e) {
        cerr << e.what() << endl;
        exit(-1);
    }
    catch(boost::program_options::invalid_syntax e) {
        //cerr << "Invalid syntax detected." << e.tokens() << endl;
        exit(-1);
    }
    catch(...) {
        cerr << "Unknown error in the command line/config file parser." << endl;
        cerr << "This is most likely a syntax error in the supplied config file (stray characters for example)" << endl;
        exit(-1);
    }
}
